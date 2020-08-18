/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_video.h"

#ifdef CONFOPT_X11

#include <string.h>
#include <math.h>
#include <time.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <sys/time.h>

#ifndef WITHOUT_MIT_EXTENSIONS
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

#ifdef CONFOPT_OPENGL
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#endif

/** data **/

/* misc X11 info */

static Display *_x_display;
static int _x_screen;
static XVisualInfo _x_visualinfo;
static Window _x_window;
static Colormap _x_colormap;
static Visual *_x_visual;
static GC _x_gc;
static XEvent _x_event;
static XImage *_x_image;
static XColor _x_palette[256];
static int _x_bpp;

/* the double screen */

static unsigned char *_double_screen;

static int _mit_extensions = 0;

#ifndef WITHOUT_MIT_EXTENSIONS
int shm_major, shm_minor;
Bool shm_pixmaps;
XShmSegmentInfo _shm_seg_info;
#endif

/* opengl in use */
static int opengl_flag = 0;

#ifdef CONFOPT_OPENGL
GLXContext glxctx;
#endif


/** code **/

static void x_calc_shift(unsigned v, unsigned *mask, int *shift)
/* calcs masks and shifts */
{
    unsigned b;
    unsigned m;

    /* shift first */
    for (b = 0x80000000, *shift = 0; b; b >>= 1, (*shift)++) {
        if (b & v)
            break;
    }

    /* now masks */
    for (m = 0x80000000, *mask = 0; b; b >>= 1, (*mask) |= m, m >>= 1) {
        if (!(b & v))
            break;
    }
}


static void _qdgdfv_set_palette(void)
{
    int n;
    int *pal;

    pal = (int *) _qdgdfv_palette;

    if (_qdgdfv_pixel_size == 1) {
        short int r, g, b;

        for (n = 0; n < 256; n++) {
            r = (short) pal[n * 3] + _qdgdfv_gamma_correct;
            if (r > 255)
                r = 255;
            g = (short) pal[(n * 3) + 1] + _qdgdfv_gamma_correct;
            if (g > 255)
                g = 255;
            b = (short) pal[(n * 3) + 2] + _qdgdfv_gamma_correct;
            if (b > 255)
                b = 255;

            _x_palette[n].pixel = n;
            _x_palette[n].flags = DoRed | DoGreen | DoBlue;
            _x_palette[n].red = (r) << 8;
            _x_palette[n].green = (g) << 8;
            _x_palette[n].blue = (b) << 8;

            _qdgdfv_extended_palette[n] = n;
        }

        XStoreColors(_x_display, _x_colormap, _x_palette, 256);
    }
}


static void put_image(void)
{
    if (_mit_extensions) {
#ifndef WITHOUT_MIT_EXTENSIONS
        XShmPutImage(_x_display, _x_window, _x_gc,
                    _x_image, 0, 0, 0, 0,
                    _qdgdfv_screen_x_size * _qdgdfv_scale,
                    _qdgdfv_screen_y_size * _qdgdfv_scale,
                    False);

        XFlush(_x_display);
#endif
    }
    else {
        XPutImage(_x_display, _x_window, _x_gc,
                    _x_image, 0, 0, 0, 0, 
                    _qdgdfv_screen_x_size * _qdgdfv_scale,
                    _qdgdfv_screen_y_size * _qdgdfv_scale);

        XSync(_x_display, False);
    }
}


static void _qdgdfv_dump_argb_screen(void)
{
    _qdgdfv_scale_argb_screen((int *)_double_screen);

    put_image();
}


static void _qdgdfv_dump_virtual_screen(void)
{
    if (opengl_flag) {
#ifdef CONFOPT_OPENGL
        if (opengl_flag == 2)
            glXSwapBuffers(_x_display, _x_window);
        else
            glFlush();
#endif
    }
    else {
        _qdgdfv_scale_virtual_screen(_double_screen);
        put_image();
    }
}

