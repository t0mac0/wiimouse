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

	Response->VendorId = USB_VENDOR_ID;
	Response->ProductId = USB_PRODUCT_ID;
	Response->DeviceId = USB_DEVICE_ID;
	Response->FWVersion = FW_VERSION; // todo: query flash memory

	printf("Device queried\n");

}

void  dfu_ActionInitializeUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionBeginUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionStartSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionEndSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionEndUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}




void  dfu_ActionBeginValidation(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionStartSectionValidation(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionValidateSection(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionEndSectionValidation(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionEndValidation(DFU_Command *Cmd, DFU_Response *Response)
{


}

void  dfu_ActionCompleteUpdate(DFU_Command *Cmd, DFU_Response *Response)
{


}
