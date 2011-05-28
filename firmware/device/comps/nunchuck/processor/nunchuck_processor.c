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


    if( RESULT_IS_ERROR(result, OS_TASK_MGR_AddTask(OS_TASK_NUNCHUCK_DATA_PROCESSOR,
                                                    NUNCHUCK_PROCESSOR_TASK_NAME,
                                                    DataProcessorTask,
                                                    NUNCHUCK_PROCESSOR_STACK_SIZE,
                                                    NUNCHUCK_PROCESSOR_TASK_PRIORITY,
                                                    NULL,
                                                    DataProccessTaskHandle)) )
    {
        LOG_Printf("Failed to create the nunchuck data processor task\n");
    }



    return result;
}


/****************************************************************************/
PROTECTED Result NunchuckProcessorTaskSuspend( void )
{
	return OS_TASK_MGR_SuspendTask(DataProccessTaskHandle);

}


/****************************************************************************/
PROTECTED Result NunchuckProcessorTaskResume( void )
{
	return OS_TASK_MGR_ResumeTask(DataProccessTaskHandle);

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************



/*****************************************************************************/
PRIVATE void DataProcessorTask(void *Params)
{
    UNUSED(Params);

    for(;;)
    {
    	OS_TakeSemaphore(NunchuckRawData.DataAvailableSem, OS_SEM_WAIT_INFINITE);
        {
            NunchuckFilterData();
            NunchuckProcessedData.NewDataAvailable = TRUE;
        }
    }
}
