/*!
 * \file feeprom_page_mgr.c
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "feeprom_page_mgr.h"
#include "settings_mgr/feeprom/table_mgr/feeprom_table_mgr.h"
#include "hw_mgr/flash/hw_flash.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct {
    uint32 pointer;
    uint16 size;
} EntrySizePointer;

typedef struct {
    uint32 eraseCount;
} PageInfo;


/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE void sortEntryPointers(EntrySizePointer *entries);


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE PageInfo pageInfo[FEEPROM_PAGE_COUNT];



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//*****************************************************************************//
PROTECTED Result  FeepromPageInit(void)
{
    uint16 i;

    for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
    {
        pageInfo[i].eraseCount = 0;
    }

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PROTECTED Result  FeepromPageGetBlank(FeepromPageHeader **pageHeader)
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
        return SETTINGS_MGR_RESULT(SUCCESS);
    }
    else
    {
        *pageHeader = NULL;
        return SETTINGS_MGR_RESULT(NO_BLANK_PAGES);
    }
}


//*****************************************************************************//
PROTECTED Result  FeepromPageGetNextBlank(FeepromPageHeader** nextPageHeader, FeepromPageHeader *nextToBeErasePage)
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

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PROTECTED Result  FeepromPageForceBlank(FeepromPageHeader **pageHeader)
{
    uint16 i;

    for(i = 0; i < FEEPROM_PAGE_COUNT; i++)
    {
        if( !(FEEPROM_GET_PAGE_FLAGS(i) & PAGE_FLAG_IS_TABLE) )
        {
            *pageHeader = (FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(i);
            FeepromPageErase(*pageHeader);
            break;
        }
    }

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PROTECTED Result  FeepromPageErase(FeepromPageHeader *pageHeader)
{
    return HW_FLASH_ErasePages(((uint32)pageHeader)|FLASH_BASE, 1);
}


//*****************************************************************************//
PROTECTED Result  FeepromPageFindFreeSpace(void **pageOffset, uint16 size)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);
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
    }
    else
    {
        result = SETTINGS_MGR_RESULT(NO_FREE_SPACE);
    }


    return result;
}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


//*****************************************************************************//
// sort entry pointers is ascending order
PRIVATE void sortEntryPointers(EntrySizePointer *entries)
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
