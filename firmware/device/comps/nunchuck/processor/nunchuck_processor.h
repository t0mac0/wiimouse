/*!
 * \file nunchuck_processor.h
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_PROCESSOR_H_
#define _NUNCHUCK_PROCESSOR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define NUNCHUCK_PROCESSOR_TASK_NAME "NunchukProcessor"
#define NUNCHUCK_PROCESSOR_STACK_SIZE OS_MIN_STACK_SIZE
#define NUNCHUCK_PROCESSOR_TASK_PRIORITY OS_TASK_PRIORITY_MEDIUM


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PROTECTED typedef struct {
    bool NewDataAvailable;
    NunchuckData Data;
} NunchuckProcessedDataInfo;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result NunchuckProcessorInit( void );

PROTECTED Result NunchuckProcessorTaskSuspend( void );

PROTECTED Result NunchuckProcessorTaskResume( void );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/

PROTECTED extern NunchuckProcessedDataInfo NunchuckProcessedData;

#endif /* NUNCHUCK_PROCESSOR_H_ */
