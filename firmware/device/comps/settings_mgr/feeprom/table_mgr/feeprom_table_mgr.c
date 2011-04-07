/*!
 * \file feeprom_table_mgr.c
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
#include "feeprom_table_mgr.h"
#include "settings_mgr/feeprom/page_mgr/feeprom_page_mgr.h"
#include "hw_mgr/flash/hw_flash.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define TABLE_ENTRY_INIT(_te, _size, _id, _allocated, _flags, _dataPtr) \
        {                                                                       \
    _te->size = _size;                                                  \
    _te->key = _id;                                                     \
    _te->allocated = _allocated;                                        \
    _te->flags = _flags;                                                \
    _te->data.ptr = _dataPtr;                                           \
        }



/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE Result findTableHeader();
PRIVATE Result populateTableHeaderBuffer(FeepromTableHeader *newTableHeaderBuffer);
PRIVATE Result updateEntryDataPointers(FeepromTableHeader *oldTableHeader, uint16 *numPages);
PRIVATE uint16 getTotalTableSize(uint8 numPages);
PRIVATE Result writeEntryData(uint16 *data, int16 size);
PRIVATE Result getEntryBuffer(FeepromTableEntry **entry, uint16 **buffer, uint32 *entryDataBase, uint16 *data);


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE uint32 entryBytesWritten;
PRIVATE FeepromTableHeader tableHeaderBuffer;
PRIVATE FeepromTableHeader *newTableHeader;
PRIVATE bool updatingTable;
PRIVATE uint16 currentEntryIndex;



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//*****************************************************************************//
PROTECTED Result FeepromTableInit(void )
{
    updatingTable = FALSE;

    findTableHeader();

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PROTECTED Result FeepromTableUpdate(uint16 *data, uint16 size)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);

    if(!updatingTable && size < sizeof(FeepromTableHeader))
    {
        return SETTINGS_MGR_RESULT(INVALID_FIRST_PAGE);
    }
    else if(!updatingTable)
    {
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
        return SETTINGS_MGR_RESULT(INVALID_DATA_SIZE);
    }

    result = writeEntryData(data, size);

    return result;
}


//*****************************************************************************//
PROTECTED Result FeepromGetTableEntry(FeepromTableHeader *tableBase, FeepromTableEntry** entry, uint16 key)
{
    uint16 i;

    for(i = 0; i < tableBase->entryCount; i++)
    {
        if(tableBase->entryTable[i].key == key)
        {
            *entry = &tableBase->entryTable[i];
            return SETTINGS_MGR_RESULT(SUCCESS);
        }
    }

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PROTECTED Result FeepromTableWriteHeader(
                                         FeepromTableHeader *newTableHeader,
                                         FeepromTableHeader *tableHeaderBuffer
)
{
    return HW_FLASH_Write16Bit((uint32)newTableHeader, (uint16*)tableHeaderBuffer, sizeof(FeepromTableHeader)/2);
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


//*****************************************************************************//
PRIVATE Result findTableHeader()
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

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PRIVATE Result populateTableHeaderBuffer(FeepromTableHeader *newTableHeaderBuffer)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);
    FeepromTableHeader *oldTableHeader;
    uint16 i, numPages, id;
    FeepromTableEntry *oldEntry, *newEntry, *bufferedEntry;
    bool entryInOldTable, entryInNewTable;

    oldEntry = NULL;
    newEntry = NULL;
    oldTableHeader = FEEPROM_GET_TABLE_BASE();

    for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
    {
        bufferedEntry = &tableHeaderBuffer.entryTable[i];
        id = newTableHeaderBuffer->entryTable[i].key;

        entryInOldTable = IS_RESULT_SUCCESS(FeepromGetTableEntry(oldTableHeader, &oldEntry, id)) ? TRUE : FALSE;
        entryInNewTable = IS_RESULT_SUCCESS(FeepromGetTableEntry(newTableHeaderBuffer, &newEntry, id)) ? TRUE : FALSE;


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
            if( (oldEntry->flags & FEEPROM_ENTRY_FLAG_PROTECTED) && !(~(newEntry->flags) & FEEPROM_ENTRY_FLAG_FORCE_UPDATE) )
            {
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

    return result;
}


//*****************************************************************************//
PRIVATE Result updateEntryDataPointers(FeepromTableHeader *oldTableHeader, uint16 *numPages)
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

    return SETTINGS_MGR_RESULT(SUCCESS);
}


//*****************************************************************************//
PRIVATE uint16 getTotalTableSize(uint8 numPages)
{
    uint16 i;
    uint16 totalSize = 0;

    for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
    {
        totalSize += tableHeaderBuffer.entryTable[i].size;
    }


    totalSize += (numPages-1)*sizeof(FeepromPageHeader);

    totalSize += sizeof(FeepromTableHeader);

    return totalSize;
}


//*****************************************************************************//
PRIVATE Result writeEntryData(uint16 *data, int16 size)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);
    int16 i;
    FeepromTableEntry* entry;
    uint16 *buffer;
    uint32 entryDataBase;


    getEntryBuffer(&entry, &buffer, &entryDataBase, data);

    for( i = 0; i < size/2; i++)
    {
        if( RESULT_IS_ERROR(result, HW_FLASH_Write16Bit(entryDataBase + entryBytesWritten, &buffer[i], 1)) )
        {
            break;
        }

        entryBytesWritten += 2;

        if( entryBytesWritten == entry->size )
        {

            entry->allocated = TRUE;
            currentEntryIndex++;
            entryBytesWritten = 0;

            if(currentEntryIndex == tableHeaderBuffer.entryCount)
            {
                if( RESULT_IS_ERROR(result, FeepromTableWriteHeader(newTableHeader, &tableHeaderBuffer)) )
                {
                    break;
                }
                FeepromPageErase((FeepromPageHeader*)FEEPROM_GET_TABLE_BASE());
                FEEPROM_SET_TABLE_BASE(newTableHeader);
                break;
            }
            else
            {
                getEntryBuffer(&entry, &buffer, &entryDataBase, data);
            }
        }
    }

    return result;
}


//*****************************************************************************//
PRIVATE Result getEntryBuffer(FeepromTableEntry **entry, uint16 **buffer, uint32 *entryDataBase, uint16 *data)
{
    Result result = SETTINGS_MGR_RESULT(SUCCESS);
    *entry = &tableHeaderBuffer.entryTable[currentEntryIndex];

    *entryDataBase = (uint32)(*entry)->data.ptr;

    // TODO multi-page, account for if the entry data base crossed page borders

    if((*entry)->allocated)
    {

        if( RESULT_IS_ERROR(result, FeepromGetTableEntry(FEEPROM_GET_TABLE_BASE(), entry, (*entry)->key) ))
        {
            return SETTINGS_MGR_RESULT(INVALID_ENTRY);
        }

        *buffer = (uint16*)((uint32)(*entry)->data.ptr + entryBytesWritten);
    }
    else
    {
        *buffer = data;
    }

    return result;
}

