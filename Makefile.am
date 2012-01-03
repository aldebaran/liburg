## Makefile.am -- Process this file with automake to produce Makefile.in

SUBDIRS = include src samples
bin_SCRIPTS = urg-config c_urg-config
EXTRA_DIST = README.txt ChangeLog vc8/c/c_urg.vcproj vc8/cpp/urg.vcproj vc6/c/c_urg.dsp

${PACKAGE}-${VERSION}.tar.gz: dist

lzh: ${PACKAGE}-${VERSION}.tar.gz
	${RM} -rf ${PACKAGE}-${VERSION}
	tar zxf ${PACKAGE}-${VERSION}.tar.gz
	find ${PACKAGE}-${VERSION} -name '*.[ch]*' | xargs nkf -s --overwrite
	lha -a ${PACKAGE}-${VERSION}.lzh ${PACKAGE}-${VERSION}
	${RM} -rf ${PACKAGE}-${VERSION}

zip: ${PACKAGE}-${VERSION}.tar.gz
	${RM} -rf ${PACKAGE}-${VERSION}
	tar zxf ${PACKAGE}-${VERSION}.tar.gz
	find ${PACKAGE}-${VERSION} -name '*.[ch]*' | xargs nkf -s --overwrite
	zip -r ${PACKAGE}-${VERSION}.zip ${PACKAGE}-${VERSION}/
	${RM} -rf ${PACKAGE}-${VERSION}
	${RM} ${PACKAGE}-${VERSION}.tar.gz
