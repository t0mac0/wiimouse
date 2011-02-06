/*
* dfu_actions.c
*
*  Created on: Feb 6, 2011
*      Author: Reed
*/
#include "dfu_actions.h"
#include "usb_desc.h"


void dfu_ActionQueryDevice(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;

	switch(Cmd->SubCommand)
	{
	case DFU_SUBCMD_GET_VENDOR_ID:
		Response->u32.VendorId = USB_VENDOR_ID;
		break;
	case DFU_SUBCMD_GET_PRODUCT_ID:
		Response->u32.ProductId = USB_PRODUCT_ID;
		break;
	case DFU_SUBCMD_GET_DEVICE_ID:
		Response->u32.DeviceId = USB_DEVICE_ID;
		break;
	case DFU_SUBCMD_GET_FW_VERSION:
		Response->u32.FWVersion = FW_VERSION; // todo: query flash memory
		break;
	default:
		Response->Status = DFU_STATUS_INVALID_SUB_COMMAND;
	}

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
