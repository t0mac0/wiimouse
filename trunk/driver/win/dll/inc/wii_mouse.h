#ifndef _WII_MOUSE_H_
#define _WII_MOUSE_H_

#include <windows.h>

extern "C"
{
#include <winusb.h>
}
    
typedef struct {
    HANDLE deviceHandle;
    HANDLE infoCollectionThreadHandle;
    WINUSB_INTERFACE_HANDLE winUsbHandle;
    WINUSB_INTERFACE_HANDLE interfaceHandle;
    WINUSB_PIPE_INFORMATION setConfigPipe;
    WINUSB_PIPE_INFORMATION getConfigPipe;
    WINUSB_PIPE_INFORMATION getInfoPipe;
    WINUSB_PIPE_INFORMATION updateFirmwarePipe;
    UCHAR interfaceId;
} WiiMouse_HandleInfo_t;



#endif