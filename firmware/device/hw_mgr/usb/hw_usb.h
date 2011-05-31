/*!
 * \file hw_usb.h
 *
 * \brief 
 *
 *
 * \date Mar 16, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_H_
#define _HW_USB_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "hw_mgr.h"
#include "hw_usb_result.h"
#include "hw_usb_types.h"
#include "hw_mgr_types.h"
#include "hw_usb_types.h"
#include "hw_usb_conf.h"
#include "hw_usb_init.h"


#include "core/hw_usb_core.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define HW_USB_ISSUE_STATE_CHANGE_CALLBACK(_state)								\
{																				\
	if(HwUsbStateChangeCallback)												\
		HwUsbStateChangeCallback(_state);										\
}

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PUBLIC HwModuleInitPrototype HW_USB_Init;

PUBLIC HwModulePowerUpPrototype HW_USB_PowerUp;

PUBLIC HwModulePowerDownPrototype HW_USB_PowerDown;

PUBLIC uint32 HW_USB_SIL_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize);
PUBLIC uint32 HW_USB_SIL_Read(uint8 bEpAddr, uint8* pBufferPointer);

PUBLIC Result HW_USB_RegisterStateChangeCallback(pHW_USB_StateChangeCallback Callback);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern pHW_USB_StateChangeCallback HwUsbStateChangeCallback;

#endif /* HW_USB_H_ */
