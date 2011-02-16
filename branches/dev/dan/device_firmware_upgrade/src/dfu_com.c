/*
 * dfu_cl.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "usb_sil.h"
#include "usb_regs.h"
#include "dfu_state_machine.h"
#include "dfu_mal.h"
#include "printf.h"
#include "usb_desc.h"
#include "dfu_actions.h"



static uint32 readCount = 0;

static DFU_Command *commandBuffer = (DFU_Command*)&DFU_MalBuffer[0];
static DFU_Response *responseBuffer = (DFU_Response*)&DFU_MalBuffer[DFU_COMMAND_SIZE];

void dfu_ComReceiveCommand( void )
{
	uint32 bytesRead;

	bytesRead = USB_SIL_Read(EP3_OUT, (uint8*)&DFU_MalBuffer[readCount]);
	SetEPRxValid(ENDP3);

	readCount += bytesRead;

	if(DFU_MalWriteEnabled)
	{
		dfu_ActionWriteSectionChunk(responseBuffer, readCount);
		readCount = ((DFU_MalWriteEnabled == FALSE) ?  0 : readCount);
	}
	else if(DFU_MalReadEnabled)
	{
		dfu_ActionReadSectionChunk();
		readCount = ((DFU_MalReadEnabled == FALSE) ?  0 : readCount);
	}
	else if(readCount >= DFU_COMMAND_SIZE)
	{
		readCount = 0;
		dfu_StateTransition(commandBuffer, responseBuffer);
	}
}


void dfu_ComSendResponse( void )
{
	USB_SIL_Write(EP1_IN, (uint8*)responseBuffer, sizeof(DFU_Response));
	SetEPTxValid(ENDP1);
}

void dfu_ComSendData( uint32 byteCount )
{
#define TRANSFER_SIZE 60
	uint32 bytesSent = 0;
	uint32 bytesToSend;

	while(bytesSent < byteCount)
	{
		bytesToSend = ((byteCount-bytesSent) < TRANSFER_SIZE) ? (byteCount-bytesSent) : TRANSFER_SIZE;
		USB_SIL_Write(EP1_IN, (uint8*)&DFU_MalBuffer[bytesSent], bytesToSend);
		SetEPTxValid(ENDP1);
		bytesSent += bytesToSend;
	}
}

