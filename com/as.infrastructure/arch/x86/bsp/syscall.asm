%include "sconst.inc"

INT_VECTOR_SYS_CALL equ 0x90
_NR_dispatch        equ 0

global  dispatch

bits 32
[section .text]

; void dispatch(int cmd, void* param)
dispatch:
    mov eax, _NR_dispatch
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    int INT_VECTOR_SYS_CALL
    ret
