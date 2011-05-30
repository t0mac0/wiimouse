/*!
 * \file os.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_H_
#define _OS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "os_modules.h"
#include "os_result.h"
#include "os_types.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define OS_SEM_WAIT_INFINITE 0xffffffff

#define OS_CREATE_MUTEX(_sem) OS_CreateSemaphore(_sem, OS_SEM_TYPE_MUTEX, 0, 0)
#define OS_TAKE_MUTEX(_sem) OS_TakeSemaphore(_sem, OS_SEM_WAIT_INFINITE)
#define OS_GIVE_MUTEX(_sem) OS_GiveSemaphore(_sem)

#define OS_GIVE_SEM(_sem) OS_GiveSemaphore(_sem)
#define OS_TAKE_SEM(_sem) OS_TakeSemaphore(_sem, OS_SEM_WAIT_INFINITE)


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
/*!****************************************************************************
 * /brief Hardware Initialization
 *
 * This initializes all hardware based on the hardware configuration.
 *
 * /param
 * /return
 ******************************************************************************/
PUBLIC ModuleInitPrototype OS_Init;

// TODO: move these to sem_mgr
PUBLIC Result OS_CreateSemaphore(pOS_Semaphore Semaphore, OS_SemaphoreType SemType, uint32 InitValue, uint32 MaxCount );

PUBLIC Result OS_DestroySemaphore(OS_Semaphore Semaphore);

PUBLIC Result OS_GiveSemaphore(OS_Semaphore Semaphore);

PUBLIC Result OS_TakeSemaphore(OS_Semaphore Semaphore, uint32 BlockTime );

PUBLIC Result OS_GiveSemaphoreFromIsr(OS_Semaphore Semaphore, bool *HigherPriorityTaskWoken);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_H_ */
