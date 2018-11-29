/*
   *********************************************************************************************************
   *                                          PC SUPPORT FUNCTIONS for WIN32
   *
   *                          (c) Copyright 2004-2005, Werner.Zimmermann@fht-esslingen.de
   *                      (Functions similar to the 80x86 Real Mode port by Jean J. Labrosse)
   *                                           All Rights Reserved
   *
   * File : PC.H
   * By   : Werner Zimmermann
   *********************************************************************************************************
 */
#ifndef _PC_H_
#define _PC_H_
#define PC_CHECK_RECURSIVE_CALLS        FALSE           //Set to TRUE, if you want to check whether the keyboard
                                                        //and display functions are called recursively, i.e.
                                                        //the previous call could not be finished before the
                                                        //functions are called the next time

//#define DEBUG_PC					//Uncomment, if you want to debug the display functions

/*
   *********************************************************************************************************
   *                                               CONSTANTS
   *                                    COLOR ATTRIBUTES FOR VGA MONITOR
   *
   * Description: These #defines are used in the PC_Disp???() functions.  The 'color' argument in these
   *              function MUST specify a 'foreground' color and a 'background'.
   *              If you don't specify a background color, BLACK is assumed.  You would
   *              specify a color combination as follows:
   *
   *              PC_DispChar(0, 0, 'A', DISP_FGND_WHITE + DISP_BGND_BLUE);
   *
   *              To have the ASCII character 'A' with a white letter on a blue background.
   *********************************************************************************************************
 */
#ifndef __RS232__
#include <windows.h>
#include "ucos_ii.h"
#else
typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
#define FOREGROUND_BLUE1
#define FOREGROUND_GREEN2
#define FOREGROUND_RED4
#define FOREGROUND_INTENSITY8
#define BACKGROUND_BLUE16
#define BACKGROUND_GREEN32
#define BACKGROUND_RED64
#define BACKGROUND_INTENSITY128
#endif
//#define DEBUG_PC


#define DISP_FGND_BLACK           0x00
#define DISP_FGND_BLUE            FOREGROUND_BLUE
#define DISP_FGND_GREEN           FOREGROUND_GREEN
#define DISP_FGND_RED             FOREGROUND_RED
#define DISP_FGND_CYAN            (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DISP_FGND_YELLOW          (FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DISP_FGND_WHITE           (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define DISP_FGND_GRAY            (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

#define DISP_BGND_BLACK           0x00
#define DISP_BGND_BLUE            BACKGROUND_BLUE
#define DISP_BGND_GREEN           BACKGROUND_GREEN
#define DISP_BGND_RED             BACKGROUND_RED
#define DISP_BGND_CYAN            (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define DISP_BGND_YELLOW          (BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define DISP_BGND_WHITE           (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)
#define DISP_BGND_GRAY            (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)
#define DISP_BGND_LIGHT_GRAY      (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)

#define DISP_BLINK                0x80

/*$PAGE */
/*
   *********************************************************************************************************
   *                                           FUNCTION PROTOTYPES
   *********************************************************************************************************
 */

void PC_DispChar(INT8U x, INT8U y, INT8U c, INT8U color);
void PC_DispClrScr(INT8U bgnd_color);
void PC_DispStr(INT8U x, INT8U y, INT8U * s, INT8U color);

void PC_ElapsedInit(void);
void PC_ElapsedStart(INT8U n);
INT32U PC_ElapsedStop(INT8U n);

void PC_GetDateTime(char *s);
BOOLEAN PC_GetKey(INT16S * c);

#define  uCOS                 0x80                    /* Interrupt vector # used for context switch    */
void  PC_VectSet(INT8U irq, void (*isr)(void));
void *PC_VectGet(INT8U irq);

void PC_DOSSaveReturn(void);
void PC_DOSReturn(void);
void PC_SetTickRate(INT16U freq);


int random(void);

#endif /* _PC_H_ */

