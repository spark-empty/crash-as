#/**
#    @file        CW_Startup_vle.s
#    @version     2.0.0
#
#    @brief       AUTOSAR Sample_app - Startup file for PowerPC VLE.
#    @details     Startup file for PowerPC VLE.
#    
#    Project      : AUTOSAR 3.0 MCAL
#    Patform      : PA
#    Peripheral   : 
#    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM
#    
#    Autosar Version       : 1.9.0
#    Autosar Revision      : ASR_REL_1_9_REV_0003
#    Autosar Conf. Variant : 
#    Software Version      : 2.0.0
#    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214
#
#    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
#    All Rights Reserved.
#*/
#/*==================================================================================================
##==================================================================================================*/


#',)#==================================================================================================*/
    #Set the compiler using generated file by BEART
    .set COMPILER_GHS,  0
    .set COMPILER_DIAB, 1
    .set COMPILER_CW,   2
    
    .include "compiler_used.s"
    
    .global __start
    .global _start
    .extern main	     # Defined in main.c
    .extern __STACK_SIZE     # Defined in the linker file
    .extern __SP_INIT        # Defined in the linker file
    .extern __SP_END         # Defined in the linker file
    .extern __SRAM_LOAD      # Defined in the linker file
    .extern __SRAM_LOAD_SIZE # Defined in the linker file
    .extern __IV_ADDR        # Defined in the linker file
    .extern INT_SRAM_SIZE    # Defined in the linker file
    .extern INT_SRAM_START   # Defined in the linker file
    .extern SBSS_SRAM_SIZE   # Defined in the linker file
    .extern SBSS_SRAM_START  # Defined in the linker file
    .extern BSS_SRAM_SIZE    # Defined in the linker file
    .extern BSS_SRAM_START   # Defined in the linker file
    .extern SDATA_RO_START   # Defined in the linker file
    .extern SDATA_RW_START   # Defined in the linker file 
    .extern RC_PPC_SDATA2_SIZE # Defined in the linker file 
    .extern RC_PPC_SDATA2_SRC  # Defined in the linker file 
    .extern RC_PPC_SDATA2_DEST # Defined in the linker file
    .extern RC_SDATA_SIZE # Defined in the linker file 
    .extern RC_SDATA_SRC  # Defined in the linker file 
    .extern RC_SDATA_DEST # Defined in the linker file
    .extern RC_DATA_SIZE # Defined in the linker file 
    .extern RC_DATA_SRC  # Defined in the linker file 
    .extern RC_DATA_DEST # Defined in the linker file
    .extern RC_RAMCODE_SIZE # Defined in the linker file 
    .extern RC_RAMCODE_SRC  # Defined in the linker file 
    .extern RC_RAMCODE_DEST # Defined in the linker file


    .extern IVOR0_Handler 
	.extern IVOR1_Handler 
	.extern IVOR2_Handler 
	.extern IVOR3_Handler 
	.extern IVOR4_Handler 
	.extern IVOR5_Handler 
	.extern IVOR6_Handler 
	.extern IVOR7_Handler 
	.extern IVOR8_Handler 
	.extern IVOR9_Handler 
	.extern IVOR10_Handler
	.extern IVOR11_Handler
	.extern IVOR12_Handler
	.extern IVOR13_Handler
	.extern IVOR14_Handler
	.extern IVOR15_Handler
	.extern IVOR32_Handler
	.extern IVOR33_Handler
	.extern IVOR34_Handler

