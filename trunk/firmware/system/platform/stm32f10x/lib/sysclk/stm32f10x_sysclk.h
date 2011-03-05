/*!
 * \file stm32f10x_sysclk.h
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

#ifndef _STM32F10X_SYSCLK_H_
#define _STM32F10X_SYSCLK_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define SYSCLK_FREQ_HSI    -1
#define SYSCLK_FREQ_HSE    0
#define SYSCLK_FREQ_24MHz  24000000
#define SYSCLK_FREQ_36MHz  36000000
#define SYSCLK_FREQ_48MHz  48000000
#define SYSCLK_FREQ_56MHz  56000000
#define SYSCLK_FREQ_72MHz  72000000

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
void SysClk_SetClock(uint32 Freq);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* STM32F10X_SYSCLK_H_ */
