/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_video.h"

#ifdef CONFOPT_DDRAW

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#include <windows.h>
#include <ddraw.h>
#include <mmsystem.h>

/* #define NEWKEYCATCH 1 */


/** data **/

HINSTANCE hinst;
HWND hwnd;
LPDIRECTDRAW ddraw;
LPDIRECTDRAWSURFACE dsurface;
LPDIRECTDRAWSURFACE dback;
DDSURFACEDESC ddsd;
DDSCAPS ddsc;
LPDIRECTDRAWPALETTE dpal;
LPDIRECTDRAWCLIPPER clipper;

#if !NEWKEYCATCH
/* keyboard scancodes */
static int _scan_codes[128];
#else
/* Dan Compton added these 3 variables */
static UINT vkey;
static int keyisdown;
static int oem_scan_code;
#endif
static unsigned char *_locked_screen;


/** code **/

static void _qdgdfv_set_palette(void)
{
    int n;
    PALETTEENTRY p[256];
    unsigned int *pal;
    unsigned int r, g, b;

    if (_qdgdfv_pixel_size == 1) {
        pal = _qdgdfv_palette;

        for (n = 0; n < 256; n++, pal += 3) {
            if ((r = (*pal) + _qdgdfv_gamma_correct) > 255)
                r = 255;

            if ((g = *(pal + 1) + _qdgdfv_gamma_correct) > 255)
                g = 255;

            if ((b = *(pal + 2) + _qdgdfv_gamma_correct) > 255)
                b = 255;

            p[n].peRed = r;
            p[n].peGreen = g;
            p[n].peBlue = b;
            p[n].peFlags = 0;

            _qdgdfv_extended_palette[n] = n;
        }

        if (ddraw->lpVtbl->
            CreatePalette(ddraw, DDPCAPS_8BIT | DDPCAPS_ALLOW256, p, &dpal,
                          NULL) != DD_OK)
            qdgdfv_bang("SetPalette", "CreatePalette error");

        if (dsurface->lpVtbl->SetPalette(dsurface, dpal) != DD_OK)
            qdgdfv_bang("SetPalette", "SetPalette error");
    }
}


static void _qdgdfv_dump_virtual_screen(void)
{
    /* locks */
    if (dback->lpVtbl->Lock(dback, NULL, &ddsd,
                            DDLOCK_WAIT | DDLOCK_WRITEONLY,
                            NULL) != DD_OK) {
        /* restores */
        dback->lpVtbl->Restore(dback);

        /* tries again */
        if (dback->lpVtbl->Lock(dback, NULL, &ddsd,
                                DDLOCK_WAIT | DDLOCK_WRITEONLY,
                                NULL) != DD_OK)
            qdgdfv_bang("DumpScreen", "Lock error");
    }

    _locked_screen = (char *) ddsd.lpSurface;

    switch (_qdgdfv_scale) {
    case 1:
        memcpy(_locked_screen, _qdgdfv_virtual_screen,
               _qdgdfv_screen_x_size * _qdgdfv_screen_y_size);

        break;

    case 2:

        if (_qdgdfv_scale2x)
            _qdgdfv_s2x_dump1_screen(_qdgdfv_virtual_screen,
                                     _locked_screen);
        else
            _qdgdfv_double_dump1_screen(_qdgdfv_virtual_screen,
                                        _locked_screen);

        break;
    }

    dback->lpVtbl->Unlock(dback, ddsd.lpSurface);

    dsurface->lpVtbl->Flip(dsurface, NULL, DDFLIP_WAIT);
}


