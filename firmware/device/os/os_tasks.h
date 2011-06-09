/*!
 * \file os_tasks.h
 *
 * \brief 
 *
 *
 * \date Mar 8, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_TASKS_H_
#define _OS_TASKS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef enum {
    OS_TASK_IDLE,
    OS_TASK_PACKET_MGR,
    OS_TASK_NUNCHUCK_DATA_PROCESSOR,
    OS_TASK_NUNCHUCK_SM,
    OS_TASK_COUNT
} OS_TaskId;


// lowest number == lowest priority
PUBLIC typedef enum {
    OS_TASK_PRIORITY_IDLE  					= 0,
    OS_TASK_PRIORITY_NUNCHUCK_PROCESSOR		= 2,
    OS_TASK_PRIORITY_PACKET_MGR				= 0,
    OS_TASK_PRIORITY_NUNCHUCK_SM 			= 4,
    OS_TASK_PRIORITY_HIGHEST 				= (OS_MAX_PRIORITIES-1),
} OS_TaskPriorities;

#if(OS_TASK_PRIORITY_HIGHEST > OS_MAX_PRIORITIES)
#error OS_TASK_PRIORITY_HIGHEST > OS_MAX_PRIORITIES
#endif
/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_TASKS_H_ */
