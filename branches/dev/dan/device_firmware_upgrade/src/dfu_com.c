/*
 * dfu_cl.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "usb_sil.h"
#include "usb_regs.h"
#include "dfu_state_machine.h"

static DFU_Command dfu_CommandBuffer;
static DFU_Response dfu_ResponseBuffer;

void dfu_ComReceiveCommand( void )
{
	USB_SIL_Read(EP3_OUT, (uint8*)&dfu_CommandBuffer);
	SetEPRxValid(ENDP3);

	dfu_StateTransition(&dfu_CommandBuffer, &dfu_ResponseBuffer);
}


void dfu_ComSendResponse( void )
{
	USB_SIL_Write(EP1_IN, (uint8*)&dfu_ResponseBuffer, sizeof(DFU_Response));
	SetEPTxValid(ENDP1);
}
