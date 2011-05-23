/*!
 * \file nunchuck_com.h
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_COM_H_
#define _NUNCHUCK_COM_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"
#include "nunchuck/profile/nunchuck_profile.h"
#include "hw_mgr/i2c/hw_i2c.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PROTECTED typedef struct {
    uint8 NunchuckSlaveAddr;
    pNunchuckProfileDataFormatter DataFormatter;
} NunchuckComInfo, *pNunchuckComInfo;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result NunchuckComInit( pNunchuckComInfo InitInfo );

PROTECTED Result NunchuckComWrite(uint8 *Data, uint8 NumBytes );

PROTECTED Result NunchuckComReadReg(uint8 Register, uint8 *Buffer, uint8 NumBytes );

PROTECTED Result NunchuckComReadData(pNunchuckData Data);




/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* NUNCHUCK_COM_H_ */
