/*!
 * \file hw_usb_ep_vir_com.h
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_EP_VIR_COM_H_
#define _HW_USB_EP_VIR_COM_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "usb/hw_usb.h"
#include "hw_usb_ep_conf_stm32f10x.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define VCOMPORT_IN_FRAME_INTERVAL             5

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PROTECTED void HwUsbEpInit( void );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/

PROTECTED extern pHW_USB_ReadVirComCallBack HwUsbVirComCallback;



#endif /* HW_USB_EP_VIR_COM_H_ */
