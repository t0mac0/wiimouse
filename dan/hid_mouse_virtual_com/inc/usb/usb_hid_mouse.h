/*
 * usb_hid_mouse.h
 *
 *  Created on: Feb 2, 2011
 *      Author: Reed
 */

#ifndef USB_HID_MOUSE_H_
#define USB_HID_MOUSE_H_

#include "usb.h"
#include "usb_hid.h"

#define HID_MOUSE_REL_MIN_XY 0x81
#define HID_MOUSE_REL_MAX_XY 127
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


#endif /* USB_HID_MOUSE_H_ */
