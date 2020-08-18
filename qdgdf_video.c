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
#include <stdarg.h>

#include "qdgdf_video.h"


/** data **/

/**
 * _qdgdfv_fopen_path - Search path for qdgdfv_fopen().
 *
 * This string can contain a semicolon-separated list of paths
 * where files to be open with qdgdfv_fopen() will be tried
 * before banging.
 * [Support Variables]
 */
char _qdgdfv_fopen_path[250] = "";

/**
 * _qdgdfv_virtual_screen - The virtual screen.
 *
 * This variable points to a buffer of (_qdgdfv_screen_x_size *
 * _qdgdfv_screen_y_size) unsigned chars. All video operations are
 * done over this space. To dump it to the real screen, use
 * qdgdfv_dump_virtual_screen().
 * [Video Variables]
 */
unsigned char *_qdgdfv_virtual_screen = NULL;

/**
 * _qdgdfv_argb_screen - The virtual ARGB screen.
 * 
 * This variable points to a buffer of (_qdgdfv_screen_x_size *
 * _qdgdfv_screen_y_size) 32 bit integers, where the color information
 * is ARGB (the alpha part is unused). If a driver does not support
 * ARGB color modes this variable is set to NULL. To dump it to
 * the real screen, use qdgdfv_dump_argb_screen().
 * [Video Variables]
 */
int *_qdgdfv_argb_screen = NULL;

/**
 * _qdgdfv_clear_color - The clear color.
 *
 * This color will be used to clear the screen when using
 * qdgdfv_clear_virtual_screen().
 * [Video Variables]
 */
unsigned char _qdgdfv_clear_color = 0;

/**
 * _qdgdfv_screen_x_size - Horizontal screen size.
 *
 * This variable holds the horizontal screen size in pixels. It can be
 * set to whatever wanted before the startup. The real horizontal
 * screen size will be stored here after the startup (it can be a
 * different value).
 * [Video Variables]
 */
unsigned int _qdgdfv_screen_x_size = 320;

/**
 * _qdgdfv_screen_y_size - Vertical screen size.
 *
 * This variable holds the vertical screen size in pixels. It can be
 * set to whatever wanted before the startup. The real vertical
 * screen size will be stored here after the startup (it can be a
 * different value).
 * [Video Variables]
 */
unsigned int _qdgdfv_screen_y_size = 200;

/**
 * _qdgdfv_window_x - Initial x position of the window.
 *
 * This variable must be set before startup and holds the desired
 * initial position of the window. Not all supported systems let
 * this be set (some of them even have no window at all, just
 * fullscreen graphics), so it's purely orientative there.
 * [Video Variables]
 */
int _qdgdfv_window_x = 60;

/**
 * _qdgdfv_window_y - Initial y position of the window.
 *
 * This variable must be set before startup and holds the desired
 * initial position of the window. Not all supported systems let
 * this be set (some of them even have no window at all, just
 * fullscreen graphics), so it's purely orientative there.
 * [Video Variables]
 */
int _qdgdfv_window_y = 60;


/**
 * _qdgdfv_scale - Sets the scale.
 *
 * Sets the scale. If not set, a 1 scale (no scale) will be tried;
 * if it's impossible to set due to hardware limitations (for example,
 * a 320x200 resolution has been requested and current hardware don't
 * support it, but can do 640x400), a 2 scale (double) will be tried.
 * Some drivers allow even bigger scales.
 *
 * This variable obsoletes the old _qdgdfv_double_mode.
 * [Video Variables]
 */
int _qdgdfv_scale = 0;

/**
 * _qdgdfv_double_mode - Sets the double mode.
 *
 * The use of this variable is deprecated. Use _qdgdfv_scale instead.
 * [Video Variables]
 */
int _qdgdfv_double_mode = 0;

/**
 * _qdgdfv_double_antialias - Antialias flag for double modes.
 *
 * If you set this variable, double modes will be dumped using
 * a basic antialiasing mechanism, if the video driver implements one.
 * [Video Variables]
 */
int _qdgdfv_double_antialias = 0;

/**
 * _qdgdfv_scale2x - Scale2x algorithm flag.
 *
 * When set, double screen dumping is done by using the scale2x
 * algorithm (read about it at http://scale2x.sourceforge.net).
 * It's set by default.
 * [Video Variables]
 */
int _qdgdfv_scale2x = 1;

/**
 * _qdgdfv_window_title - Title for the window.
 *
 * This string holds the title for the window. Take note
 * that some systems are fullscreen and has no window titles.
 * [Video Variables]
 */
char _qdgdfv_window_title[150] = "qdgdf Window";

/**
 * _qdgdfv_additional_info - Additional string info for the driver.
 *
 * This string can be filled with some information for the driver.
 * Its content is purposely driver dependent and can contain,
 * for example, the remote X Window display.
 * [Video Variables]
 */
char _qdgdfv_additional_info[150] = "";

/**
 * _qdgdfv_additional_int_info - Additional integer info for the driver.
 *
 * This integer can be filled with some information for the driver.
 * Its content is purposely driver dependent and can contain,
 * for example, the Windows instance handler.
 * [Video Variables]
 */
int _qdgdfv_additional_int_info = 0;

/**
 * _qdgdfv_gamma_correct - Gamma correction.
 *
 * This variable containts the amount of gamma correction to
 * be applied when colors are created. It ranges from 0 (colors as
 * defined in the palette) to 255 (absolutely saturate).
 */
int _qdgdfv_gamma_correct = 0;

/* the keys */

/**
 * _qdgdfv_key_ - The key flags.
 *
 * This variables are set by qdgdfv_input_poll() accordingly to
 * the current keyboard status. These variables are:
 * _qdgdfv_key_up, _qdgdfv_key_down, _qdgdfv_key_left,
 * _qdgdfv_key_right, _qdgdfv_key_escape, _qdgdfv_key_space,
 * _qdgdfv_key_enter, _qdgdfv_key_control_l, _qdgdfv_key_control_r,
 * _qdgdfv_key_control, _qdgdfv_key_shift_l, _qdgdfv_key_shift_r,
 * _qdgdfv_key_pgup, _qdgdfv_key_pgdn, _qdgdfv_key_home, _qdgdfv_key_end
 * and _qdgdfv_key_f1 to f10.
 * [Keyboard Variables]
 */
