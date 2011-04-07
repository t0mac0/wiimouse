/*!
 * \file hw_timer_basic_stm32f10x.c
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "timer/counter/hw_timer_counter.h"


#ifdef STM32F10X_MD
#ifdef HW_MGR_MOD_TIMER

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
PROTECTED extern TIM_TypeDef* HwTimerCounterBase[HW_TIMER_COUNT];

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/******************************************************************************/
PROTECTED Result HwTimerCounterInit(HW_TIMER_BlockId BlockId, HW_TIMER_ConfigInfo *Config)
{
    Result result = HW_TIMER_RESULT(SUCCESS);
    //TIM_TimeBaseInitTypeDef config;




    // General timer currently only supported
    ASSERT(Config->Type == HW_TIMER_TYPE_GENERAL);

UNUSED(BlockId);


    return result;
}


/******************************************************************************/
PROTECTED Result HwTimerCounterStart(HW_TIMER_BlockId BlockId)
{
    Result result = HW_TIMER_RESULT(SUCCESS);

    UNUSED(BlockId);

    return result;
}


/******************************************************************************/
PROTECTED Result HwTimerCounterStop(HW_TIMER_BlockId BlockId)
{
    Result result = HW_TIMER_RESULT(SUCCESS);

    UNUSED(BlockId);

    return result;
}


/******************************************************************************/
PROTECTED Result HwTimerCounterReset(HW_TIMER_BlockId BlockId)
{
    Result result = HW_TIMER_RESULT(SUCCESS);

    UNUSED(BlockId);

    return result;
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************



#endif
#endif
