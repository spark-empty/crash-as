DESCRIPTION = "android binder for linux"
HOMEPAGE = "https://github.com/hungys/binder-for-linux/tree/master/libs/include/binder"
SECTION = "Android/IPC"
LICENSE = "APACHE-2.0"

S = "${WORKDIR}/"

BBCLASSEXTEND = "native"

do_fetch() {
  if ! [ -e ${TMPDIR}/../downloads/binder-for-linux.zip.done ] ; then
    wget https://github.com/hungys/binder-for-linux/archive/master.zip -O  ${TMPDIR}/../downloads/binder-for-linux.zip
    touch ${TMPDIR}/../downloads/binder-for-linux.zip.done
  fi
}

do_unpack() {
  if ! [ -e ${S}/binder-for-linux-master ] ; then
	cd ${S}
    unzip ${TMPDIR}/../downloads/binder-for-linux.zip
# ----------------------------------- [ servicemanager ] ----------------------------------
    cd ${S}/binder-for-linux-master/servicemanager
    cat > Makefile << EOF
all: servicemanager 

servicemanager: binder.o service_manager.o
	${CC} ${LDFLAGS} -o \$@ $^

clean:
	rm -f *.o servicemanager
	
%.o: %.c
	${CC} -I.. -DBINDER_IPC_32BIT ${CFLAGS} -c -o \$@ $<
EOF
# ----------------------------------- [ libs ] ----------------------------------
    cd ${S}/binder-for-linux-master/libs
    cat > Makefile << EOF
all: libbinder.a

include cutils/Makefile
include utils/Makefile
include binder/Makefile

libbinder.a: \$(objects)
	${AR} cr \$@ $^

clean:
	rm -f  libbinder.a `find -name \*.o`

%.o : %.cpp
	${CC} ${CFLAGS} -I.. -DBINDER_IPC_32BIT -Iinclude -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 -std=c++11 -c -o \$@ $<
%.o : %.c
	${CC} ${CFLAGS} -I.. -DBINDER_IPC_32BIT -Iinclude -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 -std=c++11 -c -o \$@ $<
EOF

  fi
}

do_compile() {
# ----------------------------------- [ servicemanager ] ----------------------------------
  cd ${S}/binder-for-linux-master/servicemanager
  make all
# ----------------------------------- [ libs ] ----------------------------------
  cd ${S}/binder-for-linux-master/libs
  make all
}

do_install() {
  mkdir -p ${S}/image/usr/bin ${S}/image/usr/lib ${S}/image/usr/include
  cp ${S}/binder-for-linux-master/servicemanager/servicemanager ${S}/image/usr/bin
  cp ${S}/binder-for-linux-master/libs/libbinder.a ${S}/image/usr/lib
  cp ${S}/binder-for-linux-master/libs/include/* ${S}/image/usr/include -fr
  cp ${S}/binder-for-linux-master/driver ${S}/image/usr/include/ -fr
  cp ${S}/image/* ${TMPDIR}/sysroots/${MACHINE}/ -fr
}

