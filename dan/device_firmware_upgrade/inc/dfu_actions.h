/*
 * dfu_actions.h
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */

#ifndef DFU_ACTIONS_H_
#define DFU_ACTIONS_H_

#include "dfu_type.h"



typedef void (*dfu_Action)(DFU_Command*, DFU_Response*);

void dfu_ActionQueryDevice(DFU_Command *Cmd, DFU_Response *Response);

void dfu_ActionInitializeUpdate(DFU_Command *Cmd, DFU_Response *Response);

void dfu_ActionBeginUpdate(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionStartSectionUpdate(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionSectionUpdate(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionWriteSectionChunk(DFU_Response *Response, uint32 BufferSize);
void dfu_ActionEndSectionUpdate(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionEndUpdate(DFU_Command *Cmd, DFU_Response *Response);

void dfu_ActionBeginValidation(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionStartSectionValidation(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionSectionValidate(DFU_Command *Cmd, DFU_Response *Response);
uint32 dfu_ActionReadSectionChunk(void);
void dfu_ActionEndSectionValidation(DFU_Command *Cmd, DFU_Response *Response);
void dfu_ActionEndValidation(DFU_Command *Cmd, DFU_Response *Response);

void dfu_ActionCompleteUpdate(DFU_Command *Cmd, DFU_Response *Response);




#endif /* DFU_ACTIONS_H_ */
