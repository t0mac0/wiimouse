/*!
 * \file feeprom_mem_mgr.c
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
#include "feeprom_mem_mgr.h"
#include "settings_mgr/feeprom/table_mgr/feeprom_table_mgr.h"
#include "settings_mgr/feeprom/page_mgr/feeprom_page_mgr.h"
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

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE void bufferTableHeader(FeepromTableHeader *tableHeader);

PRIVATE Result updateEntryDataPointers(
                                       FeepromTableHeader *tableHeaderBuffer,
                                       FeepromTableHeader *newTableHeader,
                                       FEEPROM_EntryKey key
);

PRIVATE Result updateEntryInfo(
                               FeepromTableEntry *entry,
                               uint16 size,
                               FEEPROM_EntryFlag flags
);
PRIVATE Result writeEntryData(
                              FeepromTableHeader *newTableHeader,
                              FEEPROM_EntryKey key,
                              uint16 *data
);

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************



//*****************************************************************************//
PROTECTED Result FeepromMemRead(FEEPROM_EntryKey key, void *data, uint16 size, uint16 *bytesRead)
{
    Result result;
    FeepromTableEntry *entry;
    uint16 i;

    (*bytesRead) = 0;

    if(RESULT_IS_ERROR(result, FeepromGetTableEntry(FEEPROM_GET_TABLE_BASE(), &entry, key)))
    {
    }
    else if(size % 2)
    {
        result = SETTINGS_MGR_RESULT(INVALID_DATA_SIZE);
    }
    else
    {
        for(i = 0; i < entry->size/2 && i < size/2; i++)
        {
            ((uint16*)data)[i] = entry->data.ptr[i];
            (*bytesRead) += 2;
        }
    }

    return result;
}



//*****************************************************************************//
PROTECTED Result FeepromMemWrite(FEEPROM_EntryKey key, void *data, uint16 size, FEEPROM_EntryFlag flags)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);
    FeepromTableEntry *entry;
    FeepromTableHeader tableHeaderBuffer, *newTableHeader;

    bufferTableHeader(&tableHeaderBuffer);

    // todo support multi-page feeprom
    if(size > FEEPROM_PAGE_SIZE - tableHeaderBuffer.size )
    {
        result = SETTINGS_MGR_RESULT(TABLE_FULL);
    }
    else if( RESULT_IS_ERROR(result, FeepromGetTableEntry(&tableHeaderBuffer, &entry, key)) )
    {
    }
    else if( (entry->flags & FEEPROM_ENTRY_FLAG_PROTECTED) && (~flags & FEEPROM_ENTRY_FLAG_FORCE_WRITE) )
    {
        result = SETTINGS_MGR_RESULT(ENTRY_PROTECTED);
    }
    else if( (size > entry->size) &&
            RESULT_IS_ERROR(result, FeepromPageFindFreeSpace((void**)&entry->data.ptr, size)) )
    {
    }
    else if( RESULT_IS_ERROR(result, FeepromPageGetBlank((FeepromPageHeader**)&newTableHeader)) )
    {
    }
    else if( RESULT_IS_ERROR(result, updateEntryInfo(entry, size, flags)) )
    {
    }
    else if( RESULT_IS_ERROR(result, updateEntryDataPointers(&tableHeaderBuffer, newTableHeader, key)) )
    {
    }
    else if( RESULT_IS_ERROR(result, FeepromTableWriteHeader(newTableHeader, &tableHeaderBuffer)))
    {
    }
    else if( RESULT_IS_ERROR(result, writeEntryData(newTableHeader, key, data)))
    {
    }
    else
    {
        FEEPROM_SET_TABLE_BASE(newTableHeader);
    }

    return result;
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


//*****************************************************************************//
PRIVATE void bufferTableHeader(FeepromTableHeader *tableHeader)
{
    uint16 i;
    FeepromTableHeader *header = FEEPROM_GET_TABLE_BASE();

    for(i = 0; i < sizeof(FeepromTableHeader)/2; i++)
    {
        ((uint16*)tableHeader)[i] = ((uint16*)header)[i];
    }
}


//*****************************************************************************//
PRIVATE Result updateEntryDataPointers(
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
            ASSERT(0);
        }
    }

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PRIVATE Result updateEntryInfo(
                               FeepromTableEntry *entry,
                               uint16 size,
                               FEEPROM_EntryFlag flags
)
{
    entry->flags = flags;
    entry->size = size;

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PRIVATE Result writeEntryData(FeepromTableHeader *newTableHeader, FEEPROM_EntryKey key, uint16 *data)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);
    uint16 i;
    FeepromTableEntry *entry;
    FeepromTableHeader *oldPage;

    // TODO: support multi-paged FEEPROM

    oldPage = (FeepromTableHeader*)FEEPROM_GET_TABLE_BASE();

    for( i = 0; i < FEEPROM_ENTRY_COUNT; i++)
    {
        entry = (FeepromTableEntry *)&newTableHeader->entryTable[i];

        if(entry->key != key)
        {
            if( RESULT_IS_ERROR(result, HW_FLASH_Write16Bit((uint32)(entry->data.ptr), oldPage->entryTable[i].data.ptr, entry->size/2)) )
            {
                break;
            }
        }
        else
        {
            if( RESULT_IS_ERROR(result, HW_FLASH_Write16Bit((uint32)(entry->data.ptr), data, entry->size/2)) )
            {
                break;
            }
        }
    }

    FeepromPageErase((FeepromPageHeader*)oldPage);

    return result;
}