#.section .init_cw,text_vle   # The "text" generates symbols for debug
.section .text_vle   # The "text" generates symbols for debug

    _start:
    __start:
    .align 4
    xor  r0, r0, r0
    xor  r1, r1, r1
    xor  r2, r2, r2
    xor  r3, r3, r3
    xor  r4, r4, r4
    xor  r5, r5, r5
    xor  r6, r6, r6
    xor  r7, r7, r7
    xor  r8, r8, r8
    xor  r9, r9, r9
    xor  r10, r10, r10
    xor  r11, r11, r11
    xor  r12, r12, r12
    xor  r13, r13, r13
    xor  r14, r14, r14
    xor  r15, r15, r15
    xor  r16, r16, r16
    xor  r17, r17, r17
    xor  r18, r18, r18
    xor  r19, r19, r19
    xor  r20, r20, r20
    xor  r21, r21, r21
    xor  r22, r22, r22
    xor  r23, r23, r23
    xor  r24, r24, r24
    xor  r25, r25, r25
    xor  r26, r26, r26
    xor  r27, r27, r27
    xor  r28, r28, r28
    xor  r29, r29, r29
    xor  r30, r30, r30
    xor  r31, r31, r31
 
#/*******************************************************************/
#/* Freescale Guidance 1 - Init registers to avoid lock-step issues */
#/* N/A                                                             */
#/*******************************************************************/

#/*******************************************************************/
#/* Freescale Guidance 2 - MMU Initialization for CPU1*/
#/* TLB0 - FLASH
#/*  TLB1 - SRAM
#/*  TLB2 - Peripherals (A/B)
#/*******************************************************************/    
    
#/* Set up MMU for pbridgeB (configured by BAM)                                */
#/* MAS0=0x10000000: Select TLB #0                                             */
#/* MAS1=0xC0000500: TLB is valid and protected, TID & TS=0, Page size = 1M    */
#/* MAS2=0xF000000A: EPN=0xFFF00, non-VLE, Write-back, Cache Inhibited, Guarded, BigEndian  */
#/* MAS2=0xF000003F: RPN=0xFFF00, User X, Supv X, User W, Supv W, User R, Supv R */

#/* - add here your code to change the default MMU settings for pbridgeB  */

#/* Set up MMU for Internal Flash  (configured by BAM)                         */
#/* MAS0=0x10010000: Select TLB #1                                             */
#/* MAS1=0xC0000700: TLB is valid and protected, TID & TS=0, Page size = 16M   */
#/* MAS2=0x00000020: EPN=0x00000, VLE, Write-back, Cacheable, Not-guarded, BigEndian  */
#/* MAS2=0x0000003F: RPN=0x00000, User X, Supv X, User W, Supv W, User R, Supv R */

#/* - add here your code to change the default MMU settings for Internal Flash */

#/* Set up MMU for External RAM   (configured by BAM)                          */
#/* MAS0=0x10020000: Select TLB #2                                             */
#/* MAS1=0xC0000700: TLB is valid and protected, TID & TS=0, Page size = 16M   */
#/* MAS2=0x20000020: EPN=0x20000, VLE, Write-back, Cacheable, Not-guarded, BigEndian  */
#/* MAS2=0x2000003F: RPN=0x20000, User X, Supv X, User W, Supv W, User R, Supv R */

#/* - add here your code to change the default MMU settings for External RAM   */

#/* Set up MMU for Internal RAM   (configured by BAM)                          */
#/* MAS0=0x10030000: Select TLB #3                                             */
#/* MAS1=0xC0000400: TLB is valid and protected, TID & TS=0, Page size = 256K  */
#/* MAS2=0x40000028: EPN=0x40000, VLE, Write-back, Cache Inhibited, Not-guarded, BigEndian */
#/* MAS2=0x4000003F: RPN=0x40000, User X, Supv X, User W, Supv W, User R, Supv R */

#/* - add here your code to change the default MMU settings for Internal RAM   */

#/* Set up MMU for pbridgeA (configured by BAM)                                */
#/* MAS0=0x10040000: Select TLB #4                                            */
#/* MAS1=0xC0000500: TLB is valid and protected, TID & TS=0, Page size = 1M    */
#/* MAS2=0xC000000A: EPN=0xC3F00, non-VLE, Write-back, Cache Inhibited, Guarded, BigEndian  */
#/* MAS2=0xC000003F: RPN=0xC3F00, User X, Supv X, User W, Supv W, User R, Supv R */

