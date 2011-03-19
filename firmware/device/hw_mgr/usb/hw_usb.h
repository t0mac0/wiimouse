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

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_USB_H_ */
