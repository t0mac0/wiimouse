#ifndef _WII_MOUSE_DRV_UTILS_H_
#define _WII_MOUSE_DRV_UTILS_H_

#include "wii_mouse.h"

BOOL WiiMouse_DrvUtil_GetDeviceHandle(GUID guidDeviceInterface, PHANDLE hDeviceHandle);

BOOL WiiMouse_DrvUtil_GetWinUsbHandle(HANDLE hDeviceHandle, PWINUSB_INTERFACE_HANDLE phWinUSBHandle);

BOOL WiiMouse_DrvUtil_GetInterfaceHandles(WiiMouse_HandleInfo_t *handleInfo);


#endif