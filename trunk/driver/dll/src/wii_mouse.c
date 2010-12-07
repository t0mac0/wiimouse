
// Include Windows headers
#include <windows.h>

extern "C"
{
#include <winusb.h>
}


#include "ifc_wii_mouse.h"
#include "wii_mouse_drv_utils.h"
#include "wii_mouse_utils.h"
#include "wii_mouse.h"



WiiMouse_AddMsg_t WiiMouse_AddMsg = NULL;



static WiiMouse_HandleInfo_t _handleInfo;
static int _connected = 0;
static int wiiMouse_InfoCollecting = 0;



static void _SetConnected( int isConnected )
{
    _connected = isConnected;
}

static void _SetInfoCollecting( int infoCollecting )
{
    wiiMouse_InfoCollecting = infoCollecting;
}

static void _FreeHandles()
{
    WinUsb_Free(_handleInfo.interfaceHandle);
    WinUsb_Free(_handleInfo.winUsbHandle);
    CloseHandle(_handleInfo.deviceHandle);
    CloseHandle(_handleInfo.infoCollectionThreadHandle);
}

WII_MOUSE_DLL int WiiMouse_IsConnected( void )
{
    return _connected;
}


WII_MOUSE_DLL int WiiMouse_IsInfoCollecting( void )
{
    return wiiMouse_InfoCollecting;
}


WII_MOUSE_DLL int WiiMouse_Connect( WiiMouse_AddMsg_t addMsg )
{
    int retval = 1;

    if( WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(INFO,"USB connection already opened to WiiMouse\n");
        return 1;
    }

    // assing the messaging function
    WiiMouse_AddMsg = addMsg;
    

    if ( WiiMouse_DrvUtil_GetDeviceHandle(GUID_WII_MOUSE, &_handleInfo.deviceHandle) )
    {
        WiiMouse_AddMsg(DERR,"Failed to get USB device handle\n");
        retval = 0;
    } 
    else if( WiiMouse_DrvUtil_GetWinUsbHandle(&_handleInfo.deviceHandle, &_handleInfo.winUsbHandle) )
    {
        WiiMouse_AddMsg(DERR,"Failed to get WinUSB handle\n");
        retval = 0;
    }
    else if( WiiMouse_DrvUtil_GetInterfaceHandles(&_handleInfo) )
    {
        WiiMouse_AddMsg(DERR,"Failed to get interface handles\n");
        retval = 0;
    }

    if(!retval)
    {
        WiiMouse_AddMsg(ERR,"Error, failed to open USB connection to WiiMouse\n");
        _FreeHandles();
    }
    else
    {
        _SetConnected(1);
        WiiMouse_AddMsg(INFO, "Connection opened to WiiMouse\n");
    }

    return retval;
}

WII_MOUSE_DLL int WiiMouse_Disconnect( void )
{
    int retval = 1;

    if( !WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(INFO, "No USB connection opened to WiiMouse\n");
        return 1;
    }

    if ( WiiMouse_IsInfoCollecting() && WiiMouse_StopInfoCollection() )
    {
        WiiMouse_AddMsg(DERR, "Error, driver was collecting mouse information, attempted to stop and failed\n");
        retval = 0;
    }

    _FreeHandles();

    if(!retval)
    {
        WiiMouse_AddMsg(ERR, "Error, failed to close USB connection to WiiMouse\n");
    }
    else
    {
        WiiMouse_AddMsg(INFO, "Closed USB connection to WiiMouse\n");
    }

    _SetConnected(0);

    return retval;
}

WII_MOUSE_DLL int WiiMouse_StartInfoCollection( WiiMouse_InfoCollectionCallback_t callback )
{
    int retval = 1;
    static WiiMouse_Util_InfoCollectionThread_Params_t params;
    
    if( callback == NULL )
    {
        WiiMouse_AddMsg(DERR, "Error, information callback function not specified\n");
        retval = 0;
    }
    else if( !WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(DERR, "Error, no USB connection to WiiMouse established\n");
        retval = 0;
    }
    else if ( WiiMouse_IsInfoCollecting() && !WiiMouse_StopInfoCollection() )
    {
        WiiMouse_AddMsg(DERR,"Error, driver was already in collection state, attempted to restart and failed\n");
        retval = 0;
    } 
    else if( retval )
    {
        params.callback = callback;
        params.collectionDelay = _handleInfo.getInfoPipe.Interval;

        _handleInfo.infoCollectionThreadHandle = CreateThread( 
                    NULL,                   // default security attributes
                    0,                      // use default stack size  
                    WiiMouse_Util_InfoCollectionThread,       // thread function name
                    &params,                // argument to thread function 
                    0,                      // use default creation flags 
                    NULL                    // returns the thread identifier   
                    );

        if( _handleInfo.infoCollectionThreadHandle == NULL )
        {
            WiiMouse_AddMsg(DERR,"Error, failed to create mouse information collecting thread\n");
            retval = 0;
        }
    }

    if(!retval)
    {
        WiiMouse_AddMsg(ERR,"Error, failed to start collecting mouse information\n");
    }
    else
    {
        _SetInfoCollecting(1);
        WiiMouse_AddMsg(INFO,"Collecting mouse information\n");
    }

    return retval;
}

