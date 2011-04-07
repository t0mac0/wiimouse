/*!
 * \file os_mem_mgr_result.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_MEM_MGR_RESULT_H_
#define _OS_MEM_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os_mem_mgr.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    OS_MEM_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    OS_MEM_MGR_RESULT_WARN = RESULT_WARN(0),

    // errors
    OS_MEM_MGR_RESULT_FAILURE = RESULT_ERROR(0),
    OS_MEM_MGR_RESULT_NULL= RESULT_ERROR(0),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#define OS_MEM_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_OS, NULL_MOD, OS_MEM_MGR_RESULT_##code))

#define OS_MEM_MGR_RESULT_INIT()(OS_MEM_MGR_RESULT(NULL))

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
PROTECTED GetResutCodeStrPrototype MEM_MGR_GetResultCodeStr;
#else
#define MEM_MGR_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_MEM_MGR_RESULT_H_ */
