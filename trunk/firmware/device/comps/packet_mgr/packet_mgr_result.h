/*!
 * \file packet_mgr_result.h
 *
 * \brief 
 *
 *
 * \date Apr 2, 2011
 * \author Dan Riedler
 *
 */

#ifndef _PACKET_MGR_RESULT_H_
#define _PACKET_MGR_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "packet_mgr.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    PACKET_MGR_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    PACKET_MGR_RESULT_WARN = RESULT_WARN(0),

    // errors
    PACKET_MGR_RESULT_FAILURE = RESULT_ERROR(0),
    PACKET_MGR_RESULT_NULL= RESULT_ERROR(0),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define PACKET_MGR_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_COMPS, COMPS_PACKET_MGR, code))

#define PACKET_MGR_RESULT_INIT()(PACKET_MGR_RESULT(PACKET_MGR_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype PACKET_MGR_GetResultCodeStr;
#else
#define PACKET_MGR_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif
/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* PACKET_MGR_RESULT_H_ */
