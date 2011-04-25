/*!
 * \file dfu_sm_actions.c
 *
 * \brief 
 *
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "dfu/dfu.h"

#include"hw/nvic/hw_nvic.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuActionQueryDevice(DFU_Command *Cmd, DFU_Response *Response)
{
    Response->Status = DFU_STATUS_SUCCESS;

    Response->Mode = *((uint32*)DEVICE_MODE_ADDR);
    Response->FWVersion = *((uint32*)DEVICE_VERSION_ADDR);

    Response->VendorId = USB_VENDOR_ID;
    Response->ProductId = USB_PRODUCT_ID;
    Response->DeviceId = USB_DEVICE_ID;

    print("Device queried\n");

}


/******************************************************************************/
PROTECTED void DfuActionInitializeUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
    Response->Status = DFU_STATUS_SUCCESS;

    print("Device initializing...\n");

    // Erase old device firmware
    DfuMalErase(DEVICE_START_ADDR, DEVICE_MEM_SIZE);

    // send DFU_STATUS_SUCCESS
    DfuComSendResponse();

    // reset device
    print("Resetting device.\n");
    HW_NVIC_SystemReset();
}

/******************************************************************************/
PROTECTED void DfuActionCompleteUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
    uint32 *mode;
    Response->Status = DFU_STATUS_SUCCESS;

    print("Completed update.\n");

    // set device to DFU_MODE_USER in non-volatile flash
    mode = (uint32*)DfuMalBuffer;
    *mode = DFU_MODE_USER;
    DfuMalWrite(DEVICE_MODE_ADDR, 4);


    // send DFU_STATUS_SUCCESS
    DfuComSendResponse();



    // reset device
    print("Resetting device.\n");
    HW_NVIC_SystemReset();

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

