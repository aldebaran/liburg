## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES = $(C_INCLUDES)
noinst_PROGRAMS = get_parameters get_version_lines gd_scan md_scan convert_2d multi_urg get_timestamp capture_sample partial_scan intensity_sample

get_parameters_SOURCES = get_parameters.c
get_version_lines_SOURCES = get_version_lines.c
gd_scan_SOURCES = gd_scan.c
md_scan_SOURCES = md_scan.c
capture_sample_SOURCES = capture_sample.c
convert_2d_SOURCES = convert_2d.c
multi_urg_SOURCES = multi_urg.c
get_timestamp_SOURCES = get_timestamp.c
intensity_sample_SOURCES = intensity_sample.c
partial_scan_SOURCES = partial_scan.c

LIBS = $(SAMPLES_LIBS_PATH) $(C_INSTALL_LIBS)

EXTRA_DIST = \
	samples_c.sln \
	get_parameters_vc8/get_parameters.vcproj \
	get_version_lines_vc8/get_version_lines.vcproj \
	gd_scan_vc8/gd_scan.vcproj \
	md_scan_vc8/md_scan.vcproj \
	convert_2d_vc8/convert_2d.vcproj \
	multi_urg_vc8/multi_urg.vcproj \
	get_timestamp_vc8/get_timestamp.vcproj \
	capture_sample_vc8/capture_sample.vcproj \
	partial_scan_vc8/partial_scan.vcproj \
	gd_scan_vc6/gd_scan.dsp
