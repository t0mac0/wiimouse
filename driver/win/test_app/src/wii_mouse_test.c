#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "ifc_wii_mouse.h"
#include "ifc_wii_mouse_types.h"



static int collectionCallback(IFC_WiiMouse_Info_t *info)
{
    printf("Wii mouse state:\n\tx: %d\n\ty: %d\n\tleft: %d\n\tright: %d\n", info->x, info->y, info->buttonLeft, info->buttinRight);
    return 0;
}

static int addMsg( WiiMouse_MsgSeverity_t severity, const char* frmt, ... )
{
    va_list args;

    switch(severity)
    {
    case ERR:
        printf("ERR: ");
        break;
    case DERR:
        printf("DERR: ");
        break;
    case INFO:
        printf("INFO: ");
        break;
    case DINFO:
        printf("DINFO: ");
        break;
    case DBUG:
        printf("DBUG: ");
        break;
    }

    va_start(args, frmt);
    vprintf(frmt,args);
    va_end(args);

    return 0;

}

int main(int argc, char *argv[])
{
    char ch;

    if( WiiMouse_Connect(addMsg) )
    {
        WiiMouse_Disconnect();
    }


    do{
    printf("Press Enter to continue\n");
    } while ((ch = getchar()) != '\n') ; 

    return 0;
}