int _qdgdfv_key_up = 0;
int _qdgdfv_key_down = 0;
int _qdgdfv_key_left = 0;
int _qdgdfv_key_right = 0;
int _qdgdfv_key_escape = 0;
int _qdgdfv_key_space = 0;
int _qdgdfv_key_enter = 0;
int _qdgdfv_key_control_l = 0;
int _qdgdfv_key_control_r = 0;
int _qdgdfv_key_alt_l = 0;
int _qdgdfv_key_alt_r = 0;
int _qdgdfv_key_pgup = 0;
int _qdgdfv_key_pgdn = 0;
int _qdgdfv_key_home = 0;
int _qdgdfv_key_end = 0;
int _qdgdfv_key_f1 = 0;
int _qdgdfv_key_f2 = 0;
int _qdgdfv_key_f3 = 0;
int _qdgdfv_key_f4 = 0;
int _qdgdfv_key_f5 = 0;
int _qdgdfv_key_f6 = 0;
int _qdgdfv_key_f7 = 0;
int _qdgdfv_key_f8 = 0;
int _qdgdfv_key_f9 = 0;
int _qdgdfv_key_f10 = 0;

/* Dan Compton added these changes */
int _qdgdfv_key_control = 0;
int _qdgdfv_key_shift_l = 0;
int _qdgdfv_key_shift_r = 0;
int _qdgdfv_key_alnum = 0;
char _qdgdfv_alnum = 0;
/* End changes */

/* extended key information */
static struct __qdgdfv_extended_key_status {
    int *key_var;       /* pointer to key variable */
    int last_val;       /* last seen value */
} _qdgdfv_extended_key_status[] = {
    { &_qdgdfv_key_up, 0},
    { &_qdgdfv_key_down, 0},
    { &_qdgdfv_key_left, 0},
    { &_qdgdfv_key_right, 0},
    { &_qdgdfv_key_escape, 0},
    { &_qdgdfv_key_space, 0},
    { &_qdgdfv_key_enter, 0},
    { &_qdgdfv_key_control_l, 0},
    { &_qdgdfv_key_control_r, 0},
    { &_qdgdfv_key_pgup, 0},
    { &_qdgdfv_key_pgdn, 0},
    { &_qdgdfv_key_home, 0},
    { &_qdgdfv_key_end, 0},
    { &_qdgdfv_key_f1, 0},
    { &_qdgdfv_key_f2, 0},
    { &_qdgdfv_key_f3, 0},
    { &_qdgdfv_key_f4, 0},
    { &_qdgdfv_key_f5, 0},
    { &_qdgdfv_key_f6, 0},
    { &_qdgdfv_key_f7, 0},
    { &_qdgdfv_key_f8, 0},
    { &_qdgdfv_key_f9, 0},
    { &_qdgdfv_key_f10, 0},
    { &_qdgdfv_key_control, 0},
    { &_qdgdfv_key_shift_l, 0},
    { &_qdgdfv_key_shift_r, 0},
    { NULL, 0}
};


/** static data **/

/* the palette. Includes by default the original palette from
   the never-finished game Freak Wars (256*rgb) */

unsigned int _qdgdfv_palette[256 * 3] = {
    0, 0, 0, 28, 24, 12, 20, 16, 8, 68, 68, 68, 255, 224, 0, 24, 24, 24,
    16, 20, 20, 8, 12, 12, 4, 8, 8, 40, 52, 28, 32, 40, 16, 20, 28, 8,
    12, 24, 0, 68, 56, 40, 64, 48, 32, 56, 40, 24, 255, 69, 0, 220, 152, 152,
    216, 148, 148, 208, 136, 136, 204, 128, 128, 196, 120, 120, 196, 112, 112,
    188, 104, 104, 180, 96, 96, 176, 88, 88, 168, 84, 84, 164, 80, 80,
    160, 72, 72, 156, 64, 64, 148, 56, 56, 144, 56, 56, 136, 48, 48,
    132, 44, 44, 128, 40, 40, 124, 32, 32, 116, 28, 28, 112, 24, 24,
    104, 24, 24, 100, 20, 20, 96, 16, 16, 92, 12, 12, 84, 8, 8, 80, 8, 8,
    72, 8, 8, 68, 0, 0, 64, 0, 0, 255, 191, 0, 228, 212, 200, 228, 204, 188,
    228, 196, 180, 228, 188, 168, 228, 184, 160, 228, 180, 152, 228, 172, 140,
    228, 168, 132, 228, 160, 120, 220, 152, 112, 212, 148, 104, 204, 140, 96,
    196, 132, 88, 192, 124, 84, 184, 120, 76, 180, 116, 72, 168, 112, 68,
    160, 104, 64, 152, 100, 60, 144, 96, 56, 136, 88, 56, 128, 88, 52,
    120, 80, 48, 112, 76, 44, 104, 72, 40, 96, 64, 36, 84, 60, 32, 72, 56, 28,
    68, 52, 24, 56, 44, 24, 44, 40, 20, 36, 32, 16, 212, 216, 216,
    204, 208, 208, 196, 200, 200, 196, 196, 196, 188, 188, 188, 180, 184, 184,
    176, 180, 180, 168, 172, 172, 164, 164, 164, 160, 160, 160, 152, 152, 152,
    148, 152, 152, 140, 144, 144, 132, 136, 136, 132, 132, 132, 124, 124, 124,
    116, 120, 120, 112, 116, 116, 104, 108, 108, 100, 100, 100, 96, 96, 96,
    88, 88, 88, 80, 84, 84, 76, 80, 80, 68, 72, 72, 64, 64, 64, 60, 60, 60,
    52, 56, 56, 48, 52, 52, 40, 44, 44, 36, 36, 36, 32, 32, 32, 255, 89, 0,
    100, 216, 92, 92, 200, 88, 84, 184, 80, 80, 172, 72, 72, 156, 64,
    68, 144, 56, 60, 132, 52, 56, 120, 44, 48, 104, 40, 40, 88, 32,
    36, 76, 24, 28, 60, 24, 20, 48, 16, 16, 32, 12, 255, 29, 0, 168, 152, 128,
    164, 144, 120, 156, 136, 116, 148, 128, 108, 140, 120, 100, 136, 116, 96,
    132, 112, 88, 124, 104, 84, 116, 96, 80, 108, 88, 72, 104, 88, 68,
    100, 80, 60, 92, 76, 56, 84, 68, 52, 76, 60, 48, 72, 56, 44, 140, 120, 88,
    128, 108, 76, 116, 96, 68, 104, 88, 56, 92, 76, 48, 80, 64, 40,
    68, 56, 32, 60, 48, 24, 108, 116, 88, 100, 104, 80, 92, 96, 72,
    80, 88, 64, 72, 80, 56, 64, 72, 48, 56, 64, 40, 48, 56, 36, 228, 228, 104,
    208, 196, 80, 192, 168, 60, 172, 140, 44, 156, 112, 28, 136, 84, 20,
    120, 60, 8, 100, 40, 0, 228, 228, 228, 228, 196, 196, 228, 168, 168,
    228, 140, 140, 228, 112, 112, 228, 88, 88, 228, 56, 56, 228, 28, 28,
    228, 0, 0, 212, 0, 0, 200, 0, 0, 192, 0, 0, 180, 0, 0, 168, 0, 0,
    160, 0, 0, 148, 0, 0, 136, 0, 0, 124, 0, 0, 112, 0, 0, 100, 0, 0,
    92, 0, 0, 80, 0, 0, 68, 0, 0, 60, 0, 0, 204, 208, 228, 176, 180, 228,
    152, 152, 228, 128, 128, 228, 100, 104, 228, 72, 76, 228, 48, 52, 228,
    24, 24, 228, 0, 0, 228, 0, 0, 204, 0, 0, 184, 0, 0, 160, 0, 0, 140,
    0, 0, 120, 0, 0, 96, 0, 0, 76, 228, 228, 228, 228, 212, 196, 228, 192, 168,
    228, 180, 140, 228, 160, 112, 228, 148, 84, 228, 128, 56, 228, 116, 24,
    216, 104, 24, 208, 100, 16, 196, 92, 16, 192, 88, 12, 180, 80, 8,
    172, 72, 0, 164, 64, 0, 156, 60, 0, 228, 228, 228, 228, 228, 192,
    228, 228, 160, 228, 228, 128, 228, 228, 96, 228, 228, 64, 228, 228, 32,
    228, 228, 0, 148, 56, 0, 140, 52, 0, 132, 44, 0, 120, 32, 0, 68, 56, 36,
    60, 44, 24, 48, 32, 20, 40, 24, 12, 255, 204, 0, 0, 0, 64, 0, 0, 56,
    0, 0, 44, 0, 0, 32, 0, 0, 24, 0, 0, 12, 148, 96, 96, 228, 144, 60,
    228, 208, 68, 255, 181, 0, 255, 159, 0, 255, 139, 0, 255, 119, 0,
    255, 109, 0, 255, 0, 255
};

