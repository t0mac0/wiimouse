/*!
 * \file nunchuck_profile.h
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_PROFILE_H_
#define _NUNCHUCK_PROFILE_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define NUNCHUCK_PROFILE_COUNT 1

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PROTECTED typedef uint8 (NunchuckProfileDataFormatterPrototype)(uint8);
PROTECTED typedef uint8 (*pNunchuckProfileDataFormatter)(uint8);


PROTECTED typedef struct
{
    uint32 SlaveAddress;
    pNunchuckProfileDataFormatter DataFormatter;
    bool UseEncryption;
} NunchuckProfileInfo, *pNunchuckProfileInfo;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED NunchuckProfileDataFormatterPrototype NunchuckProfileFormatterXOR_17_Plus17;

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern NunchuckProfileInfo NunchuckProfiles[NUNCHUCK_PROFILE_COUNT];

#endif /* NUNCHUCK_PROFILE_H_ */
