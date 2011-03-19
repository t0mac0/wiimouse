/*!
 * \file hw_usb_result.h
 *
 * \brief 
 *
 *
 * \date Mar 16, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_RESULT_H_
#define _HW_USB_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_usb.h"



/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    HW_USB_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    HW_USB_RESULT_WARN = RESULT_WARN(0),

    // errors
    HW_USB_RESULT_FAILURE = RESULT_ERROR(0),
    HW_USB_RESULT_NULL= RESULT_ERROR(0),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define HW_USB_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_HW_MGR, HW_MGR_USB, code))

#define HW_USB_RESULT_INIT()(HW_USB_RESULT(HW_USB_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype HW_USB_GetResultCodeStr;
#else
#define HW_USB_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_USB_RESULT_H_ */
