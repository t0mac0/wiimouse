/*
 * dfu_cl.c
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */
#include "usb_sil.h"
#include "usb_regs.h"
#include "dfu_state_machine.h"
#include "dfu_actions.h"
#include "dfu_com.h"
#include "printf.h"

static DFU_Command dfu_CommandBuffer;
static DFU_Response dfu_ResponseBuffer;

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
} StateType;


typedef struct _State {
	DFU_CommandType Command;
	StateType CurrentState;
	StateType NextState;
	dfu_Action Action;
} State;

static StateType currentState;

static State stateTable[] =
{
		{ DFU_CMD_QUERY_DEVICE, 			    DFU_STATE_WAITING, 					DFU_CMD_QUERY_DEVICE, 		        dfu_ActionQueryDevice    					},
		{ DFU_CMD_INITIALIZE_UPDATE, 			DFU_STATE_WAITING, 					DFU_STATE_INITIALIZE_UPDATE, 		dfu_ActionInitializeUpdate 					},

		// Update Sequence
		{ DFU_CMD_BEGIN_UPDATE, 				DFU_STATE_WAITING, 	            	DFU_STATE_BEGIN_UPDATE, 			dfu_ActionBeginUpdate 						},
		{ DFU_CMD_START_SECTION_UPDATE, 		DFU_STATE_BEGIN_UPDATE, 	    	DFU_STATE_START_SECTION_UPDATE, 	dfu_ActionStartSectionUpdate 			    },
		{ DFU_CMD_SECTION_UPDATE, 		        DFU_STATE_START_SECTION_UPDATE, 	DFU_STATE_SECTION_UPDATE, 	        dfu_ActionSectionUpdate 	                },
		{ DFU_CMD_SECTION_UPDATE, 		        DFU_STATE_SECTION_UPDATE, 	    	DFU_STATE_SECTION_UPDATE, 	        dfu_ActionSectionUpdate 	                },
		{ DFU_CMD_END_SECTION_UPDATE, 		    DFU_STATE_SECTION_UPDATE, 	    	DFU_STATE_END_SECTION_UPDATE, 	    dfu_ActionEndSectionUpdate 	                },
		{ DFU_CMD_START_SECTION_UPDATE, 		DFU_STATE_END_SECTION_UPDATE, 	    DFU_STATE_START_SECTION_UPDATE,     dfu_ActionStartSectionUpdate 	            },
		{ DFU_CMD_END_UPDATE, 		            DFU_STATE_END_SECTION_UPDATE, 	    DFU_STATE_END_UPDATE, 	            dfu_ActionEndUpdate 	         		    },
		{ DFU_CMD_COMPLETE_UPDATE, 		        DFU_STATE_END_UPDATE, 	        	DFU_STATE_COMPLETE_UPDATE, 	        dfu_ActionCompleteUpdate 			        },

		// Validation Sequence
		{ DFU_CMD_BEGIN_VALIDATION, 		    DFU_STATE_END_UPDATE, 	        	DFU_STATE_BEGIN_VALIDATION, 	    dfu_ActionBeginValidation 			        },
		{ DFU_CMD_START_SECTION_VALIDATION,     DFU_STATE_BEGIN_VALIDATION, 		DFU_STATE_START_SECTION_VALIDATION, dfu_ActionStartSectionValidation 	        },
		{ DFU_CMD_VALIDATE_SECTION,             DFU_STATE_START_SECTION_VALIDATION, DFU_STATE_VALIDATE_SECTION,         dfu_ActionValidateSection        	        },
		{ DFU_CMD_VALIDATE_SECTION,             DFU_STATE_VALIDATE_SECTION,         DFU_STATE_VALIDATE_SECTION,         dfu_ActionValidateSection        	        },
		{ DFU_CMD_END_SECTION_VALIDATION,       DFU_STATE_VALIDATE_SECTION,         DFU_CMD_END_SECTION_VALIDATION,     dfu_ActionEndSectionValidation              },
		{ DFU_CMD_START_SECTION_VALIDATION,     DFU_CMD_END_SECTION_VALIDATION,     DFU_STATE_START_SECTION_VALIDATION, dfu_ActionStartSectionValidation            },
		{ DFU_CMD_END_VALIDATION,               DFU_CMD_END_SECTION_VALIDATION,     DFU_STATE_END_VALIDATION,           dfu_ActionEndValidation                     },
		{ DFU_CMD_COMPLETE_UPDATE,              DFU_STATE_END_VALIDATION,           DFU_STATE_COMPLETE_UPDATE, 	        dfu_ActionCompleteUpdate 			        },

};

static uint32 readCount = 0;

void dfu_ComReceiveCommand( void )
{
	uint32 bytesRead;

	bytesRead = USB_SIL_Read(EP3_OUT, (uint8*)&dfu_CommandBuffer);
	SetEPRxValid(ENDP3);

	readCount += bytesRead;

	if(readCount >= sizeof(DFU_Command))
	{
		readCount = 0;
		dfu_StateTransition(&dfu_CommandBuffer, &dfu_ResponseBuffer);
	}
}


void dfu_ComSendResponse( void )
{
	USB_SIL_Write(EP1_IN, (uint8*)&dfu_ResponseBuffer, sizeof(DFU_Response));
	SetEPTxValid(ENDP1);
}






void dfu_StateMachineInit( void )
{
	currentState = DFU_STATE_WAITING;
}

void dfu_StateTransition(DFU_Command *Command, DFU_Response *Response)
{
	uint32 i;

	Response->Status = DFU_STATUS_FAILURE;

	for( i = 0; i < ARRAY_SIZE(stateTable); i++ )
	{
		if( (Command->Command == stateTable[i].Command) &&
				(currentState == stateTable[i].CurrentState) )
		{
			stateTable[i].Action(Command, Response);

			if( Response->Status == DFU_STATUS_SUCCESS)
			{
				currentState = stateTable[i].NextState;
			}

			break;
		}
	}

	if( i == ARRAY_SIZE(stateTable))
	{
		printf("State transition error: Cmd: %d, current state: %d\n", Command->Command, currentState);
		Response->Status = DFU_STATUS_STATE_TRANSISTION_ERROR;
	}

	dfu_ComSendResponse();
}
