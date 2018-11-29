#include "MPC5634M_MLQB80.h"
#include "Std_Types.h"
#include "asdebug.h"

#ifdef USE_ANYOS
#define USE_OS_CONST_ID
#define _TASK_t uint16
#define _COUNTER_t uint16
#define _ALARM_t uint16
#define _RESOURCE_t uint16
#endif

#ifdef USE_TRACE
#include "trace.h"
#endif

#include "Os.h"

#define AS_LOG_OS 1

#define CPU_FREQUENCY 64
#define SYNCR_V 0x16000000	/**PREFDIV=1,MFD=12,RFD=0,->Fsys=64MHZ*/


uint8_t xcpSimMTAMemory[32];

void InitializeUART(void) {
	ESCI_A.CR2.R = 0x2000;
	ESCI_A.CR1.R =(((CPU_FREQUENCY*1000000/(16*115200))<<16)|0x0000000c);
	SIU.PCR[89].R = 0x400;
	SIU.PCR[90].R = 0x400;
}

char ReadUARTN(void) {
	while (ESCI_A.SR.B.RDRF == 0) {}    /* Wait for receive data reg full = 1 */
	ESCI_A.SR.R = 0x20000000;           /* Clear RDRF flag */
	return ESCI_A.DR.B.D;               /* Read byte of Data*/
}

void WriteUARTN(char ch) {
	while (ESCI_A.SR.B.TDRE == 0) {}
	ESCI_A.SR.R = 0x80000000;
	ESCI_A.DR.B.D = ch;
}

void __putchar (char data) {
	WriteUARTN(data);
}

void CpuClockInit(void)
{
	FMPLL.ESYNCR1.B.CLKCFG = 0X7;
	FMPLL.SYNCR.R = 0x16080000;/**PREFDIV=1,MFD=12,RFD=1,->Fsys=32MHZ*/
	while (FMPLL.SYNSR.B.LOCK != 1) {};
	FMPLL.SYNCR.R = SYNCR_V;
}

TickType __weak OsTickCounter = 0;
void __weak OsTick(void)
{
	OsTickCounter ++;
}

void RTI_TickHandler(void)
{
	OsTick();
	PIT.RTI.TFLG.B.TIF=1;
}

void __weak OSISRSystemTimer(void)
{
	
}

void OS_isr_RTI_TickHandler(void)
{
	OSISRSystemTimer();
	RTI_TickHandler();
}

void RTI_SetFreqHz(int Freq)
{
	PIT.PITMCR.B.MDIS_RTI=0;/*turn on PIT just for RTI*/
	PIT.RTI.LDVAL.R=CPU_FREQUENCY*1000000/Freq-1;
	//PIT.RTI.TCTRL.B.TIE=1;	/*enable interrupt*/
	PIT.RTI.TCTRL.B.TEN=1;/*turn on RTI*/
	INTC_InstallINTCInterruptHandler(RTI_TickHandler,305,1);
}


void TickTimer_SetFreqHz(int Freq)
{
/* use Decrementer as the System Tick*/
	int  decr=CPU_FREQUENCY*1000000/Freq;
	__asm{
		li		r0, 0x0000
		mthid0	r0
/*Set the gap time between tick and tick*/
		lwz     r0,decr
		mtdec	r0
		mtdecar	r0
/*Set TCR[DIE]=1,TCR[ARE]=1,that is to enable DEC interrupt and enable auto-reload*/
		lis		r0, 0x0440
		mftcr   r3
		or      r0,r0,r3
		mttcr	r0
/*Set HID0[TBEN]=1,Time base enable*/
		li		r0, 0x4000
		mthid0	r0
	}
}
extern void OS_isr_Adc_Irq_eQADCA_CFIFO0_Empty(void);
extern void OS_isr_Adc_Irq_eQADCA_RFIFO0_Full(void);
extern void OS_isr_Can_IsrFCA_ERR(void);
extern void OS_isr_Can_IsrFCA_BO(void);
extern void OS_isr_Can_IsrFCA_MB_00(void);
extern void OS_isr_Can_IsrFCA_MB_01(void);
extern void OS_isr_Can_IsrFCA_MB_02(void);
extern void OS_isr_Can_IsrFCA_MB_03(void);
extern void OS_isr_Can_IsrFCA_MB_04(void);
extern void OS_isr_Can_IsrFCA_MB_05(void);
extern void OS_isr_Can_IsrFCA_MB_06(void);
extern void OS_isr_Can_IsrFCA_MB_07(void);
extern void OS_isr_Can_IsrFCA_MB_08(void);
extern void OS_isr_Can_IsrFCA_MB_09(void);
extern void OS_isr_Can_IsrFCA_MB_10(void);
extern void OS_isr_Can_IsrFCA_MB_11(void);
extern void OS_isr_Can_IsrFCA_MB_12(void);
extern void OS_isr_Can_IsrFCA_MB_13(void);
extern void OS_isr_Can_IsrFCA_MB_14(void);
extern void OS_isr_Can_IsrFCA_MB_15(void);
extern void OS_isr_Can_IsrFCA_MB_16_31(void);
extern void OS_isr_Can_IsrFCA_MB_32_63(void);

