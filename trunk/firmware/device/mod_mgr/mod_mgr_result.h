/*!
 * \file mod_mgr_result.h
 *
 * \brief 
 *
 *
 * \date Mar 4, 2011
 * \author Dan Riedler
 *
 */

#ifndef _MOD_MGR_RESULT_H_
#define _MOD_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    MOD_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // errors
    MOD_MGR_RESULT_FAILURE = RESULT_ERROR(0),
    MOD_MGR_RESULT_NULL = RESULT_ERROR(1),
};
/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define MOD_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_MOD_MGR, NULL_MOD, code))

#define MOD_MGR_RESULT_INIT()(MOD_MGR_RESULT(MOD_MGR_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
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
PUBLIC CString MOD_MGR_GetResultCodeStr(
                                        Result result
                                        );
#else
#define MOD_MGR_GetResultCodeStr(x)(NULL)
#endif


#endif /* MOD_MGR_RESULT_H_ */
