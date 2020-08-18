/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#ifndef QDGDF_VIDEO_H_
#define QDGDF_VIDEO_H_

#include <stdio.h>

#ifdef CONFOPT_OPENGL
#include <GL/gl.h>
#include <GL/glu.h>
#endif

extern char _qdgdfv_fopen_path[250];

extern int _qdgdfv_use_logger;
extern char _qdgdfv_logger_file[150];

extern int _qdgdfv_scale;
extern int _qdgdfv_double_mode;
extern int _qdgdfv_scale2x;
extern unsigned char *_qdgdfv_virtual_screen;
extern int *_qdgdfv_argb_screen;
extern unsigned char _qdgdfv_clear_color;
extern unsigned int _qdgdfv_screen_x_size;
extern unsigned int _qdgdfv_screen_y_size;
extern int _qdgdfv_window_x;
extern int _qdgdfv_window_y;
extern char _qdgdfv_window_title[150];
extern char _qdgdfv_additional_info[150];
extern int _qdgdfv_additional_int_info;
extern int _qdgdfv_double_antialias;
extern int _qdgdfv_gamma_correct;

extern int _qdgdfv_key_up;
extern int _qdgdfv_key_down;
extern int _qdgdfv_key_left;
extern int _qdgdfv_key_right;
extern int _qdgdfv_key_escape;
extern int _qdgdfv_key_space;
extern int _qdgdfv_key_enter;
extern int _qdgdfv_key_pgup;
extern int _qdgdfv_key_pgdn;
extern int _qdgdfv_key_home;
extern int _qdgdfv_key_end;
extern int _qdgdfv_key_f1;
extern int _qdgdfv_key_f2;
extern int _qdgdfv_key_f3;
extern int _qdgdfv_key_f4;
extern int _qdgdfv_key_f5;
extern int _qdgdfv_key_f6;
extern int _qdgdfv_key_f7;
extern int _qdgdfv_key_f8;
extern int _qdgdfv_key_f9;
extern int _qdgdfv_key_f10;

/* Dan Compton made these changes and additions */
extern int _qdgdfv_key_control;
extern int _qdgdfv_key_shift_l;
extern int _qdgdfv_key_shift_r;
extern int _qdgdfv_key_alt_l;
extern int _qdgdfv_key_alt_r;
extern int _qdgdfv_key_alnum;   /* catches alpha chars and numbers */
extern char _qdgdfv_alnum;      /* contains the ascii char of alpha or number or
                                   might contain a OS dependent defined keycode
                                   which would be conditionally compiled in for
                                   x11 or win32 */

extern unsigned int _qdgdfv_palette[256 * 3];
extern unsigned int _qdgdfv_extended_palette[256];
extern int _qdgdfv_pixel_size;
unsigned int _qdgdfv_red_mask;
unsigned int _qdgdfv_green_mask;
unsigned int _qdgdfv_blue_mask;
int _qdgdfv_red_shift;
int _qdgdfv_green_shift;
int _qdgdfv_blue_shift;

extern char *_qdgdfv_version;

extern int _qdgdfv_font_height;
extern int _qdgdfv_font_blend;
extern int _qdgdfv_convert_ktl_to_proportional;

extern int _qdgdfv_full_screen;

extern const char * _qdgdf_embedded_tar_start;
extern const char * _qdgdf_embedded_tar_end;

struct _qdgdfv_driver {
    char *name;
    void (*set_palette) (void);
    void (*dump_virtual_screen) (void);
    void (*dump_argb_screen) (void);
    void (*input_poll) (void);
    int (*timer) (int);
    int (*opengl) (int);
    int (*startup) (void);
    void (*shutdown) (void);
};


char *qdgdfv_sprintf(char *fmt, ...);
void qdgdfv_logger(char *where, char *msg);
void *qdgdfv_malloc(int size);

FILE *_qdgdfv_fopen(char *file, char *mode);
FILE *qdgdfv_fopen(char *file, char *mode);
char *qdgdfv_path_find(const char *file);

void qdgdfv_bang(char *where, char *msg);
#define qdgdfv_bangif(where,cond) if(cond) qdgdfv_bang(where,#cond)

void qdgdfv_load_pcx(unsigned char *pcx, char *pcxfile, int size);
void qdgdfv_load_pcx_pal(unsigned char *pcx, char *pcxfile, int size);
void qdgdfv_load_pcx_pal_set(unsigned char *pcx, char *pcxfile, int size);

void qdgdfv_load_palette(char *palfile);
void qdgdfv_set_palette(void);

void qdgdfv_input_poll(void);
void qdgdfv_clear_virtual_screen(void);

void _qdgdfv_dump2_screen(unsigned char *, short *);
void _qdgdfv_dump4_screen(unsigned char *, int *);

void _qdgdfv_double_dump1_screen(unsigned char *, char *);
void _qdgdfv_double_dump2_screen(unsigned char *, short *);
void _qdgdfv_double_dump4_screen(unsigned char *, int *);

void _qdgdfv_triple_dump1_screen(unsigned char *, char *);
void _qdgdfv_triple_dump2_screen(unsigned char *, short *);
void _qdgdfv_triple_dump4_screen(unsigned char *, int *);

void _qdgdfv_s2x_dump1_screen(unsigned char *, char *);
void _qdgdfv_s2x_dump2_screen(unsigned char *, short *);
void _qdgdfv_s2x_dump4_screen(unsigned char *, int *);

void _qdgdfv_s3x_dump1_screen(unsigned char *, char *);
void _qdgdfv_s3x_dump2_screen(unsigned char *, short *);
void _qdgdfv_s3x_dump4_screen(unsigned char *, int *);

void _qdgdfv_scale_argb_screen(int *scaled_screen);
void _qdgdfv_scale_virtual_screen(void *_double_screen);

void qdgdfv_dump_virtual_screen(void);
void qdgdfv_assert_in_virtual_screen(char *func, unsigned char *ptr);

unsigned char qdgdfv_seek_color(int r, int g, int b);

int qdgdfv_timer(int reset);

void qdgdfv_build_light_table(unsigned char *lut, int levels, int mid);
void qdgdfv_build_light_table_ext(unsigned char *lut, int levels,
                                  int mid, int fr, int fg, int fb);

unsigned char qdgdfv_blend_color(unsigned char c1, unsigned char c2,
                                 int percent);

void qdgdfv_set_accum_buffer(int percent);

int qdgdfv_extended_key_status(int *key_var);

void qdgdfv_load_ktl_font(char *fontfile);
int qdgdfv_font_size(unsigned char *string);
void qdgdfv_font_print(int x, int y, unsigned char *string,
                       unsigned char color);

int qdgdfv_write_tga(char *fn, unsigned char *bmp, int w, int h, int t);

char *qdgdfv_home_dir(void);
char *qdgdfv_app_dir(void);

int qdgdfv_opengl(int onoff);

void qdgdfv_dump_argb_screen(void);

void qdgdfv_startup(void);
void qdgdfv_shutdown(void);

#endif                          /* QDGDF_VIDEO_H_ */
