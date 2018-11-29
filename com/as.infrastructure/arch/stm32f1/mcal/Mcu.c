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


#include "Std_Types.h"
#include "Mcu.h"
#include "Os.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include <string.h>
#ifdef USE_SHELL
#include "shell.h"
#endif

#include "asdebug.h"

#include "stdio_cfg.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_x)  (sizeof(_x)/sizeof((_x)[0]))
#endif

/* Development error macros. */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define VALIDATE(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(MODULE_ID_MCU,0,_api,_err); \
          return; \
        }

#define VALIDATE_W_RV(_exp,_api,_err,_rv ) \
        if( !(_exp) ) { \
          Det_ReportError(MODULE_ID_MCU,0,_api,_err); \
          return (_rv); \
        }
#else
#define VALIDATE(_exp,_api,_err )
#define VALIDATE_W_RV(_exp,_api,_err,_rv )
#endif


typedef struct {
	uint32 lossOfLockCnt;
	uint32 lossOfClockCnt;
} Mcu_Stats;

/**
 * Type that holds all global data for Mcu
 */
typedef struct
{
  // Set if Mcu_Init() have been called
  boolean initRun;

  // Our config
  const Mcu_ConfigType *config;

  Mcu_ClockType clockSetting;

  Mcu_Stats stats;

} Mcu_GlobalType;


// Global config
Mcu_GlobalType Mcu_Global =
{
		.initRun = 0,
		.config = &McuConfigData[0],
};

//-------------------------------------------------------------------

void Mcu_ConfigureFlash(void);

static uint32_t GetPllValueFromMult(uint8_t pll)
{
	return (((uint32_t)pll - 2) << 18);
}

#ifdef STM32F10X_CL
static uint32_t GetPll2ValueFromMult(uint8_t pll)
{
	return (((uint32_t)pll - 2) << 8);
}
#endif

/**
  * Set bus clocks. SysClk,AHBClk,APB1Clk,APB2Clk
  */
static void SetClocks(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
  volatile uint32 StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSEStartUp_TimeOut));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;


    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

#ifdef STM32F10X_CL
    /* Configure PLLs ------------------------------------------------------*/
    /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
    /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

    RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                              RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
    RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | GetPll2ValueFromMult(clockSettingsPtr->Pll2) |
                             RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

    /* Enable PLL2 */
    RCC->CR |= RCC_CR_PLL2ON;
    /* Wait till PLL2 is ready */
    while((RCC->CR & RCC_CR_PLL2RDY) == 0)
    {
    }

    /* PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
    		                GetPllValueFromMult(clockSettingsPtr->Pll1));
#else
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | GetPllValueFromMult(clockSettingsPtr->Pll1));
#endif /* STM32F10X_CL */

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* HSE fails to start-up, the application will have wrong clock */
	  NVIC_SystemReset();
  }
}

/**
  * Initialize Peripherals clocks
  */
static void InitPerClocks()
{
	RCC->AHBENR |= McuPerClockConfigData.AHBClocksEnable;
	RCC->APB1ENR |= McuPerClockConfigData.APB1ClocksEnable;
	RCC->APB2ENR |= McuPerClockConfigData.APB2ClocksEnable;
}

/**
  * Initialize Flash, PLL and clocks.
  */
static void InitMcuClocks(const Mcu_ClockSettingConfigType *clockSettingsPtr)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F10X_CL */

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifndef STM32F10X_CL
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#else
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#endif /* STM32F10X_CL */

  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetClocks(clockSettingsPtr);
}

//-------------------------------------------------------------------

void Mcu_Init(const Mcu_ConfigType *configPtr)
{
  VALIDATE( ( NULL != configPtr ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

  memset(&Mcu_Global.stats,0,sizeof(Mcu_Global.stats));

  Irq_Enable();

  Mcu_Global.config = configPtr;
  Mcu_Global.initRun = 1;
}
//-------------------------------------------------------------------

void Mcu_DeInit()
{
  Mcu_Global.initRun = FALSE; // Very simple Deinit. Should we do more?
}

//-------------------------------------------------------------------
Std_ReturnType Mcu_InitRamSection(const Mcu_RamSectionType RamSection)
{
  VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
  VALIDATE_W_RV( ( RamSection <= Mcu_Global.config->McuRamSectors ), MCU_INITRAMSECTION_SERVICE_ID, MCU_E_PARAM_RAMSECTION, E_NOT_OK );

  /* NOT SUPPORTED, reason: no support for external RAM */

  return E_OK;
}



//-------------------------------------------------------------------

Std_ReturnType Mcu_InitClock(const Mcu_ClockType ClockSetting)
{
  const Mcu_ClockSettingConfigType *clockSettingsPtr;
  VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT, E_NOT_OK );
  VALIDATE_W_RV( ( ClockSetting < Mcu_Global.config->McuClockSettings ), MCU_INITCLOCK_SERVICE_ID, MCU_E_PARAM_CLOCK, E_NOT_OK );

  Mcu_Global.clockSetting = ClockSetting;
  clockSettingsPtr = &Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting];

  InitMcuClocks(clockSettingsPtr);

  InitPerClocks();

  return E_OK;
}

void Stdio_PutChar(char ch)
{
  uint32_t timeout = 0;
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until the end of transmission */
  while ( (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) &&
		  (timeout < 1000))
  {
	  timeout ++;
  }
}

//-------------------------------------------------------------------
void knl_isr_usart2_process(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		char ch = (char)(USART_ReceiveData(USART2)&0xFF);
#ifdef USE_SHELL
		if('\r' == ch)
		{
			ch = '\n';
		}
		SHELL_input(ch);
#endif
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
	NVIC_ClearPendingIRQ(USART2_IRQn);
}

