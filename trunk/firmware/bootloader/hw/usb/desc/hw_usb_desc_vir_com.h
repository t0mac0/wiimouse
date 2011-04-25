/*!
 * \file hw_usb_desc_vir_com.h
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_DESC_VIR_COM_H_
#define _HW_USB_DESC_VIR_COM_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "bootloader.h"
#include "usb/defs/usb_defs.h"
#include "usb/defs/usb_cdc_defs.h"



/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

#define IFC_NUM 2
#define CDC_IFC_NUM 0
#define CDC_DATA_IFC_NUM 1

#define VIRTUAL_COM_PORT_DATA_SIZE              64
#define VIRTUAL_COM_PORT_INT_SIZE               8

//#define VIRTUAL_COM_PORT_SIZ_CONFIG_DESC        67
#define VIRTUAL_COM_PORT_SIZ_STRING_LANGID      4
#define VIRTUAL_COM_PORT_SIZ_STRING_VENDOR      38
#define VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT     50
#define VIRTUAL_COM_PORT_SIZ_STRING_SERIAL      26

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
#pragma pack(push, 1)
typedef struct _DEVICE_CONFIGURATION_DESCRIPTOR{
    USB_CONFIGURATION_DESCRIPTOR    ConfigDesc;

    // Virtual Com Interface
    INTERFACE_ASSOCIATION_DESCRIPTOR CdcIfcAssDesc;
    USB_INTERFACE_DESCRIPTOR        CdcIfcDesc;
    CDC_HEADER_DESCRIPTOR           CdcHeaderDesc;
    CDC_CM_DESCRIPTOR               CdcCmDesc;
    CDC_ACM_DESCRIPTOR              CdcAcmDesc;
    CDC_UNION_IFC_DESCRIPTOR        CdcUnionIfcDesc;
    USB_ENDPOINT_DESCRIPTOR         CdcEpDesc;
    USB_INTERFACE_DESCRIPTOR        CdcDataIfcDesc;
    USB_ENDPOINT_DESCRIPTOR         CdcDataEpOutDesc;
    USB_ENDPOINT_DESCRIPTOR         CdcDataEpInDesc;

} DEVICE_CONFIGURATION_DESCRIPTOR;
#define DEVICE_CONFIGURATION_DESCRIPTOR_SIZE (sizeof(DEVICE_CONFIGURATION_DESCRIPTOR))
#pragma pack(pop)


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
extern const uint8 Virtual_Com_Port_DeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE];
extern const uint8 Virtual_Com_Port_ConfigDescriptor[DEVICE_CONFIGURATION_DESCRIPTOR_SIZE];

extern const uint8 Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID];
extern const uint8 Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR];
extern const uint8 Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT];
extern uint8 Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL];


#endif /* HW_USB_DESC_VIR_COM_H_ */
