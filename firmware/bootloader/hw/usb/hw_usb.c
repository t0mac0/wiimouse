/*!
 * \file hw_usb.c
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <platform_lib.h>

#include "hw_usb.h"
#include "usb/core/hw_usb_core.h"
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
 Protected Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED void HwUsbSetUsbClock(void);
PROTECTED void HwUsbInterruptsConfig(void);
PROTECTED void HwUsbPinConfig(void);


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*******************************************************************************
 * Function Name  : USB_Init
 * Description    : USB system initialization
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
PUBLIC bool HW_USB_Init(void)
{
    HwUsbPinConfig();

    HwUsbInterruptsConfig();

    HwUsbSetUsbClock();

    pInformation = &Device_Info;
    pInformation->ControlState = 2;
    pProperty = &Device_Property;
    pUser_Standard_Requests = &User_Standard_Requests;
    /* Initialize devices one by one */
    pProperty->Init();


    return TRUE;
}



/*******************************************************************************
 * Function Name  : HW_USB_Write
 * Description    : Write a buffer of data to a selected endpoint.
 * Input          : - bEpAddr: The address of the non control endpoint.
 *                  - pBufferPointer: The pointer to the buffer of data to be written
 *                    to the endpoint.
 *                  - wBufferSize: Number of data to be written (in bytes).
 * Output         : None.
 * Return         : Status.
 *******************************************************************************/
PUBLIC uint32 HW_USB_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize)
{

    /* Use the memory interface function to write to the selected endpoint */
    HwUsbUserToPMABufferCopy(pBufferPointer, GetEPTxAddr(bEpAddr & 0x7F), wBufferSize);

    /* Update the data length in the control register */
    SetEPTxCount((bEpAddr & 0x7F), wBufferSize);

    return wBufferSize;
}



/*******************************************************************************
 * Function Name  : HW_USB_Read
 * Description    : Write a buffer of data to a selected endpoint.
 * Input          : - bEpAddr: The address of the non control endpoint.
 *                  - pBufferPointer: The pointer to which will be saved the
 *                     received data buffer.
 * Output         : None.
 * Return         : Number of received data (in Bytes).
 *******************************************************************************/
PUBLIC uint32 HW_USB_Read(uint8 bEpAddr, uint8* pBufferPointer)
{
    uint32 DataLength = 0;

    /* Get the number of received data on the selected Endpoint */
    DataLength = GetEPRxCount(bEpAddr & 0x7F);

    /* Use the memory interface function to write to the selected endpoint */
    HwUsbPMAToUserBufferCopy(pBufferPointer, GetEPRxAddr(bEpAddr & 0x7F), DataLength);


    /* Return the number of received data */
    return DataLength;
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

