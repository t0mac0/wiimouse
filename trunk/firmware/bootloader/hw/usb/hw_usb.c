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
#include "usb/ep/hw_usb_ep_vir_com.h"


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


/*******************************************************************************/
PUBLIC void HW_USB_RegisterVirComReadCallback(pHW_USB_ReadVirComCallBack Callback)
{
    HwUsbVirComCallback = Callback;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

