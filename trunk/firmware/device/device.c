/*!
 * \file device.c
 *
 * \brief 
 *
 *
 * \date Mar 1, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
 ------------------------------------------------------------------------------*/
#include <string.h>
#include "device.h"
#include "os.h"


/*-----------------------------------------------------------------------------
 Defines
 ------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
 ------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
 ------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Function Prototypes
 ------------------------------------------------------------------------------*/
PROTECTED bool DeviceInit( void );

/*-----------------------------------------------------------------------------
 Data Members
 ------------------------------------------------------------------------------*/

PUBLIC uint32 DeviceMode  __attribute ((section(".device_mode")));
PUBLIC uint32 DeviceFirmwareVersion  __attribute ((section(".device_firmware_version"))) = DEVICE_FIRMWARE_VERSION;

PUBLIC uint32 DeviceSystemClock = 0;


/******************************************************************************/
int main(int argc, char *argv[])
{
    Result result;

    UNUSED(argc);
    UNUSED(argv);

    // initialize the device
    ASSERT(DeviceInit());

    if( RESULT_IS_ERROR(result, OS_TASK_MGR_StartScheduler()) )
    {
        LOG_Printf("failed to start the task scheduler\n");
    }

    for(;;);

    return 0;
}


/******************************************************************************/
PUBLIC void ASSERT_failed(uint8* file, uint32 line)
{
    LOG_Printf("Assertion Failed: File: %s, line: %d\n", file, line);
    UNUSED(file);
    UNUSED(line);
    while(1);
}


