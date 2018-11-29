
/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

/* ----------------------------[includes]------------------------------------*/

#include "EcuM.h"
#include "EcuM_Generated_Types.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#if defined(USE_MCU)
#include "Mcu.h"
#endif
#if defined(USE_GPT)
#include "Gpt.h"
#endif
#if defined(USE_CAN)
#include "Can.h"
#endif
#if defined(USE_CANIF)
#include "CanIf.h"
#endif
#if defined(USE_PDUR)
#include "PduR.h"
#endif
#if defined(USE_COM)
#include "Com.h"
#endif
#if defined(USE_CANTP)
#include "CanTp.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp.h"
#endif
#if defined(USE_XCP)
#include "Xcp.h"
#endif
#if defined(USE_DCM)
#include "Dcm.h"
#endif
#if defined(USE_PWM)
#include "Pwm.h"
#endif
#if defined(USE_IOHWAB)
#include "IoHwAb.h"
#endif
#if defined(USE_FLS)
#include "Fls.h"
#endif
#if defined(USE_EEP)
#include "Eep.h"
#endif
#if defined(USE_FEE)
#include "Fee.h"
#endif
#if defined(USE_EA)
#include "Ea.h"
#endif
#if defined(USE_NVM)
#include "NvM.h"
#endif
#if defined(USE_COMM)
#include "ComM.h"
#endif
#if defined(USE_NM)
#include "Nm.h"
#endif
#if defined(USE_CANNM)
#include "CanNm.h"
#endif
#if defined(USE_CANSM)
#include "CanSM.h"
#endif
#if defined(USE_UDPNM)
#include "UdpNm.h"
#endif
#if defined(USE_LINSM)
#include "LinSM.h"
#endif
#if defined(USE_SPI)
#include "Spi.h"
#endif
#if defined(USE_WDG)
#include "Wdg.h"
#endif
#if defined(USE_WDGM)
#include "WdgM.h"
#endif

#if defined(CFG_SHELL)
#include "shell.h"
#endif

#if defined(USE_IPC)
#include "Ipc.h"
#endif

#if defined(USE_VIRTQ)
#include "VirtQ.h"
#endif

#if defined(USE_RPMSG)
#include "RPmsg.h"
#endif

#if defined(USE_SOAD)
#include "SoAd.h"
#endif

#ifdef USE_STMO
#include "Stmo.h"
#endif

#ifdef USE_SHELL
#include "shell.h"
#endif

#include "asdebug.h"
/* ----------------------------[private define]------------------------------*/

/* Does not run functions that are not drivers */
#define NO_DRIVER(_func)  \
  if( (!EcuM_DriverRestart) ) { \
    _func; \
 }

/* ----------------------------[private macro]-------------------------------*/

/* ----------------------------[private typedef]-----------------------------*/
/* ----------------------------[private function prototypes]-----------------*/
/* ----------------------------[private variables]---------------------------*/
static boolean EcuM_DriverRestart = FALSE;
/* ----------------------------[private functions]---------------------------*/
/* ----------------------------[public functions]----------------------------*/


/**
 * Called if there is something very wrong.
 *
 * Checks for ECUM_E_RAM_CHECK_FAILED (bad hash at wakeup) or
 * ECUM_E_CONFIGURATION_DATA_INCONSISTENT (bad post-build data)
 *
 * This function should NEVER return
 *
 * @param reason
 */
void EcuM_ErrorHook(Std_ReturnType reason) {
	/* @req 4.0.3|3.1.5/EcuM2904  */

	/* Go to defined state Reset, Fail-Safe etc. */

#if (MCU_PERFORM_RESET_API == STD_ON)
	Mcu_PerformReset();
#else
	asAssert(0);
#endif

#if defined(USE_DET)
#endif
}

extern EcuM_ConfigType EcuMConfig;

static void _dummy( void ) {

}

EcuM_ConfigType* EcuM_DeterminePbConfiguration(void) {
	NO_DRIVER(_dummy());	// Keep compiler silent
	return &EcuMConfig;
}

/**
 * First callout from EcuM_Init(). May contain
 * all kind of initialization code.
 *
 * Got here by main()->EcuM_Init()
 *
 * Part of STARTUP I
 */
