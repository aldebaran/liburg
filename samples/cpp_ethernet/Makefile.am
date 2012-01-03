## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES = ${CPP_INCLUDES}
noinst_PROGRAMS = captureIntensitySample

captureIntensitySample_SOURCES = captureIntensitySample.cpp

AM_CXXFLAGS = ${SDL_CFLAGS}
LIBS = ${SAMPLES_LIBS_PATH} ${INSTALL_LIBS}

EXTRA_DIST = \
	ethernet_samples_cpp.sln \
	captureIntensitySample_vc8/captureIntensitySample.vcproj
