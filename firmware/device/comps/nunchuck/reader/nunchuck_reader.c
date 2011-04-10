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

    NunchuckRawData.TotalDataPtCount = NunchuckSettings.DataPointsPerHidReport*2+1;

    NunchuckRawData.DataPts = (pNunchuckData) AllocMemory(sizeof(NunchuckData)*NunchuckRawData.TotalDataPtCount);
    if( NunchuckRawData.DataPts == NULL )
    {
        return NUNCHUCK_RESULT(MEMORY_ALLOC_FAIL);
    }
    ZeroMemory(NunchuckRawData.DataPts, sizeof(NunchuckData)*NunchuckRawData.TotalDataPtCount);

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


    if( RESULT_IS_SUCCESS(result, NunchuckComReadData(&NunchuckRawData.DataPts[NunchuckRawData.LastPoint])) )
    {
        NunchuckRawData.LastPoint++;
        if( NunchuckRawData.LastPoint == NunchuckRawData.TotalDataPtCount )
            NunchuckRawData.LastPoint = 0;

        NunchuckRawData.NewDataAvailable = TRUE;
    }

}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