void EcuM_AL_DriverInitZero(void)
{
//	VALIDATE_STATE( ECUM_STATE_STARTUP_ONE );
#ifdef USE_SHELL
	SHELL_Init();
#endif
#if defined(USE_DET)
	Det_Init();/** @req EcuM2783 */
    Det_Start();/** @req EcuM2634 */
#endif
}

/**
 * Part of STARTUP I
 *
 * @param ConfigPtr
 */
void EcuM_AL_DriverInitOne(const EcuM_ConfigType *ConfigPtr)
{
	(void)ConfigPtr;

//	VALIDATE_STATE( ECUM_STATE_STARTUP_ONE );

  //lint --e{715}       PC-Lint (715) - ConfigPtr usage depends on configuration of modules

#if defined(USE_MCU)
	Mcu_Init(ConfigPtr->McuConfig);

	/* Set up default clock (Mcu_InitClock requires initRun==1) */
	/* Ignoring return value */
	(void) Mcu_InitClock(ConfigPtr->McuConfig->McuDefaultClockSettings);

	// Wait for PLL to sync.
	while (Mcu_GetPllStatus() != MCU_PLL_LOCKED) {
		;
	}

	Mcu_DistributePllClock();
#endif

#if defined(USE_DEM)
	// Preinitialize DEM
	NO_DRIVER(Dem_PreInit());
#endif

#if defined(USE_PORT)
	// Setup Port
	Port_Init(ConfigPtr->PortConfig);
#endif

#if defined(USE_GPT)
	// Setup the GPT
	Gpt_Init(ConfigPtr->GptConfig);
#endif

	// Setup watchdog
#if defined(USE_WDG)
	Wdg_Init(ConfigPtr->WdgConfig);
#endif
#if defined(USE_WDGM)
	NO_DRIVER(WdgM_Init(ConfigPtr->WdgMConfig));
#endif

#if defined(USE_DMA)
	// Setup DMA
	Dma_Init(ConfigPtr->DmaConfig);
#endif

#if defined(USE_ADC)
	// Setup ADC
	Adc_Init(ConfigPtr->AdcConfig);
#endif

	// Setup ICU
	// TODO

	// Setup PWM
#if defined(USE_PWM)
	// Setup PWM
	Pwm_Init(ConfigPtr->PwmConfig);
#endif

#if defined(USE_IPC)
	// Setup PWM
	Ipc_Init(&Ipc_Config);
#endif

#if defined(USE_VIRTQ)
	NO_DRIVER(VirtQ_Init(&VirtQ_Config));
#endif

#if defined(USE_RPMSG)
	NO_DRIVER(RPmsg_Init(&RPmsg_Config));
#endif

#if defined(CFG_SHELL)
	SHELL_Init();
#endif

}


/**
 * At this point OS and essential drivers have started.
 * Start the rest of the drivers
 *
 *
 * Part of STARTUP II
 *
 * @param ConfigPtr
 */

