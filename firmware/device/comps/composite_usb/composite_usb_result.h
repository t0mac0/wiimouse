/*!
 * \file composite_usb_result.h
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPOSITE_USB_RESULT_H_
#define _COMPOSITE_USB_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "composite_usb.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    COMPOSITE_USB_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    COMPOSITE_USB_RESULT_WARN = RESULT_WARN(0),

    // errors
    COMPOSITE_USB_RESULT_FAILURE = RESULT_ERROR(0),
    COMPOSITE_USB_RESULT_NULL= RESULT_ERROR(0),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define COMPOSITE_USB_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_COMPS, COMPS_COMPOSITE_USB, code))

#define COMPOSITE_USB_RESULT_INIT()(COMPOSITE_USB_RESULT(COMPOSITE_USB_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype COMPOSITE_USB_GetResultCodeStr;
#else
#define COMPOSITE_USB_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* COMPOSITE_USB_RESULT_H_ */
