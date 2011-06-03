/*!
 * \file nunchuck.c
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck.h"
#include "nunchuck/settings/nunchuck_settings.h"
#include "nunchuck/processor/nunchuck_processor.h"
#include "nunchuck/statemachine/nunchuck_sm.h"
#include "nunchuck/ctl/nunchuck_ctl.h"

#include "hw_mgr/usb/hw_usb.h"


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
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE HW_USB_StateChangeCallback usbStateChangeCallback;



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PUBLIC Result NUNCHUCK_Init( void )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);


    LOG_Printf("Initializing Nunchuck Component\n");



    if( RESULT_IS_ERROR(result, NunchuckSettingsInit()) )
    {
    }
    else if( RESULT_IS_ERROR(result, NunchuckReaderInit()) )
	{
	}
	else if( RESULT_IS_ERROR(result, NunchuckProcessorInit()) )
	{
	}
	else if( RESULT_IS_ERROR(result, NunchuckHidReporterInit()) )
	{
	}
	else if( RESULT_IS_ERROR(result, NunchuckCtlInit()) )
	{
	}
	else if( RESULT_IS_ERROR(result, NunchuckSmInit()) )
	{
	}
    // REVISIT: this shoud be in composite_usb component
	else if( RESULT_IS_ERROR(result, HW_USB_RegisterStateChangeCallback(usbStateChangeCallback)) )
	{
	}


    return result;
}


//****************************************************************************/
PUBLIC Result NUNCHUCK_PowerUp( void )
{
    Result result = NUNCHUCK_RESULT_INIT();

    return result;
}


//****************************************************************************/
PUBLIC Result NUNCHUCK_PowerDown( void )
{
    Result result = NUNCHUCK_RESULT_INIT();

    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

PRIVATE void usbStateChangeCallback(HW_USB_StateType State)
{
	switch(State)
	{
	case HW_USB_STATE_UNCONNECTED:
	case HW_USB_STATE_SUSPENDED:
		NunchuckSmIssueEvent(NUNCHUCK_SM_EVENT_USB_DISCONNECT);
		break;
	case HW_USB_STATE_CONFIGURED:
		NunchuckSmIssueEvent(NUNCHUCK_SM_EVENT_USB_CONNECT);
		break;
	default:
		break;
	}

	LOG_Printf("Usb State Change: %d\n", State);
}

