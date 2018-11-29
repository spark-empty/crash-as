@echo off
start qemu-system-arm.exe -M mini2440 -kernel ../../../../release/ascore/out/s3c2440a.exe -serial tcp:127.0.0.1:1200,server,nowait -gdb tcp::2331 -S

rem start qemu-system-arm.exe -M mini2440 -kernel ../../../../release/ascore/out/s3c2440a.exe -serial tcp:127.0.0.1:1200,server

rem start qemu-system-arm.exe -M mini2440 -kernel ../../../../release/ascore/out/s3c2440a.exe -serial tcp:127.0.0.1:1200,server,nowait

start telnet 127.0.0.1 1200

