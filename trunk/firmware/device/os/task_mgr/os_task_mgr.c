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
                                           void** Handle );

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

    LOG_RegisterModule(MOD_MGR_OS, OS_TASK_MGR, TRUE);

    ZeroMemory(taskList, sizeof(TaskInfo)*OS_TASK_COUNT);


    return OS_TASK_MGR_RESULT(OS_TASK_MGR_RESULT_SUCCESS);
}


/******************************************************************************/
PUBLIC Result OS_TASK_MGR_AddTask(OS_TaskId Id,
                                  char *Name,
                                  pOS_TaskProtoType StartAddr,
                                  uint32 StackSize,
                                  OS_TaskPriorities Priority,
                                  void *Parameter
)
{
    Result result = OS_TASK_MGR_RESULT_INIT();
    void* Handle;

    if( Id >= OS_TASK_COUNT )
    {
        result = OS_TASK_MGR_RESULT(OS_TASK_MGR_RESULT_INVALD_TASK_ID);
    }
    else if( RESULT_SUCCESS(result, TaskMgrCreateTask(StartAddr, Name, StackSize, Parameter, Priority, &Handle)) )
    {
        taskList[Id].Handle = Handle;
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
