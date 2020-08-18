/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include "config.h"
#include <stdio.h>
#include "qdgdf_video.h"

#ifdef CONFOPT_WIN32GDI

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

HINSTANCE hinst = NULL;
HWND hwnd;
HDC hdc;

#ifdef CONFOPT_OPENGL
HGLRC hrc;
#endif

/* keyboard scancodes */
static int _scan_codes[128];

/* the double screen */
static unsigned char *_double_screen;

/* the bitmap info */
BITMAPINFO bmi;

/* opengl in use */
static int opengl_flag = 0;


/** code **/

static void draw(HWND hwnd)
{
    PAINTSTRUCT ps;

    if (opengl_flag) {
        SwapBuffers(hdc);
    }
    else {
        hdc = BeginPaint(hwnd, &ps);

        SetDIBitsToDevice(hdc, 0, 0,
                          _qdgdfv_screen_x_size * _qdgdfv_scale,
                          _qdgdfv_screen_y_size * _qdgdfv_scale,
                          0,
                          0,
                          0,
                          _qdgdfv_screen_y_size * _qdgdfv_scale,
                          _double_screen, &bmi, 0);

        EndPaint(hwnd, &ps);
    }
}


long CALLBACK WndProc_GDI(HWND hwnd, UINT msg, UINT wparam, LONG lparam)
/* main window Proc */
{
    int k;

    switch (msg) {
    case WM_PAINT:
        draw(hwnd);
        break;

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

    case WM_SYSKEYUP:
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

    case WM_SETCURSOR:

        SetCursor(NULL);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wparam, lparam);
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


static void _qdgdfv_set_palette(void)
{
}


static void _qdgdfv_dump_argb_screen(void)
{
    _qdgdfv_scale_argb_screen((int *)_double_screen);

    InvalidateRect(hwnd, NULL, FALSE);
}


static void _qdgdfv_dump_virtual_screen(void)
{
    if (!opengl_flag)
        _qdgdfv_scale_virtual_screen(_double_screen);

    InvalidateRect(hwnd, NULL, FALSE);
}


static void _qdgdfv_input_poll(void)
{
    MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

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
}


static int _qdgdfv_opengl(int onoff)
{
    int ret = 0;

#ifdef CONFOPT_OPENGL

    if (onoff) {
        PIXELFORMATDESCRIPTOR pfd;
        int i;

        /* get the device context (DC) */
        hdc = GetDC(hwnd);

        /* set the pixel format for the DC */
        ZeroMemory(&pfd, sizeof(pfd));
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags =
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 24;
        pfd.cDepthBits = 16;
        pfd.iLayerType = PFD_MAIN_PLANE;
        i = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, i, &pfd);

        /* create and enable the render context (RC) */
        hrc = wglCreateContext(hdc);
        wglMakeCurrent(hdc, hrc);
    }
    else {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hrc);
        ReleaseDC(hwnd, hdc);
    }

    opengl_flag = onoff;
    ret = 1;

#endif

    return ret;
}


static int _qdgdfv_startup(void)
{
    WNDCLASSW wc;
    BITMAPINFOHEADER *h;
    RECT cr;
    RECT wr;

    if (_qdgdfv_full_screen == -1)
        _qdgdfv_full_screen = 0;

    /* reject full screen mode */
    if (_qdgdfv_full_screen == 1)
        return 0;

    if (_qdgdfv_scale > 3)
        _qdgdfv_scale = 3;

    _qdgdfv_pixel_size = 4;

    _qdgdfv_red_mask = 0xff000000;
    _qdgdfv_red_shift = 8;

    _qdgdfv_green_mask = 0xff000000;
    _qdgdfv_green_shift = 16;

    _qdgdfv_blue_mask = 0xff000000;
    _qdgdfv_blue_shift = 24;

    hinst = (HINSTANCE) _qdgdfv_additional_int_info;

    /* register the window */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc_GDI;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinst;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"qdgdf_gdi";

    if (!RegisterClassW(&wc)) {
        qdgdfv_logger("qdgdfv_startup", "RegisterClass error");
        return 0;
    }

    /* create the window */
    hwnd = CreateWindowW(L"qdgdf_gdi", L"",
                         WS_OVERLAPPED | WS_CLIPCHILDREN,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         NULL, NULL, hinst, NULL);

    if (hwnd == NULL) {
        qdgdfv_logger("qdgdfv_startup", "WIN32 GDI CreateWindow error");
        return 0;
    }

    _qdgdfv_virtual_screen = (unsigned char *)
        qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size);

    _qdgdfv_argb_screen = (int *)
        qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size * sizeof(int));

    if (_qdgdfv_scale > 1)
        _double_screen = (unsigned char *)
            qdgdfv_malloc(_qdgdfv_screen_x_size * _qdgdfv_screen_y_size *
                      _qdgdfv_scale * _qdgdfv_scale * _qdgdfv_pixel_size);
    else
        _double_screen = (unsigned char *)_qdgdfv_argb_screen;

    GetClientRect(hwnd, &cr);
    GetWindowRect(hwnd, &wr);

    MoveWindow(hwnd,
               _qdgdfv_window_x,
               _qdgdfv_window_y,
               _qdgdfv_screen_x_size * _qdgdfv_scale + (wr.right -
                                                        wr.left) -
               cr.right,
               _qdgdfv_screen_y_size * _qdgdfv_scale + (wr.bottom -
                                                        wr.top) -
               cr.bottom, FALSE);

    qdgdfv_clear_virtual_screen();

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetCursor(NULL);

    /* fill the bitmap information */
    memset(&bmi, '\0', sizeof(bmi));
    h = &bmi.bmiHeader;

    h->biSize = sizeof(BITMAPINFOHEADER);
    h->biWidth = _qdgdfv_screen_x_size * _qdgdfv_scale;
    h->biHeight = -_qdgdfv_screen_y_size * _qdgdfv_scale;
    h->biPlanes = 1;
    h->biBitCount = 32;
    h->biCompression = BI_RGB;
    h->biSizeImage = 0;
    h->biClrUsed = 0;
    h->biClrImportant = 0;

    SetWindowText(hwnd, _qdgdfv_window_title);

    qdgdfv_logger("qdgdfv_startup", "Win32 GDI driver startup");

    return 1;
}


static void _qdgdfv_shutdown(void)
{
    SendMessage(hwnd, WM_CLOSE, 0, 0);

    qdgdfv_logger("qdgdfv_startup", "Win32 GDI driver shutdown");
}


/** driver information **/

static struct _qdgdfv_driver drv = {
    "win32_gdi",
    _qdgdfv_set_palette,
    _qdgdfv_dump_virtual_screen,
    _qdgdfv_dump_argb_screen,
    _qdgdfv_input_poll,
    _qdgdfv_timer,
    _qdgdfv_opengl,
    _qdgdfv_startup,
    _qdgdfv_shutdown
};


struct _qdgdfv_driver *win32gdi_drv_detect(void)
/* detection function */
{
    if (_qdgdfv_startup())
        return &drv;

    return NULL;
}

#endif                          /* CONFOPT_WIN32GDI */
