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
PROTECTED NunchuckRawDataInfo NunchuckRawData;
PRIVATE OS_Timer readerTimer;
PRIVATE OS_TimerCallback ReaderTimerCallback;

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PROTECTED Result NunchuckReaderInit( void )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);
	uint32 period;


	ZeroMemory(&NunchuckRawData, sizeof(NunchuckRawDataInfo));

	NunchuckRawData.TotalDataPtCount = NunchuckSettings.DataPointsPerHidReport;

	period = NunchuckSettings.HidReportInterval/NunchuckSettings.DataPointsPerHidReport;
	ASSERT(period);

	NunchuckRawData.DataPts = (pNunchuckData) AllocMemory(sizeof(NunchuckData)*NunchuckRawData.TotalDataPtCount);
	if( NunchuckRawData.DataPts == NULL )
	{
		return NUNCHUCK_RESULT(MEMORY_ALLOC_FAIL);
	}

	if( RESULT_IS_ERROR(result, OS_CreateSemaphore(&NunchuckRawData.DataAvailableSem, OS_SEM_TYPE_BINARY, 0, NULL)) )
	{
		return result;
	}
	else if(RESULT_IS_ERROR(result, OS_CreateTimer(&readerTimer, period, TRUE, 0, ReaderTimerCallback)) )
	{

	}

	return result;
}


/****************************************************************************/
PROTECTED Result NunchuckReaderEnableReading( void )
{
	LOG_Printf("NunchuckReaderEnableReading\n");

	ZeroMemory(NunchuckRawData.DataPts, sizeof(NunchuckData)*NunchuckRawData.TotalDataPtCount);


	return OS_TimerStart(readerTimer, 0);
}


/****************************************************************************/
PROTECTED Result NunchuckReaderDisableReading( void )
{
	LOG_Printf("NunchuckReaderDisableReading\n");

	return OS_TimerStop(readerTimer, 0);
}


/****************************************************************************/
PUBLIC void ReaderTimerCallback( OS_Timer timer )
{
	Result result = NUNCHUCK_RESULT(SUCCESS);

	UNUSED(timer);


	if( RESULT_IS_SUCCESS(result, NunchuckComReadData(&NunchuckRawData.DataPts[NunchuckRawData.NextPoint])) )
	{
		NunchuckRawData.NextPoint++;
		if( NunchuckRawData.NextPoint == NunchuckRawData.TotalDataPtCount )
			NunchuckRawData.NextPoint = 0;

		//LOG_Printf("Nunchuck read\n");
		OS_GIVE_SEM(NunchuckRawData.DataAvailableSem);

	}
	else
	{
		LOG_Printf("Failed to read nunchuck\n");
		NunchuckSmIssueEvent(NUNCHUCK_SM_EVENT_NUNCHUCK_ERROR);
	}

}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

