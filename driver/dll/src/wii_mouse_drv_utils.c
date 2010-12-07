// Include Windows headers
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>

extern "C"
{
#include <winusb.h>
#include <Usb100.h>
#include <setupapi.h>
#include "strsafe.h"
}

#include "ifc_wii_mouse_cfg.h"
#include "ifc_wii_mouse.h"
#include "wii_mouse_drv_utils.h"

// Linked libraries
#pragma comment (lib , "setupapi.lib" )
#pragma comment (lib , "winusb.lib" )

extern WiiMouse_AddMsg_t WiiMouse_AddMsg;

static BOOL _IsValidInterface(PUSB_INTERFACE_DESCRIPTOR usbInterfaceDesc)
{
    BOOL retval = FALSE;

    if( usbInterfaceDesc->bInterfaceClass == IFC_WII_MOUSE_IFC_CLASS &&
        usbInterfaceDesc->bInterfaceSubClass == IFC_WII_MOUSE_IFC_SUBCLASS &&
        usbInterfaceDesc->bInterfaceProtocol == IFC_WII_MOUSE_IFC_PROTOCOL &&
        usbInterfaceDesc->bNumEndpoints == IFC_WII_MOUSE_IFC_NUM_EP )
    {
        retval = TRUE;
    }

    return retval;
}

static void _SetEndpoint(WiiMouse_HandleInfo_t *handleInfo, PWINUSB_PIPE_INFORMATION pipeInfo)
{
    if( pipeInfo->PipeType == UsbdPipeTypeBulk &&
        pipeInfo->PipeId == IFC_WII_MOUSE_UPDATE_FIRMWARE_EP )
    {
        memcpy(&handleInfo->updateFirmwarePipe, pipeInfo, sizeof(WINUSB_PIPE_INFORMATION));
    }
    else if(pipeInfo->PipeType == UsbdPipeTypeBulk &&
            pipeInfo->PipeId == IFC_WII_MOUSE_SET_CONFIG_EP )
    {
        memcpy(&handleInfo->setConfigPipe, pipeInfo, sizeof(WINUSB_PIPE_INFORMATION));
    }
     else if(pipeInfo->PipeType == UsbdPipeTypeBulk &&
            pipeInfo->PipeId == IFC_WII_MOUSE_GET_CONFIG_EP )
    {
        memcpy(&handleInfo->getConfigPipe, pipeInfo, sizeof(WINUSB_PIPE_INFORMATION));
    }
     else if(pipeInfo->PipeType == UsbdPipeTypeInterrupt &&
            pipeInfo->PipeId == IFC_WII_MOUSE_GET_INFO_EP )
    {
        memcpy(&handleInfo->getInfoPipe, pipeInfo, sizeof(WINUSB_PIPE_INFORMATION));
    }
    else
    {
        WiiMouse_AddMsg(DERR,"Unknown pipe id: %d, type: %d\n", pipeInfo->PipeId, pipeInfo->PipeType);
    }
}

BOOL WiiMouse_DrvUtil_GetDeviceHandle(GUID guidDeviceInterface, PHANDLE hDeviceHandle)
{
    if (guidDeviceInterface==GUID_NULL)
    {
        return TRUE;
    }

    BOOL retval = FALSE;
    BOOL bResult = TRUE;
    HDEVINFO hDeviceInfo;
    SP_DEVINFO_DATA DeviceInfoData;

    SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetailData = NULL;

    ULONG requiredLength=0;

    LPTSTR lpDevicePath = NULL;

    DWORD index = 0;

    // Get information about all the installed devices for the specified
    // device interface class.
    hDeviceInfo = SetupDiGetClassDevs( 
        &guidDeviceInterface,
        NULL, 
        NULL,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (hDeviceInfo == INVALID_HANDLE_VALUE) 
    { 
        // ERROR 
        WiiMouse_AddMsg(DERR, "Error SetupDiGetClassDevs: %d\n", GetLastError());
        retval = TRUE;
        goto done;
    }

    //Enumerate all the device interfaces in the device information set.
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (index = 0; SetupDiEnumDeviceInfo(hDeviceInfo, index, &DeviceInfoData); index++)
    {
        //Reset for this iteration
        if (lpDevicePath)
        {
            LocalFree(lpDevicePath);
        }
        if (pInterfaceDetailData)
        {
            LocalFree(pInterfaceDetailData);
        }

        deviceInterfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

        //Get information about the device interface.
        bResult = SetupDiEnumDeviceInterfaces( 
           hDeviceInfo,
           &DeviceInfoData,
           &guidDeviceInterface,
           index, 
           &deviceInterfaceData);

        // Check if last item
        if (GetLastError () == ERROR_NO_MORE_ITEMS)
        {
            break;
        }

        //Check for some other error
        if (!bResult) 
        {
            WiiMouse_AddMsg(DERR,"Error SetupDiEnumDeviceInterfaces: %d\n", GetLastError());
            retval = TRUE;
            goto done;
        }

        //Interface data is returned in SP_DEVICE_INTERFACE_DETAIL_DATA
        //which we need to allocate, so we have to call this function twice.
        //First to get the size so that we know how much to allocate
        //Second, the actual call with the allocated buffer
        
        bResult = SetupDiGetDeviceInterfaceDetail(
            hDeviceInfo,
            &deviceInterfaceData,
            NULL, 0,
            &requiredLength,
            NULL);


        //Check for some other error
        if (!bResult) 
        {
            if ((ERROR_INSUFFICIENT_BUFFER==GetLastError()) && (requiredLength>0))
            {
                //we got the size, allocate buffer
                pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, requiredLength);
                
                if (!pInterfaceDetailData) 
                { 
                    // ERROR 
                    WiiMouse_AddMsg(DERR, "Error allocating memory for the device detail buffer\n");
                    retval = TRUE;
                    goto done;
                }
            }
            else
            {
                WiiMouse_AddMsg(DERR, "Error SetupDiEnumDeviceInterfaces: %d\n", GetLastError());
                retval = TRUE;
                goto done;
            }
        }

        //get the interface detailed data
        pInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        //Now call it with the correct size and allocated buffer
        bResult = SetupDiGetDeviceInterfaceDetail(
                hDeviceInfo,
                &deviceInterfaceData,
                pInterfaceDetailData,
                requiredLength,
                NULL,
                &DeviceInfoData);
        
        //Check for some other error
        if (!bResult) 
        {
            WiiMouse_AddMsg(DERR, "Error SetupDiGetDeviceInterfaceDetail: %d.\n", GetLastError());
            retval = TRUE;
            goto done;
        }

        //copy device path
                
        size_t nLength = wcslen (pInterfaceDetailData->DevicePath) + 1;  
        lpDevicePath = (TCHAR *) LocalAlloc (LPTR, nLength * sizeof(TCHAR));
        StringCchCopy(lpDevicePath, nLength, pInterfaceDetailData->DevicePath);
        lpDevicePath[nLength-1] = 0;
                        
        WiiMouse_AddMsg(DINFO, "Device path:  %S\n", lpDevicePath);

    }

    if (!lpDevicePath)
    {
        //Error.
        WiiMouse_AddMsg(DERR, "Error, null device file path: %d\n", GetLastError());
        retval = TRUE;
        goto done;
    }

    //Open the device
    *hDeviceHandle = CreateFile (
        lpDevicePath,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL);

    if (*hDeviceHandle == INVALID_HANDLE_VALUE)
    {
        //Error.
        WiiMouse_AddMsg(DERR, "CreateFile: INVALID_HANDLE_VALUE Error %d\n", GetLastError());
        retval = TRUE;
        goto done;
    }



done:
    LocalFree(lpDevicePath);
    LocalFree(pInterfaceDetailData);    
    
    if( !SetupDiDestroyDeviceInfoList(hDeviceInfo) )
    {
        WiiMouse_AddMsg(DERR, "SetupDiDestroyDeviceInfoList failed\n");
        retval = TRUE;
    }
    
    return retval;
}

