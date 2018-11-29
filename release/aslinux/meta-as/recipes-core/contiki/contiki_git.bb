DESCRIPTION = "The Open Source OS for the Internet of Things"
HOMEPAGE = "http://www.contiki-os.org/"
SECTION = "IoT/Network"
LICENSE = "3-clause BSD"

# get the whole git is really very slow
#SRCREV = "ae5a3f9f677e64b9a5b8596db4926f5e53ff404f"
#SRC_URI = "git://github.com/contiki-os/contiki.git;protocal=git;"

S = "${WORKDIR}/"

BBCLASSEXTEND = "native"

PV="3.x"

do_fetch() {
  if ! [ -e ${TMPDIR}/../downloads/contiki_${PV}.tar.gz.done ] ; then
    wget https://github.com/contiki-os/contiki/archive/${PV}.tar.gz -O  ${TMPDIR}/../downloads/contiki_${PV}.tar.gz
    touch ${TMPDIR}/../downloads/contiki_${PV}.tar.gz.done
  fi
}

do_unpack() {
  if ! [ -e ${S}/contiki-${PV} ] ; then
    tar xf ${TMPDIR}/../downloads/contiki_${PV}.tar.gz -C ${S}
  fi
}

do_compile() {
  cd ${S}/contiki-${PV}/examples/webserver
  make V=1 LD="${CC} ${LDFLAGS}"

}

do_install() {
  mkdir -p ${S}/image/usr/bin
  cp -f ${S}/contiki-${PV}/examples/webserver/webserver-example.minimal-net ${S}/image/usr/bin
}
