/*!
 * \file nunchuck_hid_reporter.c
 *
 * \brief 
 *
 *
 * \date May 26, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"


#include "nunchuck_hid_reporter.h"
#include "hw_mgr/timer/hw_timer.h"
#include "composite_usb/composite_usb.h"
#include "nunchuck/com/nunchuck_com.h"
#include "nunchuck/settings/nunchuck_settings.h"
#include "nunchuck/processor/nunchuck_processor.h"


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
PRIVATE OS_Timer reporterTimer;
PRIVATE OS_TimerCallback ReporterTimerCallback;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
PROTECTED Result NunchuckHidReporterInit( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);


	if(RESULT_IS_ERROR(result, OS_CreateTimer(&reporterTimer, NunchuckSettings.HidReportInterval, TRUE, 0, ReporterTimerCallback)) )
	{

	}

	return result;
}


/*****************************************************************************/
PROTECTED Result NunchuckHidReporterEnableReporting( void )
{
	LOG_Printf("NunchuckHidReporterEnableReporting\n");


	return OS_TimerStart(reporterTimer, 0);
}


/*****************************************************************************/
PROTECTED Result NunchuckHidReporterDisableReporting( void )
{
	LOG_Printf("NunchuckHidReporterDisableReporting\n");

	return OS_TimerStop(reporterTimer, 0);
}


/*****************************************************************************/
PUBLIC void ReporterTimerCallback( OS_Timer timer )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);
	HID_MOUSE_REPORT HidReport;

	UNUSED(timer);

	if(NunchuckProcessedData.DataAvailable)
	{

		//LOG_Printf("Reporting\n");


		HidReport.X = NunchuckProcessedData.DataPtr->Joystick.X;
		HidReport.Y = NunchuckProcessedData.DataPtr->Joystick.Y;

		HidReport.Buttons.Left = NunchuckProcessedData.DataPtr->Buttons.Button.C;
		HidReport.Buttons.Right = NunchuckProcessedData.DataPtr->Buttons.Button.Z;

		LOG_Printf("X: %03d, Y: %03d, C:%d, Z: %d\n", HidReport.X, HidReport.Y, HidReport.Buttons.Left, HidReport.Buttons.Right );

		if( RESULT_IS_ERROR(result, COMPOSITE_USB_SendHidMouseReport(&HidReport)) )
		{
		}

		NunchuckProcessedData.DataAvailable = FALSE;
	}
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