BOOL WiiMouse_DrvUtil_GetWinUsbHandle(HANDLE hDeviceHandle, PWINUSB_INTERFACE_HANDLE phWinUSBHandle)
{
    BOOL retval = 0;

    if (hDeviceHandle == INVALID_HANDLE_VALUE)
    {
        retval = 1;
    }
    else if( !WinUsb_Initialize(hDeviceHandle, phWinUSBHandle))
    {
        WiiMouse_AddMsg(DERR, "WinUsb_Initialize Error %d\n", GetLastError());
        retval =  1;
    } 

    return retval;
}


BOOL WiiMouse_DrvUtil_GetInterfaceHandles(WiiMouse_HandleInfo_t *handleInfo)
{
    BOOL retval = FALSE;
    UCHAR interfaceIndex = 0;
    UCHAR pipeIndex = 0;
    USB_INTERFACE_DESCRIPTOR usbInterfaceDesc;
    WINUSB_PIPE_INFORMATION pipeInfo;

    while( WinUsb_QueryInterfaceSettings(handleInfo->winUsbHandle, interfaceIndex, &usbInterfaceDesc) )
    {
        if( _IsValidInterface(&usbInterfaceDesc) )
        {
            break;
        }

        interfaceIndex++;
    }

    if( GetLastError() == ERROR_INVALID_HANDLE )
    {
        WiiMouse_AddMsg(DERR,"Error, WinUsb_QueryInterfaceSettings invalid handle\n");
        return FALSE;
    }

    if( !WinUsb_GetAssociatedInterface(handleInfo->winUsbHandle, interfaceIndex, &handleInfo->interfaceHandle) )
    {
        DWORD err = GetLastError();

        if( err != ERROR_ALREADY_EXISTS )
        {
            WiiMouse_AddMsg(DERR,"Error, WinUsb_GetAssociatedInterface failed: %d\n", err);
            return FALSE;
        }
        else
        {
            handleInfo->interfaceHandle = handleInfo->winUsbHandle;
            handleInfo->interfaceId = 0;
        }
    }
    handleInfo->interfaceId = interfaceIndex;

    for( pipeIndex = 0; pipeIndex < usbInterfaceDesc.bNumEndpoints; pipeIndex++ )
    {
        if( !WinUsb_QueryPipe(handleInfo->winUsbHandle, interfaceIndex, pipeIndex, &pipeInfo) )
        {
            WiiMouse_AddMsg(DERR,"Error, WinUsb_QueryPipe failed: %d\n", GetLastError());
            retval = FALSE;
            break;
        }
        else
        {
            _SetEndpoint(handleInfo, &pipeInfo);
        }
    }

   /* if( !_ValidateEndpoints(handleInfo) )
    {
         WiiMouse_AddMsg(DERR,"Error, endpoint validation failed\n");
         retval = FALSE;
    }*/
    
    if( !retval )
    {
        WinUsb_Free(handleInfo->interfaceHandle);
    }


    return retval;
}
