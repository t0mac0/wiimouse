/*!
 * \file hw_i2c_result.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_I2C_RESULT_H_
#define _HW_I2C_RESULT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_i2c.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
enum {
    HW_I2C_RESULT_SUCCESS = RESULT_SEVERITY_SUCCESS,

    // warnings
    HW_I2C_RESULT_WARN                              = RESULT_WARN(0),

    // errors
    HW_I2C_RESULT_FAILURE                           = RESULT_ERROR(0),
    HW_I2C_RESULT_NULL                              = RESULT_ERROR(1),
    HW_I2C_RESULT_BUS_TIMEOUT                       = RESULT_ERROR(2),
    HW_I2C_RESULT_MASTER_MODE_SELECT_TIMEOUT        = RESULT_ERROR(3),
    HW_I2C_RESULT_MASTER_TRANSMIITER_SELECT_TIMEOUT = RESULT_ERROR(4),
    HW_I2C_RESULT_SET_REGISTER_TIMEOUT              = RESULT_ERROR(5),
    HW_I2C_RESULT_RECEIVER_MODE_SELECT_TIMEOUT      = RESULT_ERROR(6),
    HW_I2C_RESULT_RECEIVE_TIMEOUT                   = RESULT_ERROR(7),
    HW_I2C_RESULT_TRANSMIT_TIMEOUT                  = RESULT_ERROR(8),
};

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define HW_I2C_RESULT(code)( RESULT(GET_CURRENT_TASK_ID(), MOD_MGR_HW_MGR, HW_MGR_I2C, code))

#define HW_I2C_RESULT_INIT()(HW_I2C_RESULT(HW_I2C_RESULT_NULL))

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#ifdef DEBUG
PUBLIC GetResutCodeStrPrototype HW_I2C_GetResultCodeStr;
#else
#define HW_I2C_GetResultCodeStr(x)((pGetResutCodeStrPrototype)NULL)
#endif

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_I2C_RESULT_H_ */
