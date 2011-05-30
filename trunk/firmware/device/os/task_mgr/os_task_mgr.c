/*!
 * \file os_task_mgr.c
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os_task_mgr.h"

#ifdef OS_MOD_TASK_MGR

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct {
    char Name[OS_TASK_NAME_LEN];
    uint32 StackSize;
    uint32 Priority;
    void* Handle;
} TaskInfo, *pTaskInfo;


/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED inline Result TaskMgrCreateTask( pOS_TaskProtoType StartAddress,
                                           char* Name, uint32 StackSize,
                                           void* Parameter,
                                           OS_TaskPriorities Priority,
                                           pOS_TaskHandle Handle );

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE TaskInfo taskList[OS_TASK_COUNT];


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED Result TASK_MGR_Init( void )
{
    //Result result = HW_MGR_RESULT_INIT();

    LOG_Printf("Initializing TaskMgr\n");

    LOG_RegisterModule(MOD_MGR_OS, OS_TASK_MGR, TRUE);

    ZeroMemory(taskList, sizeof(TaskInfo)*OS_TASK_COUNT);


    return OS_TASK_MGR_RESULT(SUCCESS);
}


/******************************************************************************/
PUBLIC Result OS_TASK_MGR_Add(OS_TaskId Id,
                                  char *Name,
                                  pOS_TaskProtoType StartAddr,
                                  uint32 StackSize,
                                  OS_TaskPriorities Priority,
                                  void *Parameter,
                                  pOS_TaskHandle TaskHandle
)
{
    Result result = OS_TASK_MGR_RESULT_INIT();

    if( Id >= OS_TASK_COUNT )
    {
        result = OS_TASK_MGR_RESULT(INVALD_TASK_ID);
    }
    else if( RESULT_IS_SUCCESS(result, TaskMgrCreateTask(StartAddr, Name, StackSize, Parameter, Priority, TaskHandle)) )
    {
        taskList[Id].Handle = *TaskHandle;
        taskList[Id].Priority = Priority;
        taskList[Id].StackSize = StackSize;
        CopyMemory(taskList[Id].Name, Name, OS_TASK_NAME_LEN);
    }


    return result;
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
