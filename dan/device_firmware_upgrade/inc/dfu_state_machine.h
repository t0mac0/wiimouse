/*
 * dfu_state_machine.h
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */

#ifndef DFU_STATE_MACHINE_H_
#define DFU_STATE_MACHINE_H_

#include "dfu_type.h"

void dfu_StateMachineInit( void );
void dfu_StateTransition(DFU_Command *Command, DFU_Response *Response);

#endif /* DFU_STATE_MACHINE_H_ */
