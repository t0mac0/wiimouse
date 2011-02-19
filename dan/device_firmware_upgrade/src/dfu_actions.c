/*
 * dfu_actions.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "core_cm3.h"
#include "dfu_actions.h"
#include "usb_desc.h"
#include "printf.h"
#include "dfu_com.h"
#include "dfu_mal.h"



void dfu_ActionQueryDevice(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;

	Response->Mode = *((uint32*)DFU_MODE_ADDR); //DFU_MODE_UPDATE; //todo: query flash memory
	Response->VendorId = USB_VENDOR_ID;
	Response->ProductId = USB_PRODUCT_ID;
	Response->DeviceId = USB_DEVICE_ID;
	Response->FWVersion = FW_VERSION; // todo: query flash memory
	printf("Device queried\n");

}

void  dfu_ActionInitializeUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;
	printf("Device initializing\n");

	// set device to DFU_MODE_UPDATE in non-volatile flash
//	*(uint32 *)(DFU_MalBuffer + 0) = 0;
//	MAL_Write(DFU_MODE_ADDR, 4);
	MAL_Erase(DFU_MODE_ADDR, 4);
	*(uint32 *)(DFU_MalBuffer + 0) = DFU_MODE_UPDATE;
	MAL_Write(DFU_MODE_ADDR, 4);

	// send DFU_STATUS_SUCCESS
	dfu_ComSendResponse();

	// reset device
	NVIC_SystemReset();
}



void  dfu_ActionCompleteUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;
	printf("Complete update\n");

	// set device to DFU_MODE_USER in non-volatile flash
//	*(uint32 *)(DFU_MalBuffer + 0) = 0;
//	MAL_Write(DFU_MODE_ADDR, 4);
	MAL_Erase(DFU_MODE_ADDR, 4);
	*(uint32 *)(DFU_MalBuffer + 0) = DFU_MODE_USER;
	MAL_Write(DFU_MODE_ADDR, 4);


	// send DFU_STATUS_SUCCESS
	dfu_ComSendResponse();



	// reset device
	printf("Reseting device...\n");

	NVIC_SystemReset();



}
