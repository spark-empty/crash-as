#! /bin/sh

# show usage
show_usage="args: [-g, -d, -i, -s]	\
                  [--gui, --debug, --initrd, --systemd, --x86]"
opt_gui="no"
opt_debug="no"
opt_initrd="no"
opt_systemd="no"
system="arm"
image="zImage"
root="/dev/mmcblk0p2"

# checking page http://www.cnblogs.com/FrankTan/archive/2010/03/01/1634516.html
# ":" "::" means parameter
GETOPT_ARGS=`getopt -o gdis -al gui,debug,initrd,systemd,x86, -- "$@"`
eval set -- "$GETOPT_ARGS"
# get parameter
while [ -n "$1" ]
do
    case "$1" in
        -g|--gui) opt_gui="yes"; shift 1;;
        -d|--debug) opt_debug="yes"; shift 1;;
        -i|--initrd) opt_initrd="yes"; shift 1;;
        -s|--systemd) opt_systemd="yes"; shift 1;;
		--x86) system="x86_64"; image="bzImage"; root="/dev/sda2" shift 1;;
        --) break ;;
        *) echo $1,$show_usage; break ;;
    esac
done

echo "#! /bin/sh" > tmp_qemu_run.sh
echo "cd out" >> tmp_qemu_run.sh
echo "qemu-system-${system} -kernel rootfs/${image} \\" >> tmp_qemu_run.sh
if [ $system = "arm" ]; then
	echo "  -dtb rootfs/vexpress-v2p-ca9.dtb -M vexpress-a9 \\" >> tmp_qemu_run.sh
	echo "  -smp 4 -m 512M	\\" >> tmp_qemu_run.sh
fi

if [ $opt_initrd = "yes" ]; then
	echo "  -initrd ramdisk.cpio \\" >> tmp_qemu_run.sh
fi

if [ $system = "arm" ]; then
echo "  -sd sdcard.img \\" >> tmp_qemu_run.sh
else
echo "  -hda sdcard.img \\" >> tmp_qemu_run.sh
fi

if [ $opt_initrd = "yes" ]; then
	echo "  -append \"rdinit=/linuxrc root=/dev/ram rw \\" >> tmp_qemu_run.sh
else
  if [ $opt_systemd = "yes" ]; then
    echo "  -append \"init=/usr/lib/systemd/systemd root=${root} rw \\" >> tmp_qemu_run.sh
  else
    echo "  -append \"init=/linuxrc root=${root} rw \\" >> tmp_qemu_run.sh
  fi
fi

if [ $opt_gui = "no" ]; then
	echo "    console=ttyAMA0 \\" >> tmp_qemu_run.sh
else
	echo "    console=tty0 console=ttyAMA0 \\" >> tmp_qemu_run.sh
fi  

echo "    loglevel=7\" \\" >> tmp_qemu_run.sh

if [ $opt_gui = "no" ]; then
	echo "  -nographic \\" >> tmp_qemu_run.sh
else
	echo "  -serial stdio -net nic -net user \\" >> tmp_qemu_run.sh
fi

if [ $opt_debug = "yes" ]; then
	echo "  -s -S	\\" >> tmp_qemu_run.sh
fi

echo "" >> tmp_qemu_run.sh

chmod +x tmp_qemu_run.sh
./tmp_qemu_run.sh
exit
