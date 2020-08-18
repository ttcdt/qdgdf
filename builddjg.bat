REM qdgdf - DJGPP build

echo /* automatically created by builddjg.bat - do not modify */ > config.h
type VERSION >> config.h
echo /* */ >> config.h
echo #define CONFOPT_DJGPP 1 >> config.h

gcc -O2 -c qdgdf_video.c
gcc -O2 -c qdgdf_video_ext.c
gcc -O2 -c qdgdf_video_font.c
gcc -O2 -c qdgdf_video_x11.c
gcc -O2 -c qdgdf_video_ddraw.c
gcc -O2 -c qdgdf_video_djgpp.c
gcc -O2 -c qdgdf_video_svgalib.c
gcc -O2 -c qdgdf_audio.c
gcc -O2 -c qdgdf_audio_oss.c
gcc -O2 -c qdgdf_audio_dsound.c
gcc -O2 -c qdgdf_audio_esd.c

ar rsv qdgdfv.lib qdgdf_video.o
ar rsv qdgdfv.lib qdgdf_video_ext.o
ar rsv qdgdfv.lib qdgdf_video_font.o
ar rsv qdgdfv.lib qdgdf_video_x11.o
ar rsv qdgdfv.lib qdgdf_video_ddraw.o
ar rsv qdgdfv.lib qdgdf_video_djgpp.o
ar rsv qdgdfv.lib qdgdf_video_svgalib.o
ar rsv qdgdfa.lib qdgdf_audio.o
ar rsv qdgdfa.lib qdgdf_audio_oss.o
ar rsv qdgdfa.lib qdgdf_audio_dsound.o
ar rsv qdgdfa.lib qdgdf_audio_esd.o
