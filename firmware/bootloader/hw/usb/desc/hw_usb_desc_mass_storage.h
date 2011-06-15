/*!
 * \file hw_usb_desc_mass_storage.h
 *
 * \brief 
 *
 *
 * \date Jun 13, 2011
 * \author Dan Riedler
 *
 */
#ifndef _HW_USB_DESC_MASS_STORAGE_H_
#define _HW_USB_DESC_MASS_STORAGE_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "bootloader.h"
#include "usb/defs/usb_defs.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define IFC_NUM 1
#define MASS_STORAGE_MAX_PACKET_SIZE	  64

#define MASS_SIZ_DEVICE_DESC              18
#define MASS_SIZ_CONFIG_DESC              32

#define MASS_SIZ_STRING_LANGID            4
#define MASS_SIZ_STRING_VENDOR            38
#define MASS_SIZ_STRING_PRODUCT           38
#define MASS_SIZ_STRING_SERIAL            26
#define MASS_SIZ_STRING_INTERFACE         16
/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
extern const uint8 MASS_DeviceDescriptor[MASS_SIZ_DEVICE_DESC];
extern const uint8 MASS_ConfigDescriptor[MASS_SIZ_CONFIG_DESC];

extern const uint8 MASS_StringLangID[MASS_SIZ_STRING_LANGID];
extern const uint8 MASS_StringVendor[MASS_SIZ_STRING_VENDOR];
extern const uint8 MASS_StringProduct[MASS_SIZ_STRING_PRODUCT];
extern uint8 MASS_StringSerial[MASS_SIZ_STRING_SERIAL];
extern const uint8 MASS_StringInterface[MASS_SIZ_STRING_INTERFACE];



#endif /* _HW_USB_DESC_MASS_STORAGE_H_ */
