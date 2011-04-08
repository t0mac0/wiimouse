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
PRIVATE Result GetFrequencyFactors(HW_TIMER_CounterConfig *hwConfig, TIM_TimeBaseInitTypeDef *baseConfig);



/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED extern TIM_TypeDef* HwTimerCounterBase[HW_TIMER_COUNT];

PRIVATE uint16 CounterModes[] = {
        TIM_CounterMode_Up,
        TIM_CounterMode_Down,
        TIM_CounterMode_CenterAligned1
};

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/******************************************************************************/
PROTECTED Result HwTimerCounterInit(HW_TIMER_BlockId BlockId, HW_TIMER_ConfigInfo *Config)
{
    Result result = HW_TIMER_RESULT(SUCCESS);
    TIM_TimeBaseInitTypeDef baseConfig;
    HW_TIMER_CounterConfig *hwConfig;

    // General timer currently only supported
    ASSERT(Config->Type == HW_TIMER_TYPE_GENERAL);
    ASSERT(Config->ClkSrc == HW_TIMER_CLK_SRC_INT);

    hwConfig = (HW_TIMER_CounterConfig*)Config->config;

    TIM_TimeBaseStructInit( &baseConfig );

    if( RESULT_IS_SUCCESS(result, GetFrequencyFactors(hwConfig, &baseConfig)) )
    {
        baseConfig.TIM_CounterMode = CounterModes[hwConfig->Mode];
        TIM_TimeBaseInit( HwTimerCounterBase[BlockId], &baseConfig );

        if( hwConfig->EnableUpdateInterrupt )
        {
            TIM_ITConfig( HwTimerCounterBase[BlockId], TIM_IT_Update, ENABLE );
        }

        if( Config->Enable )
        {
            result = HwTimerCounterStart(BlockId);
        }
    }

    return result;
}


/******************************************************************************/
PROTECTED Result HwTimerCounterStart(HW_TIMER_BlockId BlockId)
{
    Result result = HW_TIMER_RESULT(SUCCESS);

    TIM_Cmd( HwTimerCounterBase[BlockId], ENABLE );

    return result;
}


/******************************************************************************/
PROTECTED Result HwTimerCounterStop(HW_TIMER_BlockId BlockId)
{
    Result result = HW_TIMER_RESULT(SUCCESS);

    TIM_Cmd( HwTimerCounterBase[BlockId], DISABLE );

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


/******************************************************************************/
PRIVATE Result GetFrequencyFactors(HW_TIMER_CounterConfig *HwConfig, TIM_TimeBaseInitTypeDef *BaseConfig)
{
    Result result = HW_TIMER_RESULT(SUCCESS);
    uint32 totalFactor;

    // TODO: make this more accurate
    totalFactor = (DeviceSystemClock / HwConfig->Frequnecy);

    if( totalFactor == 0 )
    {
        result = HW_TIMER_RESULT(BAD_FREQ);
    }
    else
    {
        if( totalFactor > UINT16_MAX )
        {
            BaseConfig->TIM_Prescaler = UINT16_MAX;
            totalFactor /= UINT16_MAX;
        }
        else
        {
            BaseConfig->TIM_Prescaler = 0;
        }

        BaseConfig->TIM_ClockDivision = TIM_CKD_DIV1;
        BaseConfig->TIM_Period = totalFactor-1;
    }

    return result;
}


#endif
#endif
