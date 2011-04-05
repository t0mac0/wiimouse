/*!
 * \file hw_i2c_types.h
 *
 * \brief 
 *
 *
 * \date Apr 4, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_I2C_TYPES_H_
#define _HW_I2C_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_mgr.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
// generic I2C defines, depended on
// enabled hardware
PUBLIC typedef enum {
HW_I2C_1,
HW_I2C_2,
HW_I2C_COUNT,
} HW_I2C_BlockId;

PUBLIC typedef enum {
HW_I2C_ACK_ADDR_BIT_7,
HW_I2C_ACK_ADDR_BIT_10,
} HW_I2C_AckAddressBitCount;

PUBLIC typedef enum {
HW_I2C_DUTY_CYCLE_2
} HW_I2C_DutyCyle;

PUBLIC typedef enum {
HW_I2C_MODE_NULL,
HW_I2C_MODE_I2C,
HW_I2C_MODE_COUNT
} HW_I2C_Mode;

PUBLIC typedef struct {
    HW_I2C_Mode Mode;
    bool AckEnable;
    HW_I2C_AckAddressBitCount AckAddrBitCount;
    HW_I2C_DutyCyle DutyCycle;
    uint32 ClockSpeed;
} HW_I2C_ConfigInfo;



/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_I2C_TYPES_H_ */
