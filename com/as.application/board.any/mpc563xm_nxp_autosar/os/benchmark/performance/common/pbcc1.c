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
*   Description:  AUTOSAR OS/MPC56xxAM "Body" performance benchmark for BCC1
*
**************************************************************************************/

#include    <os.h>                          /* OSEK API */

#define APP_START_SEC_CODE
#include "MemMap.h"

#ifdef USETIMER

#define TrustedApplication_START_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"

OSDWORD APPNEAR volatile inTime;               /* temp: start time                         */
OSDWORD APPNEAR volatile pfm1;                 /* time loosed on mesurement                */

OSDWORD APPNEAR volatile systemTimerIsrTime;   /* time from int-t arises to LeaveISR       */ 
OSDWORD APPNEAR volatile secondTimerIsrTime;   /* time from int-t arises to LeaveISR       */ 

OSDWORD APPNEAR volatile interruptLatency;     /* time from int-t arises to end of EnterISR*/ 
OSDWORD APPNEAR volatile activateTask1FromIsr; /* ActivateTask inside ISR time             */ 
OSDWORD APPNEAR volatile fromIsrToTask1;
OSDWORD APPNEAR volatile fromActivateToTask2;
OSDWORD APPNEAR volatile fromTeriminateToTask1;
OSDWORD APPNEAR volatile returnToBackGroundTask;

OSDWORD APPNEAR volatile activateTaskA1ViaAlarm;
OSDWORD APPNEAR volatile fromSecondTimerIsrToTaskA1;

OSDWORD APPNEAR volatile activated1Task;
OSDWORD APPNEAR volatile activated4Tasks;
OSDWORD APPNEAR volatile fromIsrToTaskT1;
OSDWORD APPNEAR volatile fromIsrToTaskT2;
OSDWORD APPNEAR volatile fromIsrToTaskT3;
OSDWORD APPNEAR volatile fromIsrToTaskT7;
OSDWORD APPNEAR volatile fromTaskT7ToTaskT4;

OSDWORD APPNEAR volatile expired1Alarm;
OSDWORD APPNEAR volatile expired4Alarms;
OSDWORD APPNEAR volatile expired8Alarms;
OSDWORD APPNEAR volatile fromLeaveIsrToTaskH1;
OSDWORD APPNEAR volatile fromTaskH1ToTaskH4;
OSDWORD APPNEAR volatile fromTaskH4ToTaskH8;

#define TrustedApplication_STOP_SEC_VAR_FAST_UNSPECIFIED
#include "MemMap.h"

#define flag inTime
#define SetFlag( )

#else  /* USETIMER */

#define TrustedApplication_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

OSBYTE volatile flag;                       /* synchronization flag for TASK_BGND    */

#define TrustedApplication_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define SetFlag() flag =  1

#endif /* USETIMER */

void SetPLL( void );

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

/*********************  Entry point of the application  **********************/
void IniSecondTimer( void );
void SystemTimerISR( void );

void main( void )
{
    EnableBTB( );
    SetPLL( );
    IniPort( );
    ClearTime( );
    StartOS( Mode1 );                        /* jump to OSEK startup */
}

/*****************************************************************************
 * Function :   IniSecondTimer
 *
 * Description: Initialize HW and start timer as system Second Timer
 *
 * Notes:       This code shall NOT be used in the OSEK applications -
 *              it uses OS internal macros.
 *
 *****************************************************************************/
void IniSecondTimer( void )
{
    PIT_LDVAL(0) = 16383; // (256 us / (1/64MHz)) - 1   
    PIT_TCTRL(0) = 3;     // Interrupt will be requested whenever TIF is set; Timer will be active
    PIT_MCR = 1;          // Clock for PIT timers is enabled; Timers continue to run in debug mode
}

/************************ User's functions: **********************************/
/*****************************************************************************
 * Function :   TASK_BGND
 *
 * Description: performs initializations, measures timings.
 *
 * Notes:       this task has the lowest priority
 *****************************************************************************/
