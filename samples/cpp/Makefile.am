## Makefile.am -- Process this file with automake to produce Makefile.in

if BOOST_COMPILE_COND
BOOST_DEPEND_FILES = findUrgPortsSample urg_acquire
endif

INCLUDES = $(CPP_INCLUDES)
noinst_PROGRAMS = viewVvSample viewPpSample gdCaptureSample mdCaptureSample viewSerialIdSample captureIntensitySample connectById $(BOOST_DEPEND_FILES)

viewVvSample_SOURCES = viewVvSample.cpp
viewPpSample_SOURCES = viewPpSample.cpp
gdCaptureSample_SOURCES = gdCaptureSample.cpp
mdCaptureSample_SOURCES = mdCaptureSample.cpp
findUrgPortsSample_SOURCES = findUrgPortsSample.cpp
viewSerialIdSample_SOURCES = viewSerialIdSample.cpp
urg_acquire_SOURCES = urg_acquire.cpp
captureIntensitySample_SOURCES = captureIntensitySample.cpp
connectById_SOURCES = connectById.cpp

AM_CXXFLAGS = $(SDL_CFLAGS)
LIBS = $(SAMPLES_LIBS_PATH) $(INSTALL_LIBS)

EXTRA_DIST = \
	findUrgPortsSample.cpp \
	urg_acquire.cpp \
	samples_cpp.sln \
	viewVvSample_vc8/viewVvSample.vcproj \
	viewPpSample_vc8/viewPpSample.vcproj \
	gdCaptureSample_vc8/gdCaptureSample.vcproj \
	mdCaptureSample_vc8/mdCaptureSample.vcproj \
	findUrgPortsSample_vc8/findUrgPortsSample.vcproj \
	viewSerialIdSample_vc8/viewSerialIdSample.vcproj \
	urg_acquire_vc8/urg_acquire.vcproj \
	captureIntensitySample_vc8/captureIntensitySample.vcproj \
	connectById_vc8/connectById.vcproj
