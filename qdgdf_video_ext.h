/*

    Extension to the Quick and Dirty Game Development Framework (QDGDF)

    Copyright (C) 2001 Daniel Compton  <C_Anon01@yahoo.com>

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#ifndef QDGDF_VIDEO_EXT_H_
#define QDGDF_VIDEO_EXT_H_

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "qdgdf_video.h"

#define RGB(r, g, b) (((unsigned char)(r) | ((unsigned short)((unsigned char)(g)) << 8)) | \
            (((unsigned int)(unsigned char)(b)) << 16))

#define GetRValue(rgb) ((unsigned char)(rgb))
#define GetGValue(rgb) ((unsigned char)(((unsigned short)(rgb)) >> 8))
#define GetBValue(rgb) ((unsigned char)((rgb) >> 16))

/* no protections on any memory overwrite errors */
void qdgdfv_display_pcx(unsigned char *pcx, unsigned int w, unsigned int h,
                        unsigned int x, unsigned int y);

/* safe: this will cut the image off if it will not fit in the virtual screen */
/* returns 0 if the image will not fit at all (no writting will be done), 1 otherwise */
int qdgdfv_display_pcx_safe(unsigned char *pcx, unsigned int w,
                            unsigned int h, unsigned int x,
                            unsigned int y);

/* full: this will move the image so that the whole image will be viewable and not cut off */
/* returns 0 if the image will not fit at all (no writting will be done), 1 otherwise */
int qdgdfv_display_pcx_full(unsigned char *pcx, unsigned int w,
                            unsigned int h, unsigned int x,
                            unsigned int y);

unsigned char qdgdfv_find_color(unsigned int r, unsigned int g,
                                unsigned int b);

int qdgdfv_plot_pixel_color(unsigned int x, unsigned int y,
                            unsigned char color);

int qdgdfv_plot_pixel_rgb(unsigned int x, unsigned int y,
                          unsigned long RGB);

int qdgdfv_draw_rect_fill(unsigned int x, unsigned int y, unsigned int w,
                          unsigned int h, unsigned char color);

#define qdgdfv_draw_hline(x, y, w, thick, color) \
  qdgdfv_draw_rect_fill((unsigned int)x, (unsigned int)y, (unsigned int)w, (unsigned int)thick, (unsigned char)color)

#define qdgdfv_draw_vline(x, y, h, thick, color) \
  qdgdfv_draw_rect_fill((unsigned int)x, (unsigned int)y, (unsigned int)thick, (unsigned int)h, (unsigned char)color)

int qdgdfv_draw_rect(unsigned int x, unsigned int y, unsigned int w,
                     unsigned int h, unsigned int wallw,
                     unsigned char color);

#define qdgdfv_clear_screen_at(x, y, w, h) \
  qdgdfv_draw_rect_fill((unsigned int)x, (unsigned int)y, (unsigned int)w, (unsigned int)h, \
          _qdgdfv_clear_color)

#endif                          /* QDGDF_VIDEO_EXT_H_ */
