/*
 * delay.c
 *
 *  Created on: Jan 30, 2011
 *      Author: Reed
 */

#include "delay.h"

static __IO uint32 TimingDelay;


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void DelayMs(__IO uint32 nTime)
{
  TimingDelay = nTime;
//
  while(TimingDelay != 0);
	}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}