void _qdgdfv_input_poll(void)
{
    MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

#if NEWKEYCATCH
    switch (vkey) {
    case VK_UP:
        _qdgdfv_key_up = keyisdown;
        break;
    case VK_DOWN:
        _qdgdfv_key_down = keyisdown;
        break;
    case VK_LEFT:
        _qdgdfv_key_left = keyisdown;
        break;
    case VK_RIGHT:
        _qdgdfv_key_right = keyisdown;
        break;
    case VK_ESCAPE:
        _qdgdfv_key_right = keyisdown;
        break;
    case VK_SPACE:
        _qdgdfv_key_right = keyisdown;
        break;
    case VK_RETURN:
        _qdgdfv_key_right = keyisdown;
        break;
    case VK_CONTROL:
        _qdgdfv_key_control = keyisdown;
        break;
    case VK_PRIOR:
        _qdgdfv_key_pgup = keyisdown;
        break;
    case VK_NEXT:
        _qdgdfv_key_pgdn = keyisdown;
        break;
    case VK_HOME:
        _qdgdfv_key_home = keyisdown;
        break;
    case VK_END:
        _qdgdfv_key_end = keyisdown;
        break;
    case VK_F1:
        _qdgdfv_key_f1 = keyisdown;
        break;
    case VK_SHIFT:
        if (oem_scan_code == 0x2a)
            _qdgdfv_key_shift_l = keyisdown;
        else if (oem_scan_code == 0x36)
            _qdgdfv_key_shift_r = keyisdown;
        break;
    default:
        if (isalnum((unsigned char) vkey)) {
            _qdgdfv_key_alnum = keyisdown;
            _qdgdfv_alnum = vkey;
        }
    }
#else
    _qdgdfv_key_up = _scan_codes[0x48];
    _qdgdfv_key_down = _scan_codes[0x50];
    _qdgdfv_key_left = _scan_codes[0x4b];
    _qdgdfv_key_right = _scan_codes[0x4d];
    _qdgdfv_key_escape = _scan_codes[0x01];
    _qdgdfv_key_space = _scan_codes[0x39];
    _qdgdfv_key_enter = _scan_codes[0x1c];
    _qdgdfv_key_control = _scan_codes[0x1d];
    _qdgdfv_key_pgup = _scan_codes[0x49];
    _qdgdfv_key_pgdn = _scan_codes[0x51];
    _qdgdfv_key_home = _scan_codes[0x47];
    _qdgdfv_key_end = _scan_codes[0x4f];
    /* _qdgdfv_key_control_r = _scan_codes[0x1d];
       _qdgdfv_key_control_r=_scan_codes[0x36]; 
       0x36 is right shift, windows does not differ between left and right control keys, both are 0x1d
     */
    _qdgdfv_key_shift_l = _scan_codes[0x2a];
    _qdgdfv_key_shift_r = _scan_codes[0x36];

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
#endif


}


#ifndef STDCALL
#define STDCALL __stdcall
#endif

