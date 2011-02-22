/*
 * feeprom_table_mgr.c
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#include "feeprom_table_mgr.h"
#include "feeprom_page_mgr.h"
#include "printf.h"

#define offsetof(s,m) (uint32)&(((s *)0)->m)

#define TABLE_ENTRY_INIT(_te, _size, _id, _allocated, _flags, _dataPtr)	\
{																		\
	_te->size = _size;													\
	_te->key = _id;														\
	_te->allocated = _allocated;										\
	_te->flags = _flags;												\
	_te->data.ptr = _dataPtr;											\
}

static FEEPROM_Status findTableHeader();
static FEEPROM_Status populateTableHeaderBuffer(FeepromTableHeader *newTableHeaderBuffer);
static FEEPROM_Status updateEntryDataPointers(FeepromTableHeader *oldTableHeader, uint16 *numPages);
static FEEPROM_Status writeTableHeader(void);
static uint16 getTotalTableSize(uint8 numPages);
static FeepromTableEntry* getTableEntry(FeepromTableHeader *tableBase, uint16 id);
static FEEPROM_Status writeEntryData(uint16 *data, int16 size);
static FEEPROM_Status getEntryBuffer(FeepromTableEntry **entry, uint16 **buffer, uint32 *entryDataBase, uint16 *data);



static uint32 entryBytesWritten;
static FeepromTableHeader tableHeaderBuffer;
static FeepromTableHeader *newTableHeader;
static bool updatingTable;
static uint16 currentEntryIndex;



FEEPROM_Status FeepromTableInit(void )
{
	updatingTable = FALSE;

	findTableHeader();

	return FEEPROM_STATUS_SUCCESS;
}

FEEPROM_Status FeepromTableUpdate(uint16 *data, uint16 size)
{
	FEEPROM_Status status;

	if(!updatingTable && size < sizeof(FeepromTableHeader))
	{
		printf("Initial data chunk must contain entire FeepromTableHeader\n");
		return FEEPROM_STATUS_FAILURE;
	}
	else if(!updatingTable)
	{
		printf("Updating table of size: %d\n", size);

		updatingTable = TRUE;
		FeepromPageForceBlank((FeepromPageHeader**)&newTableHeader);
		currentEntryIndex = 0;
		entryBytesWritten = 0;

		populateTableHeaderBuffer((FeepromTableHeader*) data);

		size -= sizeof(FeepromTableHeader);
		data += sizeof(FeepromTableHeader);
	}

	if(size % 2 != 0)
	{
		printf("Data size must be a multiple of 2\n");
		return FEEPROM_STATUS_FAILURE;
	}

	status = writeEntryData(data, size);

	return status;
}

FEEPROM_Status FeepromGetTableEntry(FeepromTableHeader *tableBase, FeepromTableEntry** entry, uint16 key)
{
	uint16 i;

	for(i = 0; i < tableBase->entryCount; i++)
	{
		if(tableBase->entryTable[i].key == key)
		{
			*entry = &tableBase->entryTable[i];
			return FEEPROM_STATUS_SUCCESS;
		}
	}

	return FEEPROM_STATUS_FAILURE;
}

// todo switch to FeepromGetTableEntry
static FeepromTableEntry* getTableEntry(FeepromTableHeader *tableBase, uint16 key)
{
	FeepromTableEntry* entry = NULL;
	uint16 i;

	for(i = 0; i < tableBase->entryCount; i++)
	{
		if(tableBase->entryTable[i].key == key)
		{
			entry = &tableBase->entryTable[i];
			break;
		}
	}

	return entry;
}


static FEEPROM_Status findTableHeader()
{
	uint32 i;
	FeepromPageHeader *pageHeader;

	feepromTableHeader = &feepromBaseHeader;

	for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
	{
		pageHeader = (FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(i);

		if(pageHeader->flags & PAGE_FLAG_IS_TABLE)
		{
			feepromTableHeader = (FeepromTableHeader*)pageHeader;
			break;
		}
	}

	return FEEPROM_STATUS_SUCCESS;
}

static FEEPROM_Status populateTableHeaderBuffer(FeepromTableHeader *newTableHeaderBuffer)
{
	FeepromTableHeader *oldTableHeader;
	uint16 i, numPages, id;
	FeepromTableEntry *oldEntry, *newEntry, *bufferedEntry;
	bool entryInOldTable, entryInNewTable;

	oldTableHeader = FEEPROM_GET_TABLE_BASE();

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		bufferedEntry = &tableHeaderBuffer.entryTable[i];
		id = newTableHeaderBuffer->entryTable[i].key;
		entryInOldTable = ((oldEntry = getTableEntry(oldTableHeader, id)) == NULL) ? FALSE : TRUE;
		entryInNewTable = ((newEntry = getTableEntry(newTableHeaderBuffer, id)) == NULL) ? FALSE : TRUE;

		if( !entryInOldTable && !entryInNewTable )
		{
			TABLE_ENTRY_INIT(bufferedEntry, 0, id, FALSE, 0, NULL);
		}
		else if( !entryInOldTable && entryInNewTable )
		{
			TABLE_ENTRY_INIT(bufferedEntry, newEntry->size, id, FALSE, newEntry->flags, NULL);
		}
		else if( entryInOldTable && !entryInNewTable )
		{
			TABLE_ENTRY_INIT(bufferedEntry, oldEntry->size, id, TRUE, oldEntry->flags, NULL);
		}
		else
		{
			if( (oldEntry->flags & FEEPROM_ENTRY_PROTECTED) && !(~(newEntry->flags) & FEEPROM_ENTRY_FORCE_UPDATE) )
			{
				printf("Warning: Can't update entry: %d since it's write protected\n", i);
				TABLE_ENTRY_INIT(bufferedEntry, oldEntry->size, id, TRUE, oldEntry->flags, NULL);
			}
			else
			{
				TABLE_ENTRY_INIT(bufferedEntry, newEntry->size, id, FALSE, newEntry->flags , NULL);
			}
		}
	}

	updateEntryDataPointers(oldTableHeader, &numPages);

	tableHeaderBuffer.size = getTotalTableSize( numPages);
	tableHeaderBuffer.pageCount = numPages;
	tableHeaderBuffer.entryCount = FEEPROM_ENTRY_COUNT;
	tableHeaderBuffer.pageHeader.flags = PAGE_FLAG_IS_TABLE;
	tableHeaderBuffer.pageHeader.status = PAGE_STATUS_WRITTEN;

	return FEEPROM_STATUS_SUCCESS;
}

static FEEPROM_Status updateEntryDataPointers(FeepromTableHeader *oldTableHeader, uint16 *numPages)
{
	uint16 i;
	uint32 pageOffset;

	pageOffset = ((uint32)newTableHeader + sizeof(FeepromTableHeader));
	*numPages = 1;

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		tableHeaderBuffer.entryTable[i].data.ptr = (uint16*)pageOffset;
		pageOffset += tableHeaderBuffer.entryTable[i].size;

		if( (i + 1 < FEEPROM_ENTRY_COUNT) &&
				(((pageOffset + tableHeaderBuffer.entryTable[i+1].size) & 0xFFFFC000) != (pageOffset & 0xFFFFC000)) )
		{
			FeepromPageGetNextBlank((FeepromPageHeader**)&pageOffset, (FeepromPageHeader*)oldTableHeader);
			pageOffset += sizeof(FeepromPageHeader);
			(*numPages)++;
		}
	}

	return FEEPROM_STATUS_SUCCESS;
}

FEEPROM_Status FeepromTableWriteHeader(
		FeepromTableHeader *newTableHeader,
		FeepromTableHeader *tableHeaderBuffer
		)
{
	uint16 i;
	uint32 writtenOffset;

	writtenOffset = (uint32)newTableHeader;

	for(i = 0; i < sizeof(FeepromTableHeader)/2; i++)
	{
		FLASH_If_Write_Value16(writtenOffset, ((uint16*)tableHeaderBuffer)[i]);
		writtenOffset += 2;
	}

	printf("Wrote table header\n");

	return FEEPROM_STATUS_SUCCESS;
}

// todo switch to FeepromTableWriteHeader
static FEEPROM_Status writeTableHeader(void)
{
	uint16 i;
	uint16 *buffer;
	uint32 writtenOffset;

	buffer = (uint16*)&tableHeaderBuffer;
	writtenOffset = (uint32)newTableHeader;

	for(i = 0; i < sizeof(FeepromTableHeader)/2; i++)
	{
		FLASH_If_Write_Value16(writtenOffset, buffer[i]);
		writtenOffset += 2;
	}

	printf("Wrote table header\n");

	return FEEPROM_STATUS_SUCCESS;
}

static uint16 getTotalTableSize(uint8 numPages)
{
	uint16 i;
	uint16 totalSize = 0;

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		totalSize += tableHeaderBuffer.entryTable[i].size;
	}

	printf("Total entries size: %d\n", totalSize);

	totalSize += (numPages-1)*sizeof(FeepromPageHeader);

	totalSize += sizeof(FeepromTableHeader);

	printf("Total table size: %d\n", totalSize);

	return totalSize;
}

static FEEPROM_Status writeEntryData(uint16 *data, int16 size)
{
	int16 i;
	FeepromTableEntry* entry;
	uint16 *buffer;
	uint32 entryDataBase;


	getEntryBuffer(&entry, &buffer, &entryDataBase, data);

	for( i = 0; i < size/2; i++)
	{
		FLASH_If_Write_Value16(entryDataBase + entryBytesWritten, buffer[i]);

		entryBytesWritten += 2;

		if( entryBytesWritten == entry->size )
		{
			printf("Finished writing entry: %d\n", currentEntryIndex);

			entry->allocated = TRUE;
			currentEntryIndex++;
			entryBytesWritten = 0;

			if(currentEntryIndex == tableHeaderBuffer.entryCount)
			{
				writeTableHeader();
				FeepromPageErase((FeepromPageHeader*)FEEPROM_GET_TABLE_BASE());
				FEEPROM_SET_TABLE_BASE(newTableHeader);
				printf("Completed updating table. New base %08X\n", FEEPROM_GET_TABLE_BASE());
				break;
			}
			else
			{
				getEntryBuffer(&entry, &buffer, &entryDataBase, data);
			}
		}
	}

	return FEEPROM_STATUS_SUCCESS;
}

static FEEPROM_Status getEntryBuffer(FeepromTableEntry **entry, uint16 **buffer, uint32 *entryDataBase, uint16 *data)
{
	*entry = &tableHeaderBuffer.entryTable[currentEntryIndex];

	*entryDataBase = (uint32)(*entry)->data.ptr;

	// TODO multi-page, account for if the entry data base crossed page borders

	if((*entry)->allocated)
	{
		*entry = getTableEntry(FEEPROM_GET_TABLE_BASE(), (*entry)->key);
		if(*entry == NULL)
			return FEEPROM_STATUS_FAILURE;

		*buffer = (uint16*)((uint32)(*entry)->data.ptr + entryBytesWritten);
	}
	else
	{
		*buffer = data;
	}

	return FEEPROM_STATUS_SUCCESS;
}

















