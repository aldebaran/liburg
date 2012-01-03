## Makefile.am -- Process this file with automake to produce Makefile.in

INCLUDES = ${CPP_INCLUDES}
noinst_PROGRAMS = scip_20_scip scip_20_vv scip_20_pp scip_20_ss scip_20_gd scip_20_md scip_20_ii scip_20_tm scip_20_cr

scip_20_scip_SOURCES = scip_20_scip.cpp
scip_20_vv_SOURCES = scip_20_vv.cpp
scip_20_pp_SOURCES = scip_20_pp.cpp
scip_20_ss_SOURCES = scip_20_ss.cpp
scip_20_gd_SOURCES = scip_20_gd.cpp ScipUtils.cpp ScipUtils.h
scip_20_md_SOURCES = scip_20_md.cpp
scip_20_ii_SOURCES = scip_20_ii.cpp
scip_20_tm_SOURCES = scip_20_tm.cpp ScipUtils.cpp ScipUtils.h
scip_20_cr_SOURCES = scip_20_cr.cpp ScipUtils.cpp ScipUtils.h

AM_CXXFLAGS = ${SDL_CFLAGS}
LIBS = ${SAMPLES_LIBS_PATH} -lurg_connection -lurg_system -lurg_common

EXTRA_DIST = \
	scip_samples.sln \
	scip_20_scip_vc8/scip_20_scip.vcproj \
	scip_20_vv_vc8/scip_20_vv.vcproj \
	scip_20_pp_vc8/scip_20_pp.vcproj \
	scip_20_ii_vc8/scip_20_ii.vcproj \
	scip_20_gd_vc8/scip_20_gd.vcproj \
	scip_20_md_vc8/scip_20_md.vcproj \
	scip_20_cr_vc8/scip_20_cr.vcproj \
	scip_20_ss_vc8/scip_20_ss.vcproj \
	scip_20_tm_vc8/scip_20_tm.vcproj
