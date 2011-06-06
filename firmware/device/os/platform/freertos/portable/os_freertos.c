/*!
 * \file os_freertos.c
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
#include <os_platform.h>
#include "os.h"

#ifdef FREERTOS
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


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//*****************************************************************************//
PUBLIC void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
    /* This function will get called if a task overflows its stack.   If the
    parameters are corrupt then inspect pxCurrentTCB to find which was the
    offending task. */

    ( void ) pxTask;
    ( void ) pcTaskName;

    ASSERT(0);

}


//*****************************************************************************//
PUBLIC inline pVoid AllocMemory( uint32 SizeBytes )
{
    return pvPortMalloc((size_t) SizeBytes);
}


//*****************************************************************************//
PUBLIC inline void FreeMemory( pVoid MemoryPointer )
{
    vPortFree(MemoryPointer);
}


//*****************************************************************************//
PUBLIC Result OS_CreateSemaphore(pOS_Semaphore Semaphore, OS_SemaphoreType SemType, uint32 InitValue, uint32 MaxCount )
{
    Result result = OS_RESULT(SUCCESS);
    xSemaphoreHandle semHandle = NULL;



    switch(SemType)
    {
    case OS_SEM_TYPE_BINARY:
        vSemaphoreCreateBinary( semHandle, InitValue );
        break;

#if configUSE_MUTEXES
    case OS_SEM_TYPE_MUTEX:
        semHandle = xSemaphoreCreateMutex();
        break;
#endif


    case OS_SEM_TYPE_COUNT:
#if configUSE_COUNTING_SEMAPHORES
        semHandle = xSemaphoreCreateCounting( MaxCount, InitValue );
#else
        UNUSED(MaxCount);
        UNUSED(InitValue);
        result = OS_RESULT(SEM_CREATE_FAIL);
#endif
        break;

    default:
        result = OS_RESULT(SEM_CREATE_FAIL);
    }

    if( semHandle != NULL )
    {
        *Semaphore = (OS_Semaphore)semHandle;
    }
    else
    {
        result = OS_RESULT(SEM_CREATE_FAIL);
    }

    return result;
}


//*****************************************************************************//
PUBLIC Result OS_DestroySemaphore(OS_Semaphore Semaphore)
{
    UNUSED(Semaphore);

    return OS_RESULT(SUCCESS);
}


//*****************************************************************************//
PUBLIC Result OS_GiveSemaphore(OS_Semaphore Semaphore)
{
    Result result;

    if( xSemaphoreGive( (xSemaphoreHandle)Semaphore ) )
    {
        result = OS_RESULT(SUCCESS);
    }
    else
    {
        result = OS_RESULT(SEM_GIVE_FAIL);
    }

    return result;
}

//*****************************************************************************//
PUBLIC Result OS_GiveSemaphoreFromIsr(OS_Semaphore Semaphore, bool *HigherPriorityTaskWoken)
{
    Result result;

    if( xSemaphoreGiveFromISR( (xSemaphoreHandle)Semaphore, (long int*)HigherPriorityTaskWoken ) )
    {
        result = OS_RESULT(SUCCESS);
    }
    else
    {
        result = OS_RESULT(SEM_GIVE_FAIL);
    }

    return result;
}


//*****************************************************************************//
PUBLIC Result OS_TakeSemaphore(OS_Semaphore Semaphore, uint32 BlockTime )
{
    Result result;

    //BlockTime = portTICK_RATE_MS(BlockTime);

    if( xSemaphoreTake( (xSemaphoreHandle)Semaphore, BlockTime ) )
    {
        result = OS_RESULT(SUCCESS);
    }
    else
    {
        result = OS_RESULT(SEM_TAKE_FAIL);
    }

    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
