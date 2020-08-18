/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qdgdf_audio.h"

/**
 * _qdgdfa_sound - Main sound switch.
 *
 * If set to 0 previous to startup, disables the whole sound system.
 * If it has a value of 0 after startup, something wrong occurred
 * in the initialization of the sound card.
 * [Audio Variables]
 */
int _qdgdfa_sound = 1;

/**
 * _qdgdfa_16_bit - 16 bit sound card toggle.
 *
 * If set to 0 previous to startup, use only 8 bit sound output.
 * If it has a value of 0 after startup, the sound card does not
 * support 16 bit PCM audio.
 * [Audio Variables]
 */
int _qdgdfa_16_bit = 1;

/**
 * _qdgdfa_window_title - title of the window.
 *
 * This string holds the title of the window.
 * [Audio Variables]
 */
char _qdgdfa_window_title[150] = "";

char *_qdgdfa_version = VERSION;

/**
 * _qdgdfa_big_sound_threshold - Threshold for a sound to be considered big.
 *
 * This integer holds the minimum size a sound must have
 * to be considered a 'big' sound (a sound that is paged
 * in disk instead of being loaded completely in memory).
 * [Audio Variables]
 */
int _qdgdfa_big_sound_threshold = 1024 * 1024;


/**
 * _qdgdfa_fopen_path - Search path for _qdgdfa_fopen().
 *
 * This string can contain a semicolon-separated list of paths
 * where files to be open with _qdgdfa_fopen() will be tried.
 * [Support Variables]
 */
char _qdgdfa_fopen_path[250] = "";

/* audio driver */
static struct _qdgdfa_driver *drv = NULL;


/** code **/

#include "qdgdf_path.c"

FILE *_qdgdfa_fopen(char *file, char *mode)
{
    return _path_fopen(_qdgdfa_fopen_path, file, mode);
}


/**
 * qdgdfa_path_find - Finds a file in _qdgdfa_fopen_path.
 * @file: the file to be found
 *
 * Searches for @file in the path stored in _qdgdfa_fopen_path.
 * If it's found in some of the directories there, a string is
 * allocated contaning the full path, that should be freed
 * when no longer needed. Otherwise, returns NULL.
 */
char *qdgdfa_path_find(const char *file)
{
    return _path_find(_qdgdfa_fopen_path, file);
}


FILE *qdgdfa_load_wav(char *filename, int *size, int *bits)
{
    FILE *f;
    char dummydata[256];
    int rlen, flen;
    short int b_per_sec, num_channels, tag;
    char riffid[5], waveid[5], fmtid[5], dataid[5];
    int _wav_frequency;

    if ((f = _qdgdfa_fopen(filename, "rb")) == NULL)
        return NULL;

    fread(riffid, 1, 4, f);
    riffid[4] = 0;
    fread(&rlen, 1, 4, f);
    fread(waveid, 1, 4, f);
    waveid[4] = 0;

    if (strcmp(waveid, "WAVE")) {
        fclose(f);
        return NULL;
    }

    fread(fmtid, 1, 4, f);
    fmtid[4] = 0;
    flen = fgetc(f);
    flen += (fgetc(f) * 256);
    flen += (fgetc(f) * 65536);
    flen += (fgetc(f) * 16777216);

    if (flen > 240)
        flen = 240;

    fread(&tag, 1, 2, f);

    num_channels = fgetc(f);
    num_channels += (fgetc(f) * 256);
    _wav_frequency = fgetc(f);
    _wav_frequency += (fgetc(f) * 256);
    _wav_frequency += (fgetc(f) * 65536);
    _wav_frequency += (fgetc(f) * 16777216);
    b_per_sec = fgetc(f);
    b_per_sec += (fgetc(f) * 256);
    b_per_sec += (fgetc(f) * 65536);
    b_per_sec += (fgetc(f) * 16777216);

    *bits = fgetc(f);
    (*bits) += (fgetc(f) * 256);
    (*bits) *= 8;

    fread(dummydata, 1, (size_t) flen - 14, f);
    fread(dataid, 1, 4, f);
    dataid[4] = 0;

    *size = fgetc(f);
    (*size) += (fgetc(f) * 256);
    (*size) += (fgetc(f) * 65536);
    (*size) += (fgetc(f) * 16777216);

    return f;
}


/**
 * qdgdfa_load_sound - Loads a sound.
 * @wavfile: the file containing the sound
 *
 * Loads a sound file (in .WAV format). A sound handle
 * is returned.
 * [Audio Functions]
 */
int qdgdfa_load_sound(char *wavfile)
{
    if (drv == NULL)
        return 0;

    return drv->load_sound(wavfile);
}


/**
 * qdgdfa_load_big_sound - Loads a big sound (deprecated).
 * @wavfile: the file containing the sound
 *
 * In previous versions, sounds considered (by the programmer)
 * to be big were loaded by using this function, but now the
 * 'bigness' of a file is controlled by the value in the
 * _qdgdfa_big_sound_threshold variable, so it's use is deprecated.
 * Now it's exactly equivalent to qdgdfa_load_sound().
 * [Audio Functions]
 */
