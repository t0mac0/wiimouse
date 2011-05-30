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
#include "nunchuck/ctl/nunchuck_ctl.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PROTECTED typedef struct
{
    uint8 SlaveAddress;
    pNunchuckProfileDataFormatter DataFormatter;
} NunchuckComInfo, *pNunchuckComInfo;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result NunchuckComInit( pNunchuckComInfo ComInfo );

PROTECTED Result NunchuckComDeInit( void );

PROTECTED Result NunchuckComWrite(uint8 *Data, uint8 NumBytes );

PROTECTED Result NunchuckComReadReg(uint8 Register, uint8 *Buffer, uint8 NumBytes );

PROTECTED Result NunchuckComReadData(pNunchuckData Data);

PROTECTED Result NunchuckComReadCalibration(pNunchuckCtlCalibration Calibration);

PROTECTED Result NunchuckComEnableEncryption( void );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* NUNCHUCK_COM_H_ */
