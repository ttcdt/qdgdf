/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_audio.h"

#ifdef CONFOPT_LINUX_OSS

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <linux/soundcard.h>


/** data **/

/* the audio device */
static int _audio_fd = -1;

/* the pipe */
static int _command_fd = -1;

/* daemon pid */
static int _daemon_pid = -1;

/** commands **/

#define SOUND_CMD_EXIT	  'X'
#define SOUND_CMD_RESET   'R'
#define SOUND_CMD_LOAD	  'L'
#define SOUND_CMD_LOADBIG 'B'
#define SOUND_CMD_START   'S'
#define SOUND_CMD_STOP	  'T'
#define SOUND_CMD_SETPAN  'P'
#define SOUND_CMD_ATTEN   'N'
#define SOUND_CMD_PAUSE   'A'
#define SOUND_CMD_UNPAUSE 'U'
#define SOUND_CMD_DUP	  '2'
#define SOUND_CMD_RESPAWN 'W'

/* sequential numbers */
static int _program_seq = -1;
static int _daemon_seq = -1;

/* the sound buffers */

#define SOUND_BUFFER_BITS 10
#define SOUND_BUFFER_SIZE (1<<SOUND_BUFFER_BITS)

static unsigned char _sound_buffer_8[SOUND_BUFFER_SIZE];
static short int _sound_buffer_16[SOUND_BUFFER_SIZE];

/* big sound buffer size */
int _qdgdfa_big_sound_buffer_size = 4096;

/** sounds **/

#define MAX_ORIGINAL_SOUNDS	64
#define MAX_RESPAWN_SOUNDS	16
#define MAX_SOUNDS		MAX_ORIGINAL_SOUNDS+MAX_RESPAWN_SOUNDS

struct sound {
    void *data[2];              /* 2 buffers of audio data */
    unsigned char *data_8;      /* 8 bit pointer */
    short int *data_16;         /* 16 bit pointer */

    int playing;                /* playing flag (0=off,1=on,2=loop) */
    int pan;                    /* 1, 0, -1 */
    int att;                    /* 63, full; 0, none */
    int duped;                  /* sound-is-a-duplicate flag */

    int total_size;             /* total size of sound */
    int partial_size;           /* size of current buffer */
    int total_left;             /* total samples left */
    int partial_left;           /* partial samples left */

    int offset;                 /* current playing pointer */
    int bits;                   /* # of bits */

    int big;                    /* big file flag */
    int bi;                     /* buffer index */
    FILE *file;                 /* file handle of big sound */
    long fpos;                  /* file position of audio data */
};

/* the sounds */
static struct sound _sounds[MAX_SOUNDS];

static char msg[256];
static int _msg_offset = 0;


/** code **/

static int detect_endianess(void)
/* is this machine big or little endian? */
{
    short s;
    unsigned char *c;

    s = 1;
    c = (unsigned char *) &s;

    if (*c == 1)
        return AFMT_S16_LE;
    return AFMT_S16_BE;
}


static int _open_device(void)
{
    int n;

    if ((_audio_fd = open("/dev/dsp", O_WRONLY)) == -1)
        return 0;

    n = (2 << 16) | SOUND_BUFFER_BITS;
    if (ioctl(_audio_fd, SNDCTL_DSP_SETFRAGMENT, &n) == -1)
        return 0;

    if (ioctl(_audio_fd, SNDCTL_DSP_RESET, 0) == -1)
        return 0;

    n = 11025;
    if (ioctl(_audio_fd, SNDCTL_DSP_SPEED, &n) == -1)
        return 0;

    n = 1;
    if (ioctl(_audio_fd, SNDCTL_DSP_STEREO, &n) == -1)
        return 0;

    if (_qdgdfa_16_bit) {
        n = detect_endianess();
        if (ioctl(_audio_fd, SNDCTL_DSP_SETFMT, &n) == -1)
            _qdgdfa_16_bit = 0;
    }

    if (!_qdgdfa_16_bit) {
        n = AFMT_U8;
        if (ioctl(_audio_fd, SNDCTL_DSP_SETFMT, &n) == -1)
            return 0;
    }

    return 1;
}


