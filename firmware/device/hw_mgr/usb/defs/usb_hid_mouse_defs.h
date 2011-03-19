/*!
 * \file usb_hid_mouse_defs.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _USB_HID_MOUSE_DEFS_H_
#define _USB_HID_MOUSE_DEFS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "usb_defs.h"
#include "usb_hid_defs.h"

#define HID_MOUSE_REL_MIN_XY 0x81 // -127
#define HID_MOUSE_REL_MAX_XY 127


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
#pragma pack(push, 1)
typedef struct _HID_MOUSE_REPORT
{
    struct {
        unsigned Left :1;
        unsigned Right :1;
        unsigned Middle :1;
        unsigned Unused :5;
    } Buttons;
    uint8 X;
    uint8 Y;
} HID_MOUSE_REPORT;
#define HID_MOUSE_REPORT_SIZE sizeof(HID_MOUSE_REPORT)

#pragma pack(pop)

typedef uint8 HID_MOUSE_REPORT_DESCRIPTOR[50];
#define HID_MOUSE_REPORT_DESCRIPTOR_SIZE sizeof(HID_MOUSE_REPORT_DESCRIPTOR)

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* USB_HID_MOUSE_DEFS_H_ */