/**
 * _qdgdfv_use_logger - Logger use flag.
 *
 * If this variable is set, the logger will be active.
 * [Support Variables]
 */
int _qdgdfv_use_logger = 1;

/**
 * _qdgdfv_logger_file - Logger file.
 *
 * This string holds the path of the logger file.
 * [Support Variables]
 */
char _qdgdfv_logger_file[150] = "";

char *_qdgdfv_version = VERSION;


/**
 * _qdgdfv_accum_buffer - Accumulation buffer.
 *
 * This buffer holds the last dumped virtual screen if
 * the accumulation buffer is used, or a NULL pointer
 * otherwise. It's rarely used directly, as the accumulation
 * buffer is treated transparently.
 * [Video Variables]
 */
unsigned char *_qdgdfv_accum_buffer = NULL;

unsigned char _qdgdfv_accum_table[256][256];

/* the extended palette (for 15, 16, 24 and 32 bpp) */
unsigned int _qdgdfv_extended_palette[256];

/* pixel size (1, 2 or 4) */
int _qdgdfv_pixel_size;

/* video driver */
static struct _qdgdfv_driver *drv = NULL;

/* masks and shifts for pixel sizes > 1 */
unsigned int _qdgdfv_red_mask;
unsigned int _qdgdfv_green_mask;
unsigned int _qdgdfv_blue_mask;
int _qdgdfv_red_shift;
int _qdgdfv_green_shift;
int _qdgdfv_blue_shift;

/**
 * _qdgdfv_full_screen - Full screen flag.
 *
 * When set before initialization, it expresses the preference
 * of running full screen or not (a value of -1 means it doesn't matter).
 * After initialization, contains what really happened.
 */
int _qdgdfv_full_screen = -1;

const char * _qdgdf_embedded_tar_start = NULL;
const char * _qdgdf_embedded_tar_end = NULL;


/** code **/

#include "qdgdf_path.c"

/** basic tools **/

/**
 * qdgdfv_sprintf - Static sprintf.
 * @fmt: the format string
 *
 * Formats a string, using sprintf.
 * A static buffer is returned.
 * [Support Functions]
 */
char *qdgdfv_sprintf(char *fmt, ...)
{
    static char sp_buf[4096];
    va_list argptr;

    va_start(argptr, fmt);
    vsprintf(sp_buf, fmt, argptr);
    va_end(argptr);

    return sp_buf;
}


/**
 * qdgdfv_logger - Logs a message.
 * @where: caller function name
 * @msg: message
 *
 * Logs the @message to the logger file, usually an error.
 * [Support Functions]
 */
void qdgdfv_logger(char *where, char *msg)
{
    FILE *f;

    if (_qdgdfv_use_logger && _qdgdfv_logger_file[0] != '\0') {
        if ((f = fopen(_qdgdfv_logger_file, "a")) != NULL) {
            fprintf(f, "%s: %s\n", where, msg);

            fclose(f);
        }
    }
}


/**
 * qdgdfv_bang - Bangs on unrecoverable problems.
 * @where: caller function name
 * @msg: message
 *
 * Logs the @message to the logger and returns to the system.
 * [Support Functions]
 */
void qdgdfv_bang(char *where, char *msg)
{
    qdgdfv_logger(where, msg);

    printf("\nBANG! %s: %s\n", where, msg);
    fflush(stdout);

    exit(1);
}


/**
 * qdgdfv_malloc - 'Secure' malloc.
 * @size: the size of the block to malloc
 *
 * Tries to alloc the desired memory @size and, if not succesful,
 * bangs out to the system. This make unnecesary to test if
 * the block could be allocated.
 * Returns the allocated block.
 * [Support Functions]
 */
void *qdgdfv_malloc(int size)
{
    void *ptr;

    ptr = malloc(size);

    if (!ptr)
        qdgdfv_bang("a_malloc", "Out of memory");

    return ptr;
}


FILE *_qdgdfv_fopen(char *file, char *mode)
{
    return _path_fopen(_qdgdfv_fopen_path, file, mode);
}