__weak void OS_isr_Adc_Irq_eQADCA_CFIFO0_Empty(void) 
{
	
}
__weak void OS_isr_Adc_Irq_eQADCA_RFIFO0_Full(void) 
{
	
}

void Bsp_Init(void)
{
	EXCEP_InitExceptionHandlers();
	INTC_InitINTCInterrupts();
	CpuClockInit();
	InitializeUART();

	#ifndef USE_ANYOS
	/* ADC */
	INTC_InstallINTCInterruptHandler(OS_isr_Adc_Irq_eQADCA_CFIFO0_Empty,104,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Adc_Irq_eQADCA_RFIFO0_Full,105,1);
	/* CAN A */
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_BO,152,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_ERR,153,1);
	/* CAN A wakeup INT 154 */
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_00,155,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_01,156,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_02,157,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_03,158,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_04,159,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_05,160,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_06,161,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_07,162,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_08,163,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_09,164,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_10,165,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_11,166,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_12,167,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_13,168,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_14,169,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_15,170,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_16_31,171,1);
	INTC_InstallINTCInterruptHandler(OS_isr_Can_IsrFCA_MB_32_63,172,1);
	#endif
	INTC.CPR.B.PRI = 0;
}

asm imask_t __Irq_Save(void)
{
nofralloc
	mfmsr   r3
	wrteei  0
	blr
}

asm void Irq_Restore(imask_t mask)
{
nofralloc
	mtmsr   r3;
	blr
}

void Irq_Enable(void)
{
	__asm("wrteei 1");
}

void Irq_Disable(void)
{
	__asm("wrteei 0");
}

void __weak OS_SuspendAllInterrupts(void)
{
	Irq_Disable();
}

void __weak OS_ResumeAllInterrupts(void)
{
	Irq_Enable();		
}

void PreTaskHook(void)
{
	#ifdef USE_TRACE
	TaskType TaskID;
	GetTaskID(&TaskID);
	Trace_PerfStart(TaskID);
	#endif
}
void PostTaskHook(void)
{
	#ifdef USE_TRACE
	TaskType TaskID;
	GetTaskID(&TaskID);
	Trace_PerfStop(TaskID);
	#endif
}

void ShutdownHook(StatusType ercd)
{
	printf("ShutdownHook(%X)\n",ercd);

	asAssert(0);
}

void ErrorHook(StatusType ercd)
{

	switch(ercd)
	{
		case E_OS_ACCESS:
			ASLOG(OS,"ercd = %d E_OS_ACCESS!\r\n",ercd);
			break;
		case E_OS_CALLEVEL:
			ASLOG(OS,"ercd = %d E_OS_CALLEVEL!\r\n",ercd);
			break;
		case E_OS_ID:
			ASLOG(OS,"ercd = %d E_OS_ID!\r\n",ercd);
			break;
		case E_OS_LIMIT:
			ASLOG(OS,"ercd = %d E_OS_LIMIT!\r\n",ercd);
			break;
		case E_OS_NOFUNC:
			ASLOG(OS,"ercd = %d E_OS_NOFUNC!\r\n",ercd);
			break;
		case E_OS_RESOURCE:
			ASLOG(OS,"ercd = %d E_OS_RESOURCE!\r\n",ercd);
			break;
		case E_OS_STATE:
			ASLOG(OS,"ercd = %d E_OS_STATE!\r\n",ercd);
			break;
		case E_OS_VALUE	:
			ASLOG(OS,"ercd = %d E_OS_VALUE!\r\n",ercd);
			break;
		default:
			ASLOG(OS,"ercd = %d unknown error!\r\n",ercd);
			break;
	}

	if(E_OS_CALLEVEL == ercd)
	{
		ShutdownOS(E_OS_CALLEVEL);
	}
	else
	{
		/* recover-able error */
	}
}

void __weak Dem_ReportErrorStatus(uint16 EventId, uint8 EventStatus)
{
	printf("Dem_ReportErrorStatus(%d, %d)\n", EventId, EventStatus);
}

extern char McuConfigData[];
int main(void) {
	Bsp_Init();
	EcuM_Init();
	Irq_Disable();
	/* Loop forever */
	for (;;) {
	}
}

void __weak CanIf_CancelTxConfirmation(void)
{
	
	
}
void __weak Can_MainFunction_Error(void)
{
	
}

void __weak Can_MainFunction_Wakeup(void)
{
	
}

void __weak Can_MainFunction_Read(void)
{
	
}

void __weak Can_MainFunction_Write(void)
{
	
}

void __weak Can_MainFunction_BusOff(void)
{
	
}

void StartupHook(void)
{
	#ifdef USE_TRACE
	Trace_Init();
	#endif
}

