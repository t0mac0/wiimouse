/*!
 * \file dfu_sm.c
 *
 * \brief 
 *
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "dfu/dfu.h"


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
    DFU_STATE_WAITING,
    //DFU_STATE_INITIALIZE_UPDATE,
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


typedef struct {
    DFU_CommandType Command;
    StateType CurrentState;
    StateType NextState;
    DfuAction Action;
} State;

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE StateType currentState;

PRIVATE State stateTable[] =
{
        //  Command                             Current State                       Next State                          Current State Action
        { DFU_CMD_QUERY_DEVICE,                 DFU_STATE_WAITING,                  DFU_CMD_QUERY_DEVICE,               DfuActionQueryDevice                       },
        { DFU_CMD_INITIALIZE_UPDATE,            DFU_CMD_QUERY_DEVICE,               DFU_STATE_NULL,                     DfuActionInitializeUpdate                  },

        // Update Sequence
        { DFU_CMD_BEGIN_UPDATE,                 DFU_CMD_QUERY_DEVICE,               DFU_STATE_BEGIN_UPDATE,             DfuActionBeginUpdate                       },
        { DFU_CMD_START_SECTION_UPDATE,         DFU_STATE_BEGIN_UPDATE,             DFU_STATE_START_SECTION_UPDATE,     DfuActionStartSectionUpdate                },
        { DFU_CMD_SECTION_UPDATE,               DFU_STATE_START_SECTION_UPDATE,     DFU_STATE_SECTION_UPDATE,           DfuActionSectionUpdate                     },
        { DFU_CMD_SECTION_UPDATE,               DFU_STATE_SECTION_UPDATE,           DFU_STATE_SECTION_UPDATE,           DfuActionSectionUpdate                     },
        { DFU_CMD_END_SECTION_UPDATE,           DFU_STATE_SECTION_UPDATE,           DFU_STATE_END_SECTION_UPDATE,       DfuActionEndSectionUpdate                  },
        { DFU_CMD_START_SECTION_UPDATE,         DFU_STATE_END_SECTION_UPDATE,       DFU_STATE_START_SECTION_UPDATE,     DfuActionStartSectionUpdate                },
        { DFU_CMD_END_UPDATE,                   DFU_STATE_END_SECTION_UPDATE,       DFU_STATE_END_UPDATE,               DfuActionEndUpdate                         },
        //{ DFU_CMD_COMPLETE_UPDATE,                DFU_STATE_END_UPDATE,               DFU_STATE_COMPLETE_UPDATE,          DfuActionCompleteUpdate                    },

        // Validation Sequence
        { DFU_CMD_BEGIN_VALIDATION,             DFU_STATE_END_UPDATE,               DFU_STATE_BEGIN_VALIDATION,         DfuActionBeginValidation                   },
        { DFU_CMD_START_SECTION_VALIDATION,     DFU_STATE_BEGIN_VALIDATION,         DFU_STATE_START_SECTION_VALIDATION, DfuActionStartSectionValidation            },
        { DFU_CMD_SECTION_VALIDATE,             DFU_STATE_START_SECTION_VALIDATION, DFU_STATE_VALIDATE_SECTION,         DfuActionSectionValidate                   },
        { DFU_CMD_SECTION_VALIDATE,             DFU_STATE_VALIDATE_SECTION,         DFU_STATE_VALIDATE_SECTION,         DfuActionSectionValidate                   },
        { DFU_CMD_END_SECTION_VALIDATION,       DFU_STATE_VALIDATE_SECTION,         DFU_CMD_END_SECTION_VALIDATION,     DfuActionEndSectionValidation              },
        { DFU_CMD_START_SECTION_VALIDATION,     DFU_CMD_END_SECTION_VALIDATION,     DFU_STATE_START_SECTION_VALIDATION, DfuActionStartSectionValidation            },
        { DFU_CMD_END_VALIDATION,               DFU_CMD_END_SECTION_VALIDATION,     DFU_STATE_END_VALIDATION,           DfuActionEndValidation                     },
        { DFU_CMD_COMPLETE_UPDATE,              DFU_STATE_END_VALIDATION,           DFU_STATE_COMPLETE_UPDATE,          DfuActionCompleteUpdate                    },

};

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuSmInit( void )
{
    currentState = DFU_STATE_WAITING;
    DfuMalReadEnabled = FALSE;
    DfuMalWriteEnabled = FALSE;
}


/******************************************************************************/
PROTECTED void DfuSmStateTransition(DFU_Command *Command, DFU_Response *Response)
{
    uint32 i;

    Response->Status = DFU_STATUS_FAILURE;


    for( i = 0; i < ARRAY_SIZE(stateTable); i++ )
    {
        if( (Command->Command == stateTable[i].Command) &&
                (currentState == stateTable[i].CurrentState) )
        {
            stateTable[i].Action(Command, Response);

            if( Response->Status == DFU_STATUS_SUCCESS )
            {
                currentState = stateTable[i].NextState;
            }
            break;
        }
    }

    if( i >= ARRAY_SIZE(stateTable))
    {
        print("State transition error: Cmd: %d, current state: %d\n", Command->Command, currentState);
        Response->Status = DFU_STATUS_STATE_TRANSISTION_ERROR;
        DfuSmInit();
    }

    DfuComSendResponse();

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

