/*!
 * \file hw_timer_stm32f10x.c
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
#include "timer/hw_timer.h"

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
 Exported Data Members
------------------------------------------------------------------------------*/


PROTECTED TIM_TypeDef* HwTimerCounterBase[HW_TIMER_COUNT] =
{
#ifdef TIM1
        TIM1,
#else
        NULL,
#endif
#ifdef TIM2
        TIM2,
#else
        NULL,
#endif
#ifdef TIM3
        TIM3,
#else
        NULL,
#endif
#ifdef TIM4
        TIM4,
#else
        NULL,
#endif
};


PROTECTED uint32 HwTimerRccApbPeriphTimer[HW_TIMER_COUNT] =
{
#ifdef RCC_APB2Periph_TIM1
		RCC_APB2Periph_TIM1,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_TIM2
        RCC_APB1Periph_TIM2,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_TIM3
        RCC_APB1Periph_TIM3,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_TIM4
        RCC_APB1Periph_TIM4,
#else
        NULL,
#endif
};

PROTECTED uint32 HwTimerIRQChannel[HW_TIMER_COUNT] =
{
		TIM1_UP_IRQChannel,
		TIM2_IRQChannel,
		TIM3_IRQChannel,
		TIM4_IRQChannel
};



PRIVATE HW_TIMER_Mode timerMode[HW_TIMER_COUNT] = {0};




//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PUBLIC Result HW_TIMER_Init(uint32 BlockId, void* ConfigInfo )
{
    Result result = HW_TIMER_RESULT_INIT();
    HW_TIMER_ConfigInfo *config;

    config = ConfigInfo;

    switch(config->Mode)
    {
    case HW_TIMER_MODE_COUNTER:
        result = HwTimerCounterInit(BlockId, config);
        break;

    default:
        // mode not supported
        ASSERT(0);
    }

    if( IS_RESULT_SUCCESS(result) )
    {
        timerMode[BlockId] = config->Mode;
    }

    return result;
}


//****************************************************************************/
PUBLIC Result HW_TIMER_PowerUp( uint32 BlockId )
{
    Result result = HW_TIMER_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_TIMER_PowerDown( uint32 BlockId )
{
    Result result = HW_TIMER_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_TIMER_Start(HW_TIMER_BlockId Id)
{
    Result result = HW_TIMER_RESULT_INIT();

    switch(timerMode[Id])
    {
    case HW_TIMER_MODE_COUNTER:
        result = HwTimerCounterStart(Id);
        break;
    default:
        ASSERT(0);
    }

    return result;
}

//****************************************************************************/
PUBLIC Result HW_TIMER_Stop(HW_TIMER_BlockId Id)
{
    Result result = HW_TIMER_RESULT_INIT();

    switch(timerMode[Id])
    {
    case HW_TIMER_MODE_COUNTER:
        result = HwTimerCounterStop(Id);
        break;
    default:
        ASSERT(0);
    }

    return result;
}

//****************************************************************************/
PUBLIC Result HW_TIMER_Reset(HW_TIMER_BlockId Id)
{
    Result result = HW_TIMER_RESULT_INIT();

    switch(timerMode[Id])
    {
    case HW_TIMER_MODE_COUNTER:
        result = HwTimerCounterReset(Id);
        break;
    default:
        ASSERT(0);
    }

    return result;
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
#endif
