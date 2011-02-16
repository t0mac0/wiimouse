/*
 * dfu_actions_upgrade.c
 *
 *  Created on: Feb 8, 2011
 *      Author: Reed
 */
#include "dfu_mal.h"
#include "dfu_actions.h"
#include "printf.h"
#include "dfu_com.h"

#define IS_DATA_OVERFLOW()( ((writeAddress - sectionStartAddress) + writeSize) > sectionSize )

static uint32 sectionStartAddress;
static uint32 sectionsRemaining;
static uint32 sectionSize;
static DFU_DestinationType destination;
static uint32 writeSize;
static uint32 writeAddress;


static void InitializeDataMembers( void )
{
	sectionStartAddress = 0;
	sectionsRemaining = 0;
	sectionSize = 0;
	destination = DFU_DESTINATION_UNKNOWN;
	DFU_MalWriteEnabled = FALSE;
	writeSize = 0;
	writeAddress = 0;
}

void  dfu_ActionBeginUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	// TODO: Read flash memory to make sure in DFU_MODE_UPDATE
	// return failure if not

	InitializeDataMembers();

	sectionsRemaining = Cmd->SectionsCount;

	if( sectionsRemaining > DFU_DESTINATION_COUNT)
	{
		Response->Status = DFU_STATUS_TOO_MANY_SECTIONS;
		printf("ActionBeginUpdate: too many sections: %d (max %d)\n",
				sectionsRemaining, DFU_DESTINATION_COUNT);
	}
	else
	{
		Response->Status = DFU_STATUS_SUCCESS;

		printf("ActionBeginUpdate: section count: %d\n", sectionsRemaining);
	}
}

void  dfu_ActionStartSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	sectionsRemaining--;
	destination = Cmd->Destination;

	if(sectionsRemaining < 0)
	{
		Response->Status = DFU_STATUS_SECTION_OVERFLOW;
		printf("ActionStartSectionUpdate: DFU_STATUS_SECTION_OVERFLOW\n");
		InitializeDataMembers();
	}
	else if( destination > DFU_DESTINATION_COUNT )
	{
		Response->Status = DFU_STATUS_INVALID_DESTINATION;
		printf("ActionBeginUpdate: invalid destination: %d\n", destination);
	}
	else
	{
		writeAddress = sectionStartAddress = Cmd->StartAddress;
		sectionSize = Cmd->Length;
		Response->Status = DFU_STATUS_SUCCESS;

		MAL_Erase(writeAddress, sectionSize);

		printf("ActionStartSectionUpdate: size: %d\n", sectionSize);
	}

}

void  dfu_ActionSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{

	writeAddress += Cmd->Offset;
	writeSize = Cmd->Length;

	if(IS_DATA_OVERFLOW()){
		printf("ActionSectionUpdate: Error data overflow\n");
		Response->Status = DFU_STATUS_SECTION_DATA_OVERFLOW;
		InitializeDataMembers();
	}
	else
	{
		DFU_MalWriteEnabled = TRUE;
		Response->Status = DFU_STATUS_SUCCESS;
		printf("ActionSectionUpdate: writeAddress: %08X, size: %d\n", writeAddress, writeSize);
	}

}

void dfu_ActionWriteSectionChunk(DFU_Response *Response, uint32 BufferSize)
{

	if(BufferSize >= writeSize)
	{
		uint32 i;

		printf("Before:\n");
			for(i=48; i >= 48 && i < 72; i++)
				printf("%X ", DFU_MalBuffer[i]);
			printf("\n");

		// write length bytes to writeAddress of destination here
		MAL_Write(writeAddress, writeSize);

		printf("ActionWriteSectionChunk: wrote %d bytes to %08X\n", writeSize, writeAddress);

		Response->Status = DFU_STATUS_SUCCESS;

		DFU_MalWriteEnabled = FALSE;
		dfu_ComSendResponse();
	}

}

void  dfu_ActionEndSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;

	printf("ActionEndSectionUpdate\n");

}

void  dfu_ActionEndUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;

	printf("ActionEndUpdate\n");

}
