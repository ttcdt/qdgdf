/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

/*

    Usage:
    qdgdf_i [X size] [Y size] [scale] [full screen]

*/

#include "config.h"
#include "qdgdf_video.h"
#include "qdgdf_audio.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

char *info[100];

void build_info(void)
{
    int y = 0;

    info[y++] = strdup(qdgdfv_sprintf("QDGDF %s", _qdgdfv_version));
    info[y++] = strdup(qdgdfv_sprintf("%d x %d (scale %d)",
                                      _qdgdfv_screen_x_size,
                                      _qdgdfv_screen_y_size,
                                      _qdgdfv_scale));
    info[y++] = strdup(qdgdfv_sprintf("full screen: %d",
                                      _qdgdfv_full_screen));
    info[y++] = strdup(qdgdfv_sprintf("window position: %d x %d",
                                    _qdgdfv_window_x,
                                    _qdgdfv_window_y));
    info[y++] = strdup(qdgdfv_sprintf("pixel size: %d", _qdgdfv_pixel_size));
    info[y++] = strdup(qdgdfv_sprintf("home dir: %s", qdgdfv_home_dir()));
    info[y++] = strdup(qdgdfv_sprintf("app dir: %s", qdgdfv_app_dir()));
    info[y++] = strdup(qdgdfv_sprintf("sound: %d (%d bit)",
                                      _qdgdfa_sound,
                                      _qdgdfa_16_bit ? 16 : 8));

#ifdef CONFOPT_OPENGL
    info[y++] = "OpenGL support enabled";
#else
    info[y++] = "OpenGL support disabled";
#endif
}


void show_info(void)
{
    int c = qdgdfv_seek_color(255, 255, 255);
    int y;

    qdgdfv_clear_virtual_screen();

    for (y = 0; info[y] != NULL; y++)
        qdgdfv_font_print(1, y * _qdgdfv_font_height, (unsigned char *)info[y], c);

    qdgdfv_font_print(1, y * _qdgdfv_font_height,
            (unsigned char *)qdgdfv_sprintf("%d %c", _qdgdfv_key_alnum, _qdgdfv_alnum),
            c);

    qdgdfv_font_print(-1, -1, (unsigned char *)"Press ESCAPE", c);

    qdgdfv_dump_virtual_screen();
}


void show_opengl(void)
{
#ifdef CONFOPT_OPENGL
    static double theta = 0.0;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.87f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.87f, -0.5f);
    glEnd();

    glPopMatrix();

    theta += 1.0;

    qdgdfv_dump_virtual_screen();
#endif
}
/*

Inspired by:

http://codegolf.stackexchange.com/questions/35569/tweetable-mathematical-art

*/

#define DIM _qdgdfv_screen_x_size

unsigned char RD(int i,int j,double d){
    float s=(3. + d)/(j+99);
    return ((int)((i+DIM)*s+j*s)%2+(int)((DIM*2-i)*s+j*s)%2)*127;
}
unsigned char GR(int i,int j,double d){
    float s=(2. + d)/(j+99);
    return ((int)((i+DIM)*s+j*s)%2+(int)((DIM*2-i)*s+j*s)%2)*127;
}
unsigned char BL(int i,int j,double d){
    float s=(3.5 + d)/(j+99);
    return ((int)((i+DIM)*s+j*s)%2+(int)((DIM*2-i)*s+j*s)%2)*127;
}

#define _sq(x) ((x)*(x))
#if 0
unsigned char RD(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return ((int)((i+DIM)*s+y)%2+(int)((DIM*2-i)*s+y)%2)*127;
}
unsigned char GR(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return ((int)(5*((i+DIM)*s+y))%2+(int)(5*((DIM*2-i)*s+y))%2)*127;
}
unsigned char BL(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return ((int)(29*((i+DIM)*s+y))%2+(int)(29*((DIM*2-i)*s+y))%2)*127;
}
#endif
#if 0
unsigned char RD(int i,int j){
#define P 6.43
float s=3./(j+250),y=(j+sin((i*i+_sq(j-700)*5)/100./DIM+P)*15)*s;
return ((int)((i+DIM)*s+y)%2+(int)((DIM*2-i)*s+y)%2)*127;}

unsigned char GR(int i,int j){
float s=3./(j+250);
float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM+P)*15)*s;
return ((int)(5*((i+DIM)*s+y))%2+(int)(5*((DIM*2-i)*s+y))%2)*127;}

unsigned char BL(int i,int j){
float s=3./(j+250);
float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM+P)*15)*s;
return ((int)(29*((i+DIM)*s+y))%2+(int)(29*((DIM*2-i)*s+y))%2)*127;}
#endif

void show_argb(void)
{
    int i, j;
    double d = 0.0;
    double dd = 0.01;

    if (_qdgdfv_argb_screen == NULL)
        return;

    for (;;) {
        for (j = 0; j < _qdgdfv_screen_y_size; j++) {
            for (i = 0; i < _qdgdfv_screen_x_size; i++) {
                int c = (RD(i, j, d) << 16) |
                        (GR(i, j, d) << 8)  |
                        (BL(i, j, d) << 0);

               _qdgdfv_argb_screen[i + j * _qdgdfv_screen_x_size] = c;
            }
        }

        d += dd;
        if (d > 5.0 || d < -5.0)
            dd = -dd;

        qdgdfv_input_poll();
        qdgdfv_dump_argb_screen();

        if (_qdgdfv_key_escape)
            break;
    }

    while (_qdgdfv_key_escape)
        qdgdfv_input_poll();
}


int main(int argc, char *argv[])
{
    int n = 1;

    strcpy(_qdgdfv_window_title, "QDGDF Information");

    if (argc > n)
        _qdgdfv_screen_x_size = atoi(argv[n++]);
    if (argc > n)
        _qdgdfv_screen_y_size = atoi(argv[n++]);
    if (argc > n)
        _qdgdfv_scale = atoi(argv[n++]);
    if (argc > n)
        _qdgdfv_full_screen = atoi(argv[n++]);

    strcpy(_qdgdfv_logger_file, "qdgdf.log");
    _qdgdfv_use_logger = 1;

    qdgdfa_startup();
    qdgdfv_startup();

    build_info();

    do {
        show_info();
        qdgdfv_input_poll();
    } while (!_qdgdfv_key_escape);

    while (_qdgdfv_key_escape)
        qdgdfv_input_poll();

    show_argb();

    if (qdgdfv_opengl(1)) {
        do {
            show_opengl();
            qdgdfv_input_poll();
        } while (!_qdgdfv_key_escape);
    }

    qdgdfv_shutdown();
    qdgdfa_shutdown();

    return 0;
}