#/* - add here your code to change the default MMU settings for pbridgeB  */

#/* ASM_KEYWORD(" e_lis   r3, 0x1000 ");  */
#/* ASM_KEYWORD(" mtMAS0 r3          ");  */
#/* ASM_KEYWORD(" e_lis   r4, 0xC000 ");  */
#/* ASM_KEYWORD(" e_or2i  r4, 0x0700 ");  */
#/* ASM_KEYWORD(" mtMAS1 r4          ");  */
#/* ASM_KEYWORD(" e_lis   r5, 0x0000 ");  */
#/* ASM_KEYWORD(" e_or2i  r5, 0x0028 ");  */
#/* ASM_KEYWORD(" mtMAS2 r5          ");  */
#/* ASM_KEYWORD(" e_lis  r6, 0x0000  ");  */
#/* ASM_KEYWORD(" e_or2i r6, 0x003f  ");  */
#/* ASM_KEYWORD(" mtMAS3 r6          ");  */
#/* ASM_KEYWORD(" tlbwe              ");  */
                    
                                                                                
#/******************************************************************/            
#/* Autosar Guidance 1 - The start-up code shall initialize the    */            
#/* base addresses for interrupt and trap vector tables. These base*/            
#/* addresses are provided as configuration parameters or          */            
#/* linker/locator setting.                                        */            
#/******************************************************************/            
    # /* Initialize IVPR register to address of Interrupt Vector Table */         
    e_lis r5, __IV_ADDR@h                                   
    e_or2i  r5,__IV_ADDR@l                                  
    mtIVPR r5                                                 
                                                                  
    se_mr   r0, r31                                            
                                                                  
    e_lis r5,IVOR0_Handler@h                                  
    e_or2i r5,IVOR0_Handler@l                                 
    mtspr   400, r5                                        
                                                              
    e_lis r5,IVOR1_Handler@h                                  
    e_or2i r5,IVOR1_Handler@l                                 
    mtspr   401, r5                                        
                                                              
    e_lis r5, IVOR2_Handler@h                                 
    e_or2i r5, IVOR2_Handler@l                                
    mtspr   402, r5                                       
                                                              
    e_lis r5, IVOR3_Handler@h                                 
    e_or2i r5, IVOR3_Handler@l                                
    mtspr   403, r5                                            
                                                                  
    e_lis r5, __IV_ADDR@h                                    
    e_or2i r5, __IV_ADDR@l                                   
    mtspr   404, r5                                       
                                                                  
    e_lis r5, IVOR5_Handler@h                                 
    e_or2i r5, IVOR5_Handler@l                                
    mtspr   405, r5                                       
                                                              
    e_lis r5, IVOR6_Handler@h                                 
    e_or2i r5, IVOR6_Handler@l                                
    mtspr   406, r5                                      
                                                              
    e_lis r5, IVOR7_Handler@h                                 
    e_or2i r5, IVOR7_Handler@l                                
    mtspr   407, r5                                       
                                                              
    e_lis r5, IVOR8_Handler@h                                 
    e_or2i r5, IVOR8_Handler@l                                
    mtspr   408, r5                                        
                                                              
    e_lis r5, IVOR9_Handler@h                                 
    e_or2i r5, IVOR9_Handler@l                                
    mtspr   409, r5                                       
                                                              
    e_lis r5, IVOR10_Handler@h                                
    e_or2i r5, IVOR10_Handler@l                               
    mtspr   410, r5                                       
                                                              
    e_lis r5, IVOR11_Handler@h                                
    e_or2i r5, IVOR11_Handler@l                               
    mtspr   411, r5                                       
                                                              
    e_lis r5, IVOR12_Handler@h                                
    e_or2i r5, IVOR12_Handler@l                               
    mtspr   412, r5                                       
                                                              
    e_lis r5, IVOR13_Handler@h                                
    e_or2i r5, IVOR13_Handler@l                               
    mtspr   413, r5                                       
                                                              
    e_lis r5, IVOR14_Handler@h                                
    e_or2i r5, IVOR14_Handler@l                               
    mtspr   414, r5                                     
                                                              
    e_lis r5, IVOR15_Handler@h                                
    e_or2i r5, IVOR15_Handler@l                               
    mtspr   415, r5                                   
                                                              
    e_lis r5, IVOR32_Handler@h                                
    e_or2i r5, IVOR32_Handler@l                               
    mtspr   528, r5                                      
                                                              
    e_lis r5, IVOR33_Handler@h                                
    e_or2i r5, IVOR33_Handler@l                               
    mtspr   529, r5                                      
                                                              
    e_lis r5, IVOR34_Handler@h                                
    e_or2i r5, IVOR34_Handler@l                               
    mtspr   530, r5                                        
                                                                                
    #/* define MSR mask to enable Machine Check and Exception / IRQ */           
    .equ    MSR_Mask, 0x00009000 
    mfmsr   r5 
    e_lis   r6, MSR_Mask@h 
    e_or2i  r6, MSR_Mask@l 
    se_or   r5, r6 
    mtmsr   r5 
    se_isync 
   
