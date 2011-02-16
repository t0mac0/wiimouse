/*
 * dfu_actions.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "dfu_actions.h"
#include "usb_desc.h"
#include "printf.h"


void dfu_ActionQueryDevice(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;

	Response->Mode = DFU_MODE_UPDATE; //todo: query flash memory
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
	// send DFU_STATUS_SUCCESS
	// reset device
}



void  dfu_ActionCompleteUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;
	printf("Complete update\n");
	// set device to DFU_MODE_USER in non-volatile flash
	// send DFU_STATUS_SUCCESS
	// reset device
}
