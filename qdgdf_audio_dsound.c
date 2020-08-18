/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_audio.h"

#ifdef CONFOPT_DSOUND

#include <string.h>
#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>

/** data **/

LPDIRECTSOUND dsound;

/** the sounds **/

#define MAX_SOUNDS		64
#define MAX_SPAWNED_SOUNDS	16

LPDIRECTSOUNDBUFFER _primary;
LPDIRECTSOUNDBUFFER _sounds[MAX_SOUNDS];
LPDIRECTSOUNDBUFFER _spawned_sounds[MAX_SPAWNED_SOUNDS];

static int _sound_seq = 0;

/* external hwnd */
HWND hwnd = NULL;

/** code **/

static int sound_test(void)
{
    DSBUFFERDESC dsbd;
    WAVEFORMATEX wf;
    static int _started = 0;

    if (!_started) {
        /* deferred startup */

        /* gets hwnd from the outside by the
           window title. What the hell these
           Microsoft morons were thinking when they
           associated a sound buffer to a WINDOW? */
        if (_qdgdfa_window_title[0] != '\0')
            hwnd = FindWindow(NULL, _qdgdfa_window_title);

        /* no window title or window can't be found by name,
           try to get the background window hwnd */
        if (hwnd == NULL)
            hwnd = GetForegroundWindow();

        if (hwnd == NULL)
            hwnd = GetDesktopWindow();

        if (hwnd == NULL) {
            _qdgdfa_sound = 0;
            return 0;
        }

        if (dsound->lpVtbl->
            SetCooperativeLevel(dsound, hwnd, DSSCL_PRIORITY) != DS_OK) {
            _qdgdfa_sound = 0;
            return 0;
        }

        /* tries to set the primary buffer capabilities;
           if it doesn't work, just use the defaults */
        memset(&dsbd, '\0', sizeof(dsbd));
        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
        dsbd.dwBufferBytes = 0;
        dsbd.lpwfxFormat = NULL;

        memset(&wf, '\0', sizeof(wf));
        wf.wFormatTag = WAVE_FORMAT_PCM;
        wf.nChannels = 1;
        wf.nSamplesPerSec = 11025;
        wf.wBitsPerSample = 16;
        wf.nBlockAlign = 2;
        wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;

        if (dsound->lpVtbl->
            CreateSoundBuffer(dsound, &dsbd, &_primary, NULL) == DS_OK)
            _primary->lpVtbl->SetFormat(_primary, &wf);

        _started = 1;
    }

    /* everything is ok */
    return 1;
}


/* driver */

static int _qdgdfa_load_sound(char *wavfile)
{
    PCMWAVEFORMAT pcmwf;
    DSBUFFERDESC dsbd;
    FILE *f;
    int n, size, bits;
    char *w1;
    char *w2;
    unsigned long s1;
    unsigned long s2;

    if (!sound_test())
        return 1;

    if ((f = qdgdfa_load_wav(wavfile, &size, &bits)) == NULL)
        return -1;

    memset(&pcmwf, '\0', sizeof(pcmwf));

    pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
    pcmwf.wf.nChannels = 1;
    pcmwf.wf.nSamplesPerSec = 11025;
    pcmwf.wf.nBlockAlign = bits / 8;
    pcmwf.wf.nAvgBytesPerSec =
        pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
    pcmwf.wBitsPerSample = bits;

    memset(&dsbd, '\0', sizeof(dsbd));

    dsbd.dwSize = sizeof(DSBUFFERDESC);
    dsbd.dwFlags =
        DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN;
    dsbd.dwBufferBytes = size;
    dsbd.lpwfxFormat = (LPWAVEFORMATEX) & pcmwf;

    n = _sound_seq;

    if (dsound->lpVtbl->
        CreateSoundBuffer(dsound, &dsbd, &_sounds[n], NULL) != DS_OK) {
        fclose(f);
        return -2;
    }

    if (_sounds[n]->lpVtbl->Lock(_sounds[n], 0, size,
                                 (void **) &w1, &s1, (void **) &w2, &s2,
                                 0) != DS_OK) {
        fclose(f);
        return -3;
    }

    if (w1 != NULL)
        fread(w1, 1, s1, f);

    if (w2 != NULL)
        fread(w2, 1, s2, f);

    fclose(f);

    if (_sounds[n]->lpVtbl->Unlock(_sounds[n], w1, s1, w2, s2) != DS_OK)
        return -4;

    _sound_seq++;
    return n;
}


static int _qdgdfa_dup_sound(int snd)
{
    int n;

    n = _sound_seq++;

    dsound->lpVtbl->DuplicateSoundBuffer(dsound, _sounds[snd],
                                         &_sounds[n]);

    return n;
}


