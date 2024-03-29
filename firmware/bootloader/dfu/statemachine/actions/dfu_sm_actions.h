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
PROTECTED typedef void (*DfuAction)( void );

PROTECTED void DfuActionQueryDevice(void);

PROTECTED void DfuActionInitializeUpdate(void);

PROTECTED void DfuActionBeginUpdate(void);
PROTECTED void DfuActionStartSectionUpdate(void);
PROTECTED void DfuActionSectionUpdate(void);
PROTECTED void DfuActionWriteSectionChunk(DFU_Response *Response, uint32 BufferSize);
PROTECTED void DfuActionEndSectionUpdate(void);
PROTECTED void DfuActionEndUpdate(void);

PROTECTED void DfuActionBeginValidation(void);
PROTECTED void DfuActionStartSectionValidation(void);
PROTECTED void DfuActionSectionValidate(void);
PROTECTED void DfuActionEndSectionValidation(void);
PROTECTED void DfuActionEndValidation(void);
PROTECTED void DfuActionReadSectionChunk(uint32 *BytesRead);

PROTECTED void DfuActionCompleteUpdate(void);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* DFU_SM_ACTIONS_H_ */
