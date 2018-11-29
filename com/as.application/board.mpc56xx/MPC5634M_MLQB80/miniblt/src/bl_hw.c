#include "miniblt.h"
#include "MPC5634M_MLQB80.h"

#define CPU_FREQUENCY 64
#define SYNCR_V 0x16000000	/**PREFDIV=1,MFD=12,RFD=0,->Fsys=64MHZ*/

extern void OsTick(void);

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


void RTI_TickHandler(void)
{
	OsTick();
	PIT.RTI.TFLG.B.TIF=1;
}

void RTI_SetFreqHz(int Freq)
{
	PIT.PITMCR.B.MDIS_RTI=0;/*turn on PIT just for RTI*/
	PIT.RTI.LDVAL.R=CPU_FREQUENCY*1000000/Freq-1;
	//PIT.RTI.TCTRL.B.TIE=1;	/*enable interrupt*/
	PIT.RTI.TCTRL.B.TEN=1;/*turn on RTI*/
	INTC_InstallINTCInterruptHandler(RTI_TickHandler,305,1);
}

void StartOsTick(void)
{
	RTI_SetFreqHz(1000);
}

Can_ReturnType Can_Write( uint8 hth, Can_PduType *pduInfo )
{
	uint8 i;
	CAN_A.BUF[hth].CS.B.IDE = 0;           /* Use standard ID length */
	CAN_A.BUF[hth].ID.B.STD_ID = pduInfo->id;      /* Transmit ID is 555 */
	CAN_A.BUF[hth].CS.B.RTR = 0;           /* Data frame, not remote Tx request frame */
	CAN_A.BUF[hth].CS.B.LENGTH = pduInfo->length ; /* # bytes to transmit w/o null */
	for (i=0; i<pduInfo->length; i++) {
		((uint8*)(CAN_A.BUF[hth].DATA.W))[i] = pduInfo->sdu[i];      /* Data to be transmitted */
	}
	CAN_A.BUF[hth].CS.B.SRR = 1;           /* Tx frame (not req'd for standard frame)*/
	CAN_A.BUF[hth].CS.B.CODE =0xC;         /* Activate msg. buf. to transmit data frame */ 	
}

#define CAN_BAUDRATE_KBPS 1000
#define CanControllerPropSeg 6
#define CanControllerSeg1    3
#define CanControllerSeg2    3
#define CanControllerRJW     3
void initCAN_A (void) {
  uint8_t   i;
  uint8_t tq;
  uint8_t tq1;
  uint8_t tq2;

  CAN_A.MCR.R = 0x5000003F;       /* Put in Freeze Mode & enable all 64 message buffers */
  tq1 = (CanControllerPropSeg + CanControllerSeg1 + 2);
  tq2 = (CanControllerSeg2 + 1);
  tq = 1 + tq1 + tq2;
    
  CAN_A.CR.B.CLKSRC = 1;
  CAN_A.CR.B.PRESDIV = (CPU_FREQUENCY*1000000) / (CAN_BAUDRATE_KBPS * 1000 * tq) - 1;
  CAN_A.CR.B.PROPSEG = CanControllerPropSeg;
  CAN_A.CR.B.PSEG1   = CanControllerSeg1;
  CAN_A.CR.B.PSEG2   = CanControllerSeg2;
  CAN_A.CR.B.RJW     = CanControllerRJW;
  CAN_A.CR.B.SMP     = 1; /* 3 samples better than 1 ?? */
  CAN_A.CR.B.LPB     = 0;
  CAN_A.CR.B.BOFFREC = 1; /* Disable bus off recovery */
  for (i=0; i<64; i++) {
    CAN_A.BUF[i].CS.B.CODE = 0;   /* Inactivate all message buffers */
  } 
  CAN_A.BUF[0].CS.B.CODE = 8;     /* Message Buffer 0 set to TX INACTIVE */
  
  CAN_A.BUF[4].CS.B.IDE = 0;        /* MB 4 will look for a standard ID */
  CAN_A.BUF[4].ID.B.STD_ID = 0x731; /* MB 4 will look for ID = 0x731 */
  CAN_A.BUF[4].CS.B.CODE = 4;       /* MB 4 set to RX EMPTY */
  CAN_C.RXGMASK.R = 0x1FFFFFFF; 
 
  SIU.PCR[83].R = 0x062C;         /* Configure pad as CNTXA, open drain */
  SIU.PCR[84].R = 0x0500;         /* Configure pad as CNRXA */
  CAN_A.MCR.R = 0x0000003F;       /* Negate FlexCAN A halt state for 64 MB */
}

void BL_HwInit(void)
{
	CpuClockInit();	
	InitializeUART();
	initCAN_A();	
}

void BL_HwMonitor(void)
{
	uint32_t RxCODE;               /* Received message buffer code */
	uint32_t RxID;                 /* Received message ID */
	uint32_t RxLENGTH;             /* Recieved message number of data bytes */
	uint8_t  RxDATA[8];            /* Received message data string*/
	uint32_t dummy;
	uint8_t j;
	if(PIT.RTI.TFLG.B.TIF)
	{
		RTI_TickHandler();
	}
	
	if(1 == CAN_A.IFRL.B.BUF04I)
	{
		RxCODE   = CAN_A.BUF[4].CS.B.CODE;      /* Read CODE, ID, LENGTH, DATA, TIMESTAMP */
		RxID     = CAN_A.BUF[4].ID.B.STD_ID;
		RxLENGTH = CAN_A.BUF[4].CS.B.LENGTH;
		for (j=0; j<RxLENGTH; j++) { 
			RxDATA[j] = ((uint8_t*)(CAN_A.BUF[4].DATA.W))[j];
		}
		dummy = CAN_A.TIMER.R;                /* Read TIMER to unlock message buffers */    
		/* Use 1 of the next 2 lines: */
		/*CAN_C.IFLAG1.R = 0x00000010; */       /* MPC551x: Clear CAN C MB 4 flag */
		CAN_A.IFRL.R = 0x00000010;            /* MPC555x: Clear CAN C MB 4 flag */
		CanIf_RxIndication(4, RxID, RxLENGTH, RxDATA);
	}
	
	if(1 == CAN_A.IFRL.B.BUF00I)
	{
		CAN_A.IFRL.R = 0x00000001;            /* MPC555x: Clear CAN C MB 4 flag */
		CanIf_TxConfirmation(Can0Hrh);
	}
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


void application_main(void)
{
	const struct appbam_s {
		uint32_t bam;
		void (*entry)(void);
	} *appbam = (struct appbam_s*)0x40000;
	printf("application bam is 0x%X, entry is 0x%X\n", appbam->bam, appbam->entry);
	if((0x015A015A == appbam->bam) && (NULL != appbam->entry))
	{
		appbam->entry();
	}
}
