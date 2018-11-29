/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/** \addtogroup adc_module Working with ADC
 * The ADC driver provides the interface to configure and use the ADC peripheral.
 * \n
 *
 * It converts the analog input to digital format. The converted result could be
 * 12bit or 10bit. The ADC supports up to 16 analog lines.
 *
 * To Enable a ADC conversion,the user has to follow these few steps:
 * <ul>
 * <li> Select an appropriate reference voltage on ADVREF   </li>
 * <li> Configure the ADC according to its requirements and special needs,which
 * could be  broken down into several parts:
 * -#   Select the resolution by setting or clearing ADC_MR_LOWRES bit in
 *      ADC_MR (Mode Register)
 * -#   Set ADC clock by setting ADC_MR_PRESCAL bits in ADC_MR, the clock is
 *      calculated with ADCClock = MCK / ( (PRESCAL+1) * 2 )
 * -#   Set Startup Time,Tracking Clock cycles and Transfer Clock respectively
 *      in ADC_MR.
 </li>
 * <li> Start conversion by setting ADC_CR_START in ADC_CR. </li>
 * </ul>
 *
 * For more accurate information, please look at the ADC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref adc.c\n
 * \ref adc.h\n
 */
/*@{*/
/*@}*/
/**
 * \file
 *
 * Implementation of Analog-to-Digital Converter (ADC).
 *
 */
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize the ADC controller
 *
 * \param pAdc Pointer to an Adc instance.
 * \param idAdc ADC Index
 * \param trgEn trigger mode, software or Hardware
 * \param trgSel hardware trigger selection
 * \param sleepMode sleep mode selection
 * \param resolution resolution selection 10 bits or 12 bits
 * \param mckClock value of MCK in Hz
 * \param adcClock value of the ADC clock in Hz
 * \param startup value of the start up time (in ADCClock) (see datasheet)
 * \param tracking Tracking Time (in ADCClock cycle)
 */
extern void ADC_Initialize( Adc* pAdc, uint32_t idAdc )
{
    /* Enable peripheral clock*/
    PMC->PMC_PCER0 = 1 << idAdc;

    /*  Reset the controller */
    pAdc->ADC_CR = ADC_CR_SWRST;

    /* Reset Mode Register set to default */
    /* TrackTime set to 0 */
    /* Transfer set to 1 */
    /* settling set to 3 */
    pAdc->ADC_MR = ADC_MR_TRANSFER(1) | ADC_MR_TRACKTIM(0) | ADC_MR_SETTLING(3);
}

/**
 * \brief Initialize the ADC Timing
 */
extern void ADC_CfgTiming( Adc* pAdc, uint32_t tracking, uint32_t settling, uint32_t transfer )
{
    pAdc->ADC_MR = ADC_MR_TRANSFER( transfer )
                 | ADC_MR_SETTLING( settling )
                 | ADC_MR_TRACKTIM( tracking ) ;
}

/**
 * \brief Initialize the ADC Timing
 */
extern void ADC_cfgFrequency( Adc* pAdc, uint32_t startup, uint32_t prescal )
{
    pAdc->ADC_MR |= ADC_MR_PRESCAL( prescal )
                 | ( (startup<<ADC_MR_STARTUP_Pos) & ADC_MR_STARTUP_Msk);
}

/**
 * \brief Initialize the ADC Trigering
 */
extern void ADC_CfgTrigering( Adc* pAdc, uint32_t trgEn, uint32_t trgSel, uint32_t freeRun )
{
    pAdc->ADC_MR |= ((trgEn<<0) & ADC_MR_TRGEN)
                    | ((trgSel<<ADC_MR_TRGSEL_Pos) & ADC_MR_TRGSEL_Msk)
                    | ((freeRun<<7) & ADC_MR_FREERUN) ;
}

/**
 * \brief Initialize the ADC Low Res
 */
extern void ADC_CfgLowRes( Adc* pAdc, uint32_t resolution )
{
    pAdc->ADC_MR |= (resolution<<4) & ADC_MR_LOWRES;
}

/**
 * \brief Initialize the ADC PowerSave
 */
extern void ADC_CfgPowerSave( Adc* pAdc, uint32_t sleep, uint32_t fwup )
{
    pAdc->ADC_MR |= ( ((sleep<<5) & ADC_MR_SLEEP)
                    | ((fwup<<6) & ADC_MR_FWUP) );
}

