/*!
 * \file settings_mgr_result.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SETTINGS_MGR_RESULT_H_
#define _SETTINGS_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "settings_mgr.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    SETTINGS_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    SETTINGS_MGR_RESULT_WARN                      = RESULT_WARN(0),

    // errors
    SETTINGS_MGR_RESULT_FAILURE                   = RESULT_ERROR(0),
    SETTINGS_MGR_RESULT_NULL                      = RESULT_ERROR(1),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define SETTINGS_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_COMPS, COMPS_SETTINGS_MGR, code))

#define SETTINGS_MGR_RESULT_INIT()(SETTINGS_MGR_RESULT(SETTINGS_MGR_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype SETTINGS_MGR_GetResultCodeStr;
#else
#define SETTINGS_MGR_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* SETTINGS_MGR_RESULT_H_ */
