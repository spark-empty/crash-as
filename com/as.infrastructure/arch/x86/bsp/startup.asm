
		;;  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		;;                                kernel.asm
		;;  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		;;                                                      Forrest Yu, 2005
		;;  updated by parai for the support of multiboot
		;;  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


		%include "sconst.inc"

		;;/* the magic number for the multiboot header.  */
		MULTIBOOT_HEADER_MAGIC equ 0x1BADB002

		;;/* the flags for the multiboot header.  */
		MULTIBOOT_HEADER_FLAGS equ 0x00000003

		;;  导入函数
		extern	cstart
		extern	kmain

		;;  导入全局变量
		extern	gdt_ptr
		extern	idt_ptr

		[SECTION .bss]
		StackSpace		resb	2 * 1024
		global StackTop
StackTop:						; 栈顶

		[section .init]			; 代码在此

		global _start			; 导出 _start

_start:
	; for the purpose to check kernel is started

		jmp	multiboot_entry

		;;/* Align 32 bits boundary.  */
		align	4

	;;/* multiboot header.  */
multiboot_header:

		;;/* magic */
		dd	MULTIBOOT_HEADER_MAGIC
		;; /* flags */
		dd	MULTIBOOT_HEADER_FLAGS
		;; /* checksum */
		dd	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

		;;  此时内存看上去是这样的（更详细的内存情况在 LOADER.ASM 中有说明）：
		;;               ┃                                    ┃
		;;               ┃                 ...                ┃
		;;               ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃■■■■■■Page  Tables■■■■■■┃
		;;               ┃■■■■■(大小由LOADER决定)■■■■┃ PageTblBase
		;;     00101000h ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃■■■■Page Directory Table■■■■┃ PageDirBase = 1M
		;;     00100000h ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃□□□□ Hardware  Reserved □□□□┃ B8000h ← gs
		;;        9FC00h ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃■■■■■■■LOADER.BIN■■■■■■┃ somewhere in LOADER ← esp
		;;        90000h ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃■■■■■■■KERNEL.BIN■■■■■■┃
		;;        80000h ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃■■■■■■■■KERNEL■■■■■■■┃ 30400h ← KERNEL 入口 (KernelEntryPointPhyAddr)
		;;        30000h ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┋                 ...                ┋
		;;               ┋                                    ┋
		;;            0h ┗━━━━━━━━━━━━━━━━━━┛ ← cs, ds, es, fs, ss
		;;
		;;
		;;  GDT 以及相应的描述符是这样的：
		;;
		;; 		              Descriptors               Selectors
		;;               ┏━━━━━━━━━━━━━━━━━━┓
		;;               ┃         Dummy Descriptor           ┃
		;;               ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃         DESC_FLAT_C    (0～4G)     ┃   8h = cs
		;;               ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃         DESC_FLAT_RW   (0～4G)     ┃  10h = ds, es, fs, ss
		;;               ┣━━━━━━━━━━━━━━━━━━┫
		;;               ┃         DESC_VIDEO                 ┃  1Bh = gs
		;;               ┗━━━━━━━━━━━━━━━━━━┛
		;;
		;;  注意! 在使用 C 代码的时候一定要保证 ds, es, ss 这几个段寄存器的值是一样的
		;;  因为编译器有可能编译出使用它们的代码, 而编译器默认它们是一样的. 比如串拷贝操作会用到 ds 和 es.
		;;
		;;

multiboot_entry:
		;;  把 esp 从 LOADER 挪到 KERNEL
		mov	esp, StackTop		; 堆栈在 bss 段中

		sgdt	[gdt_ptr]		; cstart() 中将会用到 gdt_ptr
		call	cstart			; 在此函数中改变了gdt_ptr，让它指向新的GDT
		lgdt	[gdt_ptr]		; 使用新的GDT

		lidt	[idt_ptr]
		jmp	SELECTOR_KERNEL_CS:csinit
csinit:							; “这个跳转指令强制使用刚刚初始化的结构”——<<OS:D&I 2nd>> P90.

	xor	eax, eax
	mov	ax, SELECTOR_TSS
	ltr	ax

	jmp	kmain

