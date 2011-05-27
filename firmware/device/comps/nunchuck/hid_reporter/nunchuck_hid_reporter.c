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
PRIVATE HID_MOUSE_REPORT HidReport;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
PROTECTED Result NunchuckHidReporterInit( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);
	HW_TIMER_ConfigInfo timerConfig;
	HW_TIMER_CounterConfig counterConfig;


	ZeroMemory(&HidReport, sizeof(HID_MOUSE_REPORT));


	counterConfig.EnableUpdateInterrupt = TRUE;
	counterConfig.Frequnecy = 1000/COMPOSITE_USB_HID_REPORT_INTERVAL;
	counterConfig.Mode = HW_TIMER_COUNTER_MODE_UP;

	timerConfig.ClkSrc = HW_TIMER_CLK_SRC_INT;
	timerConfig.Mode = HW_TIMER_MODE_COUNTER;
	timerConfig.Type = HW_TIMER_TYPE_GENERAL;
	timerConfig.config = &counterConfig;
	timerConfig.Enable = FALSE;



	if( RESULT_IS_ERROR(result, HW_TIMER_Init(NUNCHUCK_HID_REPORTER_TIMER, &timerConfig)) )
	{
		result = NUNCHUCK_RESULT(TIMER_INIT_FAIL);
	}

	return result;
}


/*****************************************************************************/
PROTECTED Result NunchuckHidReporterEnableReporting( void )
{
	return HW_TIMER_Start(NUNCHUCK_HID_REPORTER_TIMER);
}


/*****************************************************************************/
PROTECTED Result NunchuckHidReporterDisableReporting( void )
{
	return HW_TIMER_Stop(NUNCHUCK_HID_REPORTER_TIMER);
}


/*****************************************************************************/
PUBLIC void NUNCHUCK_HID_REPORTER_SendReport( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);


	if( NunchuckProcessedData.NewDataAvailable )
	{
		HidReport.X = NunchuckProcessedData.Data.Joystick.X;
		HidReport.Y = NunchuckProcessedData.Data.Joystick.Y;

		HidReport.Buttons.Left = NunchuckProcessedData.Data.Buttons.Button.C;
		HidReport.Buttons.Right = NunchuckProcessedData.Data.Buttons.Button.Z;

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