static void _sound_read_block(FILE * f, int size, void *data, int bits)
{
    int c, c2;
    unsigned char *data_8;
    short int *data_16;

    data_8 = (unsigned char *) data;
    data_16 = (short int *) data;

    while (size) {
        if (_qdgdfa_16_bit) {
            if (bits == 8) {
                c = fgetc(f) - 128;
                c <<= 8;
            }
            else {
                c2 = (unsigned char) fgetc(f);
                c = (signed int) fgetc(f);

                c <<= 8;
                c |= c2;
            }

            *data_16 = (short int) c;
            data_16++;
        }
        else {
            if (bits == 8)
                c = (unsigned char) fgetc(f);
            else {
                fgetc(f);
                c = (signed int) fgetc(f);

                c = 128 + c;
                c &= 0xff;
            }

            /* stores as 3/4 of original sound */
            c *= 3;
            c >>= 2;

            *data_8 = (unsigned char) c;
            data_8++;
        }

        size--;
    }
}


static void _sound_update(struct sound *ss)
{
    ss->total_left--;
    ss->partial_left--;
    ss->offset++;

    if (ss->partial_left == 0) {
        if (ss->total_left == 0) {
            /* if not in loop, stop */
            if (ss->playing == 1)
                ss->playing = 0;

            ss->total_left = ss->total_size;
            ss->partial_left = ss->partial_size;

            /* big sound? */
            if (ss->big)
                ss->partial_left -= ss->offset;
            else
                ss->offset = 0;
        }
        else {
            if (ss->total_left < ss->partial_size) {
                /* load the end of the file */
                ss->partial_left = ss->total_left;

                _sound_read_block(ss->file,
                                  ss->total_left, ss->data[ss->bi],
                                  ss->bits);

                /* back to begining of file data */
                fseek(ss->file, ss->fpos, SEEK_SET);

                /* load the beginning */
                _sound_read_block(ss->file,
                                  ss->partial_size - ss->total_left,
                                  ss->data[ss->bi] + ss->total_left,
                                  ss->bits);
            }
            else {
                /* load a complete block from file */
                ss->partial_left = ss->partial_size;

                _sound_read_block(ss->file,
                                  ss->partial_size,
                                  ss->data[ss->bi], ss->bits);
            }

            /* swap the buffers and restart */
            ss->bi = !ss->bi;
            ss->data_8 = (unsigned char *) ss->data[ss->bi];
            ss->data_16 = (short int *) ss->data[ss->bi];
            ss->offset = 0;
        }
    }
}


static void sound_mix_8(void)
/* mixes the sounds in 8 bit mode */
{
    int n, m;
    int s, ls, rs;
    struct sound *ss;

    /* nothing to mix */
    if (_audio_fd == -1)
        return;

    for (n = 0; n < SOUND_BUFFER_SIZE; n += 2) {
        ls = rs = 0;

        for (m = 0; m < MAX_SOUNDS; m++) {
            ss = &_sounds[m];

            if (ss->data_8 && ss->playing) {
                s = ss->data_8[ss->offset] * ss->att;
                s /= 63;

                _sound_update(ss);

                if (ss->pan != 1)
                    ls += s;

                if (ss->pan != -1)
                    rs += s;
            }
        }

        if (ls > 255)
            ls = 255;
        if (rs > 255)
            rs = 255;

        _sound_buffer_8[n] = (unsigned char) ls;
        _sound_buffer_8[n + 1] = (unsigned char) rs;
    }

    write(_audio_fd, _sound_buffer_8, SOUND_BUFFER_SIZE);
}


