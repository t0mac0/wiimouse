/*!
 * \file os_evnt_mgr_result.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_EVNT_MGR_RESULT_H_
#define _OS_EVNT_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os_evnt_mgr.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    OS_EVNT_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    OS_EVNT_MGR_RESULT_WARN = RESULT_WARN(0),
    OS_EVNT_MGR_RESULT_NO_LISTENERS = RESULT_WARN(1),

    // errors
    OS_EVNT_MGR_RESULT_FAILURE = RESULT_ERROR(0),
    OS_EVNT_MGR_RESULT_NULL= RESULT_ERROR(1),
    OS_EVNT_MGR_RESULT_INVALID_EVENT_ID = RESULT_ERROR(2),
    OS_EVNT_MGR_RESULT_CREATE_EVENT_LIST_FAIL = RESULT_ERROR(3),
    OS_EVNT_MGR_RESULT_ADD_EVENT_TO_LIST_FAIL = RESULT_ERROR(4),
    OS_EVNT_MGR_RESULT_NULL_LISTENER = RESULT_ERROR(5),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#define OS_EVNT_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_OS, NULL_MOD, code))

#define OS_EVNT_MGR_RESULT_INIT()(OS_EVNT_MGR_RESULT(OS_EVNT_MGR_RESULT_NULL))

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
PROTECTED GetResutCodeStrPrototype EVNT_MGR_GetResultCodeStr;
#else
#define EVNT_MGR_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_EVNT_MGR_RESULT_H_ */
