/*!
 * \file nunchuck_sm_actions.h
 *
 * \brief 
 *
 *
 * \date May 27, 2011
 * \author Dan Riedler
 *
 */
#ifndef _NUNCHUCK_SM_ACTIONS_H_
#define _NUNCHUCK_SM_ACTIONS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"
#include "nunchuck/statemachine/nunchuck_sm_types.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PROTECTED NunchuckSmAction NunchuckActionUsbDisconnected;

PROTECTED NunchuckSmAction NunchuckActionUsbConnected;

PROTECTED NunchuckSmAction NunchuckActionNunchuckReconnect;

PROTECTED NunchuckSmAction NunchuckActionNunchuckConnected;

PROTECTED NunchuckSmAction NunchuckActionNunchuckDisonnected;

PROTECTED NunchuckSmAction NunchuckActionNunchuckDisable;


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/



#endif /* _NUNCHUCK_SM_ACTIONS_H_ */
