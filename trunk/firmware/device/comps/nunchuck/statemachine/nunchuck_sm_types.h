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
	NUNCHUCK_SM_EVENT_NUNCHUCK_ENABLE,
	NUNCHUCK_SM_EVENT_NUNCHUCK_DISABLE,
	NUNCHUCK_SM_EVENT_NUNCHUCK_ERROR,
	NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT,
	NUNCHUCK_SM_EVENT_NUNCHUCK_CONNECTED,
	NUNCHUCK_SM_EVENT_USB_CONNECT,
	NUNCHUCK_SM_EVENT_USB_DISCONNECT,
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
