/*!
 * \file dfu_sm_actions.h
 *
 * \brief 
 *
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

#ifndef _DFU_SM_ACTIONS_H_
#define _DFU_SM_ACTIONS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system.h"
#include "dfu/dfu_types.h"


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
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED typedef void (*DfuAction)(DFU_Command*, DFU_Response*);

PROTECTED void DfuActionQueryDevice(DFU_Command *Cmd, DFU_Response *Response);

PROTECTED void DfuActionInitializeUpdate(DFU_Command *Cmd, DFU_Response *Response);

PROTECTED void DfuActionBeginUpdate(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionStartSectionUpdate(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionSectionUpdate(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionWriteSectionChunk(DFU_Response *Response, uint32 BufferSize);
PROTECTED void DfuActionEndSectionUpdate(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionEndUpdate(DFU_Command *Cmd, DFU_Response *Response);

PROTECTED void DfuActionBeginValidation(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionStartSectionValidation(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionSectionValidate(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionEndSectionValidation(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionEndValidation(DFU_Command *Cmd, DFU_Response *Response);
PROTECTED void DfuActionReadSectionChunk(uint32 *BytesRead);

PROTECTED void DfuActionCompleteUpdate(DFU_Command *Cmd, DFU_Response *Response);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* DFU_SM_ACTIONS_H_ */
