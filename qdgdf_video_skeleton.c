/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

/* video driver skeleton */

#include "config.h"

#ifdef CONFOPT_SKELETON

#include "qdgdf_video.h"


/** data **/

/** code **/

static void _qdgdfv_set_palette(void)
{
}


static void _qdgdfv_dump_virtual_screen(void)
{
}


void _qdgdfv_input_poll(void)
{
}


static int _qdgdfv_timer(int reset)
{
    return 0;
}


static int _qdgdfv_opengl(int onoff)
{
    return 0;
}


static int _qdgdfv_startup(void)
{
    return 1;
}


static void _qdgdfv_shutdown(void)
{
}


/* driver information */

static struct _qdgdfv_driver drv = {
    "skeleton",
    _qdgdfv_set_palette,
    _qdgdfv_dump_virtual_screen,
    _qdgdfv_input_poll,
    _qdgdfv_timer,
    _qdgdfv_opengl,
    _qdgdfv_startup,
    _qdgdfv_shutdown
};


struct _qdgdfv_driver *skeleton_drv_detect(void)
/* detection function */
{
    if (_qdgdfv_startup())
        return &drv;

    return NULL;
}


#endif                          /* CONFOPT_SKELETON */
