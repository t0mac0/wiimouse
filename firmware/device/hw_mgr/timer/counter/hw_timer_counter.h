/*!
 * \file hw_timer_counter.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_TIMER_COUNTER_H_
#define _HW_TIMER_COUNTER_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "timer/hw_timer.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef enum {
    HW_TIMER_COUNTER_MODE_UP,
    HW_TIMER_COUNTER_MODE_DOWN,
    HW_TIMER_COUNTER_MODE_CENTER1,
} HW_TIMER_CounterMode;


PUBLIC typedef struct {
    uint32 Frequnecy; // Hz
    HW_TIMER_CounterMode Mode;
    bool EnableUpdateInterrupt;
} HW_TIMER_CounterConfig;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PROTECTED Result HwTimerCounterInit(HW_TIMER_BlockId BlockId, HW_TIMER_ConfigInfo *Config);

PROTECTED Result HwTimerCounterStart(HW_TIMER_BlockId BlockId);

PROTECTED Result HwTimerCounterStop(HW_TIMER_BlockId BlockId);

PROTECTED Result HwTimerCounterReset(HW_TIMER_BlockId BlockId);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_TIMER_COUNTER_H_ */