int qdgdfa_load_big_sound(char *wavfile)
{
    return qdgdfa_load_sound(wavfile);
}


/**
 * qdgdfa_dup_sound - Duplicates a sound.
 * @sound: the sound to be duplicated
 *
 * Duplicates a sound. The new sound will share the
 * sound data with the old one. Returns the
 * id for the new sound.
 * [Audio Functions]
 */
int qdgdfa_dup_sound(int snd)
{
    if (drv == NULL)
        return 0;

    return drv->dup_sound(snd);
}


/**
 * qdgdfa_play_sound - Starts playing a sound.
 * @snd: the sound handle
 * @loop: neverending loop flag
 *
 * Starts playing a sound. If @loop is set, the sound restarts
 * from the beginning when reaches the end. If the sound is
 * already playing, nothing is done.
 * [Audio Functions]
 */
void qdgdfa_play_sound(int snd, int loop)
{
    if (drv != NULL)
        drv->play_sound(snd, loop);
}


/**
 * qdgdfa_respawn_sound - Respawns a sound.
 * @snd: the sound to be respawn
 *
 * Respawns a sound, playing it even if the sound is
 * already playing. This new, duplicated sound inherits
 * all properties (as pan, etc.) from the original one
 * and cannot be stopped nor controlled in any way. The
 * poll of respawned sounds is limited; if it can't hold
 * more sounds, nothing is done. A respawned sound is
 * automatically deleted when finished.
 * [Audio Functions]
 */
void qdgdfa_respawn_sound(int snd)
{
    if (drv != NULL)
        drv->respawn_sound(snd);
}


/**
 * qdgdfa_stop_sound - Stop playing a sound.
 * @snd: the sound handle
 *
 * Stops playing a sound.
 * [Audio Functions]
 */
void qdgdfa_stop_sound(int snd)
{
    if (drv != NULL)
        drv->stop_sound(snd);
}


/**
 * qdgdfa_set_pan - Sets the pan of a sound.
 * @snd: the sound handle
 * @pan: pan of the sound
 *
 * Sets the pan of a sound. The @pan argument can be -1 (left channel only),
 * 0 (both channels, center) or 1 (right channel only).
 * [Audio Functions]
 */
void qdgdfa_set_pan(int snd, int pan)
{
    if (drv != NULL)
        drv->set_pan(snd, pan);
}


/**
 * qdgdfa_set_attenuation - Sets the attenuation of a sound.
 * @snd: the sound handle
 * @att: the attenuation
 *
 * Sets the attenuation of a sound. It ranges from 0 (no attenuation,
 * sound is as is) to 63 (total silence).
 * [Audio Functions]
 */
void qdgdfa_set_attenuation(int snd, int att)
{
    if (att < 0)
        att = 0;
    if (att > 63)
        att = 63;

    if (drv != NULL)
        drv->set_attenuation(snd, att);
}


/**
 * qdgdfa_reset - Resets the sound system.
 *
 * Resets the sound system, shuting up all sounds and unloading
 * them from memory.
 * [Audio Functions]
 */
void qdgdfa_reset(void)
{
    if (drv != NULL)
        drv->reset();
}


/**
 * qdgdfa_pause - Pause the sound system.
 * @p: toggle flag
 *
 * Pauses the sound system. The @p argument acts as a boolean
 * to pause or unpause the sound system.
 * [Audio Functions]
 */
void qdgdfa_pause(int p)
{
    if (drv != NULL)
        drv->pause(p);
}


/**
 * qdgdfa_home_dir - Returns the home user directory.
 *
 * Returns a system-dependent directory where the user can write
 * documents and create subdirectories.
 * [File Management]
 */
char *qdgdfa_home_dir(void)
{
    return _home_dir();
}


/**
 * qdgdfa_app_dir - Returns the applications directory.
 *
 * Returns a system-dependent directory where the applications store
 * their private data, as components or resources.
 * [File Management]
 */
char *qdgdfa_app_dir(void)
{
    return _app_dir();
}


/**
 * qdgdfa_startup - Starts the sound system.
 *
 * Starts the sound system. If _qdgdfa_sound is not set,
 * no action is done. If _qdgdfa_16_bit is set, it tries
 * to use the 16 bit capabilities of the sound card. It
 * also sets both previous variables accordingly to the
 * current configuration.
 * [Audio Functions]
 */
void qdgdfa_startup(void)
{
    if (!_qdgdfa_sound)
        return;

    if (!TRY_AUDIO_DRIVERS())
        _qdgdfa_sound = 0;

    atexit(qdgdfa_shutdown);
}


/**
 * qdgdfa_shutdown - Shuts down the sound system.
 *
 * Shuts down the sound system.
 * [Audio Functions]
 */
void qdgdfa_shutdown(void)
{
    if (drv != NULL)
        drv->shutdown();

    drv = NULL;
}
