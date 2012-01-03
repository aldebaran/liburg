## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES = $(CPP_INCLUDES)
noinst_PROGRAMS = versionLines parameterLines gdScan mdScan intensityScan serialId connectById findUrgPorts acquire_data thread_scan

versionLines_SOURCES = versionLines.cpp
parameterLines_SOURCES = parameterLines.cpp
gdScan_SOURCES = gdScan.cpp
mdScan_SOURCES = mdScan.cpp
intensityScan_SOURCES = intensityScan.cpp
serialId_SOURCES = serialId.cpp
connectById_SOURCES = connectById.cpp
findUrgPorts_SOURCES = findUrgPorts.cpp
acquire_data_SOURCES = acquire_data.cpp
thread_scan_SOURCES = thread_scan.cpp

AM_CXXFLAGS = $(SDL_CFLAGS)
LIBS = $(SAMPLES_LIBS_PATH) $(INSTALL_LIBS)

EXTRA_DIST = \
	samples_cpp.sln \
	versionLines_vc8/versionLines.vcproj \
	parameterLines_vc8/parameterLines.vcproj \
	gdScan_vc8/gdScan.vcproj \
	mdScan_vc8/mdScan.vcproj \
	intensityScan_vc8/intensityScan.vcproj \
	serialId_vc8/serialId.vcproj \
	connectById_vc8/connectById.vcproj \
	findUrgPorts_vc8/findUrgPorts.vcproj \
	acquire_data_vc8/acquire_data.vcproj \
	thread_scan_vc8/thread_scan.vcproj
