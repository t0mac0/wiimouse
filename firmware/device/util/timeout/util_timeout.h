/*!
 * \file util_timeout.h
 *
 * \brief 
 *
 *
 * \date Apr 4, 2011
 * \author Dan Riedler
 *
 */

#ifndef _UTIL_TIMEOUT_H_
#define _UTIL_TIMEOUT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "util/timer/util_timer.h"

#ifdef DEV_UTIL_TIMEOUT


#ifndef DEV_UTIL_TIMER
#error The timer utility should be enabled to use the Timeout Utility
#endif

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define UTIL_TIMEOUT_INIT(_timer, _timeoutval)          \
{                                                       \
    _timer = UTIL_TIMER_Ticker + _timeoutval;           \
}

#define UTIL_TIMEOUT_TIMED_OUT(_timer) ( UTIL_TIMER_Ticker -  _timer >= 0 )

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef UTIL_TIMER_Timer UTIL_TIMEOUT_Timer;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/

#endif
#endif /* UTIL_TIMEOUT_H_ */