/* macro doesnt require a function call, speed things up some in the input function */
#define qdgdfv_zero_2s_keys() { \
	if(_qdgdfv_key_up == 2) _qdgdfv_key_up = 0; \
	if(_qdgdfv_key_down == 2)  _qdgdfv_key_down = 0; \
	if(_qdgdfv_key_left == 2) _qdgdfv_key_left = 0; \
	if(_qdgdfv_key_right == 2) _qdgdfv_key_right = 0; \
	if(_qdgdfv_key_escape == 2) _qdgdfv_key_escape = 0; \
	if(_qdgdfv_key_space == 2) _qdgdfv_key_space = 0; \
	if(_qdgdfv_key_enter == 2) _qdgdfv_key_enter = 0; \
	if(_qdgdfv_key_control == 2) _qdgdfv_key_control = 0; \
	if(_qdgdfv_key_shift_l == 2) _qdgdfv_key_shift_l = 0; \
	if(_qdgdfv_key_shift_r == 2) _qdgdfv_key_shift_r = 0; \
	if(_qdgdfv_key_alnum == 2) _qdgdfv_key_alnum = 0; \
	if(_qdgdfv_key_pgup == 2) _qdgdfv_key_pgup = 0; \
	if(_qdgdfv_key_pgdn == 2) _qdgdfv_key_pgdn = 0; \
	if(_qdgdfv_key_home == 2) _qdgdfv_key_home = 0; \
	if(_qdgdfv_key_end == 2) _qdgdfv_key_end = 0; \
}

#define qdgdfv_key_set(keysym, s) { \
	switch((KeySym)keysym) \
	{ \
	case XK_Up: _qdgdfv_key_up = s; break; \
	case XK_Down: _qdgdfv_key_down = s; break; \
	case XK_Left: _qdgdfv_key_left = s; break; \
	case XK_Right: _qdgdfv_key_right = s; break; \
	case XK_Escape: _qdgdfv_key_escape = s; break; \
	case XK_space: _qdgdfv_key_space = s; break; \
	case XK_Return: _qdgdfv_key_enter = s; break; \
	case XK_Page_Up: _qdgdfv_key_pgup = s; break; \
	case XK_Page_Down: _qdgdfv_key_pgdn = s; break; \
	case XK_Home: _qdgdfv_key_home = s; break; \
	case XK_End: _qdgdfv_key_end = s; break; \
	case XK_F1: _qdgdfv_key_f1 = s; break; \
	case XK_F2: _qdgdfv_key_f2 = s; break; \
	case XK_F3: _qdgdfv_key_f3 = s; break; \
	case XK_F4: _qdgdfv_key_f4 = s; break; \
	case XK_F5: _qdgdfv_key_f5 = s; break; \
	case XK_F6: _qdgdfv_key_f6 = s; break; \
	case XK_F7: _qdgdfv_key_f7 = s; break; \
	case XK_F8: _qdgdfv_key_f8 = s; break; \
	case XK_F9: _qdgdfv_key_f9 = s; break; \
	case XK_F10: _qdgdfv_key_f10 = s; break; \
	case XK_Alt_L: _qdgdfv_key_alt_l = s; break; \
	case XK_Alt_R: _qdgdfv_key_alt_r = s; break; \
	/* Dan Compton added these changes */ \
	/* cannot distinguise between left and right control because windows doesn't */ \
	case XK_Control_L: \
	case XK_Control_R: _qdgdfv_key_control=s; break; \
	case XK_Shift_L: _qdgdfv_key_shift_l = s; break; \
	case XK_Shift_R: _qdgdfv_key_shift_r = s; break; \
	case XK_0: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '0'; break; \
	case XK_1: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '1'; break; \
	case XK_2: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '2'; break; \
	case XK_3: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '3'; break; \
	case XK_4: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '4'; break; \
	case XK_5: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '5'; break; \
	case XK_6: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '6'; break; \
	case XK_7: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '7'; break; \
	case XK_8: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '8'; break; \
	case XK_9: _qdgdfv_key_alnum = s; _qdgdfv_alnum = '9'; break; \
	case XK_a: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'a'; break; \
	case XK_b: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'b'; break; \
	case XK_c: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'c'; break; \
	case XK_d: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'd'; break; \
	case XK_e: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'e'; break; \
	case XK_f: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'f'; break; \
	case XK_g: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'g'; break; \
	case XK_h: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'h'; break; \
	case XK_i: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'i'; break; \
	case XK_j: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'j'; break; \
	case XK_k: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'k'; break; \
	case XK_l: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'l'; break; \
	case XK_m: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'm'; break; \
	case XK_n: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'n'; break; \
	case XK_o: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'o'; break; \
	case XK_p: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'p'; break; \
	case XK_q: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'q'; break; \
	case XK_r: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'r'; break; \
	case XK_s: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 's'; break; \
	case XK_t: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 't'; break; \
	case XK_u: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'u'; break; \
	case XK_v: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'v'; break; \
	case XK_w: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'w'; break; \
	case XK_x: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'x'; break; \
	case XK_y: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'y'; break; \
	case XK_z: _qdgdfv_key_alnum = s; _qdgdfv_alnum = 'z'; break; \
	} \
}

