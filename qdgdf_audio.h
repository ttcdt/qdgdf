/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#ifndef QDGDF_AUDIO_H_
#define QDGDF_AUDIO_H_

#include <stdio.h>

extern int _qdgdfa_sound;
extern char _qdgdfa_window_title[150];
extern int _qdgdfa_16_bit;
extern int _qdgdfa_big_sound_threshold;

extern char _qdgdfa_fopen_path[250];

extern char *_qdgdfa_version;

struct _qdgdfa_driver {
    char *name;
    int (*load_sound) (char *);
    int (*dup_sound) (int);
    void (*play_sound) (int, int);
    void (*respawn_sound) (int);
    void (*stop_sound) (int);
    void (*set_pan) (int, int);
    void (*set_attenuation) (int, int);
    void (*reset) (void);
    void (*pause) (int);
    int (*startup) (void);
    void (*shutdown) (void);
};

FILE *_qdgdfa_fopen(char *file, char *mode);
FILE *qdgdfa_fopen(char *file, char *mode);
char *qdgdfa_path_find(const char *file);
FILE *qdgdfa_load_wav(char *filename, int *size, int *bits);
int qdgdfa_load_sound(char *wavfile);
int qdgdfa_load_big_sound(char *wavfile);
int qdgdfa_dup_sound(int snd);
void qdgdfa_play_sound(int snd, int loop);
void qdgdfa_respawn_sound(int snd);
void qdgdfa_stop_sound(int snd);
void qdgdfa_set_pan(int snd, int pan);
void qdgdfa_set_attenuation(int snd, int att);
void qdgdfa_reset(void);
void qdgdfa_pause(int p);
char *qdgdfa_home_dir(void);
char *qdgdfa_app_dir(void);
void qdgdfa_startup(void);
void qdgdfa_shutdown(void);

#endif                          /* QDGDF_AUDIO_H_ */
