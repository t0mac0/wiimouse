/*
 * ddfu_actions_validate.c
 *
 *  Created on: Feb 8, 2011
 *      Author: Reed
 *
 */
#include "dfu_actions.h"
#include "dfu_mal.h"
#include "printf.h"
#include "dfu_com.h"


#define IS_DATA_OVERFLOW()( ((readAddress - sectionStartAddress) + readSize) > sectionSize )

static uint32 sectionStartAddress;
static uint32 sectionsRemaining;
static uint32 sectionSize;
static DFU_DestinationType destination;
static uint32 readSize;
static uint32 readAddress;

uint32 checkSum;


static void InitializeDataMembers( void )
{
	sectionStartAddress = 0;
	sectionsRemaining = 0;
	sectionSize = 0;
	destination = DFU_DESTINATION_UNKNOWN;
	DFU_MalReadEnabled = FALSE;
	readSize = 0;
	readAddress = 0;
	checkSum = 0;
}


static __inline void UpdateCheckSum( uint32 *buffer, uint32 size )
{
	uint32 i;

	for( i = 0; i < size; i++)
	{
		checkSum += buffer[i];
	}
}

void  dfu_ActionBeginValidation(DFU_Command *Cmd, DFU_Response *Response)
{
	// TODO: Read flash memory to make sure in DFU_MODE_UPDATE
	// return failure if not

	InitializeDataMembers();

	sectionsRemaining = Cmd->SectionsCount;

	if( sectionsRemaining > DFU_DESTINATION_COUNT)
	{
		Response->Status = DFU_STATUS_TOO_MANY_SECTIONS;
		printf("ActionBeginValidation: too many sections: %d (max %d)\n",
				sectionsRemaining, DFU_DESTINATION_COUNT);
	}
	else
	{
		Response->Status = DFU_STATUS_SUCCESS;

		printf("ActionBeginValidation: section count: %d\n", sectionsRemaining);
	}
}

void  dfu_ActionStartSectionValidation(DFU_Command *Cmd, DFU_Response *Response)
{
	sectionsRemaining--;
	destination = Cmd->Destination;

	if(sectionsRemaining < 0)
	{
		Response->Status = DFU_STATUS_SECTION_OVERFLOW;
		printf("ActionStartSectionValidation: DFU_STATUS_SECTION_OVERFLOW\n");
		InitializeDataMembers();
	}
	else if( destination > DFU_DESTINATION_COUNT )
	{
		Response->Status = DFU_STATUS_INVALID_DESTINATION;
		printf("ActionBeginValidation: invalid destination: %d\n", destination);
	}
	else
	{
		readAddress = sectionStartAddress = Cmd->StartAddress;
		sectionSize = Cmd->Length;
		Response->Status = DFU_STATUS_SUCCESS;

		printf("ActionStartSectionValidation: size: %d\n", sectionSize);
	}

}

void  dfu_ActionSectionValidate(DFU_Command *Cmd, DFU_Response *Response)
{

	readAddress += Cmd->Offset;
	readSize = Cmd->Length;

	if(IS_DATA_OVERFLOW()){
		printf("ActionSectionValidation: Error data overflow\n");
		Response->Status = DFU_STATUS_SECTION_DATA_OVERFLOW;
		InitializeDataMembers();
	}
	else
	{
		DFU_MalReadEnabled = TRUE;
		Response->Status = DFU_STATUS_SUCCESS;
		printf("ActionSectionValidation: readAddress: %08X, size: %d\n", readAddress, readSize);
	}

}

uint32 dfu_ActionReadSectionChunk(void)
{
	uint32 byteRead, i;

	// read length bytes to readAddress of destination here
	MAL_Read(readAddress, readSize);

	printf("ActionReadSectionChunk: read %d bytes from %08X\n", readSize, readAddress);

	printf("After:\n");
	for(i=48; i >= 48 && i < 72; i++)
		printf("%X ", DFU_MalBuffer[i]);
	printf("\n");

	//UpdateCheckSum((uint32*)Response, readSize/4);
	DFU_MalReadEnabled = FALSE;

	dfu_ComSendData(readSize);

	return readSize;
}

void  dfu_ActionEndSectionValidation(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Checksum = checkSum;
	Response->Status = DFU_STATUS_SUCCESS;

	printf("ActionEndSectionValidation\n");


}

void  dfu_ActionEndValidation(DFU_Command *Cmd, DFU_Response *Response)
{
	Response->Status = DFU_STATUS_SUCCESS;

	printf("ActionEndValidation\n");

}
