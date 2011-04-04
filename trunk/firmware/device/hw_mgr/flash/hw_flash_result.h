/*!
 * \file hw_flash_result.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_FLASH_RESULT_H_
#define _HW_FLASH_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_flash.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    HW_FLASH_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    HW_FLASH_RESULT_WARN = RESULT_WARN(0),

    // errors
    HW_FLASH_RESULT_FAILURE = RESULT_ERROR(0),
    HW_FLASH_RESULT_NULL= RESULT_ERROR(0),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define HW_FLASH_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_HW_MGR, HW_MGR_FLASH, code))

#define HW_FLASH_RESULT_INIT()(HW_FLASH_RESULT(HW_FLASH_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype HW_FLASH_GetResultCodeStr;
#else
#define HW_FLASH_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_FLASH_RESULT_H_ */
