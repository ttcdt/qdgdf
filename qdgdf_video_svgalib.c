/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_video.h"

#ifdef CONFOPT_SVGALIB

#include <string.h>
#include <time.h>

#include <vga.h>
#include <vgakeyboard.h>


/** code **/

static void _qdgdfv_set_palette(void)
{
    int n;
    unsigned int *pal;

    pal = _qdgdfv_palette;

    for (n = 0; n < 256; n++, pal += 3)
        vga_setpalette(n, *pal >> 2, *(pal + 1) >> 2, *(pal + 2) >> 2);
}


static void _qdgdfv_dump_virtual_screen(void)
{
    memcpy(graph_mem, _qdgdfv_virtual_screen,
           _qdgdfv_screen_x_size * _qdgdfv_screen_y_size);
}


void _qdgdfv_input_poll(void)
{
    keyboard_update();

    _qdgdfv_key_up = keyboard_keypressed(0x48);
    _qdgdfv_key_down = keyboard_keypressed(0x50);
    _qdgdfv_key_left = keyboard_keypressed(0x4b);
    _qdgdfv_key_right = keyboard_keypressed(0x4d);
    _qdgdfv_key_escape = keyboard_keypressed(0x01);
    _qdgdfv_key_space = keyboard_keypressed(0x39);
    _qdgdfv_key_enter = keyboard_keypressed(0x1c);
    _qdgdfv_key_control = keyboard_keypressed(0x1d);
    _qdgdfv_key_shift_l = keyboard_keypressed(0x2a);
    _qdgdfv_key_shift_r = keyboard_keypressed(0x36);
    _qdgdfv_key_pgup = keyboard_keypressed(0x49);
    _qdgdfv_key_pgdn = keyboard_keypressed(0x51);
    _qdgdfv_key_home = keyboard_keypressed(0x47);
    _qdgdfv_key_end = keyboard_keypressed(0x4f);

    _qdgdfv_key_f1 = keyboard_keypressed(0x3b);
    _qdgdfv_key_f2 = keyboard_keypressed(0x3c);
    _qdgdfv_key_f3 = keyboard_keypressed(0x3d);
    _qdgdfv_key_f4 = keyboard_keypressed(0x3e);
    _qdgdfv_key_f5 = keyboard_keypressed(0x3f);
    _qdgdfv_key_f6 = keyboard_keypressed(0x40);
    _qdgdfv_key_f7 = keyboard_keypressed(0x41);
    _qdgdfv_key_f8 = keyboard_keypressed(0x42);
    _qdgdfv_key_f9 = keyboard_keypressed(0x43);
    _qdgdfv_key_f10 = keyboard_keypressed(0x44);
}


static int _qdgdfv_timer(int reset)
{
    static clock_t prev = 0;
    clock_t c, r;

    c = clock();
    r = c - prev;

    /* avoid timer wraps */
    if (r < 0)
        r = 0;

    if (reset)
        prev = c;

    return (r * 1000) / CLOCKS_PER_SEC;
}


static int _qdgdfv_startup(void)
{
    vga_init();

    _qdgdfv_scale = 1;

    /* only 320x200 supported by now */
    _qdgdfv_screen_x_size = 320;
    _qdgdfv_screen_y_size = 200;

    vga_setmode(G320x200x256);

    _qdgdfv_set_palette();

    keyboard_init();

    keyboard_translatekeys(TRANSLATE_CURSORKEYS);

    _qdgdfv_virtual_screen = (unsigned char *)
        qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size);

    qdgdfv_clear_virtual_screen();

    /* svgalib runs always fullscreen */
    _qdgdfv_full_screen = 1;

    qdgdfv_logger("qdgdfv_startup", "SVGALIB driver startup");

    return 1;
}


static void _qdgdfv_shutdown(void)
{
    vga_setmode(TEXT);
    keyboard_close();

    printf("\x1b[H\x1b[J\n");
}


/* driver information */

static struct _qdgdfv_driver drv = {
    "svgalib",
    _qdgdfv_set_palette,
    _qdgdfv_dump_virtual_screen,
    NULL,
    _qdgdfv_input_poll,
    _qdgdfv_timer,
    NULL,
    _qdgdfv_startup,
    _qdgdfv_shutdown
};


struct _qdgdfv_driver *svgalib_drv_detect(void)
/* detection function */
{
    if (_qdgdfv_startup())
        return &drv;

    return NULL;
}


#endif                          /* CONFOPT_SVGALIB */