#/******************************************************************/
#/* Autosar Guidance 2 - The start-up code shall initialize the    */
#/* interrupt stack pointer, if an interrupt stack is              */
#/* supported by the MCU. The interrupt stack pointer base address */
#/* and the stack size are provided as configuration parameter or  */
#/* linker/locator setting.                                        */
#/* MPC5516 - Not Supported                                        */
#/******************************************************************/
    
#/******************************************************************/
#/* Autosar Guidance 3 - The start-up code shall initialize the    */
#/* user stack pointer. The user stack pointer base address and    */
#/* the stack size are provided as configuration parameter or      */
#/* linker/locator setting.                                        */
#/******************************************************************/
     e_lis   r1, __SP_INIT@h
     e_or2i    r1, __SP_INIT@l

#/******************************************************************/
#/* Autosar Guidance 4 - If the MCU supports context save          */
#/* operation, the start-up code shall initialize the memory which */
#/* is used for context save operation. The maximum amount of      */
#/* consecutive context save operations is provided as             */
#/* configuration parameter or linker/locator setting.             */
#/* MPC5516 - N/A                                                  */
#/******************************************************************/

#/******************************************************************/
#/* Autosar Guidance 5 - The start-up code shall ensure that the   */
#/* MCU internal watchdog shall not be serviced until the watchdog */
#/* is initialized from the MCAL watchdog driver. This can be      */
#/* done for example by increasing the watchdog service time.      */
#/* MPC5516 - N/A - Taken care of by BAM or HW                     */
#/******************************************************************/
    e_lis     r6,0xfff3 
    e_or2i    r6,0x8010 
    e_li      r7,0xC520 
    se_stw    r7,0x0(r6)
    e_li      r7,0xD928 
    se_stw    r7,0x0(r6)    # Disengage soft-lock */

    e_lis     r6,0xfff3 
    e_or2i    r6,0x8000 
    e_lis     r7,0xff00 
    e_or2i    r7,0x10A 
    se_stw    r7,0x0(r6)    # WEN = 0 */
#/******************************************************************/
#/* Autosar Guidance 6 - If the MCU supports cache memory for data */
#/* and/or code, it shall be initialized and enabled in the        */
#/* start-up code.                                                 */
#/* MPC5516 - N/A, No Cache                                        */
#/******************************************************************/

#/******************************************************************/
#/* Autosar Guidance 7 - The start-up code shall initialize MCU    */
#/* specific features of internal memory like memory protection.   */
#/* N/A - will be handled by Autosar OS                            */
#/******************************************************************/

