/*!
 * \file hw_timer_result.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_TIMER_RESULT_H_
#define _HW_TIMER_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_timer.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    HW_TIMER_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    HW_TIMER_RESULT_WARN                = RESULT_WARN(0),

    // errors
    HW_TIMER_RESULT_FAILURE             = RESULT_ERROR(0),
    HW_TIMER_RESULT_NULL                = RESULT_ERROR(1),
    HW_TIMER_RESULT_BAD_FREQ            = RESULT_ERROR(2),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define HW_TIMER_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_HW_MGR, HW_MGR_USART, HW_TIMER_RESULT_##code))

#define HW_TIMER_RESULT_INIT()(HW_TIMER_RESULT(NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype HW_TIMER_GetResultCodeStr;
#else
#define HW_TIMER_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_TIMER_RESULT_H_ */
