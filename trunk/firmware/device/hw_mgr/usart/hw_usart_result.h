/*!
 * \file hw_usart_result.h
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USART_RESULT_H_
#define _HW_USART_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_usart.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    HW_USART_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    HW_USART_RESULT_WARN = RESULT_WARN(0),

    // errors
    HW_USART_RESULT_FAILURE = RESULT_ERROR(0),
    HW_USART_RESULT_NULL= RESULT_ERROR(0),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define HW_USART_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_HW_MGR, HW_MGR_USART, code))

#define HW_USART_RESULT_INIT()(HW_USART_RESULT(HW_USART_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype HW_USART_GetResultCodeStr;
#else
#define HW_USART_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_USART_RESULT_H_ */