#/******************************************************************/
#/* Autosar Guidance 8 - If external memory is used, the memory    */
#/* shall be initialized in the start-up code. The start-up code   */
#/* shall be prepared to support different memory configurations   */
#/* depending on code location. Different configuration options    */
#/* shall be taken into account for code execution from            */
#/* external/internal memory.                                      */
#/* N/A - external memory is not used                              */
#/******************************************************************/

#/******************************************************************/
#/* Autosar Guidance 9 - The settings of the different memories    */
#/* shall be provided to the start-up code as configuration        */
#/* parameters.                                                    */
#/* N/A - all memories are already configured                      */
#/******************************************************************/

#/******************************************************************/
#/* Autosar Guidance 10 - In the start-up code a default           */
#/* initialization of the MCU clock system shall be performed      */
#/* including global clock prescalers.                             */
#/******************************************************************/

#/******************************************************************/
#/* Autosar Guidance 11 - The start-up code shall enable           */
#/* protection mechanisms for special function registers(SFR�s),   */
#/* if supported by the MCU.                                       */
#/* N/A - will be handled by Autosar OS                            */
#/******************************************************************/

#/* Setup the PBRIDGE bus bridge and its protection features. Avoid that any access  */
#/* to a peripheral fails due to protection settings  For this purpose remove any */
#/* protection feature that might have been defined by default settings.          */
#/* To do so, we write b'0111 (0x7) into every protection field MPCR of the       */
#/* PBRIDGE_x_MPCR0 register, which will setup all 8 master ports accordingly.     */
#/*  The meaning of these four bits is as follows:                                */
#/*   0 - Master Buffer Writes: no (Write accesses are not bufferable)            */
#/*   1 - Master Trusted for Reads                                                */
#/*   1 - Master Trusted for Writes                                               */
#/*   1 - Master Priviledge Level: accesses are not forced to user-mode           */
#/* NOTE: we do only setup the masters M0-M7, M8-M15 are not modified at all.     */
    
#    .equ PBRIDGE_A_MPCR0, 0xC3F00000
#    e_lis   r4, PBRIDGE_A_MPCR0@ha
#    e_or2i  r4, PBRIDGE_A_MPCR0@l
#    e_lis   r5, 0x77007777@ha
#    e_or2i  r5, 0x77007777@l
#    e_stw   r5, 0(r4)
#    e_li r5, 0
   
#    .equ PBRIDGE_B_MPCR0, 0xFFF00000
#    e_lis   r4, PBRIDGE_B_MPCR0@ha
#    e_or2i  r4, PBRIDGE_B_MPCR0@l
#    e_lis   r5, 0x77007777@ha
#    e_or2i  r5, 0x77007777@l
#    e_stw   r5, 0(r4)
#    e_li r5, 0
   
#/* Allow non-priviledged access to all peripherals (on and off-platform). This is */
#/* achieved by modifying the PACR and OPACR registers in the PBRIDGE_X            */
#/* To do so, we write b'0000 (0x0) into every peripheral access control reg.      */
#/* The meaning of these four bits is as follows:                                  */
#/*   0 - Buffer Writes: no                                                        */
#/*   0 - Supervisor Protect: periph. doesn't require supervisor priviledge level  */
#/*   0 - Write Protect: no (peripheral allows write accesses)                     */
#/*   0 - Trusted Protect: no (accesses from an untrusted master allowed)          */

#   .equ PBRIDGE_A_PACR0_7, 0xC3F00020
#   e_lis   r4, PBRIDGE_A_PACR0_7@ha
#   e_or2i  r4, PBRIDGE_A_PACR0_7@l 
#   e_stw   r5, 0(r4)

#   .equ PBRIDGE_A_OPACR0_7, 0xC3F00040
#   e_lis   r4, PBRIDGE_A_OPACR0_7@ha
#   e_or2i  r4, PBRIDGE_A_OPACR0_7@l
#   e_stw   r5, 0(r4)        

