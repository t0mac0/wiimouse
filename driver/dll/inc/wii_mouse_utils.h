#ifndef _WII_MOUSE_UTILS_H_
#define _WII_MOUSE_UTILS_H_

#include <WINDOWS.H>
#include <stdio.h>

#include "ifc_wii_mouse.h"


#define MAX_FILENAME_LEN 256


typedef struct {
    WiiMouse_InfoCollectionCallback_t callback;
    DWORD collectionDelay;
} WiiMouse_Util_InfoCollectionThread_Params_t;



DWORD WINAPI WiiMouse_Util_InfoCollectionThread( LPVOID lpParam );


#endif