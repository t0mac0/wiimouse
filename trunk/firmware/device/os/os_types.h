/*!
 * \file os_types.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_TYPES_H_
#define _OS_TYPES_H_

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
PROTECTED typedef Result (OsModuleInitPrototype)( void );
PROTECTED typedef Result (*pOsModuleInitPrototype)( void );


PUBLIC typedef void (OS_TaskProtoType)(void*);
PUBLIC typedef void (*pOS_TaskProtoType)(void*);

PUBLIC typedef void* OS_TaskHandle;
PUBLIC typedef OS_TaskHandle* pOS_TaskHandle;

PUBLIC typedef void* OS_Semaphore;
PUBLIC typedef OS_Semaphore* pOS_Semaphore;

PUBLIC typedef enum {
    OS_SEM_TYPE_MUTEX,
    OS_SEM_TYPE_BINARY,
    OS_SEM_TYPE_COUNT
} OS_SemaphoreType;


PUBLIC typedef void* OS_Timer;
PUBLIC typedef OS_Timer* pOS_Timer;

PUBLIC typedef void OS_TimerCallback(OS_Timer Timer);
PUBLIC typedef void (*pOS_TimerCallback)(OS_Timer Timer);


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_TYPES_H_ */