WII_MOUSE_DLL int WiiMouse_StopInfoCollection( void )
{
    int retval = 1;

    if( !WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(INFO, "No USB connection to WiiMouse established\n");
        return 1;
    }
    else if( !WiiMouse_IsInfoCollecting() )
    {
        WiiMouse_AddMsg(INFO, "Not collecting information\n");
        return 1;
    }

    if(!retval)
    {
        WiiMouse_AddMsg(ERR, "Error, failed to stop collecting WiiMouse information\n");
    }
    else
    {
        _SetInfoCollecting(0);
        CloseHandle(_handleInfo.infoCollectionThreadHandle);
        WiiMouse_AddMsg(INFO, "WiiMouse information collection stopped\n");
    }

    return retval;
}

WII_MOUSE_DLL int WiiMouse_GetInfo( IFC_WiiMouse_Info_t *info )
{
    int retval = 1;
    ULONG bytesReceived;

    if( !WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(DERR, "Error, no USB connection to WiiMouse established\n");
        retval = 0;
    }
    else if( !WinUsb_ReadPipe(_handleInfo.interfaceHandle, 
                                _handleInfo.getInfoPipe.PipeId, 
                                (PUCHAR)info, sizeof(IFC_WiiMouse_Info_t), 
                                &bytesReceived, NULL) )
    {
        WiiMouse_AddMsg(DERR, "Error, WinUsb_ReadPipe failed with status %d\n", GetLastError());
        retval = 0;
    }
    else if( bytesReceived != sizeof(IFC_WiiMouse_Info_t) )
    {
        WiiMouse_AddMsg(DERR, "Error, only %d bytes of %d received\n", bytesReceived, sizeof(IFC_WiiMouse_Info_t));
        retval = 0;
    }

    if(!retval)
    {
        WiiMouse_AddMsg(ERR, "Error,failed to get WiiMouse information\n");
    }

    return retval;
}

WII_MOUSE_DLL int WiiMouse_GetConfiguration( IFC_WiiMouse_Config_t *config )
{
    int retval = 1;
    ULONG bytesReceived;

    if( !WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(DERR, "Error, no USB connection to WiiMouse established\n");
        retval = 0;
    }
    else if( !WinUsb_ReadPipe(_handleInfo.interfaceHandle, 
                         _handleInfo.getConfigPipe.PipeId, 
                         (PUCHAR)config, sizeof(IFC_WiiMouse_Config_t), 
                         &bytesReceived, NULL) )
    {
        WiiMouse_AddMsg(DERR, "Error, WinUsb_ReadPipe failed with status %d\n", GetLastError());
        retval = 0;
    }
    else if( bytesReceived != sizeof(IFC_WiiMouse_Config_t) )
    {
        WiiMouse_AddMsg(DERR, "Error, only %d bytes of %d received\n", bytesReceived, sizeof(IFC_WiiMouse_Config_t));
        retval = 0;
    }

    if(!retval)
    {
        WiiMouse_AddMsg(ERR, "Error,failed to get WiiMouse configuration\n");
    }
    else
    {
        WiiMouse_AddMsg(INFO, "Received WiiMouse configuration\n");
    }

    return retval;
}

WII_MOUSE_DLL int WiiMouse_SetConfiguration( IFC_WiiMouse_Config_t *config )
{
    int retval = 1;
    ULONG bytesSent;

    if( !WiiMouse_IsConnected() )
    {
        WiiMouse_AddMsg(DERR, "Error, no USB connection to WiiMouse established\n");
        retval = 0;
    }
    else if( !WinUsb_WritePipe(_handleInfo.interfaceHandle, 
                                _handleInfo.setConfigPipe.PipeId, 
                                (PUCHAR)config, sizeof(IFC_WiiMouse_Config_t), 
                                &bytesSent, NULL) )
    {
        WiiMouse_AddMsg(DERR, "Error, WinUsb_WritePipe failed with status %d\n", GetLastError());
        retval = 0;
    }
    else if( bytesSent != sizeof(IFC_WiiMouse_Config_t) )
    {
        WiiMouse_AddMsg(DERR, "Error, only %d bytes of %d sent\n", bytesSent, sizeof(IFC_WiiMouse_Config_t));
        retval = 0;
    }

    if(!retval)
    {
        WiiMouse_AddMsg(ERR, "Error,failed to set WiiMouse configuration\n");
    }
    else
    {
        WiiMouse_AddMsg(INFO, "Sent WiiMouse configuration\n");
    }

    return retval;
}


WII_MOUSE_DLL int WiiMouse_UpdateFirmware( char *filePath )
{
    int retval = 1;


    return retval;
}

