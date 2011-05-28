/*!
 * \file nunchuck_sm.c
 *
 * \brief 
 *
 *
 * \date May 27, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"

#include "nunchuck_sm.h"
#include "nunchuck/statemachine/actions/nunchuck_sm_actions.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef enum {
	STATE_DISABLED,
	STATE_CONNECTED,
	STATE_DISCONNECTED,
} StateType;


typedef struct {
	NUNCHUCK_SM_Events Event;
    StateType CurrentState;
    StateType NextState;
    pNunchuckSmAction Action;
} State;


/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE OS_TaskProtoType NunchuckSmTask;
PRIVATE OS_TaskHandle NunchuckSmTaskHandle;



/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED bool NunchuckTryReconnect;

PRIVATE StateType currentState;
PRIVATE OS_Semaphore eventSem;
PRIVATE NUNCHUCK_SM_Events currentEvent;


PRIVATE State stateTable[] =
{
        //  Event                               Current State                       Next State                          Current State Action
        { NUNCHUCK_SM_EVENT_DISABLE,            STATE_DISABLED,                     STATE_DISABLED,               	    NunchuckActionNull                          },
        { NUNCHUCK_SM_EVENT_DISABLE,            STATE_CONNECTED,                    STATE_DISABLED,               	    NunchuckActionDisable                       },
        { NUNCHUCK_SM_EVENT_DISABLE,            STATE_DISCONNECTED,                 STATE_DISABLED,               	    NunchuckActionDisable                       },

        { NUNCHUCK_SM_EVENT_ENABLE,             STATE_DISABLED,                     STATE_CONNECTED,                    NunchuckActionConnect                       },
        { NUNCHUCK_SM_EVENT_ENABLE,             STATE_CONNECTED,                    STATE_CONNECTED,                    NunchuckActionNull                          },
        { NUNCHUCK_SM_EVENT_ENABLE,             STATE_DISCONNECTED,                 STATE_CONNECTED,                    NunchuckActionConnect                       },

        { NUNCHUCK_SM_EVENT_UNINITIALIZE,       STATE_DISABLED,                     STATE_DISABLED,                     NunchuckActionNull                          },
        { NUNCHUCK_SM_EVENT_UNINITIALIZE,       STATE_CONNECTED,                    STATE_DISCONNECTED,                 NunchuckActionDisconnect                    },
        { NUNCHUCK_SM_EVENT_UNINITIALIZE,       STATE_DISCONNECTED,                 STATE_DISCONNECTED,                 NunchuckActionNull                          },

        { NUNCHUCK_SM_EVENT_INITIALIZE,         STATE_DISABLED,                     STATE_DISABLED,                     NunchuckActionNull                          },
        { NUNCHUCK_SM_EVENT_INITIALIZE,         STATE_CONNECTED,                    STATE_CONNECTED,                    NunchuckActionNull                          },
        { NUNCHUCK_SM_EVENT_INITIALIZE,         STATE_DISCONNECTED,                 STATE_CONNECTED,                    NunchuckActionConnect                       },

};


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
PROTECTED Result NunchuckSmInit( void )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);

    currentEvent = NUNCHUCK_SM_EVENT_DISABLE;
    currentState = STATE_DISABLED;
    NunchuckTryReconnect = FALSE;


    if( RESULT_IS_ERROR(result, OS_TASK_MGR_AddTask(OS_TASK_NUNCHUCK_SM,
    												NUNCHUCK_SM_NAME,
    												NunchuckSmTask,
    												NUNCHUCK_SM_SIZE,
    												NUNCHUCK_SM_PRIORITY,
                                                    NULL,
                                                    &NunchuckSmTaskHandle)) )
    {
        LOG_Printf("Failed to create the nunchuck statemachine task\n");
    }
    else if( RESULT_IS_ERROR(result, OS_CreateSemaphore(&eventSem, OS_SEM_TYPE_BINARY, 0, 0)) )
    {
    }



    return result;
}


/*****************************************************************************/
PROTECTED void NunchuckSmIssueEvent(NUNCHUCK_SM_Events Event)
{
	currentEvent = Event;
	OS_GIVE_SEM(eventSem);
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

/*****************************************************************************/
PRIVATE void NunchuckSmTask(void *Params)
{
	Result result;
	uint32 i;


    UNUSED(Params);

    for(;;)
    {
    	if( !NunchuckTryReconnect )
    		OS_TAKE_SEM(eventSem);

    	NunchuckTryReconnect = FALSE;

	    for( i = 0; i < ARRAY_SIZE(stateTable); i++ )
		{
			if( (currentEvent == stateTable[i].Event) &&
					(currentState == stateTable[i].CurrentState) )
			{
				if( RESULT_IS_SUCCESS(result, stateTable[i].Action()) )
				{
					currentState = stateTable[i].NextState;
				}
				break;
			}
		}

	   ASSERT( i != ARRAY_SIZE(stateTable));
    }
}




















