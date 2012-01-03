## Makefile.am -- Process this file with automake to produce Makefile.in

if BOOST_COMPILE_COND
BOOST_DEPEND_FILES = findUrgPorts.cpp UrgUsbCom.cpp
endif

INCLUDES = $(CPP_INCLUDES)
lib_LTLIBRARIES = liburg.la
liburg_includedir = $(includedir)/urg
liburg_include_HEADERS = RangeSensor.h CaptureSettings.h RangeSensorParameter.h UrgCtrl.h RangeCaptureMode.h UrgUsbCom.h UrgUtils.h findUrgPorts.h
liburg_la_SOURCES = UrgCtrl.cpp ScipHandler.cpp $(BOOST_DEPEND_FILES) \
ScipHandler.h
AM_CXXFLAGS = $(SDL_CFLAGS)

EXTRA_DIST = $(BOOST_DEPEND_FILES)