#   .equ PBRIDGE_A_OPACR8_15, 0xC3F00044
#   e_lis   r4, PBRIDGE_A_OPACR8_15@ha
#   e_or2i  r4, PBRIDGE_A_OPACR8_15@l
#   e_stw   r5, 0(r4)
   
#   .equ PBRIDGE_A_OPACR16_23, 0xC3F00048
#   e_lis   r4, PBRIDGE_A_OPACR16_23@ha
#   e_or2i  r4, PBRIDGE_A_OPACR16_23@l
#   e_stw   r5, 0(r4)
   
#   .equ PBRIDGE_A_OPACR24_31, 0xC3F0004C
#   e_lis   r4, PBRIDGE_A_OPACR24_31@ha
#   e_or2i  r4, PBRIDGE_A_OPACR24_31@l
#   e_stw   r5, 0(r4)  

#    .equ PBRIDGE_B_PACR0_7, 0xFFF00020
#    e_lis   r4, PBRIDGE_B_PACR0_7@ha
#    e_or2i  r4, PBRIDGE_B_PACR0_7@l
#    e_stw   r5, 0(r4)

#    .equ PBRIDGE_B_PACR8_15, 0xFFF00024
#    e_lis   r4, PBRIDGE_B_PACR8_15@ha
#    e_or2i  r4, PBRIDGE_B_PACR8_15@l
#    e_stw   r5, 0(r4)
   
#    .equ PBRIDGE_B_PACR16_23, 0xFFF00028
#    e_lis   r4, PBRIDGE_B_PACR16_23@ha
#    e_or2i  r4, PBRIDGE_B_PACR16_23@l
#    e_stw   r5, 0(r4)
   
#   .equ PBRIDGE_B_OPACR0_7, 0xFFF00040
#   e_lis   r4, PBRIDGE_B_OPACR0_7@ha
#   e_or2i  r4, PBRIDGE_B_OPACR0_7@l
#   e_stw   r5, 0(r4)     

#    .equ PBRIDGE_B_OPACR8_15, 0xFFF00044
#    e_lis   r4, PBRIDGE_B_OPACR8_15@ha
#    e_or2i  r4, PBRIDGE_B_OPACR8_15@l
#    e_stw   r5, 0(r4)  
   
#    .equ PBRIDGE_B_OPACR16_23, 0xFFF00048
#    e_lis   r4, PBRIDGE_B_OPACR16_23@ha
#    e_or2i  r4, PBRIDGE_B_OPACR16_23@l
#    e_stw   r5, 0(r4)
   
#    .equ PBRIDGE_B_OPACR24_31, 0xFFF0004C
#    e_lis   r4, PBRIDGE_B_OPACR24_31@ha
#    e_or2i  r4, PBRIDGE_B_OPACR24_31@l
#    e_stw   r5, 0(r4)            
                                                                                                    

#/******************************************************************/
#/* Autosar Guidance 12 - The start-up code shall initialize all   */
#/* necessary write once registers or registers common to several  */
#/* drivers where one write, rather than repeated writes, to the   */
#/* register is required or highly desirable.                      */
#/******************************************************************/
#/* TBD - MSR */

#/******************************************************************/
#/* Autosar Guidance 13 - The start-up code shall initialize a     */
#/* minimum amount of RAM in order to allow proper execution of    */
#/* the MCU driver services and the caller of these services.      */
#/******************************************************************/
#/* MPC55xx - internal ram must be initialized for error correction*/
#/******************************************************************/
 .if LINKED_TO == FLASH               #/* LINKED_TO == FLASH/INTRAM is defined in compiler_used.s */
      e_lis   r5, INT_SRAM_SIZE@h     #/* Number of 4 byte segments */
      e_or2i    r5, INT_SRAM_SIZE@l   #/* Number of 4 byte segments */
      se_mtctr r5                     #/* configure control register for use with e_bdnz */

#/* start address of the internal SRAM */
      e_lis   r5,INT_SRAM_START@h
      e_or2i    r5, INT_SRAM_START@l

