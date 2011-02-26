/*
 * delay.h
 *
 *  Created on: Jan 30, 2011
 *      Author: Reed
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f10x_type.h"

void TimingDelay_Decrement(void);

void DelayMs(vu32 nTime);

#endif /* DELAY_H_ */
