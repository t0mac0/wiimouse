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
	//STATE_USB_CONNECTED,
	STATE_USB_DISCONNECTED,
	STATE_NUNCHUCK_RECONNECT,
	STATE_NUNCHUCK_CONNECTED,
	STATE_NUNCHUCK_DISCONNECTED,
	STATE_NUNCHUCK_DISABLED
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
PROTECTED volatile NUNCHUCK_SM_Events NunchuckCurrentEvent;
PRIVATE StateType currentState;
PRIVATE OS_Semaphore eventSem;



PRIVATE State stateTable[] =
{
//  Event                               Current State        		Next State            			Current State Action
//{ NUNCHUCK_SM_EVENT_USB_DISCONNECT,		STATE_USB_CONNECTED,		STATE_USB_DISCONNECTED,  		NunchuckActionUsbDisconnected 			},
{ NUNCHUCK_SM_EVENT_USB_DISCONNECT,		STATE_NUNCHUCK_RECONNECT,	STATE_USB_DISCONNECTED,  		NunchuckActionUsbDisconnected 			},
{ NUNCHUCK_SM_EVENT_USB_DISCONNECT,		STATE_NUNCHUCK_CONNECTED,	STATE_USB_DISCONNECTED,  		NunchuckActionUsbDisconnected 			},
{ NUNCHUCK_SM_EVENT_USB_DISCONNECT,		STATE_NUNCHUCK_DISCONNECTED,STATE_USB_DISCONNECTED,  		NunchuckActionUsbDisconnected 			},
{ NUNCHUCK_SM_EVENT_USB_DISCONNECT,		STATE_NUNCHUCK_DISABLED,	STATE_USB_DISCONNECTED,  		NunchuckActionUsbDisconnected 			},

{ NUNCHUCK_SM_EVENT_USB_CONNECT,		STATE_USB_DISCONNECTED,		STATE_NUNCHUCK_RECONNECT,  		NunchuckActionUsbConnected 		    	},

{ NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT,	STATE_NUNCHUCK_RECONNECT,	STATE_NUNCHUCK_CONNECTED,  		NunchuckActionNunchuckReconnect 		},
{ NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT,	STATE_NUNCHUCK_DISCONNECTED,STATE_NUNCHUCK_CONNECTED,  		NunchuckActionNunchuckReconnect 		},
{ NUNCHUCK_SM_EVENT_NUNCHUCK_RECONNECT,	STATE_NUNCHUCK_DISABLED,	STATE_NUNCHUCK_CONNECTED,  		NunchuckActionNunchuckReconnect 		},
//{ NUNCHUCK_SM_EVENT_NUNCHUCK_CONNECTED,	STATE_NUNCHUCK_CONNECTED,	STATE_NUNCHUCK_CONNECTED,  		NunchuckActionNunchuckConnected     	},
{ NUNCHUCK_SM_EVENT_NUNCHUCK_ERROR,		STATE_NUNCHUCK_CONNECTED,	STATE_NUNCHUCK_DISCONNECTED,    NunchuckActionNunchuckDisonnected     	},

{ NUNCHUCK_SM_EVENT_NUNCHUCK_DISABLE,	STATE_NUNCHUCK_RECONNECT,	STATE_NUNCHUCK_DISABLED,    	NunchuckActionNunchuckDisonnected     	},
{ NUNCHUCK_SM_EVENT_NUNCHUCK_DISABLE,	STATE_NUNCHUCK_CONNECTED,	STATE_NUNCHUCK_DISABLED,    	NunchuckActionNunchuckDisonnected     	},
{ NUNCHUCK_SM_EVENT_NUNCHUCK_DISABLE,	STATE_NUNCHUCK_DISCONNECTED,STATE_NUNCHUCK_DISABLED,    	NunchuckActionNunchuckDisonnected     	},

{ NUNCHUCK_SM_EVENT_NUNCHUCK_ENABLE,	STATE_NUNCHUCK_DISABLED,	STATE_NUNCHUCK_CONNECTED,    	NunchuckActionNunchuckReconnect     	},

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

    NunchuckCurrentEvent = NUNCHUCK_SM_EVENT_USB_DISCONNECT;
    currentState = STATE_USB_DISCONNECTED;


    if( RESULT_IS_ERROR(result, OS_TASK_MGR_Add(OS_TASK_NUNCHUCK_SM,
    												NUNCHUCK_SM_NAME,
    												NunchuckSmTask,
    												NUNCHUCK_SM_SIZE,
    												OS_TASK_PRIORITY_NUNCHUCK_SM,
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
	//uint32 higherPriorityTaskWoken;

	LOG_Printf("issue event: %d\n", Event);
	NunchuckCurrentEvent = Event;

	OS_GIVE_SEM(eventSem);
	//OS_GiveSemaphoreFromIsr(eventSem, &higherPriorityTaskWoken);
	//OS_TASK_MGR_YieldFromIsr(higherPriorityTaskWoken);
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
    	LOG_Printf("SM waiting...\n");
    	OS_TAKE_SEM(eventSem);

    	LOG_Printf("service event: %d\n", NunchuckCurrentEvent);

    	OS_TASK_MGR_EnterCriticalSection();

		for( i = 0; i < ARRAY_SIZE(stateTable); i++ )
		{
			if( (NunchuckCurrentEvent == stateTable[i].Event) &&
					(currentState == stateTable[i].CurrentState) )
			{
				if( RESULT_IS_SUCCESS(result, stateTable[i].Action()) )
				{
					currentState = stateTable[i].NextState;
				}
				break;
			}
		}

		if( i == ARRAY_SIZE(stateTable))
		{
			LOG_Printf("Warning: event: %d has been ignored\n", NunchuckCurrentEvent);
		}

		OS_TASK_MGR_ExitCriticalSection();
    }
}




















