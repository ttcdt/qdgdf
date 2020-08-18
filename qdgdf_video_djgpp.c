/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_video.h"

#ifdef CONFOPT_DJGPP

#include <string.h>
#include <math.h>
#include <time.h>

#include <dpmi.h>
#include <pc.h>
#include <sys/movedata.h>


/** data **/

#define KBD_INT 0x9

static _go32_dpmi_seginfo oldkbdisr;
static _go32_dpmi_seginfo kbdisr;

static int _scan_codes[128];

#define KEY_DOWN(sc) _scan_codes[sc]

unsigned char _last_scan_code;


/** code **/

static int _set_video_mode(int mode)
{
    __dpmi_regs regs;

    regs.x.ax = mode;
    __dpmi_int(0x10, &regs);
}


static void _kbd_isr(void)
{
    unsigned char k;
    unsigned char s;
    int release;

    k = inportb(0x60);

    s = inportb(0x61);
    outportb(0x61, s | 0x80);
    outportb(0x61, s);

    if (k & 0x80) {
        release = 1;
        k &= 0x7f;
    }
    else
        release = 0;

    _scan_codes[k] = !release;

    _last_scan_code = k;

    outportb(0x20, 0x20);
}


static void _qdgdfv_set_palette(void)
{
    int n;
    unsigned int *pal;

    pal = _qdgdfv_palette;

    outportb(0x3c8, 0);

    for (n = 0; n < 256; n++, pal += 3) {
        outportb(0x3c9, ((unsigned char) (*pal)) >> 2);
        outportb(0x3c9, ((unsigned char) *(pal + 1)) >> 2);
        outportb(0x3c9, ((unsigned char) *(pal + 2)) >> 2);
    }
}


static void _qdgdfv_dump_virtual_screen(void)
{
    dosmemput(_qdgdfv_virtual_screen,
              _qdgdfv_screen_x_size * _qdgdfv_screen_y_size, 0xa0000);
}


void _qdgdfv_input_poll(void)
{
    _qdgdfv_key_up = _scan_codes[0x48];
    _qdgdfv_key_down = _scan_codes[0x50];
    _qdgdfv_key_left = _scan_codes[0x4b];
    _qdgdfv_key_right = _scan_codes[0x4d];
    _qdgdfv_key_escape = _scan_codes[0x01];
    _qdgdfv_key_space = _scan_codes[0x39];
    _qdgdfv_key_enter = _scan_codes[0x1c];
    _qdgdfv_key_control = _scan_codes[0x1d];
    _qdgdfv_key_shift_l = _scan_codes[0x2a];
    _qdgdfv_key_shift_r = _scan_codes[0x36];
    _qdgdfv_key_pgup = _scan_codes[0x49];
    _qdgdfv_key_pgdn = _scan_codes[0x51];
    _qdgdfv_key_home = _scan_codes[0x47];
    _qdgdfv_key_end = _scan_codes[0x4f];

    _qdgdfv_key_f1 = _scan_codes[0x3b];
    _qdgdfv_key_f2 = _scan_codes[0x3c];
    _qdgdfv_key_f3 = _scan_codes[0x3d];
    _qdgdfv_key_f4 = _scan_codes[0x3e];
    _qdgdfv_key_f5 = _scan_codes[0x3f];
    _qdgdfv_key_f6 = _scan_codes[0x40];
    _qdgdfv_key_f7 = _scan_codes[0x41];
    _qdgdfv_key_f8 = _scan_codes[0x42];
    _qdgdfv_key_f9 = _scan_codes[0x43];
    _qdgdfv_key_f10 = _scan_codes[0x44];
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
    _qdgdfv_scale = 1;

    /* only 320x200 supported by now */
    _qdgdfv_screen_x_size = 320;
    _qdgdfv_screen_y_size = 200;

    _set_video_mode(0x13);

    _qdgdfv_set_palette();


    /* install keyboard ISR */
    _go32_dpmi_get_protected_mode_interrupt_vector(KBD_INT, &oldkbdisr);

    kbdisr.pm_offset = (int) _kbd_isr;
    _go32_dpmi_allocate_iret_wrapper(&kbdisr);

    _go32_dpmi_set_protected_mode_interrupt_vector(KBD_INT, &kbdisr);

    _last_scan_code = 0;

    memset(_scan_codes, '\0', sizeof(_scan_codes));

    _qdgdfv_virtual_screen = (unsigned char *)
        qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size);

    qdgdfv_clear_virtual_screen();

    /* always fullscreen */
    _qdgdfv_full_screen = 1;

    qdgdfv_logger("qdgdfv_startup", "DJGPP driver startup");

    return 1;
}


static void _qdgdfv_shutdown(void)
{
    _set_video_mode(0x3);

    _go32_dpmi_set_protected_mode_interrupt_vector(KBD_INT, &oldkbdisr);
}


/* driver information */

static struct _qdgdfv_driver drv = {
    "djgpp",
    _qdgdfv_set_palette,
    _qdgdfv_dump_virtual_screen,
    NULL,
    _qdgdfv_input_poll,
    _qdgdfv_timer,
    NULL,
    _qdgdfv_startup,
    _qdgdfv_shutdown
};


struct _qdgdfv_driver *djgpp_drv_detect(void)
/* detection function */
{
    if (_qdgdfv_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_DJGPP */
