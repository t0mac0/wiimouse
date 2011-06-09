/*!
 * \file nunchuck_processor.c
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
#include "nunchuck_processor.h"
#include "os.h"
#include "nunchuck/processor/filter/nunchuck_filter.h"


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
PRIVATE OS_TaskProtoType DataProcessorTask;
PRIVATE OS_TaskHandle DataProccessTaskHandle;


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED NunchuckProcessedDataInfo NunchuckProcessedData;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/****************************************************************************/
PROTECTED Result NunchuckProcessorInit( void )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);

    ZeroMemory(&NunchuckProcessedData, sizeof(NunchuckProcessedDataInfo));

    if( RESULT_IS_ERROR(result, OS_TASK_MGR_Add(OS_TASK_NUNCHUCK_DATA_PROCESSOR,
                                                    NUNCHUCK_PROCESSOR_TASK_NAME,
                                                    DataProcessorTask,
                                                    NUNCHUCK_PROCESSOR_STACK_SIZE,
                                                    OS_TASK_PRIORITY_NUNCHUCK_PROCESSOR,
                                                    NULL,
                                                    &DataProccessTaskHandle)) )
    {
        //LOG_Printf("Failed to create the nunchuck data processor task\n");
    }

//	if( RESULT_IS_ERROR(result, OS_CreateSemaphore(&NunchuckProcessedData.DataAvailableSem, OS_SEM_TYPE_BINARY, 0, NULL)) )
//	{
//		return result;
//	}

    return result;
}


/****************************************************************************/
PROTECTED Result NunchuckProcessorTaskSuspend( void )
{
	return OS_TASK_MGR_Suspend(DataProccessTaskHandle);

}


/****************************************************************************/
PROTECTED Result NunchuckProcessorTaskResume( void )
{
	LOG_Printf("NunchuckProcessorTaskResume\n");

	return OS_TASK_MGR_Resume(DataProccessTaskHandle);

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************



/*****************************************************************************/
PRIVATE void DataProcessorTask(void *Params)
{
	int8 newest;
    UNUSED(Params);

    OS_TASK_MGR_Suspend(NULL);

    for(;;)
    {
    	//LOG_Printf("Processor waiting...\n");
    	OS_TAKE_SEM(NunchuckRawData.DataAvailableSem);

    	//LOG_Printf("Processing\n");
        {
            NunchuckFilterData();
            newest = NunchuckRawData.NextPoint - 1;
            if(newest < 0) newest = NunchuckRawData.TotalDataPtCount - 1;
            NunchuckProcessedData.DataPtr = &NunchuckRawData.DataPts[newest];
            NunchuckProcessedData.DataAvailable = TRUE;

        }
    }
}
