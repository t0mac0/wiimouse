/*!
 * \file usb_defs.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _USB_DEFS_H_
#define _USB_DEFS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system_types.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define WBVAL(x) (x & 0xFF),((x >> 8) & 0xFF)


/* bmRequestType.Dir */
#define REQUEST_HOST_TO_DEVICE     0
#define REQUEST_DEVICE_TO_HOST     1

/* bmRequestType.Type */
#define REQUEST_STANDARD           0
#define REQUEST_CLASS              1
#define REQUEST_VENDOR             2
#define REQUEST_RESERVED           3

/* bmRequestType.Recipient */
#define REQUEST_TO_DEVICE          0
#define REQUEST_TO_INTERFACE       1
#define REQUEST_TO_ENDPOINT        2
#define REQUEST_TO_OTHER           3



/* USB Standard Request Codes */
#define USB_REQUEST_GET_STATUS                 0
#define USB_REQUEST_CLEAR_FEATURE              1
#define USB_REQUEST_SET_FEATURE                3
#define USB_REQUEST_SET_ADDRESS                5
#define USB_REQUEST_GET_DESCRIPTOR             6
#define USB_REQUEST_SET_DESCRIPTOR             7
#define USB_REQUEST_GET_CONFIGURATION          8
#define USB_REQUEST_SET_CONFIGURATION          9
#define USB_REQUEST_GET_INTERFACE              10
#define USB_REQUEST_SET_INTERFACE              11
#define USB_REQUEST_SYNC_FRAME                 12

/* USB GET_STATUS Bit Values */
#define USB_GETSTATUS_SELF_POWERED             0x01
#define USB_GETSTATUS_REMOTE_WAKEUP            0x02
#define USB_GETSTATUS_ENDPOINT_STALL           0x01

/* USB Standard Feature selectors */
#define USB_FEATURE_ENDPOINT_STALL             0
#define USB_FEATURE_REMOTE_WAKEUP              1



/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE             1
#define USB_CONFIGURATION_DESCRIPTOR_TYPE      2
#define USB_STRING_DESCRIPTOR_TYPE             3
#define USB_INTERFACE_DESCRIPTOR_TYPE          4
#define USB_ENDPOINT_DESCRIPTOR_TYPE           5
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE   6
#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE 7
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE    8
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE 0x0B

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED              0x00
//#define USB_DEVICE_CLASS_AUDIO                 0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS        0x02
//#define USB_DEVICE_CLASS_HUMAN_INTERFACE       0x03
//#define USB_DEVICE_CLASS_MONITOR               0x04
//#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE    0x05
//#define USB_DEVICE_CLASS_POWER                 0x06
//#define USB_DEVICE_CLASS_PRINTER               0x07
//#define USB_DEVICE_CLASS_STORAGE               0x08
#define USB_DEVICE_CLASS_HUB                   0x09
#define USB_DEVICE_CLASS_DIAGNOSTIC            0xDC
#define USB_DEVICE_CLASS_MISC                  0xEF
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC       0xFF

/* USB Interface Classes */
#define USB_INTERFACE_CLASS_AUDIO              0x01
#define USB_INTERFACE_CLASS_COMMUNICATIONS     0x02
#define USB_INTERFACE_CLASS_HUMAN_INTERFACE    0x03
#define USB_INTERFACE_CLASS_MONITOR            0x04
#define USB_INTERFACE_CLASS_PHYSICAL_INTERFACE 0x05
#define USB_INTERFACE_CLASS_IMAGE              0x06
#define USB_INTERFACE_CLASS_PRINTER            0x07
#define USB_INTERFACE_CLASS_STORAGE            0x08
#define USB_INTERFACE_CLASS_CDC_DATA           0x0A
#define USB_INTERFACE_CLASS_SMART_CARD         0x0B
#define USB_INTERFACE_CLASS_SECURITY           0x0D
#define USB_INTERFACE_CLASS_VIDEO              0x0E
#define USB_INTERFACE_CLASS_HEALTHCARE         0x0F
#define USB_INTERFACE_CLASS_DIAGNOSTIC         0xDC
#define USB_INTERFACE_CLASS_WIRELESS           0xE0
#define USB_INTERFACE_CLASS_MISC               0xEF
#define USB_INTERFACE_CLASS_APP_SPECIFIC       0xFE
#define USB_INTERFACE_CLASS_VENDOR_SPECIFIC    0xFF

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_POWERED_MASK                0xC0
#define USB_CONFIG_BUS_POWERED                 0x80
#define USB_CONFIG_SELF_POWERED                0x40
#define USB_CONFIG_REMOTE_WAKEUP               0x20

