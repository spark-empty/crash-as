# bitbake recipes for all the release of as
LICENSE = "GPLv2"

DEPENDS += "readline python sip gtk+"

S = "${WORKDIR}/"

# for rpm package /lib/as
FILES_${PN} += "/lib/as/*"


do_fetch() {
  if ! [ -e ${TMPDIR}/../downloads/as-master.zip.done ] ; then
    wget https://github.com/parai/as/archive/master.zip -O  ${TMPDIR}/../downloads/as-master.zip
    touch ${TMPDIR}/../downloads/as-master.zip.done
  fi
}

do_unpack() {
  if ! [ -e ${S}/as-master ] ; then
    unzip ${TMPDIR}/../downloads/as-master.zip -d ${S}
  fi
}

do_compile () {
	export verbose=1
	export PY34=${TMPDIR}/sysroots/${BUILD_SYS}/usr/bin/python-native/python

	cd ${S}/as-master/release/aslua
	make 91
	make 92
	# FIXME: this is ugly
	if ! [ -e ${TMPDIR}/sysroots/${BUILD_SYS}/usr/bin/sip ] ; then
	   	cp ${S}/../../sip/4.19-r0/image/* ${TMPDIR}/sysroots/${BUILD_SYS}/ -fr
	fi
	make 81
	make 82
	
	cd ${S}/as-master/release/ascore
	export sgapp=none
	make 91
	make 92

	cd ${S}/as-master/release/asboot
	make 91
	make 92
}

do_install () {
  mkdir -p ${D}/bin ${D}/lib/as/pyas
  cp ${S}/as-master/release/aslua/out/posix.exe      ${D}/bin/aslua
  cp ${S}/as-master/release/ascore/out/posix.exe     ${D}/bin/ascore
  cp ${S}/as-master/release/asboot/out/posix.exe     ${D}/bin/asboot
  cp ${S}/as-master/com/as.tool/as.one.py/*.py       ${D}/lib/as
  cp ${S}/as-master/com/as.tool/as.one.py/pyas/*.so  ${D}/lib/as/pyas
  cp ${S}/as-master/com/as.tool/as.one.py/pyas/*.py  ${D}/lib/as/pyas
  cp ${S}/as-master/com/as.tool/as.one.py/pyas/*.lua ${D}/lib/as/pyas 
}