long CALLBACK WndProc(HWND hwnd, UINT msg, UINT wparam, LONG lparam)
{
    int k;

    switch (msg) {
    case WM_SETCURSOR:

        SetCursor(NULL);
        return 0;

    case WM_CHAR:

        if (isalnum(wparam)) {
            _qdgdfv_key_alnum = 1;
            _qdgdfv_alnum = wparam;
        }

        return 0;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        k = (lparam >> 16) & 0xff;
        _scan_codes[k] = 1;

        _qdgdfv_key_alt_l = GetKeyState(VK_LMENU) & 0x8000;

        return 0;

    case WM_KEYUP:
        k = (lparam >> 16) & 0xff;
        _scan_codes[k] = 0;

        _qdgdfv_key_alnum = 0;

        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SYSCOMMAND:

        switch (wparam) {
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:

            /* disable screensavings */
            return 0;
        }

        break;

    case MM_MCINOTIFY:

/*		  vlogger("WndProc","MM_MCINOTIFY");
		_cd_playing=0; */
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}


static int _qdgdfv_timer(int reset)
{
    static int prev = 0;
    int c, r;

    c = GetTickCount();
    r = c - prev;

    /* avoid timer wraps */
    if (r < 0)
        r = 0;

    if (reset)
        prev = c;

    return r;
}


static int _qdgdfv_startup(void)
{
    WNDCLASS wc;

    if (_qdgdfv_full_screen == -1)
        _qdgdfv_full_screen = 1;

    /* reject windowed mode */
    if (_qdgdfv_full_screen == 0)
        return 0;

    if (_qdgdfv_scale > 2)
        _qdgdfv_scale = 2;

    hinst = (HINSTANCE) _qdgdfv_additional_int_info;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinst;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "qdgdf";

    if (!RegisterClass(&wc)) {
        qdgdfv_logger("qdgdfv_startup", "RegisterClass error");
        return 0;
    }

    hwnd = CreateWindow("qdgdf", _qdgdfv_window_title,
                        WS_POPUP,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinst,
                        NULL);

    if (hwnd == NULL) {
        qdgdfv_logger("qdgdfv_startup", "CreateWindow error");
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetCursor(NULL);

    if (DirectDrawCreate(NULL, &ddraw, NULL) != DD_OK) {
        qdgdfv_logger("qdgdfv_startup", "DirectDrawCreate error");
        return 0;
    }

    _qdgdfv_pixel_size = 1;

    if (ddraw->lpVtbl->SetCooperativeLevel(ddraw, hwnd,
                                           DDSCL_EXCLUSIVE |
                                           DDSCL_FULLSCREEN) != DD_OK) {
        qdgdfv_logger("qdgdfv_startup", "SetCooperativeLevel error");
        return 0;
    }

    if (ddraw->lpVtbl->SetDisplayMode(ddraw,
                                      _qdgdfv_screen_x_size,
                                      _qdgdfv_screen_y_size, 8) != DD_OK) {
        _qdgdfv_scale = 2;

        qdgdfv_logger("qdgdfv_startup", "switching to scale 2");
    }
    else
        _qdgdfv_scale = 1;

    /* this cannot be an else from previous if */

    if (_qdgdfv_scale == 2) {
        if (ddraw->lpVtbl->SetDisplayMode(ddraw,
                                          _qdgdfv_screen_x_size * 2,
                                          _qdgdfv_screen_y_size * 2,
                                          8) != DD_OK) {
            qdgdfv_logger("qdgdfv_startup", "SetDisplayMode error");
            return 0;
        }
    }

    /* get currently set mode */

    memset(&ddsd, '\0', sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_ALL;

    ddraw->lpVtbl->GetDisplayMode(ddraw, &ddsd);

    qdgdfv_logger("qdgdfv_startup",
                  qdgdfv_sprintf("GetDisplayMode: %d x %d", ddsd.dwWidth,
                                 ddsd.dwHeight)
        );

    if (ddsd.dwWidth != _qdgdfv_screen_x_size * _qdgdfv_scale ||
        ddsd.dwHeight != _qdgdfv_screen_y_size * _qdgdfv_scale) {
        qdgdfv_logger("qdgdfv_startup", "bad resolution");
        return 0;
    }

    /* primary surface */

    memset(&ddsd, '\0', sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps =
        DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;

    if (ddraw->lpVtbl->CreateSurface(ddraw, &ddsd, &dsurface, NULL) !=
        DD_OK) {
        qdgdfv_logger("qdgdfv_startup", "CreateSurface error");
        return 0;
    }

    /* obtains the backbuffer */

    ddsc.dwCaps = DDSCAPS_BACKBUFFER;

    if (dsurface->lpVtbl->GetAttachedSurface(dsurface, &ddsc, &dback) !=
        DD_OK) {
        qdgdfv_logger("qdgdfv_startup", "GetAttachedSurface error");
        return 0;
    }

    SetCursorPos(0, 0);

    _qdgdfv_set_palette();

    _qdgdfv_virtual_screen = (unsigned char *)
        qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size);

    qdgdfv_clear_virtual_screen();

    qdgdfv_logger("qdgdfv_startup", "DirectDraw driver startup");

    return 1;
}


static void _qdgdfv_shutdown(void)
{
    dsurface->lpVtbl->Release(dsurface);
    ddraw->lpVtbl->Release(ddraw);

    SendMessage(hwnd, WM_CLOSE, 0, 0);

    qdgdfv_logger("qdgdfv_startup", "DirectDraw driver shutdown");
}


/* driver information */

static struct _qdgdfv_driver drv = {
    "ddraw",
    _qdgdfv_set_palette,
    _qdgdfv_dump_virtual_screen,
    NULL,
    _qdgdfv_input_poll,
    _qdgdfv_timer,
    NULL,
    _qdgdfv_startup,
    _qdgdfv_shutdown
};


struct _qdgdfv_driver *ddraw_drv_detect(void)
/* detection function */
{
    if (_qdgdfv_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_DDRAW */