static void _qdgdfa_play_sound(int snd, int loop)
{
    unsigned long status;

    if (!sound_test())
        return;

    if (snd >= 0 && snd < _sound_seq) {
        /* if sound is playing, don't start it again */
        _sounds[snd]->lpVtbl->GetStatus(_sounds[snd], &status);

        if (status & (DSBSTATUS_PLAYING | DSBSTATUS_LOOPING))
            return;

        if (loop == 0)
            _sounds[snd]->lpVtbl->Stop(_sounds[snd]);

        _sounds[snd]->lpVtbl->SetCurrentPosition(_sounds[snd], 0);

        _sounds[snd]->lpVtbl->Play(_sounds[snd], 0, 0,
                                   loop ? DSBPLAY_LOOPING : 0);
    }
}


static void _qdgdfa_respawn_sound(int snd)
{
    int n;
    unsigned long status;

    for (n = 0; n < MAX_SPAWNED_SOUNDS; n++) {
        /* if it's free, use it */
        if (_spawned_sounds[n] == NULL)
            break;

        /* if it's not free, test if it has already finished */
        _spawned_sounds[n]->lpVtbl->GetStatus(_spawned_sounds[n], &status);

        if (status != DSBSTATUS_PLAYING) {
            _spawned_sounds[n]->lpVtbl->Release(_spawned_sounds[n]);
            break;
        }
    }

    if (n != MAX_SPAWNED_SOUNDS) {
        dsound->lpVtbl->DuplicateSoundBuffer(dsound,
                                             _sounds[snd],
                                             &_spawned_sounds[n]);

        _spawned_sounds[n]->lpVtbl->SetCurrentPosition(_spawned_sounds[n],
                                                       0);

        _spawned_sounds[n]->lpVtbl->Play(_spawned_sounds[n], 0, 0, 0);
    }
}


static void _qdgdfa_stop_sound(int snd)
{
    if (!sound_test())
        return;

    if (snd >= 0 && snd < _sound_seq)
        _sounds[snd]->lpVtbl->Stop(_sounds[snd]);
}


static void _qdgdfa_set_pan(int snd, int pan)
{
    if (!sound_test())
        return;

    if (snd >= 0 && snd < _sound_seq)
        _sounds[snd]->lpVtbl->SetPan(_sounds[snd], 10000 * pan);
}


static void _qdgdfa_set_attenuation(int snd, int att)
{
    if (!sound_test())
        return;

    att *= -3000;
    att /= 63;

    if (snd >= 0 && snd < _sound_seq)
        _sounds[snd]->lpVtbl->SetVolume(_sounds[snd], att);
}


static void _qdgdfa_reset(void)
{
    int n;

    if (!sound_test())
        return;

    /* frees all sounds */
    for (n = 0; n < MAX_SOUNDS; n++) {
        if (_sounds[n] != NULL) {
            _sounds[n]->lpVtbl->Release(_sounds[n]);
            _sounds[n] = NULL;
        }
    }

    for (n = 0; n < MAX_SPAWNED_SOUNDS; n++) {
        if (_spawned_sounds[n] != NULL) {
            _spawned_sounds[n]->lpVtbl->Release(_spawned_sounds[n]);
            _spawned_sounds[n] = NULL;
        }
    }

    _sound_seq = 0;
}


static void _qdgdfa_pause(int p)
{
    /* TO BE DONE */
}


static int _qdgdfa_startup(void)
{
    int n;

    for (n = 0; n < MAX_SOUNDS; n++)
        _sounds[n] = NULL;
    for (n = 0; n < MAX_SPAWNED_SOUNDS; n++)
        _spawned_sounds[n] = NULL;

    if (DirectSoundCreate(NULL, &dsound, NULL) != DS_OK)
        return 0;

    return 1;
}


static void _qdgdfa_shutdown(void)
{
    qdgdfa_reset();

    dsound->lpVtbl->Release(dsound);
}


/* driver information */

static struct _qdgdfa_driver drv = {
    "dsound",

    _qdgdfa_load_sound,
    _qdgdfa_dup_sound,
    _qdgdfa_play_sound,
    _qdgdfa_respawn_sound,
    _qdgdfa_stop_sound,

    _qdgdfa_set_pan,
    _qdgdfa_set_attenuation,
    _qdgdfa_reset,
    _qdgdfa_pause,
    _qdgdfa_startup,
    _qdgdfa_shutdown
};


struct _qdgdfa_driver *dsound_drv_detect(void)
/* detection function */
{
    if (_qdgdfa_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_DSOUND */