/* bMaxPower in Configuration Descriptor */
#define USB_CONFIG_POWER_MA(mA)                ((mA)/2)

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK            0x80
#define USB_ENDPOINT_OUT(addr)                 ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)                  ((addr) | 0x80)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK                 0x03
#define USB_ENDPOINT_TYPE_CONTROL              0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS          0x01
#define USB_ENDPOINT_TYPE_BULK                 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT            0x03
#define USB_ENDPOINT_SYNC_MASK                 0x0C
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION   0x00
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS         0x04
#define USB_ENDPOINT_SYNC_ADAPTIVE             0x08
#define USB_ENDPOINT_SYNC_SYNCHRONOUS          0x0C
#define USB_ENDPOINT_USAGE_MASK                0x30
#define USB_ENDPOINT_USAGE_DATA                0x00
#define USB_ENDPOINT_USAGE_FEEDBACK            0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK   0x20
#define USB_ENDPOINT_USAGE_RESERVED            0x30


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

#pragma pack(push, 1)

typedef union {
    uint16 W;
    struct {
        uint8 L;
        uint8 H;
    } WB;
} WORD_BYTE;


/* bmRequestType Definition */
typedef union _USB_REQUEST_TYPE
{
    struct _BM
    {
        uint8 Recipient : 5;
        uint8 Type      : 2;
        uint8 Dir       : 1;
    } BM;
    uint8 B;
} USB_REQUEST_TYPE;

/* USB Default Control Pipe Setup Packet */
typedef struct _USB_SETUP_PACKET {
    USB_REQUEST_TYPE bmRequestType;
    uint8         bRequest;
    WORD_BYTE    wValue;
    WORD_BYTE    wIndex;
    uint16         wLength;
} USB_SETUP_PACKET;

/* USB Standard Device Descriptor */
typedef struct _USB_DEVICE_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
    uint16  bcdUSB;
    uint8  bDeviceClass;
    uint8  bDeviceSubClass;
    uint8  bDeviceProtocol;
    uint8  bMaxPacketSize0;
    uint16  idVendor;
    uint16  idProduct;
    uint16  bcdDevice;
    uint8  iManufacturer;
    uint8  iProduct;
    uint8  iSerialNumber;
    uint8  bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;
#define USB_DEVICE_DESCRIPTOR_SIZE sizeof(USB_DEVICE_DESCRIPTOR)

/* USB 2.0 Device Qualifier Descriptor */
typedef struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
    uint16  bcdUSB;
    uint8  bDeviceClass;
    uint8  bDeviceSubClass;
    uint8  bDeviceProtocol;
    uint8  bMaxPacketSize0;
    uint8  bNumConfigurations;
    uint8  bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR;
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_SIZE sizeof(USB_DEVICE_QUALIFIER_DESCRIPTOR)

/* USB Standard Configuration Descriptor */
typedef struct _USB_CONFIGURATION_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
    uint16  wTotalLength;
    uint8  bNumInterfaces;
    uint8  bConfigurationValue;
    uint8  iConfiguration;
    uint8  bmAttributes;
    uint8  MaxPower;
} USB_CONFIGURATION_DESCRIPTOR;
#define USB_CONFIGURATION_DESCRIPTOR_SIZE sizeof(USB_CONFIGURATION_DESCRIPTOR)

/* USB Standard Interface Descriptor */
typedef struct _USB_INTERFACE_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
    uint8  bInterfaceNumber;
    uint8  bAlternateSetting;
    uint8  bNumEndpoints;
    uint8  bInterfaceClass;
    uint8  bInterfaceSubClass;
    uint8  bInterfaceProtocol;
    uint8  iInterface;
} USB_INTERFACE_DESCRIPTOR;
#define USB_INTERFACE_DESCRIPTOR_SIZE sizeof(USB_INTERFACE_DESCRIPTOR)

/* USB Standard Endpoint Descriptor */
typedef struct _USB_ENDPOINT_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
    uint8  bEndpointAddress;
    uint8  bmAttributes;
    uint16  wMaxPacketSize;
    uint8  bInterval;
} USB_ENDPOINT_DESCRIPTOR;
#define USB_ENDPOINT_DESCRIPTOR_SIZE sizeof(USB_ENDPOINT_DESCRIPTOR)

/* USB String Descriptor */
typedef struct _USB_STRING_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
    uint16  bString/*[]*/;
} USB_STRING_DESCRIPTOR;

/* USB Common Descriptor */
typedef struct _USB_COMMON_DESCRIPTOR {
    uint8  bLength;
    uint8  bDescriptorType;
} USB_COMMON_DESCRIPTOR;

/* Interface Association Descriptor */
typedef struct _INTERFACE_ASSOCIATION_DESCRIPTOR {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bFirstInterface;
    uint8 bInterfaceCount;
    uint8 bFunctionClass;
    uint8 bFunctionSubClass;
    uint8 bFunctionProtocol;
    uint8 iFunction;
} INTERFACE_ASSOCIATION_DESCRIPTOR;
#define INTERFACE_ASSOCIATION_DESCRIPTOR_SIZE sizeof(INTERFACE_ASSOCIATION_DESCRIPTOR)

#pragma pack(pop)

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* USB_DEFS_H_ */
