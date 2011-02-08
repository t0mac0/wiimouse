/*
 * dfu_actions_upgrade.c
 *
 *  Created on: Feb 8, 2011
 *      Author: Reed
 */
#include "dfu_actions.h"
#include "printf.h"

#define CHUNK_SIZE 64

static uint32 totalNumSections;
static uint32 sectionsProcessed;
static uint32 sectionStartAddess;
static uint32 chunksRemaining;
static uint32 partialChunkSize;

void*  dfu_ActionBeginUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	totalNumSections = Cmd->SectionsCount;
	sectionsProcessed = 0;

	Response->Status = DFU_STATUS_SUCCESS;

	printf("ActionBeginUpdate: section count: %d\n", totalNumSections);

	return NULL;
}

void*  dfu_ActionStartSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	void* retval = NULL;

	sectionsProcessed++;

	if(sectionsProcessed > totalNumSections)
	{
		Response->Status = DFU_STATUS_MAX_SECTION_UPGRADE;
		printf("ActionStartSectionUpdate: Error: sections processed(%d) > total num sections (%d)\n",
				sectionsProcessed, totalNumSections);
	}
	else
	{
		sectionStartAddess = Cmd->StartAddress;
		chunksRemaining = Cmd->Length / CHUNK_SIZE;
		partialChunkSize = Cmd->Length & CHUNK_SIZE;
		Response->Status = DFU_STATUS_SUCCESS;

		printf("ActionStartSectionUpdate: start addr: %X, num chuck: %d, partial chunk: %d\n",
				sectionStartAddess, chunksRemaining, partialChunkSize);

		retval = dfu_ActionSectionUpdate;
	}

	return retval;
}

void*  dfu_ActionSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	void* retval = NULL;

	if(chunksRemaining > 0)
	{
		// write 64 bytes to flash
		chunksRemaining--;

		if(chunksRemaining > 0)
			retval = dfu_ActionSectionUpdate;
		Response->Status = DFU_STATUS_SUCCESS;
	}
	else if(partialChunkSize > 0)
	{
		partialChunkSize = 0;
		Response->Status = DFU_STATUS_SUCCESS;
	}
	else
	{
		printf("ActionSectionUpdate: Error data overflow\n");
		Response->Status = DFU_STATUS_SECTION_UPGRADE_DATA_OVERFLOW;
	}

	return retval;
}

void*  dfu_ActionEndSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{

	return NULL;
}

void*  dfu_ActionEndUpdate(DFU_Command *Cmd, DFU_Response *Response)
{

	return NULL;
}
