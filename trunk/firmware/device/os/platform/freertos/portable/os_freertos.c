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


/*****************************************************************************/
PUBLIC void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will get called if a task overflows its stack.   If the
    parameters are corrupt then inspect pxCurrentTCB to find which was the
    offending task. */

	( void ) pxTask;
	( void ) pcTaskName;

	ASSERT(0);

}


/*****************************************************************************/
PUBLIC inline pVoid AllocMemory( uint32 SizeBytes )
{
	return pvPortMalloc((size_t) SizeBytes);
}


/*****************************************************************************/
PUBLIC inline void FreeMemory( pVoid MemoryPointer )
{
	vPortFree(MemoryPointer);
}


/*****************************************************************************/
PUBLIC Result OS_CreateSemaphore(pOS_Semaphore Semaphore, OS_SemaphoreType SemType, uint32 InitValue, uint32 MaxCount )
{
	Result result = OS_RESULT(SUCCESS);
	xSemaphoreHandle semHandle = NULL;



	switch(SemType)
	{
	case OS_SEM_TYPE_BINARY:
		vSemaphoreCreateBinary( semHandle );
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


/*****************************************************************************/
PUBLIC Result OS_DestroySemaphore(OS_Semaphore Semaphore)
{
	UNUSED(Semaphore);

	return OS_RESULT(SUCCESS);
}


/*****************************************************************************/
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

/*****************************************************************************/
PUBLIC Result OS_GiveSemaphoreFromIsr(OS_Semaphore Semaphore, uint32 *HigherPriorityTaskWoken)
{
	Result result;


	*HigherPriorityTaskWoken = 0;

	if( xSemaphoreGiveFromISR( (xSemaphoreHandle)Semaphore, (long*)HigherPriorityTaskWoken) )
	{
		result = OS_RESULT(SUCCESS);
	}
	else
	{
		result = OS_RESULT(SEM_GIVE_FAIL);
	}

	if(*HigherPriorityTaskWoken)
		LOG_Printf("Higher priority taken\n");

	return result;
}


/*****************************************************************************/
PUBLIC Result OS_TakeSemaphore(OS_Semaphore Semaphore, uint32 BlockTime )
{
	Result result;

	if(BlockTime != OS_SEM_WAIT_INFINITE)
		BlockTime = OS_MSToTicks(BlockTime);

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


/*****************************************************************************/
PUBLIC Result OS_CreateTimer(pOS_Timer Timer, uint32 PeriodMs, bool AutoReload, uint32 Id, pOS_TimerCallback TimerCallback)
{
	Result result = OS_RESULT(SUCCESS);
	xTimerHandle timer;
	unsigned portBASE_TYPE reload;

	PeriodMs = OS_MSToTicks(PeriodMs);
	reload = AutoReload ? pdTRUE : pdFALSE;

	if( (timer = xTimerCreate((const signed char*)"T",
			(portTickType)PeriodMs,
			reload,
			(void*)Id,
			(tmrTIMER_CALLBACK)TimerCallback)) == 0 )
	{
		result = OS_RESULT(TIMER_CREATE_FAIL);
	}

	*Timer = timer;

	return result;
}


/*****************************************************************************/
PUBLIC Result OS_TimerStart(OS_Timer Timer, uint32 StallTimeMs)
{
	Result result = OS_RESULT(SUCCESS);

	StallTimeMs = OS_MSToTicks(StallTimeMs);

	if( xTimerStart(Timer, StallTimeMs) == pdFAIL )
	{
		result = OS_RESULT(TIMER_START_FAIL);
	}

	return result;
}


/*****************************************************************************/
PUBLIC Result OS_TimerStop(OS_Timer Timer, uint32 StallTimeMs)
{
	Result result = OS_RESULT(SUCCESS);

	StallTimeMs = OS_MSToTicks(StallTimeMs);

	if( xTimerStop(Timer, StallTimeMs) == pdFAIL )
	{
		result = OS_RESULT(TIMER_STOP_FAIL);
	}

	return result;
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
