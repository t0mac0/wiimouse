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
#include "util/timer/util_timer.h"


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
    ASSERT(RESULT_IS_SUCCESS(result, LOG_Init()));

    // register the default usart as the default logging output destination
    ASSERT(RESULT_IS_SUCCESS(result, LOG_RegisterOutputDest(LOG_OUTPUT_DEFAULT, HW_USART_DefaultOutputDest, TRUE)));
    LOG_Printf("Logging enabled on default USART\n");

    //  initialize device modules
    if( RESULT_IS_ERROR(result, MOD_MGR_Init()) )
    {
        LOG_CatchError(result);
        ASSERT(0);
    }

    // initialize the system timer
    ASSERT(UTIL_TIMER_Init());

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