void EcuM_AL_DriverInitTwo(const EcuM_ConfigType* ConfigPtr)
{
	(void)ConfigPtr;
  //lint --e{715}       PC-Lint (715) - ConfigPtr usage depends on configuration of modules
//	VALIDATE_STATE(ECUM_STATE_STARTUP_TWO);

#if defined(USE_SPI)
	// Setup SPI
	Spi_Init(ConfigPtr->SpiConfig);
#endif

#if defined(USE_EEP)
	// Setup EEP
	NO_DRIVER(Eep_Init(ConfigPtr->EepConfig));
#endif

#if defined(USE_FLS)
	// Setup Flash
	NO_DRIVER(Fls_Init(ConfigPtr->FlashConfig));
#endif

#if defined(USE_FEE)
	// Setup FEE
	NO_DRIVER(Fee_Init());
#endif

#if defined(USE_EA)
	// Setup EA
	NO_DRIVER(Ea_Init());
#endif

#if defined(USE_NVM)
	// Setup NVRAM Manager and start the read all job
	NO_DRIVER(NvM_Init());
	NO_DRIVER(NvM_ReadAll());
#endif

	// Setup CAN tranceiver
	// TODO

#if defined(USE_CAN)
	// Setup Can driver
	Can_Init(ConfigPtr->CanConfig);
#endif

#if defined(USE_CANIF)
	// Setup CanIf
	NO_DRIVER(CanIf_Init(ConfigPtr->CanIfConfig));
#endif

#if defined(USE_CANTP)
	// Setup CAN TP
	NO_DRIVER(CanTp_Init());
#endif

#if defined(USE_CANSM)
	NO_DRIVER(CanSM_Init(ConfigPtr->CanSMConfig));
#endif

#if defined(USE_J1939TP)
	// Setup J1939Tp
	NO_DRIVER(J1939Tp_Init(ConfigPtr->J1939TpConfig));
#endif

	// Setup LIN
	// TODO

#if defined(USE_PDUR)
	// Setup PDU Router
	NO_DRIVER(PduR_Init(ConfigPtr->PduRConfig));
#endif

#if defined(USE_CANNM)
    // Setup Can Network Manager
	NO_DRIVER(CanNm_Init(ConfigPtr->CanNmConfig));
#endif

#if defined(USE_UDPNM)
        // Setup Udp Network Manager
	NO_DRIVER(UdpNm_Init(ConfigPtr->UdpNmConfig));
#endif

#if defined(USE_NM)
        // Setup Network Management Interface
	NO_DRIVER(Nm_Init(ConfigPtr->NmConfig));
#endif

#if defined(USE_COM)
	// Setup COM layer
	NO_DRIVER(Com_Init(ConfigPtr->ComConfig));
#endif

#if defined(USE_XCP)
	// Setup XCP
	NO_DRIVER(Xcp_Init(&XcpConfig));
#endif
#if defined(USE_DCM)
	// Setup DCM
	NO_DRIVER(Dcm_Init());
#endif

#if defined(USE_IOHWAB)
	// Setup IO hardware abstraction layer
	IoHwAb_Init();
#endif

#if defined(USE_SOAD)
	SoAd_Init();
#endif

#ifdef USE_STMO
	Stmo_Init(&Stmo_ConfigData);
#endif
}


/**
 * Part of STARTUP II
 *
 * @param ConfigPtr
 */
void EcuM_AL_DriverInitThree(const EcuM_ConfigType* ConfigPtr)
{
	(void)ConfigPtr;
  //lint --e{715}       PC-Lint (715) - ConfigPtr usage depends on configuration of modules

#if defined(USE_DEM)
	// Setup DEM
	Dem_Init();
#endif

#if defined(USE_COMM)
	// Setup Communication Manager
    ComM_Init(ConfigPtr->ComMConfig);
#endif
}

void EcuM_OnEnterRun(void)
{
#if defined(CFG_ECUM_CS_SETEVENT)
	SetEvent(EVENT_MASK_EcuMEnterRUN,TASK_ID_Application);
#endif
}

void EcuM_OnExitRun(void)
{

}

void EcuM_OnExitPostRun(void)
{

}

void EcuM_OnPrepShutdown(void)
{

}

void EcuM_OnGoSleep(void)
{

}

void EcuM_OnGoOffOne(void)
{

}

void EcuM_OnGoOffTwo(void)
{

}



/**
 * This function should be the last this called before reset.
 * Normally this manipulates some pin that controls DC to power off
 * the board (ie it will never get to Mcu_PerformReset())
 */
void EcuM_AL_SwitchOff(void)
{
#if defined(USE_MCU) && (MCU_PERFORM_RESET_API == STD_ON)
	Mcu_PerformReset();
#endif
}
/**
 *
 * Called to check other wakeup sources. Assume for example that
 * we want to check something else than the actual wakeup pin.
 *
 * Can be called from interrupt context.
 * @param wakeupSource
 */

void EcuM_CheckWakeup(EcuM_WakeupSourceType source) {
#ifdef USE_MCU
	/* Re-enable PLL again */
	EcuM_ConfigType *ecuMConfigPtr;
	ecuMConfigPtr = EcuM_DeterminePbConfiguration();
	(void) Mcu_InitClock(ecuMConfigPtr->McuConfig->McuDefaultClockSettings);

	// Wait for PLL to sync.
	while (Mcu_GetPllStatus() != MCU_PLL_LOCKED) {
		;
	}
#endif
}