static void _qdgdfv_input_poll(void)
{
    KeySym k;
    KeySym lastkeysym = 0;
    int state;

    qdgdfv_zero_2s_keys();

    while (XPending(_x_display)) {
        XNextEvent(_x_display, &_x_event);

        if (_x_event.type == KeyPress) {
            lastkeysym =
                XKeycodeToKeysym(_x_display, _x_event.xkey.keycode, 0);
            qdgdfv_key_set(lastkeysym, 1);
        }
        else
        if (_x_event.type == KeyRelease) {
            k = XKeycodeToKeysym(_x_display, _x_event.xkey.keycode, 0);
            /* 2 indicates that the press will be removed next call */
            if (k == lastkeysym)
                state = 2;
            else
                state = 0;

            qdgdfv_key_set(k, state);
        }
    }
}


static int _qdgdfv_timer(int reset)
{
#ifndef WITHOUT_GETTIMEOFDAY

    static unsigned int prev = 0;
    unsigned int c;
    int r;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    c = (tv.tv_sec * 1000000) + tv.tv_usec;
    r = c - prev;

    /* avoid timer wraps */
    if (r < 0)
        r = 0;

    if (reset)
        prev = c;

    return r / 1000;

#else                           /* using more standard but less accurate clock() */

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
#endif
}


#ifdef CONFOPT_OPENGL

static int attr_list_sgl[] = {
    GLX_RGBA,
    GLX_RED_SIZE, 4,
    GLX_GREEN_SIZE, 4,
    GLX_BLUE_SIZE, 4,
    GLX_DEPTH_SIZE, 16,
    None
};

static int attr_list_dbl[] = {
    GLX_RGBA,
    GLX_DOUBLEBUFFER,
    GLX_RED_SIZE, 4,
    GLX_GREEN_SIZE, 4,
    GLX_BLUE_SIZE, 4,
    GLX_DEPTH_SIZE, 16,
    None
};
#endif /* CONFOPT_OPENGL */

static int _qdgdfv_opengl(int onoff)
{
    int ret = 0;

#ifdef CONFOPT_OPENGL
    opengl_flag = onoff;

    if (onoff) {
        XVisualInfo *vi;

        vi = glXChooseVisual(_x_display, _x_screen, attr_list_dbl);

        if (vi == NULL) {
            vi = glXChooseVisual(_x_display, _x_screen, attr_list_sgl);
            opengl_flag = 1;
        }
        else
            opengl_flag = 2;

        if (vi == NULL) {
            qdgdfv_logger("qdgdfv_opengl", "glXChooseVisual() failed");
            opengl_flag = 0;
        }
        else {
            glxctx = glXCreateContext(_x_display, vi, 0, GL_TRUE);

            glXMakeCurrent(_x_display, _x_window, glxctx);

            qdgdfv_logger("qdgdfv_opengl",
                          glXIsDirect(_x_display, glxctx) ?
                          "DRI enabled" : "DRI not available");

            ret = 1;
        }
    }
    else {
        /* disable OpenGL */
        /* ... */
        opengl_flag = 0;
        ret = 1;
    }

#endif

    return ret;
}