#/* Repeat */
     sram_loop:
     e_stmw  r16,0(r5)   #/* write 0 to to L2RAM and update r5 address */
     e_addi r5,r5,64 
      e_bdnz   sram_loop #/* loop for 64k of L2RAM */
 .endif

#/************************/
#/* Erase ".sbss Section" */
#/************************/
      xor   r0, r0, r0 
      e_lis  r5, SBSS_SRAM_SIZE@h       #/* Number of words */
      e_or2i   r5, SBSS_SRAM_SIZE@l   #/* Number of words */
      or.  r5, r5, r5                 #/* Number of words */
      e_beq    sram_erase1
      se_mtctr r5                        #/* configure control register for use with e_bdnz */

#/* start address of the sbss section */
      e_lis   r5,SBSS_SRAM_START@h
      e_or2i    r5, SBSS_SRAM_START@l
      xor   r0, r0, r0 
      e_subi  r5,r5,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Repeat */
     sram_loop1:
      e_stwu   r0,4(r5)                 #/* write 0 to RAM and update r5 address */
      e_bdnz   sram_loop1
     sram_erase1:

#/************************/
#/* Erase ".bss Section" */
#/************************/
      e_lis   r5, BSS_SRAM_SIZE@h      #/* Number of words */
      e_or2i    r5, BSS_SRAM_SIZE@l  #/* Number of words */
      or.   r5, r5, r5               #/* Number of words */
      e_beq   sram_erase2
      se_mtctr r5                       #/* configure control register for use with e_bdnz */

#/* start address of the bss section */
      e_lis   r5, BSS_SRAM_START@h
      e_or2i    r5, BSS_SRAM_START@l
      e_subi  r5,r5,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Repeat */
     sram_loop2:
      e_stwu r0,4(r5)                  #/* write 0 to RAM and update r5 address, r0 must be zero */
      e_bdnz   sram_loop2
     sram_erase2:

#/******************************************************************/
#/* Copy  initialized data from Flash to SRAM                      */
#/******************************************************************/
#/*******************/
#/* .PPC.EMB.sdata0 */
#/*******************/
      e_lis   r5, RC_PPC_SDATA2_SIZE@h      #/* Number of words */
      e_or2i    r5, RC_PPC_SDATA2_SIZE@l  #/* Number of words */
      or.   r5, r5, r5                     #/* Number of words */
      e_beq   data_copy1
      se_mtctr r5                       #/* configure control register for use with e_bdnz */

#/* source address of the section */
      e_lis   r8, RC_PPC_SDATA2_SRC@h
      e_or2i    r8, RC_PPC_SDATA2_SRC@l
      e_subi  r8,r8,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Destination address of the section */
      e_lis   r9, RC_PPC_SDATA2_DEST@h
      e_or2i    r9, RC_PPC_SDATA2_DEST@l
      e_subi  r9,r9,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Repeat */
     data_copy_loop1:
      e_lwzu  r10,4(r8)
      e_stwu  r10,4(r9)
      e_bdnz  data_copy_loop1
    data_copy1:
#/**********/
#/* .sdata */
#/**********/
      e_lis   r5, RC_SDATA_SIZE@h      #/* Number of words */
      e_or2i    r5, RC_SDATA_SIZE@l      #/* Number of words */
      or.   r5, r5, r5                     #/* Number of words */
      e_beq   data_copy2
      se_mtctr r5                       #/* configure control register for use with e_bdnz */

#/* source address of the section */
      e_lis   r8, RC_SDATA_SRC@h
      e_or2i    r8, RC_SDATA_SRC@l
      e_subi  r8,r8,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Destination address of the section */
      e_lis   r9, RC_SDATA_DEST@h
      e_or2i    r9, RC_SDATA_DEST@l
      e_subi  r9,r9,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Repeat */
     data_copy_loop2:
      e_lwzu  r10,4(r8)
      e_stwu  r10,4(r9)
      e_bdnz  data_copy_loop2
     data_copy2:
#/**********/
#/* .data */
#/**********/
      e_lis   r5, RC_DATA_SIZE@h      #/* Number of words */
      e_or2i    r5, RC_DATA_SIZE@l      #/* Number of words */
      or.   r5, r5, r5                     #/* Number of words */
      e_beq   data_copy3
      se_mtctr r5                       #/* configure control register for use with e_bdnz */

#/* source address of the section */
      e_lis   r8, RC_DATA_SRC@h
      e_or2i    r8, RC_DATA_SRC@l
      e_subi  r8,r8,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Destination address of the section */
      e_lis   r9, RC_DATA_DEST@h
      e_or2i    r9, RC_DATA_DEST@l
      e_subi  r9,r9,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Repeat */
     data_copy_loop3:
      e_lwzu  r10,4(r8)
      e_stwu  r10,4(r9)
      e_bdnz  data_copy_loop3
     data_copy3:

#/************/
#/* .ramcode */
#/************/
      e_lis   r5, RC_RAMCODE_SIZE@h      #/* Number of words */
      e_or2i    r5, RC_RAMCODE_SIZE@l      #/* Number of words */
      or.   r5, r5, r5                     #/* Number of words */
      e_beq   data_copy4
      se_mtctr r5                       #/* configure control register for use with e_bdnz */

#/* source address of the section */
      e_lis   r8, RC_RAMCODE_SRC@h
      e_or2i    r8, RC_RAMCODE_SRC@l
      e_subi  r8,r8,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Destination address of the section */
      e_lis   r9, RC_RAMCODE_DEST@h
      e_or2i    r9, RC_RAMCODE_DEST@l
      e_subi  r9,r9,4                   #/* decrement by 4 to prepare for e_stwu in loop */

#/* Repeat */
     data_copy_loop4:
      e_lwzu  r10,4(r8)
      e_stwu  r10,4(r9)
      e_bdnz  data_copy_loop4
     data_copy4:


#/*********************************/
#/* Set the small ro data pointer */
#/*********************************/
      e_lis   r2, SDATA_RO_START@h
      e_or2i    r2, SDATA_RO_START@l

#/*********************************/
#/* Set the small rw data pointer */
#/*********************************/
      e_lis   r13, SDATA_RW_START@h
      e_or2i    r13, SDATA_RW_START@l

#/******************************************************************/
#/* Freescale Guidance 4 - Set up INTC                             */
#/******************************************************************/
    #/* Configure INTC for hardware vector mode */
    #/* S_REG_WRITE32(S_INTC_MCR,S_INTC_MCR_HVEN_ON|S_INTC_MCR_VTES_4BYTES); */

    #/* Setup main code priority */
    #/* S_REG_WRITE32(S_INTC_CPR,0); */

	e_lis	r7, 0xFFF5
	se_li	r0, 0x1
	e_add16i	r7, r7, -0x8000
	se_stw	r0, 0x0(r7)
	e_lis	r0, 0xFFF5
	se_li	r7, 0x0
	e_add16i	r0, r0, -0x7FF8
	se_stw	r7, 0x0(r0)
#/******************************************************************/
#/* Call Main Routine                                              */
#/******************************************************************/
    #/* Prepare a terminating stack record. */
    e_li r0, -1
    e_stwu r1, -8(r1) #/* Decrement stack by 8 bytes, (write word) */
    e_stw  r0, 4(r1)  #/* Make an illegal return address of 0xFFFFFFFF */
    e_stw  r0, 0(r1)  #/* Make an illegal back chain address of 0xFFFFFFFF */

    e_bl main
     
    #/* Define a symbol to Turn OFF (stop the tracing and save the data) the LTB PowerTracer */    
    .global MCAL_LTB_TRACE_OFF
    MCAL_LTB_TRACE_OFF:
        e_nop

     se_illegal         #/* SW breakpoint to stop debugging */
    while_1:
     se_b while_1
