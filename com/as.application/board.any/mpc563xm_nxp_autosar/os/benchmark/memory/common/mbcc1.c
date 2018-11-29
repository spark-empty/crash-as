/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2008 - 2010
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*   Description:  AUTOSAR OS/MPC56xxAM "Body" benchmark for BCC1
*
**************************************************************************************/

/*  Include-files   */

#include    <os.h>                          /* OSEK API */

#define APP_START_SEC_CODE
#include "MemMap.h"

/******************** variables for calculating overhead *********************/

#define TrustedApplication_START_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"

OSDWORD APPNEAR volatile sysCnt;             /* counter for "useful" work */
OSDWORD APPNEAR volatile nosys;              /* counter for "useful" work w/o system overhead */
OSWORD  APPNEAR procent;                     /* result goes here */

#define TrustedApplication_STOP_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"

#define TrustedApplication_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#if defined(__CLASS_SC1)
#define ARLEN 1
#else
#define ARLEN 13
#endif
int  stackUsage[ARLEN];                   /* measured stack usage */
unsigned char *tmpSP;                     /* temporary Stack Pointer  */
unsigned char *tmpPtr;                    /* temporary Pointer  */
int iterator;

#define TrustedApplication_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

void SetPLL( void );

#define GetTOS(tskNum) ((OSBYTE*)(OsTaskCfgTable[OSNTSKS - tskNum - 1].tos))
#define GetBOS(tskNum,tskStkSize) (GetTOS(tskNum) - tskStkSize)

#if defined(OSMEMPROTECTION)
/***************************************************************************
 * Function:   StackProtectionOff
 *
 * Description: Put off the memory protection for stacks of runables. 
 *              For that it's used one of free MPU descriptors.
 *              This descriptor permits RW access to 'osstack' area
 *              for all runables.
 *
 * Notes:  This code shall NOT be used in the AUTOSAR applications -
 *         it uses OS internal macros
 *
 **************************************************************************/
void StackProtectionOff(void);

void StackProtectionOff(void)
{
    extern char OS_BEGIN_DSADDR(osstack)[];  /* beginning of OS stack section */
    extern char OS_END_DSADDR(osstack)[];    /* end of of OS stack section */

    OSMPU_RGD(OSMPU_RGD_DESC7,OSMPU_RGD_WORD0) = (OSDWORD) OS_BEGIN_DSADDR( osstack );
    OSMPU_RGD(OSMPU_RGD_DESC7,OSMPU_RGD_WORD1) = (OSDWORD) OS_END_DSADDR( osstack );
    OSMPU_RGD(OSMPU_RGD_DESC7,OSMPU_RGD_WORD2) = OSMPU_RGD_W2_M0( OSMPU_PE_OFF, 0, OSMPU_UM_R | OSMPU_UM_W );
    OSMPU_RGD(OSMPU_RGD_DESC7,OSMPU_RGD_WORD3) = OSMPU_RGD_W3_VLD;
}
#endif /* defined(OSMEMPROTECTION) */

/***************************************************************************
 * Function:   GetUsedBytes
 *
 * Description: Calculates number of used bytes
 *
 * inp:  stack bottom pointer, size in bytes
 *
 * Returns: number of bytes
 *
 **************************************************************************/

OSDWORD GetUsedBytes( OSBYTE* start, OSDWORD num )
{
    OSBYTE c;
    
    for( ; num > 0; num-- )
    {
        c = *start;
        if ( c != (OSBYTE)STACKPATTERN )
            break;
        start++;
    }
    return num;
}

/***************************************************************************
 * Function:   IniStack
 *
 * Description: fills stack area with pattern
 *
 * inp:  stack bottom pointer, size in bytes
 *
 **************************************************************************/
#define IniStack(start, len)  { tmpPtr = (unsigned char*)(start); \
              for( iterator=0; iterator<len; iterator++ ) { tmpPtr[iterator] = (OSBYTE)STACKPATTERN; } }

