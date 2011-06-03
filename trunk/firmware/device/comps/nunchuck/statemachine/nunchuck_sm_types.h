/*!
 * \file nunchuck_sm_types.h
 *
 * \brief 
 *
 *
 * \date May 27, 2011
 * \author Dan Riedler
 *
 */
#ifndef _NUNCHUCK_SM_TYPES_H_
#define _NUNCHUCK_SM_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "comps.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef enum
{
	NUNCHUCK_SM_EVENT_NUNCHUCK_ENABLE				= 0,
	NUNCHUCK_SM_EVENT_NUNCHUCK_DISABLE				= 1,
	NUNCHUCK_SM_EVENT_NUNCHUCK_ERROR				= 2,
	NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT			= 3,
	NUNCHUCK_SM_EVENT_NUNCHUCK_CONNECTED			= 4,
	NUNCHUCK_SM_EVENT_USB_CONNECT					= 5,
	NUNCHUCK_SM_EVENT_USB_DISCONNECT				= 6,
} NUNCHUCK_SM_Events;



PROTECTED typedef Result (*pNunchuckSmAction)(void);
PROTECTED typedef Result (NunchuckSmAction)(void);

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/



#endif /* _NUNCHUCK_SM_TYPES_H_ */
