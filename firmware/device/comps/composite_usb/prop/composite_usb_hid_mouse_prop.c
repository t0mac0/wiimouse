/*!
 * \file composite_usb_hid_mouse_prop.c
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "composite_usb_hid_mouse_prop.h"
#include "desc/composite_usb_desc.h"
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
uint32 ProtocolValue;



ONE_DESCRIPTOR CustomHID_Report_Descriptor =
{
        (uint8 *)CustomHID_ReportDescriptor,
        HID_MOUSE_REPORT_DESCRIPTOR_SIZE
};


ONE_DESCRIPTOR CustomHID_Hid_Descriptor =
{
        (uint8*)Virtual_Com_Port_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,
        HID_DESCRIPTOR_SIZE
};


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*******************************************************************************
 * Function Name  : CustomHID_GetReportDescriptor.
 * Description    : Gets the HID report descriptor.
 * Input          : Length
 * Output         : None.
 * Return         : The address of the configuration descriptor.
 *******************************************************************************/
uint8 *CustomHID_GetReportDescriptor(uint16 Length)
{
    //printf("getting eport desc: %d\n", Length);
    return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}

/*******************************************************************************
 * Function Name  : CustomHID_GetHIDDescriptor.
 * Description    : Gets the HID descriptor.
 * Input          : Length
 * Output         : None.
 * Return         : The address of the configuration descriptor.
 *******************************************************************************/
uint8 *CustomHID_GetHIDDescriptor(uint16 Length)
{
    //printf("getting hid desc: %d\n", Length);
    return Standard_GetDescriptorData(Length, &CustomHID_Hid_Descriptor);
}


/*******************************************************************************
 * Function Name  : CustomHID_SetProtocol
 * Description    : Joystick Set Protocol request routine.
 * Input          : None.
 * Output         : None.
 * Return         : USB SUCCESS.
 *******************************************************************************/
USB_RESULT CustomHID_SetProtocol(void)
{
    uint8 wValue0 = pInformation->USBwValue0;
    //printf("getting setting hid protocol\n");
    ProtocolValue = wValue0;
    return USB_SUCCESS;
}

/*******************************************************************************
 * Function Name  : CustomHID_GetProtocolValue
 * Description    : get the protocol value
 * Input          : Length.
 * Output         : None.
 * Return         : address of the protcol value.
 *******************************************************************************/
uint8 *CustomHID_GetProtocolValue(uint16 Length)
{
    //printf("getting get protocol val: %d\n", Length);
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 1;
        return NULL;
    }
    else
    {
        return (uint8 *)(&ProtocolValue);
    }
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

