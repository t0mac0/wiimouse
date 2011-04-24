/*!
 * \file usb_cdc_defs.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _USB_CDC_DEFS_H_
#define _USB_CDC_DEFS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system_types.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
/* CDC SubClass Codes */
#define CDC_SUBCLASS_RESERVED           0x00
#define CDC_SUBCLASS_DLM                0x01
#define CDC_SUBCLASS_ACM                0x02
#define CDC_SUBCLASS_TCM                0x03
#define CDC_SUBCLASS_MCCM               0x04
#define CDC_SUBCLASS_CAPICM             0x05
#define CDC_SUBCLASS_ENCM               0x06
#define CDC_SUBCLASS_ATM                0x07

/* CDC Protocol Codes */
#define CDC_PROTOCOL_NONE               0x00
#define CDC_PROTOCOL_AT                 0x01
#define CDC_PROTOCOL_VENDER_SPECIFI     0xFF

/* CDC Descriptor Types */
#define CDC_CS_INTERFACE_DESCRIPTOR_TYPE 0x24
#define CDC_CS_ENDPOINT_DESCRIPTOR_TYPE 0x25

/* CDC Functional Descriptor SubTypes */
#define CDC_HEADER_FUNC_DESCRIPTOR_SUBTYPE          0x00
#define CDC_CM_FUNC_DESCRIPTOR_SUBTYPE              0x01
#define CDC_ACM_FUNC_DESCRIPTOR_SUBTYPE             0x02
#define CDC_DLM_FUNC_DESCRIPTOR_SUBTYPE             0x03
#define CDC_TR_FUNC_DESCRIPTOR_SUBTYPE              0x04
#define CDC_TCLSRC_FUNC_DESCRIPTOR_SUBTYPE          0x05
#define CDC_UNION_IFC_FUNC_DESCRIPTOR_SUBTYPE       0x06
#define CDC_CSL_FUNC_DESCRIPTOR_SUBTYPE             0x07
#define CDC_TOM_FUNC_DESCRIPTOR_SUBTYPE             0x08
#define CDC_USBT_FUNC_DESCRIPTOR_SUBTYPE            0x09
#define CDC_NCT_FUNC_DESCRIPTOR_SUBTYPE             0x0A
#define CDC_PU_FUNC_DESCRIPTOR_SUBTYPE              0x0B
#define CDC_EU_FUNC_DESCRIPTOR_SUBTYPE              0x0C
#define CDC_MCM_FUNC_DESCRIPTOR_SUBTYPE             0x0D
#define CDC_CAPICM_FUNC_DESCRIPTOR_SUBTYPE          0x0E
#define CDC_EN_FUNC_DESCRIPTOR_SUBTYPE              0x0F
#define CDC_ATMN_FUNC_DESCRIPTOR_SUBTYPE            0x10


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
/* CDC Header Descriptor  */
#pragma pack(push, 1)
typedef struct _CDC_HEADER_DESCRIPTOR {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bDescriptorSubType;
    uint16 bcdCDC;
} CDC_HEADER_DESCRIPTOR;
#define CDC_HEADER_DESCRIPTOR_SIZE sizeof(CDC_HEADER_DESCRIPTOR)
#pragma pack(pop)

/* CDC Call Management Descriptor  */
#pragma pack(push, 1)
typedef struct _CDC_CM_DESCRIPTOR {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bDescriptorSubType;
    uint8 bmCapabilities;
    uint8 bDataInterface;
} CDC_CM_DESCRIPTOR;
#define CDC_CM_DESCRIPTOR_SIZE sizeof(CDC_CM_DESCRIPTOR)
#pragma pack(pop)

/* CDC Abstract Control Management Descriptor  */
#pragma pack(push, 1)
typedef struct _CDC_ACM_DESCRIPTOR {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bDescriptorSubType;
    uint8 bmCapabilities;
} CDC_ACM_DESCRIPTOR;
#define CDC_ACM_DESCRIPTOR_SIZE sizeof(CDC_ACM_DESCRIPTOR)
#pragma pack(pop)


/* CDC Union Interface Descriptor  */
#pragma pack(push, 1)
typedef struct _CDC_UNION_IFC_DESCRIPTOR {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bDescriptorSubType;
    uint8 bMasterInterface;
    uint8 bSlaveInterface;
} CDC_UNION_IFC_DESCRIPTOR;
#define CDC_UNION_IFC_DESCRIPTOR_SIZE sizeof(CDC_UNION_IFC_DESCRIPTOR)
#pragma pack(pop)

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* USB_CDC_DEFS_H_ */
