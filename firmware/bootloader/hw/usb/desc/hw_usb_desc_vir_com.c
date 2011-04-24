/*!
 * \file hw_usb_desc_vir_com.c
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
#include "hw_usb_desc_vir_com.h"


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



/* USB Standard Device Descriptor */
const uint8 Virtual_Com_Port_DeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE] =
{
        USB_DEVICE_DESCRIPTOR_SIZE,        /* bLength */
        USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
        WBVAL(0x0110), /* 1.1 */           /* bcdUSB */
        USB_DEVICE_CLASS_COMMUNICATIONS,   /* bDeviceClass */
        0x00,                              /* bDeviceSubClass: common */
        0x00,                              /* bDeviceProtocol: IAD */
        0x40,                              /* bMaxPacketSize0 (64 bytes) */
        WBVAL(0xF46D),                     /* idVendor */
        WBVAL(0xF52B),                     /* idProduct */
        WBVAL(0x0000),                      /* 0.00 */   /* bcdDevice */
        1,                                  /*Index of string descriptor describing manufacturer */
        2,                                  /*Index of string descriptor describing product*/
        3,                                  /*Index of string descriptor describing the device serial number */
        0x01                               /* bNumConfigurations */
};


const uint8 Virtual_Com_Port_ConfigDescriptor[DEVICE_CONFIGURATION_DESCRIPTOR_SIZE] =
{
        USB_CONFIGURATION_DESCRIPTOR_SIZE, /* bLength */
        USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
        WBVAL(DEVICE_CONFIGURATION_DESCRIPTOR_SIZE),   /* wTotalLength */
        IFC_NUM,                            /* bNumInterfaces */
        1,                                  /* bConfigurationValue */
        0,                                  /* iConfiguration: Index of string descriptor describing the configuration*/
        USB_CONFIG_BUS_POWERED, /*|*/       /* bmAttributes */
        /*USB_CONFIG_REMOTE_WAKEUP*/
        USB_CONFIG_POWER_MA(100),          /* bMaxPower */

/********************************************************************************
 CDC Interface Association Descriptor
*********************************************************************************/
        INTERFACE_ASSOCIATION_DESCRIPTOR_SIZE,      // bLength
        USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,  // bDescriptorType = 11
        CDC_IFC_NUM,                                // bFirstInterface
        0x02,                                       // bInterfaceCount
        USB_INTERFACE_CLASS_COMMUNICATIONS,         // bFunctionClass (Communication Class)
        CDC_SUBCLASS_ACM,                           // bFunctionSubClass (Abstract Control Model)
        CDC_PROTOCOL_AT,                            // bFunctionProcotol (V.25ter, Common AT commands)
        0x00,                                       // iInterface

/********************************************************************************
 Interface 0, Communications Device Control
*********************************************************************************/
        USB_INTERFACE_DESCRIPTOR_SIZE,      /* bLength */
        USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
        CDC_IFC_NUM,                        /* bInterfaceNumber */
        0x00,                               /* bAlternateSetting */
        1,                                  /* bNumEndpoints */
        USB_INTERFACE_CLASS_COMMUNICATIONS, /* bInterfaceClass: Communication Interface Class */
        CDC_SUBCLASS_ACM,               /* bInterfaceSubClass: Abstract Control Model */
        CDC_PROTOCOL_AT,                    /* bInterfaceProtocol: Common AT commands */
        0,                                  /* iInterface: Index of string descriptor */

/********************************************************************************
 CDC Header Functional Descriptor
*********************************************************************************/
        CDC_HEADER_DESCRIPTOR_SIZE,         /* bLength: Endpoint Descriptor size */
        CDC_CS_INTERFACE_DESCRIPTOR_TYPE,   /* bDescriptorType: CS_INTERFACE */
        CDC_HEADER_FUNC_DESCRIPTOR_SUBTYPE, /* bDescriptorSubtype: Header Func Desc */
        WBVAL(0x0110),                      /* bcdCDC: spec release number: 1.10 */

/********************************************************************************
 CDC Call Management Functional Descriptor
*********************************************************************************/
        CDC_CM_DESCRIPTOR_SIZE,             /* bLength */
        CDC_CS_INTERFACE_DESCRIPTOR_TYPE,   /* bDescriptorType: CS_INTERFACE */
        CDC_CM_FUNC_DESCRIPTOR_SUBTYPE,     /* bDescriptorSubtype: Call Management Func Desc */
        0x00,                               /* bmCapabilities: D0+D1 */
        CDC_DATA_IFC_NUM,                   /* bDataInterface: 1 */

/********************************************************************************
 CDC ACM Functional Descriptor
*********************************************************************************/
        CDC_ACM_DESCRIPTOR_SIZE,            /* bFunctionLength */
        CDC_CS_INTERFACE_DESCRIPTOR_TYPE,   /* bDescriptorType: CS_INTERFACE */
        CDC_ACM_FUNC_DESCRIPTOR_SUBTYPE,    /* bDescriptorSubtype: Abstract Control Management desc */
        0x02,                               /* bmCapabilities */

/********************************************************************************
 CDC Union Functional Descriptor
*********************************************************************************/
        CDC_UNION_IFC_DESCRIPTOR_SIZE,      /* bFunctionLength */
        CDC_CS_INTERFACE_DESCRIPTOR_TYPE,   /* bDescriptorType: CS_INTERFACE */
        CDC_UNION_IFC_FUNC_DESCRIPTOR_SUBTYPE, /* bDescriptorType: CS_INTERFACE */
        CDC_IFC_NUM,                        /* bMasterInterface: Communication class interface */
        CDC_DATA_IFC_NUM,                   /* bSlaveInterface0: Data Class Interface */

/********************************************************************************
 Endpoint 2, CDC Interrupt In
*********************************************************************************/
        USB_ENDPOINT_DESCRIPTOR_SIZE,       /* bLength */
        USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
        USB_ENDPOINT_IN(2),                 /* bEndpointAddress */
        USB_ENDPOINT_TYPE_INTERRUPT,        /* bmAttributes */
        WBVAL(VIRTUAL_COM_PORT_INT_SIZE),   /* wMaxPacketSize */
        0x1,                                /* bInterval  */

/********************************************************************************
 Interface 2, CDC Data Interface
*********************************************************************************/
        USB_INTERFACE_DESCRIPTOR_SIZE,      /* bLength */
        USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
        CDC_DATA_IFC_NUM,                   /* bInterfaceNumber */
        0x00,                               /* bAlternateSetting */
        2,                                  /* bNumEndpoints */
        USB_INTERFACE_CLASS_CDC_DATA,       /* bInterfaceClass: CDC-Data */
        0x00,                               /* bInterfaceSubClass:  */
        0x00,                               /* bInterfaceProtocol:  */
        0,                                  /* iInterface: Index of string descriptor */

/********************************************************************************
 Endpoint 3, CDC-Data Bulk Out
*********************************************************************************/
        USB_ENDPOINT_DESCRIPTOR_SIZE,       /* bLength */
        USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
        USB_ENDPOINT_OUT(3),                /* bEndpointAddress */
        USB_ENDPOINT_TYPE_BULK,             /* bmAttributes */
        WBVAL(VIRTUAL_COM_PORT_DATA_SIZE),  /* wMaxPacketSize */
        0x00,                               /* bInterval: Ignore bulk transfer  */

/********************************************************************************
 Endpoint 4, CDC-Data Bulk In
*********************************************************************************/
        USB_ENDPOINT_DESCRIPTOR_SIZE,       /* bLength */
        USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
        USB_ENDPOINT_IN(1),                 /* bEndpointAddress */
        USB_ENDPOINT_TYPE_BULK,             /* bmAttributes */
        WBVAL(VIRTUAL_COM_PORT_DATA_SIZE),  /* wMaxPacketSize */
        0x00,                               /* bInterval: Ignore bulk transfer  */
};




/* USB String Descriptors */
const uint8 Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID] =
{
        VIRTUAL_COM_PORT_SIZ_STRING_LANGID,
        USB_STRING_DESCRIPTOR_TYPE,
        0x09,
        0x04 /* LangID = 0x0409: U.S. English */
};

const uint8 Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR] =
{
        VIRTUAL_COM_PORT_SIZ_STRING_VENDOR,     /* Size of Vendor string */
        USB_STRING_DESCRIPTOR_TYPE,             /* bDescriptorType*/
        /* Manufacturer: "STMicroelectronics" */
        'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
        'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
        'c', 0, 's', 0
};

const uint8 Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT] =
{
        VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT,          /* bLength */
        USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
        /* Product name: "STM32 Virtual COM Port" */
        'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'V', 0, 'i', 0,
        'r', 0, 't', 0, 'u', 0, 'a', 0, 'l', 0, ' ', 0, 'C', 0, 'O', 0,
        'M', 0, ' ', 0, 'P', 0, 'o', 0, 'r', 0, 't', 0, ' ', 0, ' ', 0
};

uint8 Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL] =
{
        VIRTUAL_COM_PORT_SIZ_STRING_SERIAL,           /* bLength */
        USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
        'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '1', 0, '0', 0
};


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