/***************************************************************************
 * Function :   main
 *
 * Description: performs HW initialization and starts OS
 *
 * Notes:       this function never returns
 **************************************************************************/

#define CUR100MS 6400000

void main( void )
{
    EnableBTB( );
    SetPLL();
        
#if defined(OSMEMPROTECTION)
	StackProtectionOff();
#endif

    InitTime();

    tmpSP  = (unsigned char*)OSGETSTACKPOINTER();
    IniStack( SP_BOTTOM, tmpSP - SP_BOTTOM - 16 );
#if !defined(__CLASS_SC1)
    IniStack( GetBOS(0, OSTASKBGNDSTKSIZE),  OSTASKBGNDSTKSIZE );
    IniStack( GetBOS(1,    OSTASK1STKSIZE),  OSTASK1STKSIZE    );
    IniStack( GetBOS(2,    OSTASK2STKSIZE),  OSTASK2STKSIZE    );
    IniStack( GetBOS(3,    OSTASK3STKSIZE),  OSTASK3STKSIZE    );
    IniStack( GetBOS(4,    OSTASK4STKSIZE),  OSTASK4STKSIZE    );
    IniStack( GetBOS(5,    OSTASK5STKSIZE),  OSTASK5STKSIZE    );
    IniStack( GetBOS(6,    OSTASK6STKSIZE),  OSTASK6STKSIZE    );
    IniStack( GetBOS(7,    OSTASK7STKSIZE),  OSTASK7STKSIZE    );
    IniStack( GetBOS(8,    OSTASK8STKSIZE),  OSTASK8STKSIZE    );
    IniStack( GetBOS(9,    OSTASK9STKSIZE),  OSTASK9STKSIZE    );
    IniStack( GetBOS(10,  OSTASK10STKSIZE),  OSTASK10STKSIZE   );    
#if defined(__CLASS_SC2)
    IniStack( (OSBYTE*)OsISRStack, OSISRSTACKSIZE*4 ); 
#else
    IniStack( (OSBYTE*)(OS_SysTimer_STKBOS), OSIPL2STKSIZE );
#endif
#endif
    StartOS( Mode1 );                        /* jump to OSEK startup */
}

/* Application Tasks: */
extern void EndMeasurement(void);
extern OSDWORD Count(void);

/***************************************************************************
 * Function :   TASK_BGND
 *
 * Description: performs initializations, measures timings.
 *
 * Notes:       this task has the lowest priority
 **************************************************************************/