/**
 * \brief Initialize the ADC Channel Mode
 */
extern void ADC_CfgChannelMode( Adc* pAdc, uint32_t useq, uint32_t anach )
{
    pAdc->ADC_MR |= ( ((anach<<23) & ADC_MR_ANACH)
                    | ((useq <<31) & (uint32_t)ADC_MR_USEQ) );
}


/**
 * \brief calcul_startup
 */
static uint32_t calcul_startup( uint32_t startup )
{
    uint32_t startup_value=0;

    if( startup == 0 )
        startup_value = 0;
    else if( startup == 1 )
        startup_value = 8;
    else if( startup == 2 )
        startup_value = 16;
    else if( startup == 3 )
        startup_value = 24;
    else if( startup == 4 )
        startup_value = 64;
    else if( startup == 5 )
        startup_value = 80;
    else if( startup == 6 )
        startup_value = 96;
    else if( startup == 7 )
        startup_value = 112;
    else if( startup == 8 )
        startup_value = 512;
    else if( startup == 9 )
        startup_value = 576;
    else if( startup == 10 )
        startup_value = 640;
    else if( startup == 11 )
        startup_value = 704;
    else if( startup == 12 )
        startup_value = 768;
    else if( startup == 13 )
        startup_value = 832;
    else if( startup == 14 )
        startup_value = 896;
    else if( startup == 15 )
        startup_value = 960;

    return startup_value;
}

/**
 * \brief ADC check
 */
extern void ADC_check( Adc* pAdc, uint32_t mck_freq )
{
    uint32_t adc_freq;
    uint32_t prescal;
    uint32_t startup;

    /* ADCClock = MCK / ( (PRESCAL+1) * 2 ) */
    prescal = (( pAdc->ADC_MR & ADC_MR_PRESCAL_Msk) >> ADC_MR_PRESCAL_Pos);
    adc_freq = mck_freq / ((prescal+1)*2);
    printf("ADC clock frequency =  %d Hz\r\n", (int)adc_freq );

    if( adc_freq < ADC_FREQ_MIN )
    {
        printf("adc frequency too low (out of specification: %d Hz)\r\n", (int)ADC_FREQ_MIN);
    }
    if( adc_freq > ADC_FREQ_MAX )
    {
        printf("adc frequency too high (out of specification: %d Hz)\r\n", (int)ADC_FREQ_MAX);
    }

    startup = (( pAdc->ADC_MR & ADC_MR_STARTUP_Msk) >> ADC_MR_STARTUP_Pos);
    if( !(pAdc->ADC_MR & ADC_MR_SLEEP_SLEEP) )
    {
        /* 40�s */
        if( ADC_STARTUP_NORM * adc_freq / 1000000 > calcul_startup(startup) )
        {
            printf("Startup time too small: %d, programmed: %d\r\n", (int)(ADC_STARTUP_NORM * adc_freq / 1000000), (int)calcul_startup(startup));
        }
    }
    else
    {
        if(pAdc->ADC_MR & ADC_MR_FREERUN_ON)
        {
            printf("FreeRun forbidden in sleep mode\n\r");
        }
        if( !(pAdc->ADC_MR & ADC_MR_FWUP_ON) )
        {
            /* Sleep 40�s */
            if( ADC_STARTUP_NORM * adc_freq / 1000000 > calcul_startup(startup) )
            {
                printf("Startup time too small: %d, programmed: %d\r\n", (int)(ADC_STARTUP_NORM * adc_freq / 1000000), (int)(calcul_startup(startup)));
            }
        }
        else
        {
            if( pAdc->ADC_MR & ADC_MR_FWUP_ON )
            {
                /* Fast Wake Up Sleep Mode: 12�s */
                if( ADC_STARTUP_FAST * adc_freq / 1000000 > calcul_startup(startup) )
                {
                    printf("Startup time too small: %d, programmed: %d\r\n", (int)(ADC_STARTUP_NORM * adc_freq / 1000000), (int)(calcul_startup(startup)));
                }
            }
        }
    }




}



/**
 * Return the Channel Converted Data
 *
 * \param pAdc Pointer to an Adc instance.
 * \param channel channel to get converted value
 */
