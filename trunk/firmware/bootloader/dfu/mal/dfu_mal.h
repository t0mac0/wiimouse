/*!
 * \file dfu_mal.h
 *
 * \brief 
 *
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

#ifndef _DFU_MAL_H_
#define _DFU_MAL_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define DFU_MAL_BUFFER_SIZE 1024




/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED bool DfuMalInit (void);
PROTECTED bool DfuMalErase (uint32 SectorAddress, uint32 Length);
PROTECTED bool DfuMalWrite (uint32 SectorAddress, uint32 DataLength);
PROTECTED bool DfuMalRead (uint32 SectorAddress,  uint32 DataLength);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/

PROTECTED extern uint8  DfuMalBuffer[DFU_MAL_BUFFER_SIZE]; /* RAM Buffer for Downloaded Data */

PROTECTED extern bool DfuMalWriteEnabled;
PROTECTED extern bool DfuMalReadEnabled;

#endif /* DFU_MAL_H_ */