static int _qdgdfv_startup(void)
{
    unsigned long attrmask;
    XSetWindowAttributes attrs;
    XGCValues xgcvalues;
    XSizeHints hints;

    if (_qdgdfv_scale > 3)
        _qdgdfv_scale = 3;

    _x_display = XOpenDisplay(_qdgdfv_additional_info);

    if (!_x_display) {
        qdgdfv_logger("qdgdfv_startup", "Bad display");
        return 0;
    }

#ifndef WITHOUT_MIT_EXTENSIONS
    if (XShmQueryVersion(_x_display, &shm_major, &shm_minor, &shm_pixmaps))
        _mit_extensions = 1;
#endif

    _x_screen = DefaultScreen(_x_display);
    _x_bpp = DefaultDepth(_x_display, _x_screen);

    switch (_x_bpp) {
    case 8:
        _qdgdfv_pixel_size = 1;
        break;
    case 15:
    case 16:
        _qdgdfv_pixel_size = 2;
        break;
    case 24:
    case 32:
        _qdgdfv_pixel_size = 4;
        break;
    }

    if (!XMatchVisualInfo(_x_display, _x_screen, _x_bpp,
                          _x_bpp == 8 ? PseudoColor : TrueColor,
                          &_x_visualinfo)) {
        qdgdfv_logger("qdgdfv_startup", "XMatchVisualInfo error");
        return 0;
    }

    /* calculate color masks */
    if (_qdgdfv_pixel_size > 1) {
        x_calc_shift(_x_visualinfo.red_mask, &_qdgdfv_red_mask,
                     &_qdgdfv_red_shift);
        x_calc_shift(_x_visualinfo.green_mask, &_qdgdfv_green_mask,
                     &_qdgdfv_green_shift);
        x_calc_shift(_x_visualinfo.blue_mask, &_qdgdfv_blue_mask,
                     &_qdgdfv_blue_shift);

        qdgdfv_logger("qdgdfv_startup",
                      qdgdfv_sprintf
                      ("X11 TrueColor bpp: %d pixelsize: %d [%02X,%d,%02X,%d,%02X,%d]",
                       _x_bpp, _qdgdfv_pixel_size,
                       _qdgdfv_red_mask, _qdgdfv_red_shift,
                       _qdgdfv_green_mask, _qdgdfv_green_shift,
                       _qdgdfv_blue_mask, _qdgdfv_blue_shift)
            );
    }

    _x_visual = _x_visualinfo.visual;

    _x_colormap = XCreateColormap(_x_display,
                                  RootWindow(_x_display, _x_screen),
                                  _x_visual,
                                  _x_bpp == 8 ? AllocAll : AllocNone);

    attrmask = CWEventMask | CWColormap | CWBorderPixel;
    attrs.event_mask = KeyPressMask | KeyReleaseMask | ExposureMask;
    attrs.colormap = _x_colormap;
    attrs.border_pixel = 0;

    _x_window = XCreateWindow(_x_display,
                                  RootWindow(_x_display, _x_screen),
                                  _qdgdfv_window_x, _qdgdfv_window_y,
                                  _qdgdfv_screen_x_size * _qdgdfv_scale,
                                  _qdgdfv_screen_y_size * _qdgdfv_scale,
                                  0, _x_bpp,
                                  InputOutput, _x_visual, attrmask,
                                  &attrs);

    hints.width = hints.min_width = hints.max_width =
            _qdgdfv_screen_x_size * _qdgdfv_scale;

    hints.height = hints.min_height = hints.max_height =
            _qdgdfv_screen_y_size * _qdgdfv_scale;


    hints.flags = PPosition | PSize | PMinSize | PMaxSize;
    XSetWMNormalHints(_x_display, _x_window, &hints);

    xgcvalues.graphics_exposures = False;

    _x_gc = XCreateGC(_x_display, _x_window, GCGraphicsExposures, &xgcvalues);

    XMapWindow(_x_display, _x_window);

    for (;;) {
        XNextEvent(_x_display, &_x_event);

        if (_x_event.type == Expose && !_x_event.xexpose.count)
            break;
    }

    if (_mit_extensions) {
#ifndef WITHOUT_MIT_EXTENSIONS
        memset(&_shm_seg_info, '\0', sizeof(XShmSegmentInfo));

        _x_image = XShmCreateImage(_x_display, _x_visual,
                                       _x_bpp, ZPixmap, 0, &_shm_seg_info,
                                       _qdgdfv_screen_x_size * _qdgdfv_scale,
                                       _qdgdfv_screen_y_size * _qdgdfv_scale);

        _shm_seg_info.shmid = shmget(IPC_PRIVATE,
                                         _x_image->bytes_per_line *
                                         _x_image->height,
                                         IPC_CREAT | 0777);

        if (_shm_seg_info.shmid < 0) {
            qdgdfv_logger("shmget", "shmid < 0");
            return 0;
        }

        _shm_seg_info.shmaddr = shmat(_shm_seg_info.shmid, NULL, 0);
        _shm_seg_info.readOnly = False;

        _x_image->data = _shm_seg_info.shmaddr;

        if (_qdgdfv_pixel_size == 1 && _qdgdfv_scale == 1)
            _qdgdfv_virtual_screen = (unsigned char *) _x_image->data;
        else {
            _qdgdfv_virtual_screen = (unsigned char *)
                qdgdfv_malloc(_qdgdfv_screen_x_size *
                              _qdgdfv_screen_y_size);
            _double_screen = (unsigned char *) _x_image->data;
        }

        XShmAttach(_x_display, &_shm_seg_info);

        qdgdfv_logger("qdgdfv_startup", "using MIT X extensions");
#endif
    }
    else {
        _qdgdfv_virtual_screen = (unsigned char *)
            qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size);

        if (_qdgdfv_pixel_size > 1 || _qdgdfv_scale > 1)
            _double_screen = qdgdfv_malloc(_qdgdfv_screen_x_size *
                                       _qdgdfv_screen_y_size *
                                       _qdgdfv_scale * _qdgdfv_scale *
                                       _qdgdfv_pixel_size);

        _x_image = XCreateImage(_x_display, _x_visual,
                                    _x_bpp, ZPixmap, 0,
                                    _qdgdfv_pixel_size == 1 && _qdgdfv_scale == 1 ?
                                    (char *) _qdgdfv_virtual_screen :
                                    (char *) _double_screen,
                                    _qdgdfv_screen_x_size * _qdgdfv_scale,
                                    _qdgdfv_screen_y_size * _qdgdfv_scale, 32,
                                    _qdgdfv_screen_x_size * _qdgdfv_scale *
                                    _qdgdfv_pixel_size);
    }

    if (_qdgdfv_pixel_size == 4) {
        if (_qdgdfv_scale == 1)
            _qdgdfv_argb_screen = (int *)_double_screen;
        else
            _qdgdfv_argb_screen = (int *)
                qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size * sizeof(int));
    }

    XStoreName(_x_display, _x_window, _qdgdfv_window_title);

    if (_qdgdfv_window_x != -1 && _qdgdfv_window_y != -1)
        XMoveWindow(_x_display, _x_window, _qdgdfv_window_x,
                    _qdgdfv_window_y);

    _qdgdfv_set_palette();

    qdgdfv_clear_virtual_screen();

    /* x11 always run windowed */
    _qdgdfv_full_screen = 0;

    qdgdfv_logger("qdgdfv_startup", "X11 Driver startup");
    return 1;
}


static void _qdgdfv_shutdown(void)
{
    if (_mit_extensions) {
#ifndef WITHOUT_MIT_EXTENSIONS
        XShmDetach(_x_display, &_shm_seg_info);
        XDestroyImage(_x_image);
        shmdt(_shm_seg_info.shmaddr);
        shmctl(_shm_seg_info.shmid, IPC_RMID, NULL);
#endif
    }
    else
        XDestroyImage(_x_image);

    XFreeGC(_x_display, _x_gc);
    XDestroyWindow(_x_display, _x_window);
    XCloseDisplay(_x_display);

    qdgdfv_logger("qdgdfv_startup", "X11 Driver shutdown");
}


/* driver information */

static struct _qdgdfv_driver drv = {
    "x11",
    _qdgdfv_set_palette,
    _qdgdfv_dump_virtual_screen,
    _qdgdfv_dump_argb_screen,
    _qdgdfv_input_poll,
    _qdgdfv_timer,
    _qdgdfv_opengl,
    _qdgdfv_startup,
    _qdgdfv_shutdown
};


struct _qdgdfv_driver *x11_drv_detect(void)
/* detection function */
{
    if (_qdgdfv_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_X11 */
