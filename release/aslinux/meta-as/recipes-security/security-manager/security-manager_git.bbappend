

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
   file://0001-Fix-build-error-of-security-manager.patch \
"

EXTRA_OECMAKE_append = " -DCMAKE_BUILD_TYPE=DEBUG "

do_compile_prepend() {
  if ! [ -e ${TMPDIR}/.${MACHINE}_security_manager_gcc_include_next_fix ] ; then
    sed -i "75c #include \"./stdlib.h\"" ${TMPDIR}/sysroots/${MACHINE}/usr/include/c++/6.2.0/cstdlib
    sed -i "45c #include \"./math.h\""  ${TMPDIR}/sysroots/${MACHINE}/usr/include/c++/6.2.0/cmath
	touch ${TMPDIR}/.security_manager_gcc_include_next_fix
  fi
}