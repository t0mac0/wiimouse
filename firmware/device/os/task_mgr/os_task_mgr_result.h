/*!
 * \file os_task_mgr_result.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_TASK_MGR_RESULT_H_
#define _OS_TASK_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os_task_mgr.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    OS_TASK_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    OS_TASK_MGR_RESULT_WARN = RESULT_WARN(0),

    // errors
    OS_TASK_MGR_RESULT_FAILURE = RESULT_ERROR(0),
    OS_TASK_MGR_RESULT_NULL= RESULT_ERROR(1),
    OS_TASK_MGR_RESULT_NOT_ENOUGH_MEM = RESULT_ERROR(2),
    OS_TASK_MGR_RESULT_INVALD_TASK_ID = RESULT_ERROR(3),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#define OS_TASK_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_OS, NULL_MOD, code))

#define OS_TASK_MGR_RESULT_INIT()(OS_TASK_MGR_RESULT(OS_TASK_MGR_RESULT_NULL))

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
PROTECTED GetResutCodeStrPrototype TASK_MGR_GetResultCodeStr;
#else
#define TASK_MGR_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_TASK_MGR_RESULT_H_ */
