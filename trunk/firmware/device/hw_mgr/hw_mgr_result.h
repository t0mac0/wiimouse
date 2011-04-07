/*!
 * \file hw_result.h
 *
 * \brief 
 *
 *
 * \date Mar 4, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_MGR_RESULT_H_
#define _HW_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_mgr.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    HW_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    HW_MGR_RESULT_WARN = RESULT_WARN(0),

    // errors
    HW_MGR_RESULT_FAILURE               = RESULT_ERROR(0),
    HW_MGR_RESULT_NULL                  = RESULT_ERROR(1),
    HW_MGR_RESULT_USB_INIT_FAIL         = RESULT_ERROR(1),
};


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#define HW_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_HW_MGR, NULL_MOD, HW_MGR_RESULT_##code))

#define HW_MGR_RESULT_INIT()(HW_MGR_RESULT(NULL))

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
PUBLIC GetResutCodeStrPrototype HW_MGR_GetResultCodeStr;
#else
#define HW_MGR_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_RESULT_H_ */
