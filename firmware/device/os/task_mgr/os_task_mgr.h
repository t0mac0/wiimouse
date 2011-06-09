/*!
 * \file os_task_mgr.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_TASK_MGR_H_
#define _OS_TASK_MGR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"
#include "os_task_mgr_result.h"
#include "os_tasks.h"
#include "os_types.h"

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
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED OsModuleInitPrototype TASK_MGR_Init;

PUBLIC inline Result OS_TASK_MGR_StartScheduler( void );

PUBLIC Result OS_TASK_MGR_Add(OS_TaskId Id,
                                  char *Name,
                                  pOS_TaskProtoType StartAddr,
                                  uint32 StackSize,
                                  OS_TaskPriorities Priority,
                                  void *Parameter,
                                  pOS_TaskHandle TaskHandle
                                  );

PUBLIC inline Result OS_TASK_MGR_Suspend(OS_TaskHandle Handle);

PUBLIC inline Result OS_TASK_MGR_Resume(OS_TaskHandle Handle);

PUBLIC inline Result OS_TASK_MGR_Delay( uint32 TimeMs );

PUBLIC inline void OS_TASK_MGR_YieldFromIsr( bool shouldYield );

PUBLIC inline void OS_TASK_MGR_EnterCriticalSection( void );

PUBLIC inline void OS_TASK_MGR_ExitCriticalSection( void );

/*----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_TASK_MGR_H_ */
