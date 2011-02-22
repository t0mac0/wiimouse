/*
 * flash_eeprom.c
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */
#include "dfu_mal.h"

#include "feeprom.h"
#include "feeprom_prepreprocess.h"
#include "feeprom_mem_mgr.h"
#include "feeprom_table_mgr.h"
#include "feeprom_page_mgr.h"
#include "printf.h"

FeepromTableHeader *feepromTableHeader;

FeepromTableHeader feepromBaseHeader  __attribute ((section(".flash_eeprom"))) =
{
		{ PAGE_STATUS_WRITTEN,	// page status
				PAGE_FLAG_IS_TABLE }, // page flags
				_$FEEPROM_ENTRY_COUNT$_,    // entry count
				0, // page count
				NULL, // size
				_$FEEPROM_ENTRIES$_  // entries
};

uint16 feepromEntryData1[FEEPROM_PAGE_SIZE/2-sizeof(FeepromTableHeader)] __attribute ((section(".flash_eeprom"))) = _$FEEPROM_ENTRY_DATA$_;
// page 2
uint16 feepromEntryData2[FEEPROM_PAGE_SIZE/2] __attribute ((section(".flash_eeprom"))) __attribute ((aligned(FEEPROM_PAGE_SIZE)));
// page 3
//uint16 feepromEntryData3[FEEPROM_PAGE_SIZE/2] __attribute ((section(".flash_eeprom"))) __attribute ((aligned(FEEPROM_PAGE_SIZE)));






FEEPROM_Status FEEPROM_Init( void )
{
	FEEPROM_Status status;
	FeepromTableHeader *header;
	uint16 j;

	FLASH_Unlock();

	FeepromTableInit();
	FeepromPageInit(); // must be call after table init


	for(j = 0; j*2 < sizeof(FeepromTableHeader); j++)
	{
		((uint16*)DFU_MalBuffer)[j] = ((uint16*)&feepromBaseHeader)[j];
	}
	for(j = 0; j*2 < 50; j++)
	{
		((uint16*)DFU_MalBuffer)[sizeof(FeepromTableHeader)+j] = feepromEntryData1[j];
	}
	status = FEEPROM_Write(FEEPROM_ENTRY_TABLE_HEADER, DFU_MalBuffer, sizeof(FeepromTableHeader)+50, 0);

	header = FEEPROM_GET_TABLE_BASE();

	printf("Table:\n");
	printf("Status: %X\n", header->pageHeader.status);
	printf("flags: %X\n", header->pageHeader.flags);
	printf("entry count: %X\n", header->entryCount);
	printf("table size: %X\n", header->size);
	printf("page count: %X\n", header->pageCount);

	printf("Entries:\n");
	for(j = 0; j < header->entryCount; j++)
	{
		printf("Entry: %d\n", header->entryTable[j].key);
		printf("\tptr: %X\n", (uint32)header->entryTable[j].data.ptr);
		printf("\tsize: %d\n", header->entryTable[j].size);
		printf("\tflags: %d\n", header->entryTable[j].flags);
		printf("\tallocted: %d\n", header->entryTable[j].allocated);
	}



	return status;
}

FEEPROM_Status FEEPROM_Write( FEEPROM_EntryKey key, void *data, uint16 size, FEEPROM_EntryFlag flags)
{
	FEEPROM_Status status;

	if( key == FEEPROM_ENTRY_TABLE_HEADER)
	{
		status = FeepromTableUpdate(data, size);
	}
	else
	{
		status = FeepromMemWrite(key, data, size, flags);
	}

	return status;
}

FEEPROM_Status FEEPROM_Read( FEEPROM_EntryKey key, void *data, uint16 size, uint16 *bytesRead)
{

	return FeepromMemRead(key, data, size, bytesRead);
}