/**
 * qdgdfv_path_find - Finds a file in _qdgdfv_fopen_path.
 * @file: the file to be found
 *
 * Searches for @file in the path stored in _qdgdfv_fopen_path.
 * If it's found in some of the directories there, a string is
 * allocated contaning the full path, that should be freed
 * when no longer needed. Otherwise, returns NULL.
 */
char *qdgdfv_path_find(const char *file)
{
    return _path_find(_qdgdfv_fopen_path, file);
}


/**
 * qdgdfv_fopen - 'Secure' open.
 * @file: file to be opened
 * @mode: mode for the file
 *
 * Opens a file, banging if could not be opened. Optional search paths
 * can be defined in _qdgdfv_fopen_path.
 * Returns the opened file.
 * [Support Functions]
 */
FILE *qdgdfv_fopen(char *file, char *mode)
{
    FILE *f;

    if ((f = _qdgdfv_fopen(file, mode)) == NULL)
        qdgdfv_bang("qdgdfv_fopen: can't open", file);

    return f;
}


static void load_pcx(unsigned char *pcx, char *pcxfile, int size, int usepal)
{
    int n, m;
    unsigned char c;
    FILE *f;
    unsigned char _pcx_palette[256][3];

    f = qdgdfv_fopen(pcxfile, "rb");

    /* skips header */
    fseek(f, 128, SEEK_SET);

    n = 0;
    while (n < size) {
        c = fgetc(f);

        if (c > 0xC0) {
            /* run-length */
            m = c & 0x3F;

            c = fgetc(f);
        }
        else
            m = 1;

        while (m) {
            pcx[n++] = c;
            m--;
        }
    }

    /* reads palette */
    fseek(f, -((long) sizeof(_pcx_palette)), SEEK_END);
    fread(_pcx_palette, 3, 256, f);

    fclose(f);

    /* if the palette is not to be used, it's over */
    if (!usepal)
        return;

    if (usepal == 1) {
        /* fixes the pcx to use current palette */
        for (n = 0; n < size; n++) {
            c = pcx[n];
            pcx[n] = qdgdfv_seek_color(_pcx_palette[c][0],
                           _pcx_palette[c][1], _pcx_palette[c][2]
                );
        }
    }
    else if (usepal == 2) {
        /* transfers this pcx's palette to system one */
        for (n = 0; n < 256; n++) {
            _qdgdfv_palette[n * 3] = _pcx_palette[n][0];
            _qdgdfv_palette[(n * 3) + 1] = _pcx_palette[n][1];
            _qdgdfv_palette[(n * 3) + 2] = _pcx_palette[n][2];
        }

        /* and set it */
        qdgdfv_set_palette();
    }
}


/**
 * qdgdfv_load_pcx - Loads a graphic in PCX format.
 * @pcx: the buffer where the graphic will be stored
 * @pcxfile: the file containing the graphic
 * @size: the size in bytes of the graphic data
 *
 * Loads a graphic into the supplied @pcx buffer. The file must be
 * in 256 color PCX format. The palette included inside the file
 * is not used.
 * [Video Functions]
 */
void qdgdfv_load_pcx(unsigned char *pcx, char *pcxfile, int size)
{
    load_pcx(pcx, pcxfile, size, 0);
}


/**
 * qdgdfv_load_pcx_pal - Loads a graphic in PCX format using its palette.
 * @pcx: the buffer where the graphic will be stored
 * @pcxfile: the file containing the graphic
 * @size: the size in bytes of the graphic data
 *
 * This function does the same as qdgdfv_load_pcx(), but taking into
 * account the palette information stored inside the file to match
 * the current palette.
 * [Video Functions]
 */
void qdgdfv_load_pcx_pal(unsigned char *pcx, char *pcxfile, int size)
{
    load_pcx(pcx, pcxfile, size, 1);
}


/**
 * qdgdfv_load_pcx_pal_set - Loads a graphic in PCX format setting its palette.
 * @pcx: the buffer where the graphic will be stored
 * @pcxfile: the file containing the graphic
 * @size: the size in bytes of the graphic data
 *
 * This function does the same as qdgdfv_load_pcx(), but setting the palette
 * store inside the file as the default.
 * [Video Functions]
 */
void qdgdfv_load_pcx_pal_set(unsigned char *pcx, char *pcxfile, int size)
{
    load_pcx(pcx, pcxfile, size, 2);
}


/**
 * qdgdfv_load_palette - Loads an external palette.
 * @palette_file: the file containing the palette
 *
 * Loads an external palette. The file is a text one having
 * lines with three decimal values from 0 to 255 for the red,
 * green and blue parts of each color, respectively. To be used,
 * qdgdfv_set_palette() must be called afterwards.
 * [Video Functions]
 */
void qdgdfv_load_palette(char *palette_file)
{
    int n;
    FILE *f;
    char lin[80];
    unsigned int r, g, b;

    if (*palette_file == '\0')
        return;

    f = qdgdfv_fopen(palette_file, "r");

    /* ignores first three lines */
    fgets(lin, sizeof(lin) - 1, f);
    fgets(lin, sizeof(lin) - 1, f);
    fgets(lin, sizeof(lin) - 1, f);

    for (n = 0; n < 256; n++) {
        if (fscanf(f, "%u %u %u\n", &r, &g, &b) != 3)
            break;

        _qdgdfv_palette[n * 3] = r;
        _qdgdfv_palette[(n * 3) + 1] = g;
        _qdgdfv_palette[(n * 3) + 2] = b;
    }

    /* fills to the end with zeroes */
    for (; n < 256; n++) {
        _qdgdfv_palette[n * 3] = 0;
        _qdgdfv_palette[(n * 3) + 1] = 0;
        _qdgdfv_palette[(n * 3) + 2] = 0;
    }

    fclose(f);
}


static void fill_extended_palette(void)
{
    int n;
    unsigned int r, g, b;
    int *pal;

    pal = (int *) _qdgdfv_palette;

    for (n = 0; n < 256; n++) {

        if ((r = (unsigned int) pal[n * 3] + _qdgdfv_gamma_correct) > 255)
            r = 255;

        if ((g = (unsigned int) pal[(n * 3) + 1] + _qdgdfv_gamma_correct) > 255)
            g = 255;

        if ((b = (unsigned int) pal[(n * 3) + 2] + _qdgdfv_gamma_correct) > 255)
            b = 255;

        r = ((r << 24) & _qdgdfv_red_mask) >> _qdgdfv_red_shift;
        g = ((g << 24) & _qdgdfv_green_mask) >> _qdgdfv_green_shift;
        b = ((b << 24) & _qdgdfv_blue_mask) >> _qdgdfv_blue_shift;

        _qdgdfv_extended_palette[n] = r | g | b;
    }
}


