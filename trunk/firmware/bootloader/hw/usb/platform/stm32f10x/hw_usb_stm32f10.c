/*!
 * \file hw_usb_stm32f10.c
 *
 * \brief 
 *
 *
 * \date May 20, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "usb/hw_usb.h"
#include "usb/mem/hw_usb_mem.h"


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

/*****************************************************************************/
PUBLIC uint32 HW_USB_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize)
{

    /* Use the memory interface function to write to the selected endpoint */
    HwUsbUserToPMABufferCopy(pBufferPointer, GetEPTxAddr(bEpAddr & 0x7F), wBufferSize);

    /* Update the data length in the control register */
    SetEPTxCount((bEpAddr & 0x7F), wBufferSize);

    SetEPTxValid(bEpAddr&0x0F);

    return wBufferSize;
}


/*****************************************************************************/
PUBLIC uint32 HW_USB_Read(uint8 bEpAddr, uint8* pBufferPointer)
{
    uint32 DataLength = 0;


    /* Get the number of received data on the selected Endpoint */
    DataLength = GetEPRxCount(bEpAddr & 0x7F);

    /* Use the memory interface function to write to the selected endpoint */
    HwUsbPMAToUserBufferCopy(pBufferPointer, GetEPRxAddr(bEpAddr & 0x7F), DataLength);

    SetEPRxValid(bEpAddr & 0x0F);


    return DataLength;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
