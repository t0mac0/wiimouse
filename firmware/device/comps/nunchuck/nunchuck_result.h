/*!
 * \file nunchuck_result.h
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_RESULT_H_
#define _NUNCHUCK_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "comps.h"



/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    NUNCHUCK_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    NUNCHUCK_RESULT_WARN                        = RESULT_WARN(0),

    // errors
    NUNCHUCK_RESULT_FAILURE                     = RESULT_ERROR(0),
    NUNCHUCK_RESULT_NULL                        = RESULT_ERROR(1),
    NUNCHUCK_RESULT_MEMORY_ALLOC_FAIL           = RESULT_ERROR(2),
    NUNCHUCK_RESULT_READ_TIMER_INIT_FAIL        = RESULT_ERROR(3),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define NUNCHUCK_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_COMPS, COMPS_NUNCHUCK, NUNCHUCK_RESULT_##code))

#define NUNCHUCK_RESULT_INIT()(NUNCHUCK_RESULT(NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype NUNCHUCK_GetResultCodeStr;
#else
#define NUNCHUCK_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif
/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* NUNCHUCK_RESULT_H_ */
