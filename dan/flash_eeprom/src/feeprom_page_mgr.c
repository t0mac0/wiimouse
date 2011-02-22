/*
 * feeprom_page_mgr.c
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#include "feeprom_table_mgr.h"
#include "feeprom_page_mgr.h"
#include "flash_if.h"
#include "printf.h"

typedef struct {
	uint32 pointer;
	uint16 size;
} EntrySizePointer;

typedef struct {
	uint32 eraseCount;
} PageInfo;

void sortEntryPointers(EntrySizePointer *entries);



static PageInfo pageInfo[FEEPROM_PAGE_COUNT];


FEEPROM_Status FeepromPageInit(void)
{
	uint16 i;

	for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
	{
		pageInfo[i].eraseCount = 0;
	}

	return FEEPROM_STATUS_SUCCESS;
}


FEEPROM_Status FeepromPageGetBlank(FeepromPageHeader **pageHeader)
{
	uint16 i, min = 0xFFFF;
	int16 pageIndex = -1;

	for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
	{
		if( FEEPROM_GET_PAGE_STATUS(i) & PAGE_STATUS_ERASED )
		{
			if(pageInfo[i].eraseCount < min)
			{
				min = pageInfo[i].eraseCount;
				pageIndex = i;
			}
		}
	}

	if(pageIndex >= 0)
	{
		*pageHeader = (FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(pageIndex);
		pageInfo[pageIndex].eraseCount++;
		return FEEPROM_STATUS_SUCCESS;
	}
	else
	{
		printf("Error, no blank pages\n");
		*pageHeader = NULL;
		return FEEPROM_STATUS_FAILURE;
	}
}

FEEPROM_Status FeepromPageGetNextBlank(FeepromPageHeader** nextPageHeader, FeepromPageHeader *nextToBeErasePage)
{
	uint16 i, min = 0xFFFF;
	int16 pageIndex = -1;

	for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
	{
		if( (FEEPROM_GET_PAGE_STATUS(i) & PAGE_STATUS_ERASED))
		{
			if(pageInfo[i].eraseCount < min)
			{
				min = pageInfo[i].eraseCount;
				pageIndex = i;
			}
		}
	}

	if(pageIndex > 0)
	{
		*nextPageHeader = (FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(pageIndex);
	}
	else
	{
		*nextPageHeader = nextToBeErasePage;
	}

	return FEEPROM_STATUS_SUCCESS;
}

FEEPROM_Status FeepromPageForceBlank(FeepromPageHeader **pageHeader)
{
	uint16 i;

	for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
	{
		if( !(FEEPROM_GET_PAGE_FLAGS(i) & PAGE_FLAG_IS_TABLE) )
		{
			*pageHeader = (FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(i);
			printf("Forcing page %08X to be blank\n", *pageHeader);
			FeepromPageErase(*pageHeader);
			break;
		}
	}

	return FEEPROM_STATUS_SUCCESS;
}

FEEPROM_Status FeepromPageErase(FeepromPageHeader *pageHeader)
{

	FLASH_If_Erase( ((uint32)pageHeader)|FLASH_BASE, 2);

	return FEEPROM_STATUS_SUCCESS;
}

FEEPROM_Status FeepromPageFindFreeSpace(void **pageOffset, uint16 size)
{
	FEEPROM_Status status = FEEPROM_STATUS_SUCCESS;
	uint32 offset;
	uint16 i;
	EntrySizePointer entries[FEEPROM_ENTRY_COUNT];

	// todo support multi-paged feeprom


	// sort entry pointers is ascending order
	sortEntryPointers(entries);

	offset = (uint32)FEEPROM_GET_TABLE_BASE() + sizeof(FeepromTableHeader);

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		// try to fit in-between other entries
		if( offset + size <= entries[i].pointer )
		{
			printf("Fitting entry in-between old entries %d and %d\n", i-1, i);
			break;
		}
		else
		{
			offset = entries[i].pointer + entries[i].size;
		}

	}


	if( offset + size < (uint32)FEEPROM_GET_TABLE_BASE() + FEEPROM_PAGE_SIZE )
	{
		*pageOffset = (void*)(offset);
		printf("Found page offset: %X\n", *pageOffset);
	}
	else
	{
		status = FEEPROM_STATUS_FAILURE;
	}


	return status;
}

	// sort entry pointers is ascending order
void sortEntryPointers(EntrySizePointer *entries)
{
	uint16 iPos, iMin, i;
	FeepromTableHeader *tableHeader;

	tableHeader = FEEPROM_GET_TABLE_BASE();

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		entries[i].pointer = (uint32)tableHeader->entryTable[i].data.ptr;
		entries[i].size = (uint32)tableHeader->entryTable[i].size;
	}

	/* advance the position through the entire array */
	/*   (could do iPos < n-1 because single element is also min element) */
	for (iPos = 0; iPos < FEEPROM_ENTRY_COUNT; iPos++)
	{
	  /* find the min element in the unsorted a[iPos .. n-1] */

	  /* assume the min is the first element */
	  iMin = iPos;
	  /* test against all other elements */
	  for (i = iPos+1; i < FEEPROM_ENTRY_COUNT; i++)
	    {
	      /* if this element is less, then it is the new minimum */
	      if (entries[i].pointer < entries[iMin].pointer)
	        {
	          /* found new minimum; remember its index */
	          iMin = i;
	        }
	    }

	  /* iMin is the index of the minimum element. Swap it with the current position */
	  if ( iMin != iPos )
	  {
		  EntrySizePointer tmp;

		  tmp.pointer = entries[iPos].pointer;
		  tmp.size = entries[iPos].size;

		  entries[iPos].pointer = entries[iMin].pointer;
		  entries[iPos].size = entries[iMin].size;

		  entries[iMin].pointer = tmp.pointer;
		  entries[iMin].size = tmp.size;

	  }
	}
}