static void Usart_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);

    /* Enable the USART2 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_EnableIRQ(USART2_IRQn);
    /* Enable USART */
    USART_Cmd(USART2, ENABLE);
}
void Mcu_DistributePllClock(void)
{
  VALIDATE( ( 1 == Mcu_Global.initRun ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_UNINIT );
//  VALIDATE( ( FMPLL.SYNSR.B.LOCK == 1 ), MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID, MCU_E_PLL_NOT_LOCKED );

  /* NOT IMPLEMENTED due to pointless function on this hardware */
  Usart_Init();

#ifdef USE_LWIP
  /* Enable ETHERNET clock  */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ETH_MAC | RCC_AHBPeriph_ETH_MAC_Tx |
                        RCC_AHBPeriph_ETH_MAC_Rx, ENABLE);
#endif

}

//-------------------------------------------------------------------


Mcu_PllStatusType Mcu_GetPllStatus(void) {
	VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_GETPLLSTATUS_SERVICE_ID, MCU_E_UNINIT, MCU_PLL_STATUS_UNDEFINED );
	Mcu_PllStatusType rv;

#if !defined(USE_SIMULATOR)
	if (RCC->CR & RCC_CR_PLLRDY) {
		rv = MCU_PLL_LOCKED;
	} else {
		rv = MCU_PLL_UNLOCKED;
	}
#else
	/* We are running on instruction set simulator. PLL is then always in sync... */
	rv = MCU_PLL_LOCKED;
#endif
	return rv;
}

//-------------------------------------------------------------------

/**
 *
 * @return
 */
Mcu_ResetType Mcu_GetResetReason(void) {
	Mcu_ResetType rv;
	uint32_t csr;

	VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_RESET_UNDEFINED );

	csr = RCC->CSR;

	if (csr & RCC_CSR_SFTRSTF) {
		rv = MCU_SW_RESET;
	} else if (csr & (RCC_CSR_IWDGRSTF|RCC_CSR_WWDGRSTF) ) {
		rv = MCU_WATCHDOG_RESET;
	} else if ( csr & RCC_CSR_PORRSTF ) {
		rv = MCU_POWER_ON_RESET;
	} else {
		rv = MCU_RESET_UNDEFINED;
	}

	return rv;
}

//-------------------------------------------------------------------

/**
 * Shall read the raw reset value from hardware register if the hardware
 * supports this.
 *
 * @return
 */

Mcu_RawResetType Mcu_GetResetRawValue(void) {
	VALIDATE_W_RV( ( 1 == Mcu_Global.initRun ), MCU_GETRESETREASON_SERVICE_ID, MCU_E_UNINIT, MCU_GETRESETRAWVALUE_UNINIT_RV );

	if (!Mcu_Global.initRun) {
		return MCU_GETRESETRAWVALUE_UNINIT_RV;
	} else {
		return (RCC->CSR) & (RCC_CSR_RMVF | RCC_CSR_PINRSTF | RCC_CSR_PORRSTF
				| RCC_CSR_SFTRSTF | RCC_CSR_IWDGRSTF | RCC_CSR_WWDGRSTF
				| RCC_CSR_LPWRRSTF);
	}
	return 0;
}

//-------------------------------------------------------------------

#if ( MCU_PERFORM_RESET_API == STD_ON )
/**
 * Shell perform a microcontroller reset by using the hardware feature
 * of the micro controller.
 */
void Mcu_PerformReset(void)
{
  VALIDATE( ( 1 == Mcu_Global.initRun ), MCU_PERFORMRESET_SERVICE_ID, MCU_E_UNINIT );

  NVIC_SystemReset();
}
#endif

//-------------------------------------------------------------------

void Mcu_SetMode(const Mcu_ModeType McuMode)
{
  VALIDATE( ( 1 == Mcu_Global.initRun ), MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT );
  VALIDATE( (0), MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE );
  //VALIDATE( ( McuMode <= Mcu_Global.config->McuNumberOfMcuModes ), MCU_SETMODE_SERVICE_ID, MCU_E_PARAM_MODE );
  (void) McuMode;

}

//-------------------------------------------------------------------

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32_t McuE_GetSystemClock(void)
{
  uint32_t f_sys;

  uint32  extal = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].McuClockReferencePointFrequency;
  uint32 pll1 = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].Pll1;

#ifdef STM32F10X_CL
  uint32 pll2 = Mcu_Global.config->McuClockSettingConfig[Mcu_Global.clockSetting].Pll2;
  /* PLL2 configuration: PLL2CLK = (HSE / 5) * PLL2 */
  /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 */
  /* PLL configuration: PLLCLK = PREDIV1 * PLL1 */
  f_sys = (extal / 5 * pll2) / 5 * pll1;
#else
  /* PLL configuration: PLLCLK = HSE * PLL1 */
  f_sys = extal * pll1;
#endif

  return f_sys;
}

/**
 * Get the peripheral clock in Hz for a specific device
 */
uint32_t McuE_GetPeripheralClock(McuE_PeriperalClock_t type)
{
	uint32_t res = 0;

	switch(type)
	{
	case PERIPHERAL_CLOCK_AHB:
		res = McuE_GetSystemClock();
		break;
	case PERIPHERAL_CLOCK_APB1:
		res = McuE_GetSystemClock() / 2;
		break;
	case PERIPHERAL_CLOCK_APB2:
		res = McuE_GetSystemClock();
		break;
	default:
		break;
	}

	return res;
}


/**
 * Function to setup the internal flash for optimal performance
 */

void Mcu_ConfigureFlash(void)
{

}

void TaskIdleHook(void)
{
	FLUSH_STDIO_IF(USART_GetFlagStatus(USART2, USART_FLAG_TC) != RESET);
}

