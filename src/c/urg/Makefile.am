## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES = ${C_INCLUDES}
lib_LTLIBRARIES = libc_urg.la
libc_urg_includedir = ${includedir}/c_urg
libc_urg_include_HEADERS = urg_ctrl.h urg_t.h urg_parameter_t.h scip_handler.h
libc_urg_la_SOURCES = urg_ctrl.c scip_handler.c urg_errno.c \
urg_errno.h

libc_urg_la_LIBADD = ../connection/libc_urg_connection.la ../system/libc_urg_system.la
