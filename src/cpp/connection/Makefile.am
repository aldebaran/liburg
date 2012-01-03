## Makefile.am -- Process this file with automake to produce Makefile.in

SUBDIRS = sdl

if BOOST_COMPILE_COND
BOOST_DEPEND_FILES = FindComPorts.cpp isUsingComDriver.cpp
endif

INCLUDES = $(CPP_INCLUDES)
lib_LTLIBRARIES = liburg_connection.la
liburg_connection_includedir = $(includedir)/urg
liburg_connection_include_HEADERS = Connection.h SerialDevice.h ConnectionUtils.h FindComPorts.h isUsingComDriver.h IsUsbCom.h TcpipSocket.h
liburg_connection_la_SOURCES = SerialDevice.cpp ConnectionUtils.cpp $(BOOST_DEPEND_FILES)

EXTRA_DIST = SerialDevice_lin.cpp SerialDevice_win.cpp $(BOOST_DEPEND_FILES)
