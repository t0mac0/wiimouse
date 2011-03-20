/*!
 * \file composite_usb.h
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPOSITE_USB_H_
#define _COMPOSITE_USB_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "comps.h"
#include "composite_usb_result.h"
#include "composite_usb_types.h"
#include "composite_usb_conf.h"
#include "usb/hw_usb.h"
#include "usb/defs/usb_hid_mouse_defs.h"


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
PUBLIC ModuleInitPrototype COMPOSITE_USB_Init;

PUBLIC ModulePowerUpPrototype COMPOSITE_USB_PowerUp;

PUBLIC ModulePowerDownPrototype COMPOSITE_USB_PowerDown;

PUBLIC Result COMPOSITE_USB_SendHidMouseReport(HID_MOUSE_REPORT *Report);

PUBLIC Result COMPOSITE_USB_WriteVirCom(void *Buffer, uint32 StartIndex, uint32 EndIndex, uint32 MaxSize);

PUBLIC Result COMPOSITE_USB_RegisterReadVirComCallback(pCOMPOSITE_USB_ReadVirComCallBack ReadVirCom);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* COMPOSITE_USB_H_ */
