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
PRIVATE OS_TaskProtoType HidReportTask;
PRIVATE OS_TaskHandle HidReportTaskHandle;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
PROTECTED Result NunchuckHidReporterInit( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);

	if( RESULT_IS_ERROR(result, OS_TASK_MGR_Add(OS_TASK_NUNCHUCK_HID_REPORT,
			NUNCHUCK_HID_REPORT_TASK_NAME,
			HidReportTask,
			NUNCHUCK_HID_REPORT_STACK_SIZE,
			NUNCHUCK_HID_REPORT_TASK_PRIORITY,
			NULL,
			HidReportTaskHandle)) )
	{
		//LOG_Printf("Failed to create the nunchuck data processor task\n");
	}

	return result;
}


/*****************************************************************************/
PROTECTED Result NunchuckHidReporterEnableReporting( void )
{
	LOG_Printf("NunchuckHidReporterEnableReporting\n");


	return OS_TASK_MGR_Resume(HidReportTaskHandle);
}


/*****************************************************************************/
PROTECTED Result NunchuckHidReporterDisableReporting( void )
{

	return OS_TASK_MGR_Suspend(HidReportTaskHandle);
}


/*****************************************************************************/
PUBLIC void HidReportTask( void *Params )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);
	HID_MOUSE_REPORT HidReport;

	UNUSED(Params);

	//OS_TASK_MGR_Suspend(HidReportTaskHandle);

	for(;;)
	{
		OS_TASK_MGR_Delay(NunchuckSettings.HidReportInterval);

		while( !NunchuckProcessedData.NewDataAvailable );


		HidReport.X = NunchuckProcessedData.Data.Joystick.X;
		HidReport.Y = NunchuckProcessedData.Data.Joystick.Y;

		HidReport.Buttons.Left = NunchuckProcessedData.Data.Buttons.Button.C;
		HidReport.Buttons.Right = NunchuckProcessedData.Data.Buttons.Button.Z;

		LOG_Printf("X: %03d, Y: %03d, C:%d, Z: %d\n", HidReport.X, HidReport.Y, HidReport.Buttons.Left, HidReport.Buttons.Right );

		if( RESULT_IS_ERROR(result, COMPOSITE_USB_SendHidMouseReport(&HidReport)) )
		{
		}

		NunchuckProcessedData.NewDataAvailable = FALSE;

	}


}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
