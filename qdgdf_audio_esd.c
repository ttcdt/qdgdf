/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_audio.h"

#ifdef CONFOPT_ESD

#include <unistd.h>

#include "esd.h"


/** data **/

/* esd socket */
int _esd_fd;

/* sound sample ids */
#define MAX_SAMPLES 512

int _sample_ids[MAX_SAMPLES];
int _sample_idx = 0;


/** code **/

static int _qdgdfa_load_sound(char *wavfile)
{
    int snd;

    snd = esd_file_cache(_esd_fd, "qdgdfa", wavfile);

    /* fill the pool */
    _sample_ids[_sample_idx++] = snd;

    return snd;
}


static int _qdgdfa_dup_sound(int snd)
{
    /* sounds cannot be duplicated with esound,
       but seems not necessary as sounds can
       be directly played many times; so, return
       the same sample id. Does esound allows
       a sample to be freed many times without crashing? */

    return snd;
}


static void _qdgdfa_play_sound(int snd, int loop)
{
    esd_sample_stop(_esd_fd, snd);

    /* Esd is crap. I just can't force it to stop
       big files played in loops, nor unload them,
       nor kill them; looped sounds are played
       forever. So, looped sounds are disabled
       by now. */
    if (!loop)
        esd_sample_play(_esd_fd, snd);
}


static void _qdgdfa_respawn_sound(int snd)
{
    esd_sample_play(_esd_fd, snd);
}


static void _qdgdfa_stop_sound(int snd)
{
    esd_sample_stop(_esd_fd, snd);
}


static void _qdgdfa_set_pan(int snd, int pan)
{
    int left = 256, right = 256;

    if (pan == -1)
        right = 0;
    if (pan == 1)
        left = 0;

    esd_set_default_sample_pan(_esd_fd, snd, left, right);
}


static void _qdgdfa_set_attenuation(int snd, int att)
{
    /* unimplemented */
}


static void _qdgdfa_reset(void)
{
    int n;

    for (n = 0; n < _sample_idx; n++) {
        qdgdfa_stop_sound(_sample_ids[n]);

        esd_sample_free(_esd_fd, _sample_ids[n]);

        _sample_ids[n] = -1;
    }

    _sample_idx = 0;
}


static void _qdgdfa_pause(int p)
{
    if (p)
        esd_standby(_esd_fd);
    else
        esd_resume(_esd_fd);
}


static int _qdgdfa_startup(void)
{
    _esd_fd = esd_open_sound(NULL);

    if (_esd_fd < 0)
        return 0;

    _sample_idx = 0;
    return 1;
}


static void _qdgdfa_shutdown(void)
{
    qdgdfa_reset();

    esd_close(_esd_fd);
}


/* driver information */

static struct _qdgdfa_driver drv = {
    "esd",

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


struct _qdgdfa_driver *esd_drv_detect(void)
/* detection function */
{
    if (_qdgdfa_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_ESD */
