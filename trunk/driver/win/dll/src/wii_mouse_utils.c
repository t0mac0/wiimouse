
#include <string.h>
#include "wii_mouse_utils.h"
#include "wii_mouse.h"

extern WiiMouse_AddMsg_t WiiMouse_AddMsg;

DWORD WINAPI WiiMouse_Util_InfoCollectionThread( LPVOID lpParam )
{
    IFC_WiiMouse_Info_t info;
    WiiMouse_Util_InfoCollectionThread_Params_t params;
    DWORD retval = 0;
        
    memcpy(&params, lpParam, sizeof(WiiMouse_Util_InfoCollectionThread_Params_t));

    while( WiiMouse_IsInfoCollecting() )
    {
        if( WiiMouse_GetInfo(&info) )
        {
            WiiMouse_AddMsg(ERR,"Error getting mouse information, stopping collection and exiting collection thread\n");
            WiiMouse_StopInfoCollection();
            retval = 1;
            break;
        }
        if( params.callback(&info) )
        {
            WiiMouse_AddMsg(ERR,"Error executing collection callback, stopping collection and exiting collection thread\n");
            WiiMouse_StopInfoCollection();
            retval = 1;
            break;
        }

        Sleep(params.collectionDelay);
    }

    return retval;
}
