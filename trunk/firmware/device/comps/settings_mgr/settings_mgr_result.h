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
    SETTINGS_MGR_RESULT_WARN                        = RESULT_WARN(0),
    SETTINGS_MGR_RESULT_NO_FREE_SPACE               = RESULT_WARN(1),
    SETTINGS_MGR_RESULT_ENTRY_PROTECTED             = RESULT_WARN(1),

    // errors
    SETTINGS_MGR_RESULT_FAILURE                     = RESULT_ERROR(0),
    SETTINGS_MGR_RESULT_NULL                        = RESULT_ERROR(1),
    SETTINGS_MGR_RESULT_INVALID_ENTRY               = RESULT_ERROR(2),
    SETTINGS_MGR_RESULT_INVALID_DATA_SIZE           = RESULT_ERROR(3),
    SETTINGS_MGR_RESULT_INVALID_FIRST_PAGE          = RESULT_ERROR(4),
    SETTINGS_MGR_RESULT_NO_BLANK_PAGES              = RESULT_ERROR(5),
    SETTINGS_MGR_RESULT_TABLE_FULL                  = RESULT_ERROR(6),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define SETTINGS_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_COMPS, COMPS_SETTINGS_MGR, SETTINGS_MGR_RESULT_##code))

#define SETTINGS_MGR_RESULT_INIT()(SETTINGS_MGR_RESULT(NULL))

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