/**
 * Enable wakeup sources that should wake us. This is when going to sleep.
 *
 * This function is called once for each wakeup source.(ie source
 * can only have one bit set at any time). See ECUM2389 for example.
 *
 * @param source
 */
void EcuM_EnableWakeupSources( EcuM_WakeupSourceType source ) {

	/* ADD CODE BELOW */
}

/**
 *
 * @param wakeupSource
 */
void EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource) {

	/* ADD CODE BELOW */
}


/**
 * Start wakeup sources that need validation.
 *
 * 1. For wakeup sources that don't need validation nothing needs to be done.
 * 2. For wakeup sources that may have false wakeup, start then up, e.g. CanIf
 *
 * Called once when entering ECUM_STATE_WAKEUP_VALIDATION state
 *
 * @param wakeupSource
 */

void EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource) {
	VALIDATE_STATE( ECUM_STATE_WAKEUP_VALIDATION );

	/* ADD CODE BELOW */
}

/**
 * Stop not validated events
 *
 * @param wakeupSource
 */
void EcuM_StopWakeupSources(EcuM_WakeupSourceType wakeupSource)
{
	VALIDATE_STATE( ECUM_STATE_WAKEUP_VALIDATION);
	(void)wakeupSource;
}

/**
 *
 * @param wakeupSource
 */
void EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource) {

	VALIDATE_STATE( ECUM_STATE_WAKEUP_VALIDATION);

	/* ADD CODE BELOW */

	(void) wakeupSource;
}

/**
 * Restart drivers. Have no restart list, instead the
 * drivers restarted are drivers that have had it's hardware
 * registers reset.  If memory is also lost (=all memory is not
 * powered during sleep), this strategy does not work.
 *
 * This calls:
 * - EcuM_AL_DriverInitOne()
 * - EcuM_AL_DriverInitTwo()
 *
 */
void EcuM_AL_DriverRestart(void) {
	EcuM_ConfigType* config;

	VALIDATE_STATE( ECUM_STATE_WAKEUP_ONE);

	config = EcuM_DeterminePbConfiguration();

	/* Start all drivers for now */
	EcuM_AL_DriverInitOne(config);

	EcuM_AL_DriverInitTwo(config);
}

/**
 * Called once validation is done and a may change the wakeup at a very
 * late stage.
 *
 * For example if a wakeup event have been verified (=ECUM_WKACT_RUN) but here
 * a switch or something indicating immediate shutdown the reaction
 * can be changed here from ECUM_WKACT_RUN to ECUM_WKACT_SHUTDOWN.
 * This makes would make EcuM to go to
 * ECUM_STATE_PREP_SHUTDOWN(ECUM_STATE_WAKEUP_WAKESLEEP) instead of
 * ECUM_STATE_WAKEUP_TWO
 *
 * @param wact
 * @return
 */
EcuM_WakeupReactionType EcuM_OnWakeupReaction( EcuM_WakeupReactionType wact ) {

	VALIDATE_STATE( ECUM_STATE_WAKEUP_REACTION );

	/* ADD CODE BELOW */
	return wact;
}


/**
 * Generate RAM hash.
 * We are in ECUM_STATE_SLEEP here.
 *
 */
void EcuM_GenerateRamHash(void)
{
	/* De-init drivers.
	 * There is really no suiteable place to do this but here
	 */
	VALIDATE_STATE( ECUM_STATE_SLEEP );
	 
#if defined(USE_GPT) && (GPT_DEINIT_API == STD_ON)
	Gpt_DeInit();
#endif
#if defined(USE_ADC) && (ADC_DEINIT_API == STD_ON)
	Adc_DeInit();
#endif
#if defined(USE_PWM) && (PWM_DE_INIT_API == STD_ON)
	Pwm_DeInit();
#endif
#if defined(USE_SPI)
	Spi_DeInit();
#endif
}

/**
 * Check RAM hash.
 * We are still in ECUM_STATE_SLEEP here.
 *
 * @return
 */
uint8 EcuM_CheckRamHash( void ) {
	VALIDATE_STATE( ECUM_STATE_SLEEP );

	/* ADD CODE BELOW */

	return 0;
}