TASK( TASK_BGND )
{

#if defined(OSMEMPROTECTION)
    StackProtectionOff();
#endif

#if !defined(OSTIMINGPROTECTION)    
    StartTime();
#endif

    CMPSetHW(16);

    SetStartTime( );
#ifdef USETIMER
    pfm1 = GetTime();
    pfm1 -= inTime;    /* time spent for mesurements, to be substracted */
#endif
    MTSCMP(16) = ISR1DELAY;
    ClearCMP(16);
    EnableCMP(16);
    
    flag = 0;
    while( flag == 0 );                 /* wait to tasks 1,2 activated */
    ClrPort( );
    CalcTime( returnToBackGroundTask ); /* return to background after ISR   */ 

    DisableCMP(16);

    flag = 0;    
    IniSecondTimer( );
    SetRelAlarm( ALARM_ONE, 1, 0 );     /* one-shot alarm ( 2ms ) */
    while( flag == 0 );                 /* wait to task 3 activated */
    ClrPort( );
#ifdef USETIMER
    activateTaskA1ViaAlarm = secondTimerIsrTime; /* fix one-shot alarm interrupt timing */
#endif
    /* NB! setting alarms in order of attached tasks priorities (from low to high)
       gives a better (~1.5 times) performanse in case of many activations at one point */
    SetRelAlarm( ALARM_8, 4, 4 );       /* period 1024 us */
    SetRelAlarm( ALARM_7, 4, 4 );       /* period 1024 us */
    SetRelAlarm( ALARM_6, 4, 4 );       /* period 1024 us */
    SetRelAlarm( ALARM_5, 4, 4 );       /* period 1024 us */
    SetRelAlarm( ALARM_4, 4, 2 );       /* period 512 us  */
    SetRelAlarm( ALARM_3, 4, 2 );       /* period 512 us  */
    SetRelAlarm( ALARM_2, 4, 2 );       /* period 512 us  */
    SetRelAlarm( ALARM_1, 4, 1 );       /* period 256 us  */

    /* this line works only when code is in RAM, it does not works for ROM! */
    OsIsrTable[OsIsr[59]].userISR = SystemTimerISR; /* replace OSISRSystemTimer, eMIOS, Channel 8 */

    /* wait when second timer will be near 1/2 of period before start schedule table to ensure that  
       there will not be any interference between schedule table and harmonic alarms  */

    while( GetTime() < ST_DELAY );

    StartScheduleTableRel( ScheduleTable1, 1 );

    for(;;)
    {
        SetPort( PIN7 );                /* toggle pin7 to check MCU speed  */
        ClrPort( );
    }
}

/***************************************************************************
 * Function :   OneTaskISR
 *
 * Description: ISR for eMIOS0 Channel 16
 *
 * Notes:
 **************************************************************************/

ISR( OneTaskISR )
{
    ClearCMP(16); /* Clear output compare interrupt flag */

    SetPort( PIN4 );

#ifdef USETIMER
    interruptLatency = MTSCNT(16) - ISR1DELAY - pfm1; /* time from the point when interrupt raised */    
#endif

    SetStartTime( );
    ActivateTask( TASK_1 );
    ClrPort( );
    CalcTime( activateTask1FromIsr );
    SetStartTime( );
}

/***************************************************************************
 * Functions:   TASK_[1,2]
 *
 * Description: only pin setting and/or timer capture for measurements
 *              done in all tasks
 *
 * Notes:       these two tasks are activated from ISR
 **************************************************************************/

TASK( TASK_1 ) /* priority = 21    */
{
    SetPort( PIN4 ); /* the same pin used in ISR */
    CalcTime( fromIsrToTask1 );
    SetStartTime( );
    ActivateTask( TASK_2 );
    SetPort( PIN4 );
    CalcTime( fromTeriminateToTask1 );
    SetStartTime( );
    TerminateTask( );
}

TASK( TASK_2 ) /* priority = 22    */
{
    SetPort( PIN5 );
    CalcTime( fromActivateToTask2 );
    SetFlag( );
    SetStartTime( );
    TerminateTask( );
}

/***************************************************************************
 *
 * Function :   SecondTimerISR
 *
 * Description: stripped copy of OSEKturbo Second Timer ISR
 *
 * Notes:   This code shall NOT be used in the OSEK applications, it is
 *          the part of OS code modified for measurements.
 *
 **************************************************************************/

ISR( SecondTimerISR )
{
    SetPort( PIN4 );   

    PIT_TFLG(0) = 1; // Clear interrupt flag for PIT channel 0

    OSDI();

    OSCounterTrigger(OS_GETOBJIND(Counter2));

    ClrPort();
#ifdef USETIMER
    secondTimerIsrTime = PIT_LDVAL(0) - PIT_CVAL(0); /* time from the point when interrupt raised */    
#endif
    SetStartTime( );
}

/***************************************************************************
 * Functions:   TaskA
 *
 * Description: only pin setting and/or timer capture for measurements
 *              done in all tasks
 *
 * Notes:       this task are activated by one-shot alarm
 **************************************************************************/

