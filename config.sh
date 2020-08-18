#!/bin/sh

# Configuration shell script

VIDEO_DRIVERS=""
VIDEO_DRV_OBJS=""
AUDIO_DRIVERS=""
AUDIO_DRV_OBJS=""
TARGET_EXT=""

# gets program version
VERSION=`cut -f2 -d\" VERSION`

# store command line args for configuring the libraries
CONF_ARGS="$*"

# default installation prefix
PREFIX=/usr/local

MINGW32_PREFIX=x86_64-w64-mingw32

# parse arguments
while [ $# -gt 0 ] ; do

    case $1 in
    --help)             CONFIG_HELP=1 ;;

    --mingw32-prefix=*)     MINGW32_PREFIX=`echo $1 | sed -e 's/--mingw32-prefix=//'`
                            ;;

    --mingw32)          CC=${MINGW32_PREFIX}-gcc
                        WINDRES=${MINGW32_PREFIX}-windres
                        AR=${MINGW32_PREFIX}-ar
                        LD=${MINGW32_PREFIX}-ld
                        CPP=${MINGW32_PREFIX}-g++
                        ;;

    --without-opengl)   WITHOUT_OPENGL=1 ;;
    --prefix)           PREFIX=$2 ; shift ;;
    --prefix=*)         PREFIX=`echo $1 | sed -e 's/--prefix=//'` ;;
    esac

    shift
done

if [ "$CONFIG_HELP" = "1" ] ; then

    echo "Available options:"
    echo "--prefix=PREFIX       Installation prefix ($PREFIX)."
    echo "--without-opengl      Disable OpenGL detection."
    echo "--mingw32             Build using the mingw32 compiler."

    echo
    echo "Environment variables:"
    echo "CC                    C Compiler."
    echo "CFLAGS                Compile flags (i.e., -O3)."
    echo "AR                    Archiver."

    exit 1
fi

echo "Configuring Quick and Dirty Game Development Framework..."

echo "/* automatically created by config.sh - do not modify */" > config.h
echo "# automatically created by config.sh - do not modify" > makefile.opts
> config.ldflags
> config.cflags
> .config.log

# set compiler
if [ "$CC" = "" ] ; then
    CC=cc
    # if CC is unset, try if gcc is available
    which gcc > /dev/null

    if [ $? = 0 ] ; then
        CC=gcc
        echo "#define _GNU_SOURCE 1" >> config.h
    fi
fi

echo "CC=$CC" >> makefile.opts

# set cflags
if [ "$CFLAGS" = "" -a "$CC" = "gcc" ] ; then
    CFLAGS="-g -Wall"
fi

echo "CFLAGS=$CFLAGS -Icompat" >> makefile.opts

# Add CFLAGS to CC
CC="$CC $CFLAGS"

# set archiver
if [ "$AR" = "" ] ; then
    AR=ar
fi

if [ "$LD" = "" ] ; then
    LD=ld
fi

if [ "$TAR" = "" ] ; then
    TAR=tar
fi

echo "AR=$AR" >> makefile.opts
echo "LD=$LD" >> makefile.opts
echo "TAR=$TAR" >> makefile.opts

# add version
cat VERSION >> config.h

# add installation prefix
echo "#define CONFOPT_PREFIX \"$PREFIX\"" >> config.h

#########################################################

# configuration directives

# test for x11
echo -n "Testing for X11..."
echo "#include <stdio.h>" > .tmp.c
echo "#include <X11/Xlib.h>" >> .tmp.c
echo "#include <X11/Xutil.h>" >> .tmp.c
echo "#include <X11/keysym.h>" >> .tmp.c
echo "#include <sys/time.h>" >> .tmp.c
echo "int main(void) { XOpenDisplay(NULL); return 0; }" >> .tmp.c

