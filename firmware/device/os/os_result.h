/*!
 * \file os_result.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_RESULT_H_
#define _OS_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    OS_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    OS_RESULT_WARN = RESULT_WARN(0),

    // errors
    OS_RESULT_FAILURE = RESULT_ERROR(0),
    OS_RESULT_NULL= RESULT_ERROR(1),
    OS_RESULT_SEM_INVALID_TYPE= RESULT_ERROR(2),
    OS_RESULT_SEM_CREATE_FAIL = RESULT_ERROR(3),
    OS_RESULT_SEM_TAKE_FAIL = RESULT_ERROR(4),
    OS_RESULT_SEM_GIVE_FAIL = RESULT_ERROR(5),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#define OS_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_OS, NULL_MOD, OS_RESULT_##code))

#define OS_RESULT_INIT()(OS_RESULT(NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*!****************************************************************************
 * /brief Get result code string message
 *
 * This converts a result code to a readable string
 *
 * /param The full result type
 * /return The corresponding readable string describing the result code
 ******************************************************************************/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype OS_GetResultCodeStr;
#else
#define OS_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_RESULT_H_ */
