/*!
 * \file nunchuck_hid_reporter.h
 *
 * \brief 
 *
 *
 * \date May 26, 2011
 * \author Dan Riedler
 *
 */
#ifndef _NUNCHUCK_HID_REPORTER_H_
#define _NUNCHUCK_HID_REPORTER_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"
#include "composite_usb/composite_usb.h"

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
PROTECTED Result NunchuckHidReporterInit( void );

PUBLIC void NUNCHUCK_HID_REPORTER_SendReport( void );


PROTECTED Result NunchuckHidReporterEnableReporting( void );

PROTECTED Result NunchuckHidReporterDisableReporting( void );


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* _NUNCHUCK_HID_REPORTER_H_ */