TASK( TASK_ALM ) /* priority = 23    */
{
    SetPort( PIN5 );
    CalcTime( fromSecondTimerIsrToTaskA1 );
    SetFlag( );
    SetStartTime( );
    TerminateTask( );
}

/***************************************************************************
 * Functions:   TASK_h[1...8]
 *
 * Description: only pin setting and/or timer capture for measurements
 *              done in the tasks
 *
 * Notes:       this 8 tasks are activated by Alarm[1...8]
 **************************************************************************/

TASK( TASK_h1 ) /* priority = 8     */
{
    SetPort( PIN4 );  /* the same pin used in SecondTimer ISR */
    CalcTime( fromLeaveIsrToTaskH1 );
    SetStartTime( );
    TerminateTask( );
}

TASK( TASK_h2 ) /* priority = 7     */
{
    TerminateTask( );
}

TASK( TASK_h3 ) /* priority = 6     */
{
    TerminateTask( );
}

TASK( TASK_h4 ) /* priority = 5     */
{
    SetPort( PIN5 );
    CalcTime( fromTaskH1ToTaskH4 );
    SetStartTime( );
    TerminateTask( );
}

TASK( TASK_h5 ) /* priority = 4     */
{
    TerminateTask( );
}

TASK( TASK_h6 ) /* priority = 3     */
{
    TerminateTask( );
}

TASK( TASK_h7 ) /* priority = 2     */
{
    TerminateTask( );
}

TASK( TASK_h8 ) /* priority = 1     */
{
    SetPort( PIN6 );
    CalcTime( fromTaskH4ToTaskH8 );    
    SetStartTime( );
    TerminateTask( );
}

/***************************************************************************
 *
 * Function :   SystemTimerISR
 *
 * Description: stripped copy of OSEKturbo System Timer ISR
 *
 * Notes:   This code shall NOT be used in the OSEK applications, it is
 *          the part of OS code modified for measurements.
 *
 **************************************************************************/

void SystemTimerISR( void )          
{
    SetPort( PIN0 );    

    OSSystemEnterISR2();
    OSSysTimClearFlag();                        /* clear output compare interrupt flag */

/*** NB!: functions begining with "OS" shall NOT be used in AUTOSAR applications! ***/
#ifdef USETIMER
    inTime = OSHWCtrGetOC( 0 );
#endif  

    OSDI();
    OSCounterNotify( OSTIMER1 );
    ClrPort( );
#ifdef USETIMER
    systemTimerIsrTime = OSTIMTCNT - inTime - pfm1;
#endif  
    SetStartTime( );    
    OSSystemLeaveISR2();
    OSWARNSUPPRESS
}

/***************************************************************************
 * Functions:   TASK_t[1...7]
 *
 * Description: only pin setting and/or timer capture for measurements
 *              done in the tasks
 *
 * Notes:       this 7 tasks are activated from ScheduleTable
 **************************************************************************/

TASK( TASK_t1 )
{
    SetPort( PIN0 );         /* the same pin used in TimeScale ISR   */ 
    CalcTime( fromIsrToTaskT1 );
#ifdef USETIMER
    expired4Alarms = secondTimerIsrTime;
#endif
    TerminateTask( );
}

TASK( TASK_t2 )   /* priority = 12    */
{
    SetPort( PIN1 );
    CalcTime( fromIsrToTaskT2 );
#ifdef USETIMER
    expired1Alarm = secondTimerIsrTime;
    activated1Task = systemTimerIsrTime;
#endif
    TerminateTask( );
}

TASK( TASK_t3 )   /* priority = 13    */
{
    SetPort( PIN2 );
    CalcTime( fromIsrToTaskT3 );
#ifdef USETIMER
    expired8Alarms = secondTimerIsrTime;
#endif
    TerminateTask( );
}

TASK( TASK_t4 )   /* priority = 14    */
{
    SetPort( PIN0 );
    CalcTime( fromTaskT7ToTaskT4 );    
#ifdef USETIMER
    activated4Tasks = systemTimerIsrTime;
#endif
    TerminateTask( );
}

TASK( TASK_t5 )   /* priority = 15    */
{
    SetPort( PIN1 );
    TerminateTask( );
}

TASK( TASK_t6 )   /* priority = 16    */
{
    SetPort( PIN2 );
    TerminateTask( );
}

TASK( TASK_t7 )   /* priority = 17    */
{
    SetPort( PIN3 );
    CalcTime( fromIsrToTaskT7 );
    SetStartTime( );         /* TASK_t4 starts after  TASK_t7, TASK_t6 and TASK_t5 */
    TerminateTask( );
}

#define APP_STOP_SEC_CODE
#include "MemMap.h"