TASK( TASKBGND )
{
    OSDWORD tvalue, temp;            /* temp - for current timer value   */

    DisableCMP( 8 );  // DisableTimerInt(); /* disable SystemCounter and alarms */
                                            /* thus removing system overhead    */

    SetAbsAlarm( ALARM1,   20, 200 );       /* start ALARM1  after  20 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM2,   40, 200 );       /* start ALARM2  after  40 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM3,   60, 200 );       /* start ALARM3  after  60 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM4,   80, 200 );       /* start ALARM4  after  80 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM5,  100, 200 );       /* start ALARM5  after 100 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM6,  120, 200 );       /* start ALARM6  after 120 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM7,  140, 200 );       /* start ALARM7  after 140 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM8,  160, 200 );       /* start ALARM8  after 160 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM9,  180, 200 );       /* start ALARM9  after 180 ms with cycle 200 ms*/
    SetAbsAlarm( ALARM10, 200, 200 );       /* start ALARM10 after 200 ms with cycle 200 ms*/

    sysCnt = 0L;
    nosys  = 0L;

#if !defined(OSTIMINGPROTECTION)    
    StartTime();
#endif

    ClearTime();
    tvalue = GetTime();
    do{                                     /* synchronize */
        temp = GetTime();
    }while( temp - tvalue < 2*CUR100MS );

    nosys = Count();
   
    EnableCMP( 8 );  // EnableTimerInt();   /* thus enabling alarms             */

    sysCnt = Count();

    DisableCMP( 8 ); // DisableTimerInt();  /* disable SystemCounter and alarms */
    
    procent = (int)((nosys - sysCnt) * 1000 / (nosys / 10));
                        /* at this point "procent" helds system overhead in (% * 100) */


#if defined(OSMEMPROTECTION)
    StackProtectionOff();
#endif
    stackUsage[0]  = GetUsedBytes( (OSBYTE*)SP_BOTTOM, SP_TOP - SP_BOTTOM );
#if !defined(__CLASS_SC1)
    stackUsage[1]  = GetUsedBytes( GetBOS(1, OSTASK1STKSIZE ),    OSTASK1STKSIZE );
    stackUsage[2]  = GetUsedBytes( GetBOS(2, OSTASK2STKSIZE ),    OSTASK2STKSIZE );
    stackUsage[3]  = GetUsedBytes( GetBOS(3, OSTASK3STKSIZE ),    OSTASK3STKSIZE );
    stackUsage[4]  = GetUsedBytes( GetBOS(4, OSTASK4STKSIZE ),    OSTASK4STKSIZE );
    stackUsage[5]  = GetUsedBytes( GetBOS(5, OSTASK5STKSIZE ),    OSTASK5STKSIZE );
    stackUsage[6]  = GetUsedBytes( GetBOS(6, OSTASK6STKSIZE ),    OSTASK6STKSIZE );
    stackUsage[7]  = GetUsedBytes( GetBOS(7, OSTASK7STKSIZE ),    OSTASK7STKSIZE );
    stackUsage[8]  = GetUsedBytes( GetBOS(8, OSTASK8STKSIZE ),    OSTASK8STKSIZE );
    stackUsage[9]  = GetUsedBytes( GetBOS(9, OSTASK9STKSIZE ),    OSTASK9STKSIZE );
    stackUsage[10] = GetUsedBytes( GetBOS(10,OSTASK10STKSIZE ),   OSTASK10STKSIZE );
    stackUsage[11] = GetUsedBytes( GetBOS(0, OSTASKBGNDSTKSIZE ), OSTASKBGNDSTKSIZE );
#if defined(__CLASS_SC2)
    stackUsage[12] = GetUsedBytes( (OSBYTE*)OsISRStack, OSISRSTACKSIZE*4 );
#else    
    stackUsage[12] = GetUsedBytes( (OSBYTE*)(OS_SysTimer_STKBOS), OSIPL2STKSIZE );
#endif
#endif
    EndMeasurement();
}

#if defined(OSGHSPPC)
#pragma ghs startnoinline 
#endif

void EndMeasurement(void)
{
    while(1)
    {
    }
}

OSDWORD Count( void )
{
    volatile OSDWORD tvalue, temp, counter=0L;

    tvalue = GetTime();
    do{                                     /* mesure during 10ticks            */
        counter++;                            /* make some work and calculate it  */
        temp = GetTime();
    }while(  temp - tvalue < 10*CUR100MS );
    return counter;
}

#if defined(OSGHSPPC)
#pragma ghs endnoinline 
#endif

/***************************************************************************
 * Functions:   TASK[1...10]
 *
 * Description: this tasks do nothing, used for measuring system overhead
 *
 **************************************************************************/

TASK( TASK1 )
{
    TerminateTask();
}

TASK( TASK2 )
{
    TerminateTask();
}

TASK( TASK3 )
{
    TerminateTask();
}

TASK( TASK4 )
{
    TerminateTask();
}

TASK( TASK5 )
{
    TerminateTask();
}

TASK( TASK6 )
{
    TerminateTask();
}

TASK( TASK7 )
{
    TerminateTask();
}

TASK( TASK8 )
{
    TerminateTask();
}

TASK( TASK9 )
{
    TerminateTask();
}

TASK( TASK10 )
{
    TerminateTask();
}

#define APP_STOP_SEC_CODE
#include "MemMap.h"
