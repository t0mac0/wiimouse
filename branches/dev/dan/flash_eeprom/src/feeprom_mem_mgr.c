/*
 * flash_eeprom_mem_util.c
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#include "feeprom_mem_mgr.h"
#include "feeprom_table_mgr.h"
#include "feeprom_page_mgr.h"
#include "printf.h"
#include "flash_if.h"

static void bufferTableHeader(
		FeepromTableHeader *tableHeader
		);
static FEEPROM_Status updateEntryDataPointers(
		FeepromTableHeader *tableHeaderBuffer,
		FeepromTableHeader *newTableHeader,
		FEEPROM_EntryKey key
		);

static FEEPROM_Status updateEntryInfo(
		FeepromTableEntry *entry,
		uint16 size,
		FEEPROM_EntryFlag flags
		);
static FEEPROM_Status writeEntryData(
		FeepromTableHeader *newTableHeader,
		FEEPROM_EntryKey key,
		uint16 *data
		);


FEEPROM_Status FeepromMemRead(FEEPROM_EntryKey key, void *data, uint16 size, uint16 *bytesRead)
{
	FEEPROM_Status status;
	FeepromTableEntry *entry;
	uint16 i;

	(*bytesRead) = 0;

	if(!FEEPROM_SUCCESS(status, FeepromGetTableEntry(FEEPROM_GET_TABLE_BASE(), &entry, key)))
	{
		printf("Key %d, not found\n", key);
	}
	else if(size % 2)
	{
		printf("Can old read in multiples of 2\n", key);
		status = FEEPROM_STATUS_FAILURE;
	}
	else
	{
		for(i = 0; i < entry->size/2 && i < size/2; i++)
		{
			((uint16*)data)[i] = entry->data.ptr[i];
			(*bytesRead) += 2;
		}
	}

	return status;
}


FEEPROM_Status FeepromMemWrite(FEEPROM_EntryKey key, void *data, uint16 size, FEEPROM_EntryFlag flags)
{
	FEEPROM_Status status = FEEPROM_STATUS_SUCCESS;
	FeepromTableEntry *entry;
	FeepromTableHeader tableHeaderBuffer, *newTableHeader;

	bufferTableHeader(&tableHeaderBuffer);

	// todo support multi-page feeprom
	if(size > FEEPROM_PAGE_SIZE - tableHeaderBuffer.size )
	{
		status = FEEPROM_STATUS_FAILURE;
		printf("Not enough room in table");
	}
	else if( !FEEPROM_SUCCESS(status, FeepromGetTableEntry(&tableHeaderBuffer, &entry, key)) )
	{
		printf("Key %d, not found\n", key);
	}
	else if( (entry->flags & FEEPROM_ENTRY_PROTECTED) && (~flags & FEEPROM_ENTRY_FORCE_WRITE) )
	{
		status = FEEPROM_STATUS_FAILURE;
		printf("can't write key, it's protected\n");
	}
	else if( (size > entry->size) &&
			!FEEPROM_SUCCESS(status, FeepromPageFindFreeSpace((void**)&entry->data.ptr, size)) )
	{
		printf("FeepromPageFindFreeSpace failed\n");
	}
	else if( !FEEPROM_SUCCESS(status, FeepromPageGetBlank((FeepromPageHeader**)&newTableHeader)) )
	{
		printf("Couldn't find blank page\n");
	}
	else if( !FEEPROM_SUCCESS(status, updateEntryInfo(entry, size, flags)) )
	{
		printf("Failed to update entry info\n");
	}
	else if( !FEEPROM_SUCCESS(status, updateEntryDataPointers(&tableHeaderBuffer, newTableHeader, key)) )
	{
		printf("Failed to update entry data pointers\n");
	}
	else if( !FEEPROM_SUCCESS(status, FeepromTableWriteHeader(newTableHeader, &tableHeaderBuffer)))
	{
		printf("Failed to write the table header\n");
	}
	else if( !FEEPROM_SUCCESS(status, writeEntryData(newTableHeader, key, data)))
	{
		printf("Failed to write entry data\n");
	}
	else
	{
		FEEPROM_SET_TABLE_BASE(newTableHeader);
		printf("Entry written, new table base: %X\n", FEEPROM_GET_TABLE_BASE());
	}

	return status;
}


static void bufferTableHeader(FeepromTableHeader *tableHeader)
{
	uint16 i;
	FeepromTableHeader *header = FEEPROM_GET_TABLE_BASE();

	for(i = 0; i < sizeof(FeepromTableHeader)/2; i++)
	{
		((uint16*)tableHeader)[i] = ((uint16*)header)[i];
	}
}

static FEEPROM_Status updateEntryDataPointers(
		FeepromTableHeader *tableHeaderBuffer,
		FeepromTableHeader *newTableHeader,
		FEEPROM_EntryKey key
)
{
	uint16 i;
	uint32 newTablePage, oldTablePage;


	newTablePage = (uint32)FEEPROM_GET_PAGE_NUMBER(newTableHeader);
	oldTablePage = (uint32)FEEPROM_GET_PAGE_NUMBER(FEEPROM_GET_TABLE_BASE());

	for( i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		if( FEEPROM_GET_PAGE_NUMBER(tableHeaderBuffer->entryTable[i].data.ptr) == oldTablePage )
		{
			tableHeaderBuffer->entryTable[i].data.ptr = (uint16*)(newTablePage |
					((uint32)tableHeaderBuffer->entryTable[i].data.ptr & (FEEPROM_PAGE_SIZE-1)));
		}
		else if( tableHeaderBuffer->entryTable[i].key == key )
		{
			// TODO: support multi-paged FEEPROM
			printf("Multi-page FEEPROM not supported yet!\n");
			return FEEPROM_STATUS_FAILURE;
		}
	}

	return FEEPROM_STATUS_SUCCESS;
}

static FEEPROM_Status updateEntryInfo(
		FeepromTableEntry *entry,
		uint16 size,
		FEEPROM_EntryFlag flags
)
{
	entry->flags = flags;
	entry->size = size;

	return FEEPROM_STATUS_SUCCESS;
}

static FEEPROM_Status writeEntryData(FeepromTableHeader *newTableHeader, FEEPROM_EntryKey key, uint16 *data)
{
	uint16 i, j;
	FeepromTableEntry *entry;
	FeepromTableHeader *oldPage;

	// TODO: support multi-paged FEEPROM

	oldPage = (FeepromTableHeader*)FEEPROM_GET_TABLE_BASE();

	for( i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		entry = (FeepromTableEntry *)&newTableHeader->entryTable[i];

		if(entry->key != key)
		{
			for(j = 0; j < entry->size/2; j++)
			{
				FLASH_If_Write_Value16((uint32)(entry->data.ptr +j), oldPage->entryTable[i].data.ptr[j]);
			}
		}
		else
		{
			for(j = 0; j < entry->size/2; j++)
			{
				FLASH_If_Write_Value16((uint32)(entry->data.ptr +j), data[j]);
			}
		}
	}

	FeepromPageErase(oldPage);

	return FEEPROM_STATUS_SUCCESS;
}
