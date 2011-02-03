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
#pragma pack(1)
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
#pragma pack()
#define HID_MOUSE_REPORT_SIZE sizeof(HID_MOUSE_REPORT)

typedef uint8 HID_MOUSE_REPORT_DESCRIPTOR[50];
#define HID_MOUSE_REPORT_DESCRIPTOR_SIZE sizeof(HID_MOUSE_REPORT_DESCRIPTOR)


typedef struct _WII_MOUSE_CONFIGURATION_DESCRIPTOR{
	USB_CONFIGURATION_DESCRIPTOR ConfigDesc;
	USB_INTERFACE_DESCRIPTOR IfcDesc;
	HID_DESCRIPTOR HidDesc;
	USB_ENDPOINT_DESCRIPTOR EpDesc;
} WII_MOUSE_CONFIGURATION_DESCRIPTOR;
#define WII_MOUSE_CONFIGURATION_DESCRIPTOR_SIZE sizeof(WII_MOUSE_CONFIGURATION_DESCRIPTOR)
#pragma pack()

#endif /* USB_HID_MOUSE_H_ */
