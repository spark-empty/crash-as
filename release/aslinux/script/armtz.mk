# make file to study the arm trust-zone techology
# start from a clean directory,
# ln -fs /as/release/aslinux/script/armtz.mk makefile

# arm or aarch64
ARCH ?= aarch64

ifeq ($(ARCH),arm)
export PLATFORM?=vexpress-qemu_virt 
export CROSS_COMPILE?=arm-linux-gnueabihf-
export TARGET?=default
else
export PLATFORM?=vexpress-qemu_armv8a
export CROSS_COMPILE?=aarch64-linux-gnu-
export TARGET?=qemu_v8
endif

POKY=poky-${ARCH}
export REPO_URL?='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/'

default:all

qemu-tz:
	@git clone https://git.linaro.org/virtualization/qemu-tz.git
	@(cd qemu-tz;git submodule update --init dtc)

qemu-tztest:
	@git clone https://git.linaro.org/virtualization/qemu-tztest.git

qemu:
	@git clone git://git.qemu-project.org/qemu.git

asqemutz:qemu-tz
	@(cd qemu-tz;./configure;make)

asqemutztest:qemu-tztest
	@(cd qemu-tztest;./configure --arch=$(ARCH);make)

test:
ifeq ($(ARCH),arm)
	@(./qemu-tz/arm-softmmu/qemu-system-arm -bios ./qemu-tztest/tztest.img	\
        -serial stdio -display none -m 1024 -machine type=virt -cpu cortex-a15)
else
	@(./qemu-tz/aarch64-softmmu/qemu-system-aarch64 -bios ./qemu-tztest/tztest.img	\
		-serial stdio -display none -m 1024 -machine type=virt -cpu cortex-a57)
endif

optee_os:
	@git clone https://github.com/OP-TEE/optee_os.git -b 2.3.0

# need: sudo apt-get install libmagickwand-dev && sudo pip install Wand
asoptee_os:optee_os
	@(cd optee_os; make)

optee_client:
	@git clone https://github.com/OP-TEE/optee_client.git -b 2.3.0

asoptee_client:optee_client
	@(cd optee_client; make)

all-legency: asqemutz asqemutztest 
	@(echo "  >> build done")

# after reading https://github.com/OP-TEE/build, so drop the above action, using repo.
$(CURDIR)/${POKY}:
	@(mkdir -p $@)
	@(cd $@; repo init -u https://github.com/OP-TEE/manifest.git -m ${TARGET}.xml; repo sync)
	@(cd $@/qemu;git submodule update --init dtc)

all:$(CURDIR)/${POKY}
	@(cd $</build;make toolchains; make all)

runqemu:
	@nc -z  127.0.0.1 54320 || gnome-terminal -t ""Normal"" -x ${POKY}/soc_term/soc_term 54320 &
	@nc -z  127.0.0.1 54321 || gnome-terminal -t ""Secure"" -x ${POKY}/soc_term/soc_term 54321 &
	@while ! nc -z 127.0.0.1 54320 || ! nc -z 127.0.0.1 54321; do sleep 1; done
	@(${POKY}/qemu/arm-softmmu/qemu-system-arm \
		-nographic \
		-serial tcp:localhost:54320 -serial tcp:localhost:54321 \
		-machine virt -machine secure=on -cpu cortex-a15 \
		-m 1057 \
		-bios ${POKY}/out/bios-qemu/bios.bin)