/**
 * qdgdfv_set_palette - Sets the palette.
 *
 * Sets the stored palette as the current one, probably
 * loading it into video hardware.
 * [Video Functions]
 */
void qdgdfv_set_palette(void)
{
    /* call the driver setting */
    drv->set_palette();

    if (_qdgdfv_pixel_size > 1)
        fill_extended_palette();
}


/**
 * qdgdfv_clear_virtual_screen - Clears the virtual screen.
 *
 * Clears the virtual screen, using _qdgdfv_clear_color.
 * [Video Functions]
 */
void qdgdfv_clear_virtual_screen(void)
{
    memset(_qdgdfv_virtual_screen, _qdgdfv_clear_color,
           _qdgdfv_screen_x_size * _qdgdfv_screen_y_size);
}


/* screen dumping */

#define DUMP_PLAIN(NAME,TYPE) \
void NAME(unsigned char * screen, TYPE * dscreen) { \
    int n; TYPE a; \
    for(n = _qdgdfv_screen_x_size * _qdgdfv_screen_y_size;n > 0;n--) { \
        a = (TYPE) _qdgdfv_extended_palette[(int)*screen++]; \
        *dscreen++ = a; \
    } \
}

DUMP_PLAIN(_qdgdfv_dump2_screen, short)
 DUMP_PLAIN(_qdgdfv_dump4_screen, int)

#define DOUBLE_DUMP_PLAIN(NAME,TYPE) \
void NAME(unsigned char * screen, TYPE * dscreen) { \
    int n, m, l; TYPE a; \
    l = _qdgdfv_screen_x_size * 2; \
    for(n = 0;n < _qdgdfv_screen_y_size;n++) { \
        for(m = 0;m < _qdgdfv_screen_x_size;m++) { \
            a = (TYPE) _qdgdfv_extended_palette[(int)*screen++]; \
            *dscreen = a; *(dscreen + l) = a; dscreen++; \
            *dscreen = a; *(dscreen + l) = a; dscreen++; \
        } \
        dscreen += l; \
    } \
}
DOUBLE_DUMP_PLAIN(_qdgdfv_double_dump1_screen, char)
 DOUBLE_DUMP_PLAIN(_qdgdfv_double_dump2_screen, short)
 DOUBLE_DUMP_PLAIN(_qdgdfv_double_dump4_screen, int)

#define TRIPLE_DUMP_PLAIN(NAME,TYPE) \
void NAME(unsigned char * screen, TYPE * dscreen) { \
    int n, m, l, l2; TYPE a; \
    l = _qdgdfv_screen_x_size * 3; \
    l2 = _qdgdfv_screen_x_size * 3 * 2; \
    for(n = 0;n < _qdgdfv_screen_y_size;n++) { \
        for(m = 0;m < _qdgdfv_screen_x_size;m++) { \
            a = (TYPE) _qdgdfv_extended_palette[(int)*screen++]; \
            *dscreen = a; *(dscreen + l) = a; *(dscreen + l2) = a; dscreen++; \
            *dscreen = a; *(dscreen + l) = a; *(dscreen + l2) = a; dscreen++; \
            *dscreen = a; *(dscreen + l) = a; *(dscreen + l2) = a; dscreen++; \
        } \
        dscreen += l2; \
    } \
}
TRIPLE_DUMP_PLAIN(_qdgdfv_triple_dump1_screen, char)
 TRIPLE_DUMP_PLAIN(_qdgdfv_triple_dump2_screen, short)
 TRIPLE_DUMP_PLAIN(_qdgdfv_triple_dump4_screen, int)


/** scale2x: algorithm taken from http://scale2x.sourceforge.net **/

static void scale2x_peek(unsigned char *p, int tx, unsigned char o[9])
{
    o[0] = *(p - tx - 1);   o[1] = *(p - tx);   o[2] = *(p - tx + 1);
    o[3] = *(p - 1);    o[4] = *p;      o[5] = *(p + 1);
    o[6] = *(p + tx - 1);   o[7] = *(p + tx);   o[8] = *(p + tx + 1);
}


void qdgdfv_scale2x_p(unsigned char *p, int tx, int o[4])
{
    unsigned char i[9];

    scale2x_peek(p, tx, i);

    o[0] = (i[3] == i[1] && i[1] != i[5] && i[3] != i[7]) ? i[3] : i[4];
    o[1] = (i[1] == i[5] && i[1] != i[3] && i[5] != i[7]) ? i[5] : i[4];
    o[2] = (i[3] == i[7] && i[3] != i[1] && i[7] != i[5]) ? i[3] : i[4];
    o[3] = (i[7] == i[5] && i[3] != i[7] && i[1] != i[5]) ? i[5] : i[4];
}


void qdgdfv_scale3x_p(unsigned char *p, int tx, int o[9])
{
    unsigned char i[9];

    scale2x_peek(p, tx, i);

    if (i[1] != i[7] && i[3] != i[5]) {
        o[0] = i[3] == i[1] ? i[3] : i[4];
        o[1] = (i[3] == i[1] && i[4] != i[2]) ||
            (i[1] == i[5] && i[4] != i[0]) ? i[1] : i[4];
        o[2] = i[1] == i[5] ? i[5] : i[4];
        o[3] = (i[3] == i[1] && i[4] != i[6]) ||
            (i[3] == i[1] && i[4] != i[0]) ? i[3] : i[4];
        o[4] = i[4];
        o[5] = (i[1] == i[5] && i[4] != i[8]) ||
            (i[7] == i[5] && i[4] != i[2]) ? i[5] : i[4];
        o[6] = i[3] == i[7] ? i[3] : i[4];
        o[7] = (i[3] == i[7] && i[4] != i[8]) ||
            (i[7] == i[5] && i[4] != i[6]) ? i[7] : i[4];
        o[8] = i[7] == i[5] ? i[5] : i[4];
    }
    else {
        int n;

        for (n = 0; n < 9; n++)
            o[n] = i[4];
    }
}