static void sound_mix_16(void)
/* mixes the sounds in 16 bit mode */
{
    int n, m;
    int s, ls, rs;
    struct sound *ss;

    /* nothing to mix */
    if (_audio_fd == -1)
        return;

    for (n = 0; n < SOUND_BUFFER_SIZE; n += 2) {
        ls = rs = 0;

        for (m = 0; m < MAX_SOUNDS; m++) {
            ss = &_sounds[m];

            if (ss->data_16 && ss->playing) {
                s = ss->data_16[ss->offset] * ss->att;
                s /= 63;

                _sound_update(ss);

                if (ss->pan != 1)
                    ls += s;
                if (ss->pan != -1)
                    rs += s;
            }
        }

        if (ls < -32768)
            ls = -32768;
        if (ls > 32767)
            ls = 32767;
        if (rs < -32768)
            rs = -32768;
        if (rs > 32767)
            rs = 32767;

        _sound_buffer_16[n] = (short) ls;
        _sound_buffer_16[n + 1] = (short) rs;
    }

    write(_audio_fd, _sound_buffer_16, SOUND_BUFFER_SIZE * 2);
}


static void sound_mix(void)
{
    if (_qdgdfa_16_bit)
        sound_mix_16();
    else
        sound_mix_8();
}


static void sound_reset(void)
{
    int n;

    for (n = 0; n < MAX_SOUNDS; n++) {
        /* free pointers */
        if (_sounds[n].data[0] != NULL && !_sounds[n].duped)
            if (!_sounds[n].duped)
                free(_sounds[n].data[0]);

        if (_sounds[n].data[1] != NULL)
            free(_sounds[n].data[1]);

        /* close files */
        if (_sounds[n].file != NULL)
            fclose(_sounds[n].file);
    }

    /* clean everything else */
    memset(_sounds, '\0', sizeof(_sounds));

    _daemon_seq = -1;
}


static void sound_cmd_load(char *wavfile)
/* load a sound */
{
    FILE *f;
    int size, bits;
    struct sound *ss;
    int big = 1;

    if (_daemon_seq == MAX_ORIGINAL_SOUNDS)
        return;

    _daemon_seq++;

    if ((f = qdgdfa_load_wav(wavfile, &size, &bits)) == NULL)
        return;

    if (!_qdgdfa_16_bit && bits == 16)
        size /= 2;
    if (_qdgdfa_16_bit && bits == 8)
        size *= 2;

    ss = &_sounds[_daemon_seq];

    /* test if file must not be considered big */
    if (size < _qdgdfa_big_sound_threshold)
        big = 0;
    else
        /* big files must be at least two buffers big */
    if (size < 2 * _qdgdfa_big_sound_buffer_size)
        big = 0;

    ss->total_size = size;

    if (big) {
        ss->file = f;
        ss->fpos = ftell(f);

        ss->partial_size = _qdgdfa_big_sound_buffer_size;
        ss->data[0] = (unsigned char *) malloc(ss->partial_size);
        ss->data[1] = (unsigned char *) malloc(ss->partial_size);
    }
    else {
        ss->partial_size = size;
        ss->data[0] = (unsigned char *) malloc(ss->partial_size);
    }

    /* sound size is stored as # of samples, not bytes */
    if (_qdgdfa_16_bit) {
        ss->total_size /= 2;
        ss->partial_size /= 2;
    }

    ss->playing = 0;
    ss->pan = 0;
    ss->att = 63;
    ss->duped = 0;
    ss->bits = bits;
    ss->big = big;
    ss->bi = 0;

    ss->partial_left = ss->partial_size;
    ss->total_left = ss->total_size;

    ss->data_8 = (unsigned char *) ss->data[0];
    ss->data_16 = (short int *) ss->data[0];

    _sound_read_block(f, ss->partial_size, _sounds[_daemon_seq].data[0],
                      bits);

    if (big)
        _sound_read_block(f, ss->partial_size,
                          _sounds[_daemon_seq].data[1], bits);
    else
        fclose(f);
}


static void sound_cmd_dup(int snd)
/* duplicates a sound */
{
    if (_daemon_seq == MAX_ORIGINAL_SOUNDS)
        return;

    _daemon_seq++;

    /* big sounds cannot be duped */
    if (_sounds[snd].big)
        return;

    _sounds[_daemon_seq] = _sounds[snd];

    _sounds[_daemon_seq].playing = 0;
    _sounds[_daemon_seq].duped = 1;
}


