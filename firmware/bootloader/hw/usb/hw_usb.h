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

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef void (HW_USB_ReadVirComCallBack)(uint8 *, uint32);

PUBLIC typedef void (*pHW_USB_ReadVirComCallBack)(uint8 *, uint32);

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PUBLIC bool HW_USB_Init(void);
PUBLIC void HW_USB_RegisterVirComReadCallback(pHW_USB_ReadVirComCallBack Callback);
PUBLIC uint32 HW_USB_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize);
PUBLIC uint32 HW_USB_Read(uint8 bEpAddr, uint8* pBufferPointer);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_USB_H_ */
