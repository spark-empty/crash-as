target remote localhost:2331

monitor endian little

monitor flash device = STM32F107VC

monitor flash download = 1

monitor flash breakpoints = 1

monitor sleep 100

monitor reset

monitor speed 1000

monitor sleep 100

echo load stm32f107vc.s19
load stm32f107vc.s19

echo symbol-file stm32f107vc.exe
file stm32f107vc.exe

echo monitor sleep 100

echo set *  =

monitor reg sp=0x00000000

monitor reg pc=0x08000004

continue

