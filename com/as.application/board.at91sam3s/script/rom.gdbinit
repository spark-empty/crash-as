target remote localhost:2331

monitor endian little

monitor flash device = AT91SAM3S4

monitor flash download = 1

monitor flash breakpoints = 1

monitor sleep 100

monitor reset

monitor speed 1000

monitor sleep 100

echo load at91sam3s.s19
load at91sam3s.s19

echo symbol-file at91sam3s.exe
file at91sam3s.exe

echo monitor sleep 100

monitor reset

continue
