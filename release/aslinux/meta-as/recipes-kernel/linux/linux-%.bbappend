# for aslinux
# take meta-intel-iot-security/meta-integrity/recipes-kernel/linux as a reference
FILESEXTRAPATHS_prepend := "${THISDIR}/linux:"

SRC_URI_append = "file://0001-asvirt-driver-for-kernel-v4.x.patch \
			   "
