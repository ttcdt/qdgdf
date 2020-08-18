/*

    Extension to the Quick and Dirty Game Development Framework (QDGDF)

    Copyright (C) 2001 Daniel Compton  <C_Anon01@yahoo.com>

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"

#include "qdgdf_video_ext.h"

void qdgdfv_display_pcx(unsigned char *pcx, unsigned int w, unsigned int h, unsigned int x,
            unsigned int y)
{
    unsigned int sw = _qdgdfv_screen_x_size;    /* max screen width is sw */
    unsigned char *vscreen = _qdgdfv_virtual_screen + y * sw;
    unsigned int i;

    for (i = 0; i < h; i++) {
        memcpy(vscreen + x, pcx, w);
        vscreen += sw;
        pcx += w;
    }
}

int qdgdfv_display_pcx_safe(unsigned char *pcx, unsigned int w, unsigned int h, unsigned int x,
                unsigned int y)
{
    unsigned int sw = _qdgdfv_screen_x_size;    /* max screen width is sw */
    unsigned int sh = _qdgdfv_screen_y_size;    /* max screen heigh is sh */
    unsigned char *vscreen = _qdgdfv_virtual_screen;
    unsigned int i;

    if (x >= sw || y >= sh)
        return 0;

    if ((x + w) > sw)
        w = sw - x;
    if ((y + h) > sh)
        h = sh - y;

    vscreen += y * sw;
    for (i = 0; i < h; i++) {
        memcpy(vscreen + x, pcx, w);
        vscreen += sw;
        pcx += w;
    }

    return 1;
}

int qdgdfv_display_pcx_full(unsigned char *pcx, unsigned int w, unsigned int h, unsigned int x,
                unsigned int y)
{
    unsigned int sw = _qdgdfv_screen_x_size;    /* max screen width is sw */
    unsigned int sh = _qdgdfv_screen_y_size;    /* max screen heigh is sh */
    unsigned char *vscreen = _qdgdfv_virtual_screen;
    unsigned int i;

    if (w > sw || h > sh)
        return 0;

    if ((x + w) > sw) {
        x = sw - w;
    }
    if ((y + h) > sh) {
        y = sh - h;
    }

    vscreen += y * sw;
    for (i = 0; i < h; i++) {
        memcpy(vscreen + x, pcx, w);
        vscreen += sw;
        pcx += w;
    }

    return 1;
}

unsigned char qdgdfv_find_color(unsigned int r, unsigned int g, unsigned int b)
{
    unsigned int *table = _qdgdfv_palette;
    unsigned long lastcolor = abs(r - table[0]) + abs(g - table[1]) + abs(b - table[2]);
    unsigned int i = 3;
    unsigned int pos = 0;

    for (; i < 256 * 3; i += 3) {
        unsigned long curcolor =
            abs(r - table[i]) + abs(g - table[i + 1]) + abs(b - table[i + 2]);
        if (curcolor < lastcolor) {
            lastcolor = curcolor;
            pos = i;
        }
    }
    return pos / 3;
}

int qdgdfv_plot_pixel_color(unsigned int x, unsigned int y, unsigned char color)
{
    if (x < _qdgdfv_screen_x_size && y < _qdgdfv_screen_y_size) {
        _qdgdfv_virtual_screen[y * _qdgdfv_screen_x_size + x] = color;
        return 1;
    }
    return 0;
}

int qdgdfv_plot_pixel_rgb(unsigned int x, unsigned int y, unsigned long RGB)
{
    if (x < _qdgdfv_screen_x_size && y < _qdgdfv_screen_y_size) {
        _qdgdfv_virtual_screen[y * _qdgdfv_screen_x_size + x] =
            qdgdfv_find_color(GetRValue(RGB), GetGValue(RGB), GetBValue(RGB));
        return 1;
    }
    return 0;
}

int qdgdfv_draw_rect_fill(unsigned int x, unsigned int y, unsigned int w, unsigned int h,
              unsigned char color)
{
    unsigned int sw = _qdgdfv_screen_x_size;    /* max screen width is sw */
    unsigned int sh = _qdgdfv_screen_y_size;    /* max screen heigh is sh */
    unsigned long totsw = x + w;
    unsigned long totsh = y + h;
    if ((totsw <= sw) && (totsh <= sh)) {   /* if memset cant be sent a 0 length, then add (w != 0) */
        unsigned char *vscreen = _qdgdfv_virtual_screen + y * sw;
        unsigned int i = 0;
        for (; i < h; i++) {
            memset(vscreen + x, color, w);
            vscreen += sw;
        }
        return 1;
    }
    return 0;
}

/* wallw is number of pixels for size of the wall */
int qdgdfv_draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h,
             unsigned int wallw, unsigned char color)
{
    int result;
    result = qdgdfv_draw_hline(x, y, w, wallw, color);
    if (!result)
        return result;
    result = qdgdfv_draw_vline(x, y, h, wallw, color);
    if (!result)
        return result;
    result = qdgdfv_draw_hline(x, y + h - wallw, w, wallw, color);
    if (!result)
        return result;
    result = qdgdfv_draw_vline(x + w - wallw, y, h, wallw, color);
    return result;
}
