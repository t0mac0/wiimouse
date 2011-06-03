/*!
 * \file feeprom.c
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
#include "feeprom.h"
#include "feeprom_preprocess_entry.h"
#include "settings_mgr/feeprom/table_mgr/feeprom_table_mgr.h"
#include "settings_mgr/feeprom/page_mgr/feeprom_page_mgr.h"
#include "settings_mgr/feeprom/mem_mgr/feeprom_mem_mgr.h"

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

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED FeepromTableHeader *feepromTableHeader;

//PROTECTED FeepromTableHeader feepromBaseHeader  __attribute ((section(".flash_eeprom"))) =
		PROTECTED FeepromTableHeader feepromBaseHeader   =
{
        { PAGE_STATUS_WRITTEN,  // page status
                PAGE_FLAG_IS_TABLE }, // page flags
                _$FEEPROM_ENTRY_COUNT$_,    // entry count
                0, // page count
                NULL, // size
                _$FEEPROM_ENTRIES$_  // entries
};

//PROTECTED uint16 feepromEntryData1[FEEPROM_PAGE_SIZE/2-sizeof(FeepromTableHeader)] __attribute ((section(".flash_eeprom"))) = _$FEEPROM_ENTRY_DATA$_;
// page 2
//ROTECTED uint16 feepromEntryData2[FEEPROM_PAGE_SIZE/2] __attribute ((section(".flash_eeprom"))) __attribute ((aligned(FEEPROM_PAGE_SIZE)));
// page 3
//uint16 feepromEntryData3[FEEPROM_PAGE_SIZE/2] __attribute ((section(".flash_eeprom"))) __attribute ((aligned(FEEPROM_PAGE_SIZE)));


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//*****************************************************************************//
PUBLIC Result FEEPROM_Init( void )
{
    Result result;


    FLASH_Unlock();

    if( RESULT_IS_ERROR(result, FeepromTableInit()) )
    {

    }
    // must be call after table init
    else if( RESULT_IS_ERROR(result, FeepromPageInit()) )
    {

    }

    return result;
}


//*****************************************************************************//
PUBLIC Result FEEPROM_Write( FEEPROM_EntryKey key, void *data, uint16 size, FEEPROM_EntryFlag flags)
{
    Result result;

    if( key == FEEPROM_ENTRY_TABLE_HEADER)
    {
        result = FeepromTableUpdate(data, size);
    }
    else
    {
        result = FeepromMemWrite(key, data, size, flags);
    }

    return result;
}


//*****************************************************************************//
PUBLIC Result FEEPROM_Read( FEEPROM_EntryKey key, void *data, uint16 size, uint16 *bytesRead)
{

    return FeepromMemRead(key, data, size, bytesRead);
}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

