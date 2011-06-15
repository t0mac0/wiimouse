/*!
 * \file hw_usb.h
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_H_
#define _HW_USB_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "bootloader.h"
#include "hw_conf.h"
#include "hw_usb_platform.h"
#include "hw_usb_types.h"
#include "hw/usb/desc/hw_usb_desc_mass_storage.h"
#include "hw/usb/bot/hw_usb_bot.h"


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
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PUBLIC void HW_USB_Init(void);
PUBLIC void HW_USB_RegisterMassStorageReadCallback(pHW_USB_MassStorageCallBack Callback);
PUBLIC void HW_USB_RegisterMassStorageWriteCallback(pHW_USB_MassStorageCallBack Callback);

PUBLIC uint32 HW_USB_Read(uint8 bEpAddr, uint8* pBufferPointer, bool SetValid);
PUBLIC uint32 HW_USB_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize, bool SetValid);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/



#endif /* HW_USB_H_ */
