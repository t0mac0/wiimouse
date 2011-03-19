/*!
 * \file composite_usb_hid_mouse_prop.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPOSITE_USB_HID_MOUSE_PROP_H_
#define _COMPOSITE_USB_HID_MOUSE_PROP_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "composite_usb.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;



/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
USB_RESULT CustomHID_SetProtocol(void);
uint8 *CustomHID_GetProtocolValue(uint16 Length);
USB_RESULT CustomHID_SetProtocol(void);
uint8 *CustomHID_GetReportDescriptor(uint16 Length);
uint8 *CustomHID_GetHIDDescriptor(uint16 Length);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* COMPOSITE_USB_HID_MOUSE_PROP_H_ */
