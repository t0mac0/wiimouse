/*!
 * \file comps_result.h
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPS_RESULT_H_
#define _COMPS_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    COMPS_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // errors
    COMPS_RESULT_FAILURE = RESULT_ERROR(0),
    COMPS_RESULT_NULL = RESULT_ERROR(1),
};
/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define COMPS_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_COMPS, NULL_MOD, COMPS_RESULT_##code))

#define COMPS_RESULT_INIT()(COMPS_RESULT(NULL))

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
PUBLIC CString COMPS_GetResultCodeStr(
                                        Result result
                                        );
#else
#define COMPS_GetResultCodeStr(x)(NULL)
#endif

#endif /* COMPS_RESULT_H_ */
