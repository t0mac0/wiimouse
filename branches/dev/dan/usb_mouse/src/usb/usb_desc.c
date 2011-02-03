/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_desc.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Descriptors for Custom HID Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_conf.h"
//
///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
///* Extern variables ----------------------------------------------------------*/
///* Private function prototypes -----------------------------------------------*/
///* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8 CustomHID_DeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE] =
{
		USB_DEVICE_DESCRIPTOR_SIZE,        /* bLength */
		USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
		WBVAL(0x0200), /* 2.0 */           /* bcdUSB */
		0x00,                              /* bDeviceClass */
		0x00,                              /* bDeviceSubClass */
		0x00,                              /* bDeviceProtocol */
		0x40,                              /* bMaxPacketSize0 (64 bytes)_ */
		WBVAL(0x046D),    					/* idVendor */
		WBVAL(0xC52B),   					/* idProduct */
		WBVAL(0x0200),        				/* 2.00 */   /* bcdDevice */
		1,									/*Index of string descriptor describing manufacturer */
		2,									/*Index of string descriptor describing product*/
		3, 									/*Index of string descriptor describing the device serial number */
		0x01                               /* bNumConfigurations */
}; /* CustomHID_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8 CustomHID_ConfigDescriptor[WII_MOUSE_CONFIGURATION_DESCRIPTOR_SIZE] =
{
		USB_CONFIGURATION_DESCRIPTOR_SIZE, /* bLength */
		USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
		WBVAL(WII_MOUSE_CONFIGURATION_DESCRIPTOR_SIZE),   /* wTotalLength */
		1,             				        /* bNumInterfaces */
		1,        							/* bConfigurationValue */
		0,									/* iConfiguration: Index of string descriptor describing the configuration*/
		USB_CONFIG_BUS_POWERED, /*|*/       /* bmAttributes */
		/*USB_CONFIG_REMOTE_WAKEUP*/
		USB_CONFIG_POWER_MA(100),          /* bMaxPower */

/********************************************************************************
Interface 0, Generic HID Mouse
*********************************************************************************/

		USB_INTERFACE_DESCRIPTOR_SIZE,     /* bLength */
		USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
		0,   							   /* bInterfaceNumber */
		0x00,                              /* bAlternateSetting */
		1,                                 /* bNumEndpoints */
		USB_DEVICE_CLASS_HUMAN_INTERFACE,  /* bInterfaceClass */
		HID_SUBCLASS_BOOT,                 /* bInterfaceSubClass */
		HID_PROTOCOL_MOUSE,                /* bInterfaceProtocol */
		0,									/* iInterface: Index of string descriptor */

/********************************************************************************
HID Class Descriptor
*********************************************************************************/
		HID_DESCRIPTOR_SIZE,                /* bLength */
		HID_HID_DESCRIPTOR_TYPE,           /* bDescriptorType */
		WBVAL(0x0110), /* 1.10 */          /* bcdHID */
		0x00,                              /* bCountryCode */
		0x01,                              /* bNumDescriptors */
		HID_REPORT_DESCRIPTOR_TYPE,        /* bDescriptorType */
		WBVAL(HID_MOUSE_REPORT_DESCRIPTOR_SIZE),        /* wDescriptorLength */

/********************************************************************************
Endpoint 1, HID Interrupt In
*********************************************************************************/

		USB_ENDPOINT_DESCRIPTOR_SIZE,            /* bLength */
		USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
		USB_ENDPOINT_IN(1), 				/* bEndpointAddress */
		USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
		WBVAL(HID_MOUSE_REPORT_SIZE),  /* wMaxPacketSize */
		0x20,                  			 /* bInterval  (32 ms) */
}; /* CustomHID_ConfigDescriptor */


/********************************************************************************
HID Report Descriptor for a 3 Button Mouse with RELATIVE positioning

Name:  report_desc_mouse_rel

Description:
HID Report Descriptor for a 3 button mouse.

Byte                Bits                  Description
0                   0                     Left Button
					1                     Right Button
					2                     Middle Button
					3..7                  Unused
1                   0..7                  X Displacement (-127..127)
2                   0..7                  Y Displacement (-127..127)


 *********************************************************************************/
const uint8 CustomHID_ReportDescriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE] =
{
		HID_UsagePage(HID_USAGE_PAGE_GENERIC),
		HID_Usage(HID_USAGE_GENERIC_MOUSE),
		HID_Collection(HID_Application),
		HID_Usage(HID_USAGE_GENERIC_POINTER),
		HID_Collection(HID_Physical),
		HID_ReportCount(3),
		HID_ReportSize(1),
		HID_UsagePage(HID_USAGE_PAGE_BUTTON),
		HID_UsageMin(1),
		HID_UsageMax(3),
		HID_LogicalMin(0),
		HID_LogicalMax(1),
		HID_Input(HID_Data | HID_Variable | HID_Absolute),
		HID_ReportCount(1),
		HID_ReportSize(5),
		HID_Input(HID_Constant),
		HID_ReportSize(8),
		HID_ReportCount(2),
		HID_UsagePage(HID_USAGE_PAGE_GENERIC),
		HID_Usage(HID_USAGE_GENERIC_X),
		HID_Usage(HID_USAGE_GENERIC_Y),
		HID_LogicalMin(HID_MOUSE_REL_MIN_XY),		// -127
		HID_LogicalMax(HID_MOUSE_REL_MAX_XY),
		HID_Input(HID_Data | HID_Variable | HID_Relative),
		HID_EndCollection,
		HID_EndCollection,
}; /* CustomHID_ReportDescriptor */



/* USB String Descriptors (optional) */
const uint8 CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
  {
    CUSTOMHID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8 CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
  {
    CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8 CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
  {
    CUSTOMHID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'C', 0,
    'u', 0, 's', 0, 't', 0, 'm', 0, ' ', 0, 'H', 0, 'I', 0,
    'D', 0
  };
uint8 CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
  {
    CUSTOMHID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0,'3', 0,'2', 0, '1', 0, '0', 0
  };

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/