static void sound_cmd_start(int snd, int loop)
/* plays a sound */
{
    struct sound *ss;

    ss = &_sounds[snd];

    if (ss->data[0] && !ss->playing)
        ss->playing = loop ? 2 : 1;
}


static void sound_cmd_respawn(int snd)
/* respawns a sound */
{
    int n;

    /* big sounds cannot be respawned */
    if (_sounds[snd].big) {
        sound_cmd_start(snd, 0);
        return;
    }

    /* find a usable slot */
    for (n = MAX_ORIGINAL_SOUNDS; n < MAX_SOUNDS; n++) {
        if (!_sounds[n].playing)
            break;
    }

    if (n < MAX_SOUNDS) {
        _sounds[n] = _sounds[snd];

        _sounds[n].duped = 1;
        sound_cmd_start(n, 0);
    }
}


static int parse_sound_cmd(int fd, char *msg)
/* interpretes messages from the client */
{
    int sound;
    int val;
    int ret;
    char *cmd;
    char *cmd_end;
    int n = 0;

    ret = 1;

    if (_audio_fd == -1)
        return ret;

    cmd = msg;

    /* reset message offset */
    _msg_offset = 0;

/*	printf("msg: %s\n", msg);*/

    while (ret && *cmd != '\0') {
        if ((cmd_end = strchr(cmd, ';')) == NULL) {
            /* if not on the end of string and
               there is no more semicolons, it
               means a partial message have arrived,
               split by pipe bufferings; so, copy
               the rest of the message to the beginning */
            _msg_offset = strlen(cmd);
            strcpy(msg, cmd);

/*			printf("Partial msg: %s, %d\n", msg, _msg_offset);*/
            break;
        }

        /* delimit */
        *cmd_end = '\0';

/*		printf("cmd: %s\n", cmd);*/

        switch (*cmd) {
        case SOUND_CMD_EXIT:

            ret = 0;
            break;

        case SOUND_CMD_RESET:

            sound_reset();
            break;

        case SOUND_CMD_LOAD:
        case SOUND_CMD_LOADBIG:

            if (cmd[1] == '\0')
                printf("No sound name?\n");
            else
                sound_cmd_load(cmd + 1);

            break;

        case SOUND_CMD_START:

            sound = (int) cmd[1] - 'A';
            val = (int) cmd[2] - 'A';

            sound_cmd_start(sound, val);

            break;

        case SOUND_CMD_RESPAWN:

            sound = (int) cmd[1] - 'A';
            sound_cmd_respawn(sound);
            break;

        case SOUND_CMD_STOP:

            sound = (int) cmd[1] - 'A';

            if (_sounds[sound].data[0])
                _sounds[sound].playing = 0;

            break;

        case SOUND_CMD_SETPAN:

            sound = (int) cmd[1] - 'A';
            val = (int) cmd[2] - 'A';

            if (_sounds[sound].data[0])
                _sounds[sound].pan = val;

            break;

        case SOUND_CMD_ATTEN:

            sound = (int) cmd[1] - 'A';
            val = (int) cmd[2] - '@';

            if (_sounds[sound].data[0])
                _sounds[sound].att = 63 - val;

            break;

        case SOUND_CMD_DUP:

            sound = (int) cmd[1] - 'A';

            sound_cmd_dup(sound);
            break;

        case SOUND_CMD_UNPAUSE:

            if (_audio_fd != -1)
                n = 1;

            /* falls through */

        case SOUND_CMD_PAUSE:

            ioctl(fd, FIONBIO, &n);
            break;

        default:
            printf("Unknown command '%s'\n", cmd);
            break;
        }

        cmd = cmd_end + 1;
    }

    return ret;
}


