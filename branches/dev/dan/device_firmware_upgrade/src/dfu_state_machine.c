/*
 * dfu_state_machine.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "dfu_state_machine.h"
#include "dfu_actions.h"
#include "dfu_com.h"
#include "printf.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
typedef enum _StateType {
	DFU_STATE_WAITING,
	DFU_STATE_INITIALIZE_UPDATE,
	DFU_STATE_BEGIN_UPDATE,
	DFU_STATE_START_SECTION_UPDATE,
	DFU_STATE_SECTION_UPDATE,
	DFU_STATE_END_SECTION_UPDATE,
	DFU_STATE_END_UPDATE,
	DFU_STATE_BEGIN_VALIDATION,
	DFU_STATE_START_SECTION_VALIDATION,
	DFU_STATE_VALIDATE_SECTION,
	DFU_STATE_END_SECTION_VALIDATION,
	DFU_STATE_END_VALIDATION,
	DFU_STATE_COMPLETE_UPDATE,
	DFU_STATE_NULL = 0xFF
} StateType;


typedef struct _State {
	DFU_CommandType Command;
	StateType CurrentState;
	StateType NextState;
	dfu_Action Action;
} State;

static StateType currentState;
static dfu_Action transitionOverrideAction;

static State stateTable[] =
{
		//  Command								Current State						Next State							Current State Action
		{ DFU_CMD_QUERY_DEVICE, 			    DFU_STATE_WAITING, 					DFU_CMD_QUERY_DEVICE, 		        dfu_ActionQueryDevice    					},
		{ DFU_CMD_INITIALIZE_UPDATE, 			DFU_STATE_WAITING, 					DFU_STATE_INITIALIZE_UPDATE, 		dfu_ActionInitializeUpdate 					},

		// Update Sequence
		{ DFU_CMD_BEGIN_UPDATE, 				DFU_STATE_WAITING, 	            	DFU_STATE_BEGIN_UPDATE, 			dfu_ActionBeginUpdate 						},
		{ DFU_CMD_START_SECTION_UPDATE, 		DFU_STATE_BEGIN_UPDATE, 	    	DFU_STATE_START_SECTION_UPDATE, 	dfu_ActionStartSectionUpdate 			    },
		//{ DFU_CMD_SECTION_UPDATE, 		        DFU_STATE_START_SECTION_UPDATE, 	DFU_STATE_SECTION_UPDATE, 	        dfu_ActionSectionUpdate 	                },
		{ DFU_CMD_NULL, 		                DFU_STATE_SECTION_UPDATE, 	    	DFU_STATE_NULL, 	                dfu_ActionSectionUpdate 	                },
		{ DFU_CMD_END_SECTION_UPDATE, 		    DFU_STATE_SECTION_UPDATE, 	    	DFU_STATE_END_SECTION_UPDATE, 	    dfu_ActionEndSectionUpdate 	                },
		{ DFU_CMD_START_SECTION_UPDATE, 		DFU_STATE_END_SECTION_UPDATE, 	    DFU_STATE_START_SECTION_UPDATE,     dfu_ActionStartSectionUpdate 	            },
		{ DFU_CMD_END_UPDATE, 		            DFU_STATE_END_SECTION_UPDATE, 	    DFU_STATE_END_UPDATE, 	            dfu_ActionEndUpdate 	         		    },
		{ DFU_CMD_COMPLETE_UPDATE, 		        DFU_STATE_END_UPDATE, 	        	DFU_STATE_COMPLETE_UPDATE, 	        dfu_ActionCompleteUpdate 			        },

		// Validation Sequence
		{ DFU_CMD_BEGIN_VALIDATION, 		    DFU_STATE_END_UPDATE, 	        	DFU_STATE_BEGIN_VALIDATION, 	    dfu_ActionBeginValidation 			        },
		{ DFU_CMD_START_SECTION_VALIDATION,     DFU_STATE_BEGIN_VALIDATION, 		DFU_STATE_START_SECTION_VALIDATION, dfu_ActionStartSectionValidation 	        },
		//{ DFU_CMD_VALIDATE_SECTION,             DFU_STATE_START_SECTION_VALIDATION, DFU_STATE_VALIDATE_SECTION,         dfu_ActionValidateSection        	        },
		{ DFU_CMD_NULL,                         DFU_STATE_VALIDATE_SECTION,         DFU_STATE_NULL,                     dfu_ActionValidateSection        	        },
		{ DFU_CMD_END_SECTION_VALIDATION,       DFU_STATE_VALIDATE_SECTION,         DFU_CMD_END_SECTION_VALIDATION,     dfu_ActionEndSectionValidation              },
		{ DFU_CMD_START_SECTION_VALIDATION,     DFU_CMD_END_SECTION_VALIDATION,     DFU_STATE_START_SECTION_VALIDATION, dfu_ActionStartSectionValidation            },
		{ DFU_CMD_END_VALIDATION,               DFU_CMD_END_SECTION_VALIDATION,     DFU_STATE_END_VALIDATION,           dfu_ActionEndValidation                     },
		{ DFU_CMD_COMPLETE_UPDATE,              DFU_STATE_END_VALIDATION,           DFU_STATE_COMPLETE_UPDATE, 	        dfu_ActionCompleteUpdate 			        },

};




void dfu_StateMachineInit( void )
{
	currentState = DFU_STATE_WAITING;
	transitionOverrideAction = NULL;
}

void dfu_StateTransition(DFU_Command *Command, DFU_Response *Response)
{
	uint32 i;

	Response->Status = DFU_STATUS_FAILURE;

	if(transitionOverrideAction)
	{

		for( i = 0; i < ARRAY_SIZE(stateTable); i++ )
		{
			if(transitionOverrideAction == stateTable[i].Action)
			{
				currentState = stateTable[i].CurrentState;
				transitionOverrideAction = transitionOverrideAction(Command, Response);
				break;
			}
		}
	}
	else
	{
		for( i = 0; i < ARRAY_SIZE(stateTable); i++ )
		{
			if( (Command->Command == stateTable[i].Command) &&
					(currentState == stateTable[i].CurrentState) )
			{
				transitionOverrideAction = stateTable[i].Action(Command, Response);

				if( Response->Status == DFU_STATUS_SUCCESS)
				{
					currentState = stateTable[i].NextState;
				}
				break;
			}
		}
	}

	if( i >= ARRAY_SIZE(stateTable))
	{
		printf("State transition error: Cmd: %d, current state: %d\n", Command->Command, currentState);
		Response->Status = DFU_STATUS_STATE_TRANSISTION_ERROR;
	}

	if( Response->Status != DFU_STATUS_SUCCESS)
	{
		dfu_StateMachineInit();
	}

	dfu_ComSendResponse();
}
