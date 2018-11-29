/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
    MODULE  ?cstartup

    ;; Forward declaration of sections.
    SECTION CSTACK:DATA:NOROOT(3)

    SECTION .intvec:CODE:NOROOT(2)
    EXTERN __iar_program_start
    #ifdef CHIP_STM32F10X
    EXTERN SystemInit
    #endif
    EXTERN  knl_dispatch_entry,knl_start_dispatch
    EXTERN  knl_system_tick,knl_isr_process
    PUBLIC __vector_table
    DATA
__vector_table:
     /*    Internal Exceptions Vector Define                                        */
    DCD     sfe(CSTACK)                          /* 00: Top of Main Stack           */
    DCD     reset_handler                        /* 01: Reset Handler               */
    DCD     default_handler                      /* 02: NMI Handler                 */
    DCD     default_handler                      /* 03: Hard Fault Handler          */
    DCD     default_handler                      /* 04: MPU Fault Handler           */
    DCD     default_handler                      /* 05: Bus Fault Handler           */
    DCD     default_handler                      /* 06: Usage Fault Handler         */
    DCD     0                                    /* 07: Reserved                    */
    DCD     0                                    /* 08: Reserved                    */
    DCD     0                                    /* 09: Reserved                    */
    DCD     0                                    /* 10: Reserved                    */
    DCD     knl_start_dispatch                   /* 11: SVCall Handler              */
    DCD     default_handler                      /* 12: Debug Monitor Handler       */
    DCD     0                                    /* 13: Reserved                    */
    DCD     knl_dispatch_entry                   /* 14: PendSV Handler              */
    DCD     knl_system_tick                      /* 15: Systick handler             */

    /*    External Interrupts Vector Define                                         */
    DCD     knl_isr_process                      /* 16: */
    DCD     knl_isr_process                      /* 17: */
    DCD     knl_isr_process                      /* 18: */
    DCD     knl_isr_process                      /* 19: */
    DCD     knl_isr_process                      /* 20: */
    DCD     knl_isr_process                      /* 21: */
    DCD     knl_isr_process                      /* 22: */
    DCD     knl_isr_process                      /* 23: */
    DCD     knl_isr_process                      /* 24: */
    DCD     knl_isr_process                      /* 25: */
    DCD     knl_isr_process                      /* 26: */
    DCD     knl_isr_process                      /* 27: */
    DCD     knl_isr_process                      /* 28: */
    DCD     knl_isr_process                      /* 29: */
    DCD     knl_isr_process                      /* 30: */
    DCD     knl_isr_process                      /* 31: */
    DCD     knl_isr_process                      /* 32: */
    DCD     knl_isr_process                      /* 33: */
    DCD     knl_isr_process                      /* 34: */
    DCD     knl_isr_process                      /* 35: */
    DCD     knl_isr_process                      /* 36: */
    DCD     knl_isr_process                      /* 37: */
    DCD     knl_isr_process                      /* 38: */
    DCD     knl_isr_process                      /* 39: */
    DCD     knl_isr_process                      /* 40: */
    DCD     knl_isr_process                      /* 41: */
    DCD     knl_isr_process                      /* 42: */
    DCD     knl_isr_process                      /* 43: */
    DCD     knl_isr_process                      /* 44: */
    DCD     knl_isr_process                      /* 45: */
    DCD     knl_isr_process                      /* 46: */
    DCD     knl_isr_process                      /* 47: */
    DCD     knl_isr_process                      /* 48: */
    DCD     knl_isr_process                      /* 49: */
    DCD     knl_isr_process                      /* 50: */
    DCD     knl_isr_process                      /* 51: */
    DCD     knl_isr_process                      /* 52: */
    DCD     knl_isr_process                      /* 53: */
    DCD     knl_isr_process                      /* 54: */
    DCD     knl_isr_process                      /* 55: */
    DCD     knl_isr_process                      /* 56: */
    DCD     knl_isr_process                      /* 57: */
    DCD     knl_isr_process                      /* 58: */
    DCD     knl_isr_process                      /* 59: */
    DCD     knl_isr_process                      /* 60: */
    DCD     knl_isr_process                      /* 61: */
    DCD     knl_isr_process                      /* 62: */
    DCD     knl_isr_process                      /* 63: */
    DCD     knl_isr_process                      /* 64: */
    DCD     knl_isr_process                      /* 65: */
    DCD     knl_isr_process                      /* 66: */
    DCD     knl_isr_process                      /* 67: */
    DCD     knl_isr_process                      /* 68: */
    DCD     knl_isr_process                      /* 69: */
    DCD     knl_isr_process                      /* 70: */
    DCD     knl_isr_process                      /* 71: */
    DCD     knl_isr_process                      /* 72: */
    DCD     knl_isr_process                      /* 73: */
    DCD     knl_isr_process                      /* 74: */
    DCD     knl_isr_process                      /* 75: */
    DCD     knl_isr_process                      /* 76: */
    DCD     knl_isr_process                      /* 77: */
    DCD     knl_isr_process                      /* 78: */
    DCD     knl_isr_process                      /* 79: */
    DCD     knl_isr_process                      /* 80: */
    DCD     knl_isr_process                      /* 81: */
    DCD     knl_isr_process                      /* 82: */
    DCD     knl_isr_process                      /* 83: */
    DCD     knl_isr_process                      /* 84: */
    DCD     knl_isr_process                      /* 85: */
    DCD     knl_isr_process                      /* 86: */
    DCD     knl_isr_process                      /* 87: */
    DCD     knl_isr_process                      /* 88: */
    DCD     knl_isr_process                      /* 89: */
    DCD     knl_isr_process                      /* 90: */
    DCD     knl_isr_process                      /* 91: */
    DCD     knl_isr_process                      /* 92: */
    DCD     knl_isr_process                      /* 93: */
    DCD     knl_isr_process                      /* 94: */
    DCD     knl_isr_process                      /* 95: */
    DCD     knl_isr_process                      /* 96: */
    DCD     knl_isr_process                      /* 97: */
    DCD     knl_isr_process                      /* 98: */
    DCD     knl_isr_process                      /* 99: */
    DCD     knl_isr_process                      /* 100: */
    DCD     knl_isr_process                      /* 101: */
    DCD     knl_isr_process                      /* 102: */
    DCD     knl_isr_process                      /* 103: */
    DCD     knl_isr_process                      /* 104: */
    DCD     knl_isr_process                      /* 105: */
    DCD     knl_isr_process                      /* 106: */
    DCD     knl_isr_process                      /* 107: */
    DCD     knl_isr_process                      /* 108: */
    DCD     knl_isr_process                      /* 109: */
    DCD     knl_isr_process                      /* 110: */
    DCD     knl_isr_process                      /* 111: */
    DCD     knl_isr_process                      /* 112: */
    DCD     knl_isr_process                      /* 113: */
    DCD     knl_isr_process                      /* 114: */
    DCD     knl_isr_process                      /* 115: */
    DCD     knl_isr_process                      /* 116: */
    DCD     knl_isr_process                      /* 117: */
    DCD     knl_isr_process                      /* 118: */
    DCD     knl_isr_process                      /* 119: */
    DCD     knl_isr_process                      /* 120: */
    DCD     knl_isr_process                      /* 121: */
    DCD     knl_isr_process                      /* 122: */
    DCD     knl_isr_process                      /* 123: */
    DCD     knl_isr_process                      /* 124: */
    DCD     knl_isr_process                      /* 125: */
    DCD     knl_isr_process                      /* 126: */
    DCD     knl_isr_process                      /* 127: */
    DCD     knl_isr_process                      /* 128: */
    DCD     knl_isr_process                      /* 129: */
    DCD     knl_isr_process                      /* 130: */
    DCD     knl_isr_process                      /* 131: */
    DCD     knl_isr_process                      /* 132: */
    DCD     knl_isr_process                      /* 133: */
    DCD     knl_isr_process                      /* 134: */
    DCD     knl_isr_process                      /* 135: */
    DCD     knl_isr_process                      /* 136: */
    DCD     knl_isr_process                      /* 137: */
    DCD     knl_isr_process                      /* 138: */
    DCD     knl_isr_process                      /* 139: */
    DCD     knl_isr_process                      /* 140: */
    DCD     knl_isr_process                      /* 141: */
    DCD     knl_isr_process                      /* 142: */
    DCD     knl_isr_process                      /* 143: */
    DCD     knl_isr_process                      /* 144: */
    DCD     knl_isr_process                      /* 145: */
    DCD     knl_isr_process                      /* 146: */
    DCD     knl_isr_process                      /* 147: */
    DCD     knl_isr_process                      /* 148: */
    DCD     knl_isr_process                      /* 149: */
    DCD     knl_isr_process                      /* 150: */
    DCD     knl_isr_process                      /* 151: */
    DCD     knl_isr_process                      /* 152: */
    DCD     knl_isr_process                      /* 153: */
    DCD     knl_isr_process                      /* 154: */
    DCD     knl_isr_process                      /* 155: */
    DCD     knl_isr_process                      /* 156: */
    DCD     knl_isr_process                      /* 157: */
    DCD     knl_isr_process                      /* 158: */
    DCD     knl_isr_process                      /* 159: */
    DCD     knl_isr_process                      /* 160: */
    DCD     knl_isr_process                      /* 161: */
    DCD     knl_isr_process                      /* 162: */
    DCD     knl_isr_process                      /* 163: */
    DCD     knl_isr_process                      /* 164: */
    DCD     knl_isr_process                      /* 165: */
    DCD     knl_isr_process                      /* 166: */
    DCD     knl_isr_process                      /* 167: */
    DCD     knl_isr_process                      /* 168: */
    DCD     knl_isr_process                      /* 169: */
    DCD     knl_isr_process                      /* 170: */
    DCD     knl_isr_process                      /* 171: */
    DCD     knl_isr_process                      /* 172: */
    DCD     knl_isr_process                      /* 173: */
    DCD     knl_isr_process                      /* 174: */
    DCD     knl_isr_process                      /* 175: */
    DCD     knl_isr_process                      /* 176: */
    DCD     knl_isr_process                      /* 177: */
    DCD     knl_isr_process                      /* 178: */
    DCD     knl_isr_process                      /* 179: */
    DCD     knl_isr_process                      /* 180: */
    DCD     knl_isr_process                      /* 181: */
    DCD     knl_isr_process                      /* 182: */
    DCD     knl_isr_process                      /* 183: */
    DCD     knl_isr_process                      /* 184: */
    DCD     knl_isr_process                      /* 185: */
    DCD     knl_isr_process                      /* 186: */
    DCD     knl_isr_process                      /* 187: */
    DCD     knl_isr_process                      /* 188: */
    DCD     knl_isr_process                      /* 189: */
    DCD     knl_isr_process                      /* 190: */
    DCD     knl_isr_process                      /* 191: */
    DCD     knl_isr_process                      /* 192: */
    DCD     knl_isr_process                      /* 193: */
    DCD     knl_isr_process                      /* 194: */
    DCD     knl_isr_process                      /* 195: */
    DCD     knl_isr_process                      /* 196: */
    DCD     knl_isr_process                      /* 197: */
    DCD     knl_isr_process                      /* 198: */
    DCD     knl_isr_process                      /* 199: */
    DCD     knl_isr_process                      /* 200: */
    DCD     knl_isr_process                      /* 201: */
    DCD     knl_isr_process                      /* 202: */
    DCD     knl_isr_process                      /* 203: */
    DCD     knl_isr_process                      /* 204: */
    DCD     knl_isr_process                      /* 205: */
    DCD     knl_isr_process                      /* 206: */
    DCD     knl_isr_process                      /* 207: */
    DCD     knl_isr_process                      /* 208: */
    DCD     knl_isr_process                      /* 209: */
    DCD     knl_isr_process                      /* 210: */
    DCD     knl_isr_process                      /* 211: */
    DCD     knl_isr_process                      /* 212: */
    DCD     knl_isr_process                      /* 213: */
    DCD     knl_isr_process                      /* 214: */
    DCD     knl_isr_process                      /* 215: */
    DCD     knl_isr_process                      /* 216: */
    DCD     knl_isr_process                      /* 217: */
    DCD     knl_isr_process                      /* 218: */
    DCD     knl_isr_process                      /* 219: */
    DCD     knl_isr_process                      /* 220: */
    DCD     knl_isr_process                      /* 221: */
    DCD     knl_isr_process                      /* 222: */
    DCD     knl_isr_process                      /* 223: */
    DCD     knl_isr_process                      /* 224: */
    DCD     knl_isr_process                      /* 225: */
    DCD     knl_isr_process                      /* 226: */
    DCD     knl_isr_process                      /* 227: */
    DCD     knl_isr_process                      /* 228: */
    DCD     knl_isr_process                      /* 229: */
    DCD     knl_isr_process                      /* 230: */
    DCD     knl_isr_process                      /* 231: */
    DCD     knl_isr_process                      /* 232: */
    DCD     knl_isr_process                      /* 233: */
    DCD     knl_isr_process                      /* 234: */
    DCD     knl_isr_process                      /* 235: */
    DCD     knl_isr_process                      /* 236: */
    DCD     knl_isr_process                      /* 237: */
    DCD     knl_isr_process                      /* 238: */
    DCD     knl_isr_process                      /* 239: */
    DCD     knl_isr_process                      /* 240: */
    DCD     knl_isr_process                      /* 241: */
    DCD     knl_isr_process                      /* 242: */
    DCD     knl_isr_process                      /* 243: */
    DCD     knl_isr_process                      /* 244: */
    DCD     knl_isr_process                      /* 245: */
    DCD     knl_isr_process                      /* 246: */
    DCD     knl_isr_process                      /* 247: */
    DCD     knl_isr_process                      /* 248: */
    DCD     knl_isr_process                      /* 249: */
    DCD     knl_isr_process                      /* 250: */
    DCD     knl_isr_process                      /* 251: */
    DCD     knl_isr_process                      /* 252: */
    DCD     knl_isr_process                      /* 253: */
    DCD     knl_isr_process                      /* 254: */
    DCD     knl_isr_process                      /* 255: */

/*
 * Reset handle routine
 */
    SECTION .text:CODE
    THUMB
    PUBLIC reset_handler
reset_handler:
        #ifdef CHIP_STM32F10X
        LDR     R0, =SystemInit
        BLX     R0
        #endif
        LDR     R0, =__iar_program_start
        BX      R0
       
/*
 * Default exeception and interrupt process handler define
 */
	PUBLIC default_handler
default_handler:
    b       default_handler

    END