TMP_CFLAGS="-I/usr/X11R6/include"
TMP_LDFLAGS="-L/usr/X11R6/lib -lXext -lX11 -lm"
$CC $TMP_CFLAGS .tmp.c $TMP_LDFLAGS -o .tmp.o 2> .config.log
if [ $? = 0 ] ; then
    echo "#define CONFOPT_X11 1" >> config.h
    echo $TMP_LDFLAGS >> config.ldflags
    echo "OK"
    VIDEO_DRIVERS="$VIDEO_DRIVERS x11"
    VIDEO_DRV_OBJS="qdgdf_video_x11.o $VIDEO_DRV_OBJS"
else
    echo "No"
fi

# test for SVGALIB
echo -n "Testing for svgalib..."
echo "#include <vga.h>" > .tmp.c
echo "#include <vgakeyboard.h>" >> .tmp.c
echo "int main(void) { return 0; }" >> .tmp.c

TMP_CFLAGS=""
TMP_LDFLAGS="-lvga -lm"
$CC $TMP_CFLAGS .tmp.c $TMP_LDFLAGS -o .tmp.o 2> .config.log
if [ $? = 0 ] ; then
    echo "#define CONFOPT_SVGALIB 1" >> config.h
    echo $TMP_LDFLAGS >> config.ldflags
    echo "OK"
    VIDEO_DRIVERS="$VIDEO_DRIVERS svgalib"
    VIDEO_DRV_OBJS="qdgdf_video_svgalib.o $VIDEO_DRV_OBJS"
else
    echo "No"
fi


# test for Linux OSS
echo -n "Testing for Linux OSS... "
echo "#include <linux/soundcard.h>" > .tmp.c
echo "int main(void) {" >> .tmp.c
echo "int i=open(\"/dev/dsp\",0);" >> .tmp.c
echo "ioctl(i,SNDCTL_DSP_SETFRAGMENT,&i);" >> .tmp.c
echo "return 0; } " >>.tmp.c

$CC .tmp.c -o .tmp.o 2> .config.log
if [ $? = 0 ] ; then
    echo "#define CONFOPT_LINUX_OSS 1" >> config.h
    echo "OK"
    AUDIO_DRIVERS="$AUDIO_DRIVERS oss"
    AUDIO_DRV_OBJS="qdgdf_audio_oss.o $AUDIO_DRV_OBJS"
else
    echo "No"
fi

# test for esound library
echo -n "Testing for esound development libraries... "
echo "#include <esd.h>" > .tmp.c
echo "int main(void) { return 0; }" >> .tmp.c

$CC -I/usr/local/include -L/usr/local/lib -lesd .tmp.c -o .tmp.o 2> .config.log
if [ $? = 0 ] ; then
    echo "#define CONFOPT_ESD 1" >> config.h
    echo "-lesd" >> config.ldflags
    echo "OK"
    AUDIO_DRIVERS="$AUDIO_DRIVERS esd"
    AUDIO_DRV_OBJS="qdgdf_audio_esd.o $AUDIO_DRV_OBJS"
else
    echo "No"
fi

# test for win32
echo -n "Testing for win32... "
echo "#include <windows.h>" > .tmp.c
echo "#include <ddraw.h>" >> .tmp.c
echo "#include <dsound.h>" >> .tmp.c
echo "int CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR c, int m)" >> .tmp.c
echo "{ return 0; }" >> .tmp.c

TMP_CFLAGS="-Icompat"
TMP_LDFLAGS="-mwindows -lddraw -ldsound -lgdi32"

$CC $TMP_CFLAGS .tmp.c $TMP_LDFLAGS -o .tmp.o 2>> .config.log
if [ $? = 0 ] ; then
    echo "#define CONFOPT_WIN32 1" >> config.h
    echo "#define CONFOPT_DDRAW 1" >> config.h
    echo "#define CONFOPT_WIN32GDI 1" >> config.h
    echo "#define CONFOPT_DSOUND 1" >> config.h
    echo $TMP_LDFLAGS >> config.ldflags
    echo "OK"
    VIDEO_DRIVERS="$VIDEO_DRIVERS win32gdi ddraw"
    AUDIO_DRIVERS="$AUDIO_DRIVERS dsound"
    VIDEO_DRV_OBJS="qdgdf_video_win32gdi.o qdgdf_video_ddraw.o $VIDEO_DRV_OBJS"
    AUDIO_DRV_OBJS="qdgdf_audio_dsound.o $AUDIO_DRV_OBJS"
    TARGET_EXT=".exe"
    CONFOPT_WIN32=1
