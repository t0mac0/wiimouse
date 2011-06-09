/*!
 * \file util_timer.c
 *
 * \brief 
 *
 *
 * \date Apr 4, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "util_timer.h"
#include "timer/hw_timer.h"

#ifdef DEV_UTIL_TIMER

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

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PUBLIC vint32 UTIL_TIMER_Ticker;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/******************************************************************************/
PUBLIC bool UTIL_TIMER_Init( void )
{
    Result result;
    HW_TIMER_ConfigInfo timerConfig;
    HW_TIMER_CounterConfig counterConfig;

    LOG_Printf("Initializing utility timer\n");

    // TODO: maintain interrupt priorities
    counterConfig.InterruptPriority = 2;
    counterConfig.EnableUpdateInterrupt = TRUE;
    counterConfig.Frequnecy = UTIL_TIMER_FREQ;
    counterConfig.Mode = HW_TIMER_COUNTER_MODE_UP;

    timerConfig.ClkSrc = HW_TIMER_CLK_SRC_INT;
    timerConfig.Mode = HW_TIMER_MODE_COUNTER;
    timerConfig.Type = HW_TIMER_TYPE_GENERAL;
    timerConfig.config = &counterConfig;
    timerConfig.Enable = TRUE;

    if( RESULT_IS_ERROR(result, HW_TIMER_Init(UTIL_TIMER, &timerConfig)) )
    {
        return FALSE;
    }

    UTIL_TIMER_Ticker = 0;

    return TRUE;
}


/******************************************************************************/
PUBLIC bool UTIL_TIMER_Start( void )
{

    HW_TIMER_Start(UTIL_TIMER);

    return TRUE;
}


/******************************************************************************/
PUBLIC bool UTIL_TIMER_Stop( void )
{

    HW_TIMER_Stop(UTIL_TIMER);

    return TRUE;
}


/******************************************************************************/
PUBLIC bool UTIL_TIMER_Reset( void )
{
    UTIL_TIMER_Ticker = 0;

    HW_TIMER_Reset(UTIL_TIMER);

    return TRUE;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
