REM qdgdf - Borland C build

echo /* automatically created by buildbcc.bat - do not modify */ > config.h
type VERSION >> config.h
echo /* */ >> config.h
echo #define CONFOPT_DDRAW 1 >> config.h
echo #define CONFOPT_DSOUND 1 >> config.h

bcc32 -6 -O2 -c qdgdf_video.c
bcc32 -6 -O2 -c qdgdf_video_ext.c
bcc32 -6 -O2 -c qdgdf_video_font.c
bcc32 -6 -O2 -c qdgdf_video_x11.c
bcc32 -6 -O2 -c qdgdf_video_ddraw.c
bcc32 -6 -O2 -c qdgdf_video_djgpp.c
bcc32 -6 -O2 -c qdgdf_video_svgalib.c
bcc32 -6 -O2 -c qdgdf_audio.c
bcc32 -6 -O2 -c qdgdf_audio_oss.c
bcc32 -6 -O2 -c qdgdf_audio_dsound.c
bcc32 -6 -O2 -c qdgdf_audio_esd.c

tlib qdgdfv.lib -+qdgdf_video.obj
tlib qdgdfv.lib -+qdgdf_video_ext.obj
tlib qdgdfv.lib -+qdgdf_video_font.obj
tlib qdgdfv.lib -+qdgdf_video_x11.obj
tlib qdgdfv.lib -+qdgdf_video_ddraw.obj
tlib qdgdfv.lib -+qdgdf_video_djgpp.obj
tlib qdgdfv.lib -+qdgdf_video_svgalib.obj
tlib qdgdfa.lib -+qdgdf_audio.obj
tlib qdgdfa.lib -+qdgdf_audio_oss.obj
tlib qdgdfa.lib -+qdgdf_audio_dsound.obj
tlib qdgdfa.lib -+qdgdf_audio_esd.obj