extern uint32_t ADC_GetConvertedData( Adc* pAdc, uint32_t dwChannel )
{
    uint32_t dwData = 0;

    assert( dwChannel < 16 ) ;
		
    if ( 15 >= dwChannel )
    {
		dwData=*(pAdc->ADC_CDR+dwChannel) ;
    }

    return dwData ;
}
/**
 * Set compare channel
 *
 * \param pAdc Pointer to an Adc instance.
 * \param channel channel number to be set,16 for all channels
 */
extern void ADC_SetCompareChannel( Adc* pAdc, uint32_t dwChannel )
{
    assert( dwChannel <= 16 ) ;

    if ( dwChannel < 16 )
	{
        pAdc->ADC_EMR &= (uint32_t)~(ADC_EMR_CMPALL);
        pAdc->ADC_EMR &= (uint32_t)~(ADC_EMR_CMPSEL_Msk);
        pAdc->ADC_EMR |= (dwChannel << ADC_EMR_CMPSEL_Pos);
    }
	else
	{
        pAdc->ADC_EMR |= ADC_EMR_CMPALL;
    }
}
/**
 * Set compare mode
 *
 * \param pAdc Pointer to an Adc instance.
 * \param mode compare mode
 */
extern void ADC_SetCompareMode( Adc* pAdc, uint32_t dwMode )
{
    pAdc->ADC_EMR &= (uint32_t)~(ADC_EMR_CMPMODE_Msk);
    pAdc->ADC_EMR |= (dwMode & ADC_EMR_CMPMODE_Msk) ;
}
/**
 * Set comparsion window,one thereshold each time
 *
 * \param pAdc Pointer to an Adc instance.
 * \param hi_lo Comparison Window
 */
extern void ADC_SetComparisonWindow( Adc* pAdc, uint32_t dwHi_Lo )
{
    pAdc->ADC_CWR = dwHi_Lo ;
}

/**----------------------------------------------------------------------------
 * Test if ADC Interrupt is Masked
 *
 * \param pAdc Pointer to an Adc instance.
 * \param flag flag to be tested
 *
 * \return 1 if interrupt is masked, otherwise 0
 */
uint32_t ADC_IsInterruptMasked( Adc* pAdc, uint32_t dwFlag )
{
    return (ADC_GetInterruptMaskStatus( pAdc ) & dwFlag) ;
}

/**----------------------------------------------------------------------------
 * Test if ADC Status is Set
 *
 * \param pAdc Pointer to an Adc instance.
 * \param flag flag to be tested
 *
 * \return 1 if the staus is set; 0 otherwise
 */
extern uint32_t ADC_IsStatusSet( Adc* pAdc, uint32_t dwFlag )
{
    return (ADC_GetStatus( pAdc ) & dwFlag) ;
}

/**----------------------------------------------------------------------------
 * Test if ADC channel interrupt Status is Set
 *
 * \param adc_sr Value of SR register
 * \param channel Channel to be tested
 *
 * \return 1 if interrupt status is set, otherwise 0
 */
extern uint32_t ADC_IsChannelInterruptStatusSet( uint32_t dwAdc_sr, uint32_t dwChannel )
{
    uint32_t dwStatus ;

    if ( (dwAdc_sr & ((uint32_t)1 << dwChannel)) == ((uint32_t)1 << dwChannel) )
    {
        dwStatus = 1 ;
    }
    else
    {
        dwStatus = 0 ;
    }

    return dwStatus ;
}

/**
 * \brief Read converted data through PDC channel
 *
 * \param pADC the pointer of adc peripheral
 * \param pBuffer the destination buffer
 * \param dwSize the size of the buffer
 */
extern uint32_t ADC_ReadBuffer( Adc* pADC, int16_t *pwBuffer, uint32_t dwSize )
{
    /* Check if the first PDC bank is free*/
    if ( (pADC->ADC_RCR == 0) && (pADC->ADC_RNCR == 0) )
    {
        pADC->ADC_RPR = (uint32_t)pwBuffer ;
        pADC->ADC_RCR = dwSize ;
        pADC->ADC_PTCR = ADC_PTCR_RXTEN;

        return 1;
    }
    /* Check if the second PDC bank is free*/
    else
    {
        if ( pADC->ADC_RNCR == 0 )
        {
            pADC->ADC_RNPR = (uint32_t)pwBuffer ;
            pADC->ADC_RNCR = dwSize ;

            return 1 ;
        }
        else
        {
            return 0 ;
        }
    }
}