#define DOUBLE_DUMP_S2X(NAME,TYPE) \
void NAME(unsigned char * screen, TYPE * dscreen) { \
    int n, m, l;  \
    l = _qdgdfv_screen_x_size * 2; \
    screen += _qdgdfv_screen_x_size + 1; \
    for(n = 0; n < _qdgdfv_screen_y_size - 2; n++) { \
        for(m = 0; m < _qdgdfv_screen_x_size; m++) { \
            int o[4]; \
            qdgdfv_scale2x_p(screen, _qdgdfv_screen_x_size, o); \
            screen++; \
            *dscreen = (TYPE)_qdgdfv_extended_palette[o[0]]; \
            *(dscreen + l) = (TYPE)_qdgdfv_extended_palette[o[2]]; \
            dscreen++; \
            *dscreen = (TYPE)_qdgdfv_extended_palette[o[1]]; \
            *(dscreen + l) = (TYPE)_qdgdfv_extended_palette[o[3]]; \
            dscreen++; \
        } \
        dscreen += l; \
    }\
}
DOUBLE_DUMP_S2X(_qdgdfv_s2x_dump1_screen, char)
 DOUBLE_DUMP_S2X(_qdgdfv_s2x_dump2_screen, short)
 DOUBLE_DUMP_S2X(_qdgdfv_s2x_dump4_screen, int)

#define TRIPLE_DUMP_S3X(NAME,TYPE) \
void NAME(unsigned char * screen, TYPE * dscreen) { \
    int n, m, l, l2; \
    l = _qdgdfv_screen_x_size * 3; \
    l2 = _qdgdfv_screen_x_size * 3 * 2; \
    screen += _qdgdfv_screen_x_size + 1; \
    for(n = 0;n < _qdgdfv_screen_y_size - 2;n++) { \
        for(m = 0;m < _qdgdfv_screen_x_size;m++) { \
            int o[9]; \
            qdgdfv_scale3x_p(screen, _qdgdfv_screen_x_size, o); \
            screen++; \
            *dscreen = (TYPE)_qdgdfv_extended_palette[o[0]]; \
            *(dscreen + l) = (TYPE)_qdgdfv_extended_palette[o[3]]; \
            *(dscreen + l2) = (TYPE)_qdgdfv_extended_palette[o[6]]; \
            dscreen++; \
            *dscreen = (TYPE)_qdgdfv_extended_palette[o[1]]; \
            *(dscreen + l) = (TYPE)_qdgdfv_extended_palette[o[4]]; \
            *(dscreen + l2) = (TYPE)_qdgdfv_extended_palette[o[7]]; \
            dscreen++; \
            *dscreen = (TYPE)_qdgdfv_extended_palette[o[2]]; \
            *(dscreen + l) = (TYPE)_qdgdfv_extended_palette[o[5]]; \
            *(dscreen + l2) = (TYPE)_qdgdfv_extended_palette[o[8]]; \
            dscreen++; \
        } \
        dscreen += l2; \
    }\
}
TRIPLE_DUMP_S3X(_qdgdfv_s3x_dump1_screen, char)
 TRIPLE_DUMP_S3X(_qdgdfv_s3x_dump2_screen, short)
 TRIPLE_DUMP_S3X(_qdgdfv_s3x_dump4_screen, int)

void _qdgdfv_scale_argb_screen(int *scaled_screen)
{
    if (_qdgdfv_scale == 1) {
        if (scaled_screen != _qdgdfv_argb_screen)
            memcpy(scaled_screen, _qdgdfv_argb_screen,
                _qdgdfv_screen_x_size * _qdgdfv_screen_y_size * sizeof(int));
    }
    else {
        int n, m, f, j;
        int *s = _qdgdfv_argb_screen;

        for (n = 0; n < _qdgdfv_screen_y_size; n++) {
            int o = n * _qdgdfv_screen_x_size * _qdgdfv_scale * _qdgdfv_scale;

            for (m = 0; m < _qdgdfv_screen_x_size; m++) {
                for (f = 0; f < _qdgdfv_scale; f++) {
                    for (j = 0; j < _qdgdfv_scale; j++) {
                        scaled_screen[(o + (f * _qdgdfv_screen_x_size * _qdgdfv_scale)) + j] = *s;
                    }
                }

                o += _qdgdfv_scale;
                s++;
            }
        }
    }
}


