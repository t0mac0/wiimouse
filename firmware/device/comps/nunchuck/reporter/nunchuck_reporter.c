/*!
 * \file nunchuck_reporter.c
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
#include "nunchuck_reporter.h"
#include "os.h"
#include "nunchuck/processor/nunchuck_processor.h"
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
PRIVATE OS_TaskProtoType DataReporterTask;


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PROTECTED Result NunchuckReporterInit( void )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);

    ZeroMemory(&NunchuckProcessedData, sizeof(NunchuckProcessedDataInfo));

    if( RESULT_IS_ERROR(result, OS_TASK_MGR_AddTask(OS_TASK_NUNCHUCK_DATA_REPORTER,
                                                    NUNCHUCK_REPORTER_TASK_NAME,
                                                    DataReporterTask,
                                                    NUNCHUCK_REPORTER_STACK_SIZE,
                                                    NUNCHUCK_REPORTER_TASK_PRIORITY,
                                                    NULL)) )
    {
        LOG_Printf("Failed to create the nunchuck data reporter task\n");
    }



    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

//*****************************************************************************//
PRIVATE void DataReporterTask(void *Params)
{
    UNUSED(Params);

    for(;;)
    {
        if( NunchuckProcessedData.PointsProcessed == NunchuckSettings.DataPointsPerHidReport )
        {
            NunchuckProcessedData.PointsProcessed = 0;
        }
    }
}
