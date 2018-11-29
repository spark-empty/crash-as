/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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
#include "board.h"

#include "CDCDSerialDriver.h"

#include <stdbool.h>
#include <stdint.h>
#ifdef USE_SHELL
#include "shell.h"
#include "ringbuffer.h"
#endif

#include "Os.h"
/* ============================ [ MACROS    ] ====================================================== */
/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (64+2)

#define USB_JOB_READ  0x01
#define USB_JOB_WRITE 0x02
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern const USBDDriverDescriptors cdcdSerialDriverDescriptors;
/* ============================ [ DATAS     ] ====================================================== */
#ifdef USE_SHELL
RB_DECLARE(usbio, char, 1024);
static uint8_t usbTxBuffer[DATABUFFERSIZE];
#endif
/** Buffer for storing incoming USB data. */
static uint8_t usbRxBuffer[DATABUFFERSIZE];

static uint8_t usbJobFlag;

/** VBus pin instance. */
static const Pin pinVbus = PIN_USB_VBUS;

/* ============================ [ LOCALS    ] ====================================================== */

/**
 * Handles interrupts coming from PIO controllers.
 */
static void ISR_Vbus(const Pin *pPin)
{
    /* Check current level on VBus */
    if (PIO_Get(&pinVbus)) {
        USBD_Connect();
    }
    else {
        USBD_Disconnect();
    }
}

/**
 * Configures the VBus pin to trigger an interrupt when the level on that pin
 * changes.
 */
static void VBus_Configure( void )
{
    /* Configure PIO */
    PIO_Configure(&pinVbus, 1);
    PIO_ConfigureIt(&pinVbus, ISR_Vbus);
    PIO_EnableIt(&pinVbus);

    /* Check current level on VBus */
    if (PIO_Get(&pinVbus)) {

        /* if VBUS present, force the connect */
        USBD_Connect();
    }
    else {
        USBD_Disconnect();
    }
}

/*----------------------------------------------------------------------------
 * Callback invoked when data has been received on the USB.
 *----------------------------------------------------------------------------*/
static void _UsbDataReceived(uint32_t unused,
                             uint8_t status,
                             uint32_t received,
                             uint32_t remaining)
{
	/* Check that data has been received successfully */
	if (status == USBD_STATUS_SUCCESS) {
		#ifdef USE_SHELL
		for(int i=0; i < received; i++) {
			if(usbRxBuffer[i]=='\r')
				usbRxBuffer[i] = '\n';
			SHELL_input(usbRxBuffer[i]);
		}
		#endif
	}

	usbJobFlag &= ~USB_JOB_READ;
}

/*----------------------------------------------------------------------------
 * Callback invoked when data has been sent.
 *----------------------------------------------------------------------------*/
static void _UsbDataSent( void )
{
	usbJobFlag &= ~USB_JOB_WRITE;
}

/**
 * \brief Configure 48MHz Clock for USB
 */
static void _ConfigureUsbClock(void)
{
    /* Enable PLLB for USB */
    PMC->CKGR_PLLBR = CKGR_PLLBR_DIVB(1)
                    | CKGR_PLLBR_MULB(7)
                    | CKGR_PLLBR_PLLBCOUNT_Msk;
    while((PMC->PMC_SR & PMC_SR_LOCKB) == 0);
    /* USB Clock uses PLLB */
    PMC->PMC_USB = PMC_USB_USBDIV(1)       /* /2   */
                 | PMC_USB_USBS;           /* PLLB */
}
/* ============================ [ FUNCTIONS ] ====================================================== */

/**
 * Invoked after the USB driver has been initialized. By default, configures
 * the UDP/UDPHS interrupt.
 */
void USBDCallbacks_Initialized(void)
{
    NVIC_EnableIRQ(UDP_IRQn);
}

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void USBDDriverCallbacks_ConfigurationChanged(unsigned char cfgnum)
{
    CDCDSerialDriver_ConfigurationChangedHandler(cfgnum);
}

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void USBDCallbacks_RequestReceived(const USBGenericRequest *request)
{
    CDCDSerialDriver_RequestHandler(request);
}

uint8_t CDCDSerial_LineCodingIsToChange(CDCLineCoding * pLineCoding)
{
	return USBRC_SUCCESS;
}

#ifdef USE_SHELL
void USB_SerialPutChar(char ch)
{
	RB_Push(&rb_usbio, &ch, 1);
}
#endif
/*----------------------------------------------------------------------------
 *          Main
 *----------------------------------------------------------------------------*/
void usb_serial_init(void)
{
	/* If they are present, configure Vbus & Wake-up pins */
	PIO_InitializeInterrupts(0);

	/* Enable UPLL for USB */
	_ConfigureUsbClock();

	/* CDC serial driver initialization */
	CDCDSerialDriver_Initialize(&cdcdSerialDriverDescriptors);

	/* connect if needed */
	VBus_Configure();

	usbJobFlag = 0;
}

void usb_serial_task(void)
{
	/* Serial port ON/OFF */
	if (CDCDSerialDriver_GetControlLineState() & CDCControlLineState_DTR) {
		#ifdef USE_SHELL
		rb_size_t r;
		if (0 == (usbJobFlag&USB_JOB_WRITE)) {
			r = RB_Pop(&rb_usbio, usbTxBuffer, sizeof(usbTxBuffer));
			if(r > 0) {
				usbJobFlag |= USB_JOB_WRITE;
				CDCDSerialDriver_Write(usbTxBuffer, r, (TransferCallback)_UsbDataSent, NULL);
			}
		}
		#endif
		if (0 == usbJobFlag) {
			usbJobFlag |= USB_JOB_READ;
			/* Start receiving data on the USB */
			CDCDSerialDriver_Read(usbRxBuffer,
						  DATABUFFERSIZE,
						  (TransferCallback) _UsbDataReceived,
						  0);
		}
	}
	else {
		usbJobFlag = 0;
	}


}