void _qdgdfv_scale_virtual_screen(void *_double_screen)
{
    switch (_qdgdfv_scale) {
    case 1:
        if (_qdgdfv_pixel_size == 2)
            _qdgdfv_dump2_screen(_qdgdfv_virtual_screen,
                                 (short *) _double_screen);
        else
        if (_qdgdfv_pixel_size == 4)
            _qdgdfv_dump4_screen(_qdgdfv_virtual_screen,
                                 (int *) _double_screen);

        break;

    case 2:
        if (_qdgdfv_scale2x) {
            if (_qdgdfv_pixel_size == 1)
                _qdgdfv_s2x_dump1_screen(_qdgdfv_virtual_screen,
                                         (char *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 2)
                _qdgdfv_s2x_dump2_screen(_qdgdfv_virtual_screen,
                                         (short *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 4)
                _qdgdfv_s2x_dump4_screen(_qdgdfv_virtual_screen,
                                         (int *) _double_screen);
        }
        else {
            if (_qdgdfv_pixel_size == 1)
                _qdgdfv_double_dump1_screen(_qdgdfv_virtual_screen,
                                            (char *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 2)
                _qdgdfv_double_dump2_screen(_qdgdfv_virtual_screen,
                                            (short *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 4)
                _qdgdfv_double_dump4_screen(_qdgdfv_virtual_screen,
                                            (int *) _double_screen);
        }

        break;

    case 3:
        if (_qdgdfv_scale2x) {
            if (_qdgdfv_pixel_size == 1)
                _qdgdfv_s3x_dump1_screen(_qdgdfv_virtual_screen,
                                         (char *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 2)
                _qdgdfv_s3x_dump2_screen(_qdgdfv_virtual_screen,
                                         (short *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 4)
                _qdgdfv_s3x_dump4_screen(_qdgdfv_virtual_screen,
                                         (int *) _double_screen);
        }
        else {
            if (_qdgdfv_pixel_size == 1)
                _qdgdfv_triple_dump1_screen(_qdgdfv_virtual_screen,
                                            (char *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 2)
                _qdgdfv_triple_dump2_screen(_qdgdfv_virtual_screen,
                                            (short *) _double_screen);
            else
            if (_qdgdfv_pixel_size == 4)
                _qdgdfv_triple_dump4_screen(_qdgdfv_virtual_screen,
                                            (int *) _double_screen);
        }

        break;
    }
}


/**
 * qdgdfv_dump_virtual_screen - Dumps the virtual screen.
 *
 * Dumps the virtual screen into the real one.
 * [Video Functions]
 */
void qdgdfv_dump_virtual_screen(void)
{
    if (_qdgdfv_accum_buffer) {
        int n;

        for (n = 0; n < _qdgdfv_screen_x_size * _qdgdfv_screen_y_size; n++)
            _qdgdfv_virtual_screen[n] =
                _qdgdfv_accum_table[_qdgdfv_virtual_screen[n]]
                [_qdgdfv_accum_buffer[n]];
    }

    drv->dump_virtual_screen();

    if (_qdgdfv_accum_buffer)
        memcpy(_qdgdfv_accum_buffer, _qdgdfv_virtual_screen,
               _qdgdfv_screen_x_size * _qdgdfv_screen_y_size);
}


/**
 * qdgdfv_assert_in_virtual_screen - Asserts that a pointer is inside the virtual screen.
 * @func: function where the test is happening
 * @ptr: the pointer
 *
 * Asserts that a pointer falls inside the virtual screen.
 * If it's outside (less than _qdgdfv_virtual_screen or further the
 * end of the virtual screen), aborts.
 */
void qdgdfv_assert_in_virtual_screen(char *func, unsigned char *ptr)
{
    int diff;

    diff = (int) (ptr - _qdgdfv_virtual_screen);

    if (diff < 0 || diff >= (_qdgdfv_screen_x_size * _qdgdfv_screen_y_size))
        qdgdfv_bang(func, qdgdfv_sprintf("virtual screen diff: %d", diff));
}


/**
 * qdgdfv_input_poll - Polls the input system.
 *
 * Polls the input system, setting the individual key variables
 * accordingly.
 * [Keyboard Functions]
 */
void qdgdfv_input_poll(void)
{
    drv->input_poll();
}


/**
 * qdgdfv_timer - Returns the elapsed time in microseconds.
 * @reset: reset flag
 *
 * Returns the elapsed time between calls, in milliseconds. If @reset
 * is set to 1, the timer is reset any time the function is called,
 * or accumulative otherwise. It's mainly used for calculating the
 * elapsed time per frame. It's wise to reset the timer just before
 * entering the main loop.
 * [Support Functions]
 */
int qdgdfv_timer(int reset)
{
    return (drv->timer(reset));
}


#define qdgdfv_max(a,b) ((a) > (b)) ? (a) : (b)

/**
 * qdgdfv_seek_color - Searches for the nearest matching color.
 * @r: the red part of the color
 * @g: the green part of the color
 * @b: the blue part of the color
 *
 * Searches the internal palette for the nearest color matching
 * the r, g and b values. This values must range from 0 to 255.
 * Returns the selected color.
 * [Video Functions]
 */
unsigned char qdgdfv_seek_color(int r, int g, int b)
{
    int n, i;
    int mindif;
    int best;
    unsigned int *pal;
    int rr, gg, bb;

    if (r > 255)
        r = 255;
    if (g > 255)
        g = 255;
    if (b > 255)
        b = 255;

    best = 255;
    mindif = 0x7fffffff;
    pal = _qdgdfv_palette;

    for (n = 0; n < 256; n++, pal += 3) {
        rr = abs(r - *pal);
        gg = abs(g - *(pal + 1));
        bb = abs(b - *(pal + 2));

        i = qdgdfv_max(rr, qdgdfv_max(gg, bb));

        if (mindif > i) {
            mindif = i;
            best = n;
        }
    }

    return (unsigned char) best;
}


/**
 * qdgdfv_build_light_table - Builds a light table.
 * @lut: the buffer where to store the light table
 * @levels: number of light levels
 * @mid: the level where color is 100%
 *
 * Builds a light table. The @lut argument must have enough size to
 * store (256 * levels) bytes, and be easily accessed (so it can wisely
 * be defined as unsigned char lut[levels][256]). The @mid value
 * is the level where color is 100% (i.e. equal to the color itself).
 * Below, colors fade to black and above colors saturate to white.
 * [Video Functions]
 */
void qdgdfv_build_light_table(unsigned char *lut, int levels, int mid)
{
    qdgdfv_build_light_table_ext(lut, levels, mid, 0, 0, 0);
}


/**
 * qdgdfv_build_light_table_ext - Builds a light table (extended).
 * @lut: the buffer where to store the light table
 * @levels: number of light levels
 * @mid: the level where color is 100%
 * @fr: red component of fade color
 * @fg: green component of fade color
 * @fb: blue component of fade color
 *
 * This function is an extended version of qdgdfv_build_light_table().
 * Instead of fading to black, this function allows to specify what
 * color the dark light levels fade to.
 * [Video Functions]
 */
void qdgdfv_build_light_table_ext(unsigned char *lut, int levels,
                  int mid, int fr, int fg, int fb)
{
    int n, m;
    int r, g, b;

    mid--;
    mid = levels - mid;

    for (n = 0; n < levels; n++) {
        for (m = 0; m < 255; m++) {
            r = _qdgdfv_palette[m * 3];
            g = _qdgdfv_palette[(m * 3) + 1];
            b = _qdgdfv_palette[(m * 3) + 2];

            /* old algorithm was r=(r*(n+mid))/levels; */

            r += ((fr - r) / levels) * (levels - (n + mid));
            g += ((fg - g) / levels) * (levels - (n + mid));
            b += ((fb - b) / levels) * (levels - (n + mid));

            lut[(n * 256) + m] = qdgdfv_seek_color(r, g, b);
        }

        lut[(n * 256) + 255] = 255;
    }
}


/**
 * qdgdfv_blend_color - Blends two colors into one.
 * @c1: first color
 * @c2: second color
 * @percent: percentage of blending
 *
 * Blends two colors into the nearest matching one. If @percent is 100,
 * the returned color will be @c1, if it's 0, @c2, or a blending between
 * both otherwise.
 * [Video Functions]
 */
unsigned char qdgdfv_blend_color(unsigned char c1, unsigned char c2, int percent)
{
    int r, g, b;
    int *p;

    if (percent == 100)
        return c1;
    if (percent == 0)
        return c2;

    p = (int *) &_qdgdfv_palette[(int) c1 * 3];

    r = (*(p++) * percent) / 100;
    g = (*(p++) * percent) / 100;
    b = (*p * percent) / 100;

    percent = 100 - percent;

    p = (int *) &_qdgdfv_palette[(int) c2 * 3];

    r += (*(p++) * percent) / 100;
    g += (*(p++) * percent) / 100;
    b += (*p * percent) / 100;

    return qdgdfv_seek_color(r, g, b);
}


/**
 * qdgdfv_set_accum_buffer - Sets or resets the accumulation buffer.
 * @percent: percentage of buffer lasting
 *
 * If @percent is set to a non zero value (the default), the contents
 * of the previous frame is blended with the actual one with the
 * specified percent.
 * [Video Functions]
 */
void qdgdfv_set_accum_buffer(int percent)
{
    int x, y;

    if (_qdgdfv_accum_buffer)
        free(_qdgdfv_accum_buffer);

    if (percent == 0)
        _qdgdfv_accum_buffer = NULL;
    else {
        /* alloc a buffer */
        _qdgdfv_accum_buffer = qdgdfv_malloc(_qdgdfv_screen_x_size *
                             _qdgdfv_screen_y_size);

        memset(_qdgdfv_accum_buffer, '\0', _qdgdfv_screen_x_size *
                            _qdgdfv_screen_y_size);

        /* build the table */
        for (y = 0; y < 256; y++)
            for (x = 0; x < 256; x++)
                _qdgdfv_accum_table[x][y] = qdgdfv_blend_color(y, x, percent);
    }
}


/**
 * qdgdfv_extended_key_status - Returns more status about a key.
 * @key_var: pointer to the wanted key variable (_qdgdfv_key_up, etc.)
 *
 * Returns extended status for the variable pointed by @key_var.
 * Returned values are: 0, key not pressed; 1, key just pressed;
 * 2, key pressed; 3, key just released; -1, no information about
 * the key is found.
 * [Keyboard Functions]
 */
int qdgdfv_extended_key_status(int *key_var)
{
    int n;
    int ret = -1;
    struct __qdgdfv_extended_key_status *xk;

    for (n = 0; ret == -1; n++) {
        xk = &_qdgdfv_extended_key_status[n];

        /* no more keys */
        if (xk->key_var == NULL)
            break;

        /* is this the wanted key? */
        if (xk->key_var == key_var) {
            if (*key_var == 0)
                ret = xk->last_val == 1 ? 3 : 0;
            else
                ret = xk->last_val == 1 ? 2 : 1;

            xk->last_val = *key_var;
        }
    }

    return ret;
}


/**
 * qdgdfv_write_tga - Writes a bitmap as a TGA file.
 * @fn: the file name
 * @bmp: the bitmap (or virtual screen)
 * @w: bitmap width
 * @h: bitmap height
 * @t: transparent color
 *
 * Writes the @bmp bitmap of size @w x @h as a TGA file. If @t is not -1,
 * it's the index of the transparent color.
 *
 * Returns -1 if the file could not be written or 0 otherwise.
 */
int qdgdfv_write_tga(char *fn, unsigned char *bmp, int w, int h, int t)
{
    int ret = 0;
    FILE *f;

    if ((f = fopen(fn, "wb")) != NULL) {
        unsigned char hdr[18];
        int n;

        memset(hdr, '\0', sizeof(hdr));

        hdr[2]  = 2;
        hdr[12] = w & 0xff;
        hdr[13] = w >> 8;
        hdr[14] = h & 0xff;
        hdr[15] = h >> 8;
        hdr[16] = 32;
        hdr[17] = 32;

        fwrite(hdr, sizeof(hdr), 1, f);

        for (n = 0; n < w * h; n++) {
            unsigned int *pal = &_qdgdfv_palette[bmp[n] * 3];

            fputc(pal[2], f);
            fputc(pal[1], f);
            fputc(pal[0], f);

            fputc((t == -1 || bmp[n] != t) ? 0xff : 0x00, f);
        }

        fclose(f);

    }
    else
        ret = -1;

    return ret;
}


/**
 * qdgdfv_home_dir - Returns the home user directory.
 *
 * Returns a system-dependent directory where the user can write
 * documents and create subdirectories.
 * [File Management]
 */
char *qdgdfv_home_dir(void)
{
    return _home_dir();
}


/**
 * qdgdfv_app_dir - Returns the applications directory.
 *
 * Returns a system-dependent directory where the applications store
 * their private data, as components or resources.
 * [File Management]
 */
char *qdgdfv_app_dir(void)
{
    return _app_dir();
}


/**
 * qdgdfv_opengl - Enables or disables the use of OpenGL.
 * @onoff: boolean value
 *
 * Enables or disables the use of OpenGL using the @onoff argument.
 * Returns 1 if the operation succeeded or 0 if not. When the OpenGL
 * mode is active, OpenGL code can be used before dumping the virtual
 * screen.
 * [Video Functions]
 */
int qdgdfv_opengl(int onoff)
{
    int ret = 0;

    if (drv->opengl != NULL)
        ret = drv->opengl(onoff);

    return ret;
}

/**
 * qdgdfv_dump_argb_screen - Dumps the ARGB virtual screen.
 *
 * Dumps the contents of the _qdgdfv_argb_screen virtual screen
 * onto the real screen.
 * [Video Functions]
 */
void qdgdfv_dump_argb_screen(void)
{
    if (drv->dump_argb_screen != NULL)
        drv->dump_argb_screen();
}


/**
 * qdgdfv_startup - Inits the video system.
 *
 * Starts up the video system.
 * [Video Functions]
 */
void qdgdfv_startup(void)
{
    char *logger;

    /* force logging */
    if ((logger = getenv("QDGDF_LOG")) != NULL) {
        _qdgdfv_use_logger = 1;
        strncpy(_qdgdfv_logger_file, logger, sizeof(_qdgdfv_logger_file) - 1);
        _qdgdfv_logger_file[sizeof(_qdgdfv_logger_file) - 1] = '\0';
    }

    /* scale setting */
    if (_qdgdfv_scale == 0)
        _qdgdfv_scale = _qdgdfv_double_mode ? 2 : 1;

    if (!TRY_VIDEO_DRIVERS())
        qdgdfv_bang("qdgdfv_startup", "No usable video driver found");

    qdgdfv_set_palette();

    atexit(qdgdfv_shutdown);
}


/**
 * qdgdfv_shutdown - Shuts down the video system.
 *
 * Shuts down the video system.
 * [Video Functions]
 */
void qdgdfv_shutdown(void)
{
    if (drv == NULL)
        return;

    drv->shutdown();

    drv = NULL;
}
