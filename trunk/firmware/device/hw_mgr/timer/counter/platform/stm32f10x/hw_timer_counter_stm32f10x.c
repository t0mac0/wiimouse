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
#include <stdlib.h>

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
PROTECTED extern uint32 HwTimerRccApbPeriphTimer[HW_TIMER_COUNT];
PROTECTED extern uint32 HwTimerIRQChannel[HW_TIMER_COUNT];



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
		if( hwConfig->EnableUpdateInterrupt )
		{
			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_InitStructure.NVIC_IRQChannel = HwTimerIRQChannel[BlockId];
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

			NVIC_Init(&NVIC_InitStructure);

			// enable the timer peripherial clock
			RCC_APB1PeriphClockCmd(HwTimerRccApbPeriphTimer[BlockId], ENABLE);

			baseConfig.TIM_CounterMode = CounterModes[hwConfig->Mode];
			TIM_TimeBaseInit( HwTimerCounterBase[BlockId], &baseConfig );
			HwTimerCounterBase[BlockId]->SR = 0;

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
	LOG_Printf("Enabling timer: %d\n", BlockId);
	TIM_Cmd( HwTimerCounterBase[BlockId], ENABLE );

	return HW_TIMER_RESULT(SUCCESS);
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
#define ACCURACY_FACTOR 32
#define MAX_VALUE (1uL << 21)
	Result result = HW_TIMER_RESULT(SUCCESS);
	uint32 prescaler, tmp_prescaler, scaled_freq, scaled_sys_freq;
	uint32 period, tmp_period;
	uint32 min, tmp_min;

	scaled_freq = ACCURACY_FACTOR*(uint64)HwConfig->Frequnecy;
	scaled_sys_freq = DeviceSystemClock*ACCURACY_FACTOR;
	prescaler = 0;
	period = (scaled_sys_freq / HwConfig->Frequnecy);

	if( period == 0 )
	{
		result = HW_TIMER_RESULT(BAD_FREQ);
	}
	else
	{

		if( period > MAX_VALUE )
		{
			min = UINT32_MAX;

			for(tmp_prescaler = 2; tmp_prescaler <= (UINT16_MAX+1); tmp_prescaler <<= 1)
			{
				tmp_period = scaled_sys_freq / (HwConfig->Frequnecy*tmp_prescaler);

				if(tmp_period <= MAX_VALUE)
				{
					tmp_min = labs(scaled_sys_freq / ((tmp_period*tmp_prescaler)/ACCURACY_FACTOR) - scaled_freq);

					if( tmp_min < min )
					{
						min = tmp_min;
						period = tmp_period;
						prescaler = tmp_prescaler;
					}
				}
			}

			BaseConfig->TIM_Prescaler = (uint16)prescaler-1;
		}
		else
		{
			BaseConfig->TIM_Prescaler = 0;

		}

		period /= ACCURACY_FACTOR;

		BaseConfig->TIM_ClockDivision = TIM_CKD_DIV1;
		BaseConfig->TIM_Period = (uint16)period-1;

		LOG_Printf("Frequency: %d\n", HwConfig->Frequnecy);
		LOG_Printf("TIM_ClockDivision: %d\n", BaseConfig->TIM_ClockDivision);
		LOG_Printf("TIM_Period: %d\n", BaseConfig->TIM_Period);
		LOG_Printf("TIM_Prescaler: %d\n", BaseConfig->TIM_Prescaler);
	}

	return result;
}


#endif
#endif
