/*!
 * \file nunchuck_sm_actions.c
 *
 * \brief 
 *
 *
 * \date May 28, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck_sm_actions.h"
#include "nunchuck/processor/nunchuck_processor.h"
#include "nunchuck/ctl/nunchuck_ctl.h"
#include "nunchuck/statemachine/nunchuck_sm.h"

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


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
PROTECTED Result NunchuckActionUsbDisconnected(void)
{
	LOG_Printf("NunchuckActionUsbDisconnected\n");
	NunchuckReaderDisableReading();

	NunchuckHidReporterDisableReporting();

	NunchuckProcessorTaskSuspend();

	//NunchuckPacketCtkTaskSuspend();

	NunchuckCtlDisconnect();

	return NUNCHUCK_RESULT(SUCCESS);
}


/*****************************************************************************/
PROTECTED Result NunchuckActionUsbConnected(void)
{
	LOG_Printf("NunchuckActionUsbConnected\n");
	//NunchuckPacketCtkTaskResume();

	if( (NunchuckCurrentEvent == NUNCHUCK_SM_EVENT_USB_CONNECT) )
	{
		NunchuckSmIssueEvent(NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT);
	}

	return NUNCHUCK_RESULT(SUCCESS);
}


/*****************************************************************************/
PROTECTED Result NunchuckActionNunchuckReconnect(void)
{
	Result result = NUNCHUCK_RESULT(SUCCESS);

	LOG_Printf("NunchuckActionNunchuckReconnect\n");

	if( RESULT_IS_SUCCESS(result, NunchuckCtlConnect()) )
	{
		NunchuckReaderEnableReading();

		NunchuckHidReporterEnableReporting();

		NunchuckProcessorTaskResume();

	}
	else
	{
		if( (NunchuckCurrentEvent == NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT) ||
				(NunchuckCurrentEvent == NUNCHUCK_SM_EVENT_NUNCHUCK_ENABLE) )
		{
			NunchuckSmIssueEvent(NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT);
		}
	}


	return result;
}

//PROTECTED Result NunchuckActionNunchuckConnected(void)
//{
//
//}


/*****************************************************************************/
PROTECTED Result NunchuckActionNunchuckDisonnected(void)
{
	LOG_Printf("NunchuckActionNunchuckDisonnected\n");

	NunchuckHidReporterDisableReporting();

	NunchuckReaderDisableReading();

	NunchuckProcessorTaskSuspend();

	NunchuckCtlDisconnect();

	if( NunchuckCurrentEvent == NUNCHUCK_SM_EVENT_NUNCHUCK_ERROR )
	{
		NunchuckSmIssueEvent(NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT);
	}

	return NUNCHUCK_RESULT(SUCCESS);
}

//PROTECTED NunchuckSmAction NunchuckActionNunchuckDisable;




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
