/*!
 * \file nunchuck_reader.c
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
#include "nunchuck_reader.h"
#include "hw_mgr/timer/hw_timer.h"
#include "composite_usb/composite_usb.h"
#include "nunchuck/com/nunchuck_com.h"
#include "nunchuck/settings/nunchuck_settings.h"

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
PROTECTED NunchuckRawDataInfo NunchuckRawData;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PROTECTED Result NunchuckReaderInit( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);
	HW_TIMER_ConfigInfo timerConfig;
	HW_TIMER_CounterConfig counterConfig;


	ZeroMemory(&NunchuckRawData, sizeof(NunchuckRawDataInfo));

	NunchuckRawData.TotalDataPtCount = NunchuckSettings.DataPointsPerHidReport;

	NunchuckRawData.DataPts = (pNunchuckData) AllocMemory(sizeof(NunchuckData)*NunchuckRawData.TotalDataPtCount);
	if( NunchuckRawData.DataPts == NULL )
	{
		return NUNCHUCK_RESULT(MEMORY_ALLOC_FAIL);
	}
	ZeroMemory(NunchuckRawData.DataPts, sizeof(NunchuckData)*NunchuckRawData.TotalDataPtCount);

	if( RESULT_IS_ERROR(result, OS_CreateSemaphore(&NunchuckRawData.DataAvailableSem, OS_SEM_TYPE_BINARY, 0, 1)) )
	{
		return result;
	}

	counterConfig.EnableUpdateInterrupt = TRUE;
	counterConfig.Frequnecy = (NunchuckSettings.DataPointsPerHidReport*1000)/COMPOSITE_USB_HID_REPORT_INTERVAL;
	counterConfig.Mode = HW_TIMER_COUNTER_MODE_UP;

	timerConfig.ClkSrc = HW_TIMER_CLK_SRC_INT;
	timerConfig.Mode = HW_TIMER_MODE_COUNTER;
	timerConfig.Type = HW_TIMER_TYPE_GENERAL;
	timerConfig.config = &counterConfig;
	timerConfig.Enable = FALSE;



	if( RESULT_IS_ERROR(result, HW_TIMER_Init(NUNCHUCK_READ_TIMER, &timerConfig)) )
	{
		result = NUNCHUCK_RESULT(READ_TIMER_INIT_FAIL);
	}

	return result;
}


//****************************************************************************/
PUBLIC void NUNCHUCK_READER_ReadDataPoint( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);
	bool higherPriorityTaskWoken;


	if( RESULT_IS_SUCCESS(result, NunchuckComReadData(&NunchuckRawData.DataPts[NunchuckRawData.NextPoint])) )
	{
		NunchuckRawData.NextPoint++;
		if( NunchuckRawData.NextPoint == NunchuckRawData.TotalDataPtCount )
			NunchuckRawData.NextPoint = 0;

		if( RESULT_IS_ERROR(result, OS_GiveSemaphoreFromIsr(NunchuckRawData.DataAvailableSem, &higherPriorityTaskWoken)) )
		{

		}
	}

}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

