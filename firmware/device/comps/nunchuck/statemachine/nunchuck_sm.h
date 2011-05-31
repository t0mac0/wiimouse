/*!
 * \file nunchuck_sm.h
 *
 * \brief 
 *
 *
 * \date May 27, 2011
 * \author Dan Riedler
 *
 */
#ifndef _NUNCHUCK_SM_H_
#define _NUNCHUCK_SM_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"
#include "nunchuck_sm_types.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define NUNCHUCK_SM_NAME "NunchukSM"
#define NUNCHUCK_SM_SIZE OS_MIN_STACK_SIZE
#define NUNCHUCK_SM_PRIORITY OS_TASK_PRIORITY_MEDIUM



/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result NunchuckSmInit( void );

PROTECTED void NunchuckSmIssueEvent(NUNCHUCK_SM_Events Event);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern volatile NUNCHUCK_SM_Events NunchuckCurrentEvent;



#endif /* _NUNCHUCK_SM_H_ */
