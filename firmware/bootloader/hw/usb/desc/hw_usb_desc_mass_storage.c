/*!
 * \file hw_usb_desc_mass_storage.c
 *
 * \brief 
 *
 *
 * \date Jun 13, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <hw_usb_platform.h>

#include "hw_usb_desc_mass_storage.h"


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
const uint8 MASS_DeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE] =
{
        USB_DEVICE_DESCRIPTOR_SIZE,        /* bLength */
        USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
        WBVAL(0x0200), /* 1.1 */           /* bcdUSB */
        USB_DEVICE_CLASS_RESERVED,         /* bDeviceClass */
        0x00,                              /* bDeviceSubClass: common */
        0x00,                              /* bDeviceProtocol: IAD */
        0x40,                              /* bMaxPacketSize0 (64 bytes) */
        WBVAL(USB_VENDOR_ID),              /* idVendor */
        WBVAL(USB_PRODUCT_ID),             /* idProduct */
        WBVAL(USB_BOOTLOADER_ID),          /* 0.00 */   /* bcdDevice */
        1,                                 /*Index of string descriptor describing manufacturer */
        2,                                 /*Index of string descriptor describing product*/
        3,                                 /*Index of string descriptor describing the device serial number */
        0x01                               /* bNumConfigurations */
};

const uint8 MASS_ConfigDescriptor[MASS_SIZ_CONFIG_DESC] =
{
        USB_CONFIGURATION_DESCRIPTOR_SIZE, 	/* bLength */
        USB_CONFIGURATION_DESCRIPTOR_TYPE, 	/* bDescriptorType */
        WBVAL(MASS_SIZ_CONFIG_DESC),   		/* wTotalLength */
        IFC_NUM,                            /* bNumInterfaces */
        1,                                  /* bConfigurationValue */
        0,                                  /* iConfiguration: Index of string descriptor describing the configuration*/
        USB_CONFIG_BUS_POWERED, /*|*/       /* bmAttributes */
        /*USB_CONFIG_REMOTE_WAKEUP*/
        USB_CONFIG_POWER_MA(100),          	/* bMaxPower */

/********************************************************************************
  Mass Storage Descriptor
*********************************************************************************/
        USB_INTERFACE_DESCRIPTOR_SIZE,      /* bLength */
        USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
        0,                        			/* bInterfaceNumber */
        0x00,                               /* bAlternateSetting */
        EP_NUM,                     		/* bNumEndpoints */
        USB_INTERFACE_CLASS_STORAGE, 		/* bInterfaceClass: Storage Interface Class */
        0x06,               				/* bInterfaceSubClass: SCSI Transparent */
        0x50,                    			/* bInterfaceProtocol:  */
        4,                                  /* iInterface: Index of string descriptor */

/********************************************************************************
 Endpoint 1, Mass Storage Bulk In
*********************************************************************************/
        USB_ENDPOINT_DESCRIPTOR_SIZE,       /* bLength */
        USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
        USB_ENDPOINT_IN(MASS_STORAGE_READ_EP_NUM),  /* bEndpointAddress */
        USB_ENDPOINT_TYPE_BULK,        		/* bmAttributes */
        WBVAL(MASS_STORAGE_MAX_PACKET_SIZE),/* wMaxPacketSize */
        0x0,                                /* bInterval  */

/********************************************************************************
 Endpoint 2, Mass Storage Bulk Out
*********************************************************************************/
        USB_ENDPOINT_DESCRIPTOR_SIZE,       /* bLength */
        USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
        USB_ENDPOINT_OUT(MASS_STORAGE_WRITE_EP_NUM),    /* bEndpointAddress */
        USB_ENDPOINT_TYPE_BULK,             /* bmAttributes */
        WBVAL(MASS_STORAGE_MAX_PACKET_SIZE), /* wMaxPacketSize */
        0x00,                               /* bInterval: Ignore bulk transfer  */

};




/* USB String Descriptors */
const uint8 MASS_StringLangID[MASS_SIZ_STRING_LANGID] =
{
		MASS_SIZ_STRING_LANGID,
        USB_STRING_DESCRIPTOR_TYPE,
        WBVAL(0x0409) /* LangID = 0x0409: U.S. English */
};

const uint8 MASS_StringVendor[MASS_SIZ_STRING_VENDOR] =
{
		MASS_SIZ_STRING_VENDOR,     /* Size of Vendor string */
        USB_STRING_DESCRIPTOR_TYPE,             /* bDescriptorType*/
        /* Manufacturer: "Reed Electronics" */
        'R', 0, 'e', 0, 'e', 0, 'd', 0, ' ', 0,
        'E', 0, 'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0, 'c', 0, 's', 0
};

const uint8 MASS_StringProduct[MASS_SIZ_STRING_PRODUCT]=
{
		MASS_SIZ_STRING_PRODUCT,          /* bLength */
        USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
        /* Product name: "WiiMouse Updater" */
        'W', 0, 'i', 0, 'i', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0, 'e', 0, ' ', 0,
        'U', 0, 'p', 0, 'd', 0, 'a', 0, 't', 0, 'e', 0, 'r', 0
};

uint8 MASS_StringSerial[MASS_SIZ_STRING_SERIAL]=
{
		MASS_SIZ_STRING_SERIAL,           /* bLength */
        USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
        'R', 0, 'e', 0, 'e', 0, 'd', 0, '2', 0, '0', 0, '1', 0, '1', 0
};

const uint8 MASS_StringInterface[MASS_SIZ_STRING_INTERFACE] =
  {
    MASS_SIZ_STRING_INTERFACE,
    0x03,
    /* Interface 0: "ST Mass" */
    'S', 0, 'T', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0, 's', 0
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