else
    echo "No"
fi

# openGL detection
echo -n "Testing for OpenGL... "

if [ "$WITHOUT_OPENGL" = "1" ] ; then
    echo "Disabled"
else
    rm -f .tmp.c
    
    if [ -z "$CONFOPT_WIN32" ] ; then
        TMP_LDFLAGS="-lGL -lGLU"
    else
        TMP_LDFLAGS="-lopengl32 -lglu32"
    fi
    
    echo "#include <GL/gl.h>" >> .tmp.c
    echo "#include <GL/glu.h>" >> .tmp.c
    echo "int main(void) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); return 0; }" >> .tmp.c
    
    $CC .tmp.c $(cat config.ldflags) $TMP_LDFLAGS -o .tmp.o 2>> .config.log
    if [ $? = 0 ] ; then
        echo "#define CONFOPT_OPENGL 1" >> config.h
        echo $TMP_LDFLAGS >> config.ldflags
        echo "OK"
    else
        echo "No"
    fi
fi

# unistd.h detection
echo -n "Testing for unistd.h... "
echo "#include <unistd.h>" > .tmp.c
echo "int main(void) { return(0); }" >> .tmp.c

$CC .tmp.c -o .tmp.o 2>> .config.log

if [ $? = 0 ] ; then
    echo "#define CONFOPT_UNISTD_H 1" >> config.h
    echo "OK"
else
    echo "No"
fi

# sys/types.h detection
echo -n "Testing for sys/types.h... "
echo "#include <sys/types.h>" > .tmp.c
echo "int main(void) { return(0); }" >> .tmp.c

$CC .tmp.c -o .tmp.o 2>> .config.log

if [ $? = 0 ] ; then
    echo "#define CONFOPT_SYS_TYPES_H 1" >> config.h
    echo "OK"
else
    echo "No"
fi

# pwd.h detection
echo -n "Testing for pwd.h... "
echo "#include <pwd.h>" > .tmp.c
echo "int main(void) { return(0); }" >> .tmp.c

$CC .tmp.c -o .tmp.o 2>> .config.log

if [ $? = 0 ] ; then
    echo "#define CONFOPT_PWD_H 1" >> config.h
    echo "OK"
else
    echo "No"
fi

# test for embeddable binaries
echo -n "Testing for embeddable binaries... "
if [ "$WITH_EXTERNAL_TAR" = "1" ] ; then
    echo "Disabled"
else
    echo "test" > tmp.bin
    $LD -r -b binary tmp.bin -o tmp.bin.o

    echo "extern const char _binary_tmp_bin_start;" > .tmp.c
    echo "extern const char _binary_tmp_bin_end;" >> .tmp.c
    echo "extern const char binary_tmp_bin_start;" >> .tmp.c
    echo "extern const char binary_tmp_bin_end;" >> .tmp.c
    echo "int main(void) { " >> .tmp.c
    echo "#ifdef CONFOPT_EMBED_NOUNDER" >> .tmp.c
    echo "  int c = &binary_tmp_bin_end - &binary_tmp_bin_start;" >> .tmp.c
    echo "#else" >> .tmp.c
    echo "  int c = &_binary_tmp_bin_end - &_binary_tmp_bin_start;" >> .tmp.c
    echo "#endif" >> .tmp.c
    echo "  return c; } " >> .tmp.c

    $CC .tmp.c tmp.bin.o -o .tmp.o 2>> .config.log

    if [ $? = 0 ] ; then
        echo "Yes (with underscores)"
        MORE_OBJS="mp.tar.o ${MORE_OBJS}"
        echo "#define CONFOPT_EMBED_NOUNDER 0" >> config.h
    else
        $CC -DCONFOPT_EMBED_NOUNDER .tmp.c tmp.bin.o -o .tmp.o 2>> .config.log

        if [ $? = 0 ] ; then
            echo "Yes (without underscores)"
            MORE_OBJS="mp.tar.o ${MORE_OBJS}"
            echo "#define CONFOPT_EMBED_NOUNDER 1" >> config.h
        else
            echo "No"
            WITH_EXTERNAL_TAR=1
        fi
    fi

    rm -f tmp.bin tmp.bin.o
