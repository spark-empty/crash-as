
LM3S6965
==
	get the related resource files from the below 2 links.
	http://www.ti.com/product/LM3S6965/toolssoftware
	http://www.ti.com/tool/pdl-lm3s-exe
	
	http://www.mcu123.com/product/LM3S/PDL-LM3S-1716_DriverLib.zip

	qemu-arm-system do support the machine lm3s6965evb, so use this qemu machine to do simulation of real hardware, and one of the serial port to do simulation of CAN.

	Let's start.

# Command:

	qemu-system-arm  -cpu cortex-m3 -nographic -monitor null -serial null -semihosting -machine lm3s6965evb -kernel main.elf
	qemu-system-arm  -cpu cortex-m3 -nographic -monitor null -serial stdio -semihosting -machine lm3s6965evb -kernel main.elf
	
	Check http://mathslinux.org/?p=210 about -serial
	It is also possible to attach gdb to qemu (you'll need two windows):

    qemu-system-arm -cpu cortex-m3 -nographic -monitor null -serial stdio -semihosting -machine lm3s6965evb -gdb tcp::2345 -S -kernel lm3s6965evb.exe
    arm-none-eabi-gdb lm3s6965evb.exe

	"2345" is simply a tcp port number chosen randomly. Within gdb execute the following commands:

	(gdb) target remote localhost:2345
	(gdb) load
	(gdb) break main
	(gdb) continue
