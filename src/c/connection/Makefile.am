## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES = ${C_INCLUDES}
lib_LTLIBRARIES = libc_urg_connection.la
libc_urg_connection_includedir = ${includedir}/c_urg
libc_urg_connection_include_HEADERS = serial_ctrl.h serial_utils.h serial_t.h serial_t_lin.h serial_t_win.h ring_buffer.h
libc_urg_connection_la_SOURCES = serial_ctrl.c serial_utils.c ring_buffer.c \
serial_errno.h
EXTRA_DIST = serial_ctrl_lin.c serial_ctrl_win.c serial_t_lin.h serial_t_win.h