void SchM_StartupHook(void)
{
	TickTimer_SetFreqHz(1000);
	RTI_SetFreqHz(1000);
	OsSetRelAlarm(AlarmApp, MS2TICKS(10), MS2TICKS(5));
}

extern void App_MainFunction(void);
void TaskIdleHook(void)
{
#ifndef USE_ANYOS
	if(PIT.RTI.TFLG.B.TIF)
	{
		RTI_TickHandler();
	}
#endif
	
#ifdef USE_SHELL
	extern void SHELL_input(char c);
	while(ESCI_A.SR.B.RDRF)
	{
		char ch = ReadUARTN();
		if('\r' == ch) ch = '\n';
		SHELL_input(ch);
	}
#endif
}

__weak void StartOsTick(void)
{
	RTI_SetFreqHz(10000);
}

__weak TASK(TaskApp)
{	
	static TickType ticks = 0;
	ticks ++;
	if(0 == (ticks%200))
	{ /* 1s tick */
		App_PeriodFunction1s();
	}

	App_MainFunction();
	TerminateTask();
}

__weak ALARM(AlarmApp)
{
	OsActivateTask(TaskApp);
}

__weak TASK(TaskIdle)
{
	for(;;)
	{
		Irq_Enable(); /* for robustness */
		TaskIdleHook();
	}
	TerminateTask();
}

/* OSAL for NXP OS */
#ifdef USE_ANYOS
__weak TASK(TaskCanIf)
{	
	TerminateTask();
}
__weak TASK(SchM_BswService)
{	
	TerminateTask();
}
__weak TASK(SchM_Startup)
{	
	TerminateTask();
}
void FuncTaskCanIf(void) 
{
	TaskMainTaskCanIf();	
}
void FuncSchM_BswService(void) 
{
	TaskMainSchM_BswService();	
}
void FuncSchM_Startup(void) 
{
	TaskMainSchM_Startup();	
}
void FuncTaskApp(void) 
{
	TaskMainTaskApp();	
}
void FuncTaskShell(void) 
{
	TaskMainTaskShell();	
}
void FuncTaskIdle(void) 
{
	TaskMainTaskIdle();	
}

StatusType OS_ActivateTask( TaskType taskId );
StatusType OS_TerminateTask( void );

StatusType ActivateTask( TaskType taskId )
{
	return OS_ActivateTask(taskId);
}


StatusType TerminateTask( void )
{
	return OS_TerminateTask();
}
extern void OS_ShutdownOS( StatusType Error );
void ShutdownOS( StatusType Error )
{
	OS_ShutdownOS(Error);
}


StatusType OS_GetAlarmBase( AlarmType AlarmID, AlarmBaseRefType pInfo );
StatusType OS_GetAlarm    ( AlarmType AlarmID ,TickRefType pTick );
StatusType OS_SetRelAlarm ( AlarmType AlarmID , TickType Increment ,TickType Cycle );
StatusType OS_SetAbsAlarm ( AlarmType AlarmID , TickType Start ,TickType Cycle );
StatusType OS_CancelAlarm ( AlarmType AlarmID );

StatusType OS_SetEvent  ( TaskType TaskID , EventMaskType pMask );
StatusType OS_ClearEvent( EventMaskType Mask );
StatusType OS_GetEvent  ( TaskType TaskID , EventMaskRefType pEvent );
StatusType OS_WaitEvent ( EventMaskType Mask );


StatusType GetAlarmBase( AlarmType AlarmID, AlarmBaseRefType pInfo )
{
	return OS_GetAlarmBase(AlarmID,pInfo);
}
StatusType GetAlarm    ( AlarmType AlarmID ,TickRefType pTick )
{
	return OS_GetAlarm(AlarmID,pTick);
}
StatusType SetRelAlarm ( AlarmType AlarmID , TickType Increment ,TickType Cycle )
{
	return OS_SetRelAlarm(AlarmID,Increment,Cycle);
}
StatusType SetAbsAlarm ( AlarmType AlarmID , TickType Start ,TickType Cycle )
{
	return OS_SetAbsAlarm(AlarmID,Start,Cycle);
}
StatusType CancelAlarm ( AlarmType AlarmID )
{
	return OS_CancelAlarm(AlarmID);
}

StatusType SetEvent  ( TaskType TaskID , EventMaskType pMask )
{
	return OS_SetEvent(TaskID, pMask);
}
StatusType ClearEvent( EventMaskType Mask )
{
	return OS_ClearEvent(Mask);
}
StatusType GetEvent  ( TaskType TaskID , EventMaskRefType pEvent )
{
	return OS_GetEvent(TaskID, pEvent);
}
StatusType WaitEvent ( EventMaskType Mask )
{
	return OS_WaitEvent(Mask);
}

StatusType OS_GetResource (ResourceType ResID);
StatusType OS_ReleaseResource ( ResourceType ResID );

StatusType GetResource (ResourceType ResID)
{
	return OS_GetResource(ResID);
}
StatusType ReleaseResource ( ResourceType ResID )
{
	return OS_ReleaseResource(ResID);
}
#endif

