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
PROTECTED Result NunchuckActionNull(void)
{
	return NUNCHUCK_RESULT(SUCCESS);
}


/*****************************************************************************/
PROTECTED Result NunchuckActionDisable(void)
{

	NunchuckHidReporterDisableReporting();

	NunchuckReaderDisableReading();

	NunchuckProcessorTaskSuspend();

	NunchuckCtlDisconnect();

	return NUNCHUCK_RESULT(SUCCESS);
}


/*****************************************************************************/
PROTECTED Result NunchuckActionConnect(void)
{
	Result result = NUNCHUCK_RESULT(SUCCESS);


	if( RESULT_IS_SUCCESS(result, NunchuckCtlConnect()) )
	{
		NunchuckReaderEnableReading();

		NunchuckHidReporterEnableReporting();

		NunchuckProcessorTaskResume();

	}
	else
	{
		NunchuckTryReconnect = TRUE;
	}


	return result;
}


/*****************************************************************************/
PROTECTED Result NunchuckActionDisconnect(void)
{
	NunchuckHidReporterDisableReporting();

	NunchuckReaderDisableReading();

	NunchuckProcessorTaskSuspend();

	NunchuckCtlDisconnect();

	// attempt to reinitialize if uninitialized
	if( NunchuckCurrentEvent == NUNCHUCK_SM_EVENT_UNINITIALIZE )
	{
		NunchuckCurrentEvent = NUNCHUCK_SM_EVENT_INITIALIZE;
		NunchuckTryReconnect = TRUE;
	}

	return NUNCHUCK_RESULT(SUCCESS);
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
