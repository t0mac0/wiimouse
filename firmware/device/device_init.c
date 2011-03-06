/*!
 * \file device_init.c
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "hw_mgr/hw_mgr.h"


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
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE bool CriticalHwInit( void );

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************
PROTECTED bool DeviceInit( void )
{
    bool retval = TRUE;
    Result result;

    // initialize device critical hardware
    ASSERT(CriticalHwInit());

    // initialize logging
    ASSERT(RESULT_SUCCESS(result, LOG_Init()));

    // register the default usart as the default logging output destination
    ASSERT(RESULT_SUCCESS(result, LOG_RegisterOutputDest(LOG_OUTPUT_DEFAULT, HW_USART_DefaultOutputDest, TRUE)));
    LOG_Printf("Logging enabled on default USART\n");

    //  initialize device modules
    if( !RESULT_SUCCESS(result, MOD_MGR_Init()) )
    {
        LOG_CatchError(result);
        ASSERT(0);
    }

    return retval;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
PRIVATE bool CriticalHwInit( void )
{
    bool retval = TRUE;

    // initialize system registers
    HW_SYSINIT_Init();

    // initialize system clock
    HW_SYSCLK_SetClock(DEVICE_CLOCK_RATE);
    DeviceSystemClock = DEVICE_CLOCK_RATE;

    // initialize interrupt vector table
    HW_INT_Init();

    // initialize default USART
    HW_USART_DefaultInit();


    return retval;
}

