/*
 * dfu_cl.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "usb_sil.h"
#include "usb_regs.h"
#include "dfu_state_machine.h"
#include "printf.h"

static DFU_Command commandBuffer;
static DFU_Response responseBuffer;

static uint32 readCount = 0;

void dfu_ComReceiveCommand( void )
{
	uint32 bytesRead;

	bytesRead = USB_SIL_Read(EP3_OUT, (uint8*)&commandBuffer);
	SetEPRxValid(ENDP3);

	readCount += bytesRead;

	if(readCount >= sizeof(DFU_Command))
	{
		readCount = 0;
		dfu_StateTransition(&commandBuffer, &responseBuffer);
	}
}


void dfu_ComSendResponse( void )
{
	USB_SIL_Write(EP1_IN, (uint8*)&responseBuffer, sizeof(DFU_Response));
	SetEPTxValid(ENDP1);
}