static void sound_daemon(int _pipe_read)
/* sound server main loop */
{
    int n;

    n = _open_device();

    if (n) {
        /* non-blocking mode */
        n = 1;
        ioctl(_pipe_read, FIONBIO, &n);
    }

    /* no sounds */
    memset(_sounds, '\0', sizeof(_sounds));

    for (;;) {
        if ((n =
             read(_pipe_read, msg + _msg_offset,
                  sizeof(msg) - _msg_offset)) <= 0) {
            if (errno != EWOULDBLOCK)
                break;
        }
        else {
            msg[n + _msg_offset] = '\0';

            if (!parse_sound_cmd(_pipe_read, msg))
                break;
        }

        if (_daemon_seq != -1)
            sound_mix();
    }

    if (_audio_fd != -1)
        close(_audio_fd);

    close(_pipe_read);

    exit(0);
}


/* driver */

static int _qdgdfa_load_sound(char *wavfile)
{
    if (_program_seq == MAX_ORIGINAL_SOUNDS)
        return -1;

    msg[0] = SOUND_CMD_LOAD;
    strcpy(&msg[1], wavfile);
    strcat(msg, ";");

    write(_command_fd, msg, strlen(msg));

    _program_seq++;
    return _program_seq;
}


static int _qdgdfa_dup_sound(int snd)
{
    if (snd < 0 || snd > _program_seq)
        return -1;

    msg[0] = SOUND_CMD_DUP;
    msg[1] = (char) ('A' + snd);
    msg[2] = ';';

    write(_command_fd, msg, 3);

    _program_seq++;
    return _program_seq;
}


static void _qdgdfa_play_sound(int snd, int loop)
{
    if (snd < 0 || snd > _program_seq)
        return;

    msg[0] = SOUND_CMD_START;
    msg[1] = (char) ('A' + snd);
    msg[2] = (char) ('A' + loop);
    msg[3] = ';';

    write(_command_fd, msg, 4);
}


static void _qdgdfa_respawn_sound(int snd)
{
    if (snd < 0 || snd > _program_seq)
        return;

    msg[0] = SOUND_CMD_RESPAWN;
    msg[1] = (char) ('A' + snd);
    msg[2] = ';';

    write(_command_fd, msg, 3);
}


static void _qdgdfa_stop_sound(int snd)
{
    if (snd < 0 || snd > _program_seq)
        return;

    msg[0] = SOUND_CMD_STOP;
    msg[1] = (char) ('A' + snd);
    msg[2] = ';';

    write(_command_fd, msg, 3);
}


static void _qdgdfa_set_pan(int snd, int pan)
{
    if (snd < 0 || snd > _program_seq)
        return;

    msg[0] = SOUND_CMD_SETPAN;
    msg[1] = (char) ('A' + snd);
    msg[2] = (char) ('A' + pan);
    msg[3] = ';';

    write(_command_fd, msg, 4);
}


static void _qdgdfa_set_attenuation(int snd, int att)
{
    if (snd < 0 || snd > _program_seq)
        return;

    msg[0] = SOUND_CMD_ATTEN;
    msg[1] = (char) ('A' + snd);
    msg[2] = (char) ('@' + att);
    msg[3] = ';';

    write(_command_fd, msg, 4);
}


static void _qdgdfa_reset(void)
{
    msg[0] = SOUND_CMD_RESET;
    msg[1] = ';';
    write(_command_fd, msg, 2);

    _program_seq = -1;
}


static void _qdgdfa_pause(int p)
{
    msg[0] = p ? SOUND_CMD_PAUSE : SOUND_CMD_UNPAUSE;
    msg[1] = ';';
    write(_command_fd, msg, 2);
}


static int _qdgdfa_startup(void)
{
    int p[2];

    pipe(p);

    if ((_daemon_pid = fork()) == 0) {
        close(p[1]);
        setpgid(0, 0);
        sound_daemon(p[0]);
    }

    close(p[0]);
    _command_fd = p[1];

    return 1;
}


static void _qdgdfa_shutdown(void)
{
    msg[0] = SOUND_CMD_EXIT;
    msg[1] = ';';
    write(_command_fd, msg, 2);

    close(_command_fd);

    kill(_daemon_pid, SIGKILL);
}


/* driver information */

static struct _qdgdfa_driver drv = {
    "oss",

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


struct _qdgdfa_driver *oss_drv_detect(void)
/* detection function */
{
    if (_qdgdfa_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_LINUX_OSS */