fi

# test for Grutatxt
echo -n "Testing if Grutatxt is installed... "

DOCS="\$(ADD_DOCS)"

if which grutatxt > /dev/null ; then
    echo "OK"
    echo "GRUTATXT=yes" >> makefile.opts
    DOCS="$DOCS \$(GRUTATXT_DOCS)"
else
    echo "No"
    echo "GRUTATXT=no" >> makefile.opts
fi

# test for mp_doccer
echo -n "Testing if mp_doccer is installed... "
MP_DOCCER=$(which mp_doccer || which mp-doccer)

if [ $? = 0 ] ; then

    if ${MP_DOCCER} --help | grep grutatxt > /dev/null ; then

        echo "OK"

        echo "MP_DOCCER=yes" >> makefile.opts
        DOCS="$DOCS \$(MP_DOCCER_DOCS)"

        grep GRUTATXT=yes makefile.opts > /dev/null && DOCS="$DOCS \$(G_AND_MP_DOCS)"
    else
        echo "Outdated (No)"
        echo "MP_DOCCER=no" >> makefile.opts
    fi
else
    echo "No"
    echo "MP_DOCCER=no" >> makefile.opts
fi

#########################################################

# final setup

echo "DOCS=$DOCS" >> makefile.opts
echo "VERSION=$VERSION" >> makefile.opts
echo "PREFIX=$PREFIX" >> makefile.opts
echo "VIDEO_DRV_OBJS=$VIDEO_DRV_OBJS" >> makefile.opts
echo "AUDIO_DRV_OBJS=$AUDIO_DRV_OBJS" >> makefile.opts
echo "CONF_ARGS=$CONF_ARGS" >> makefile.opts
echo "TARGET_EXT=$TARGET_EXT" >> makefile.opts
echo >> makefile.opts

cat makefile.opts makefile.in makefile.depend > Makefile

#########################################################

if [ "$VIDEO_DRIVERS" = "" ] ; then

    echo
    echo "*ERROR* No usable video drivers (interfaces) found."
    rm -f Makefile

    exit 1
fi

if [ "$AUDIO_DRIVERS" = "" ] ; then

    AUDIO_DRIVERS="none"
fi

echo
echo "Configured video drivers:" $VIDEO_DRIVERS
echo "Configured audio drivers:" $AUDIO_DRIVERS
echo

# insert driver detection code into config.h

TRY_VIDEO_DRIVERS="#define TRY_VIDEO_DRIVERS() ("
echo >> config.h
for drv in $VIDEO_DRIVERS ; do
    echo "struct _qdgdfv_driver * ${drv}_drv_detect(void);" >> config.h
    TRY_VIDEO_DRIVERS="$TRY_VIDEO_DRIVERS (drv = ${drv}_drv_detect()) || "
done

echo $TRY_VIDEO_DRIVERS '0)' >> config.h

TRY_AUDIO_DRIVERS="#define TRY_AUDIO_DRIVERS() ("
echo >> config.h
for drv in $AUDIO_DRIVERS ; do
    echo "struct _qdgdfa_driver * ${drv}_drv_detect(void);" >> config.h
    TRY_AUDIO_DRIVERS="$TRY_AUDIO_DRIVERS (drv = ${drv}_drv_detect()) || "
done

echo $TRY_AUDIO_DRIVERS '0)' >> config.h

# cleanup
rm -f .tmp.c .tmp.o

exit 0
