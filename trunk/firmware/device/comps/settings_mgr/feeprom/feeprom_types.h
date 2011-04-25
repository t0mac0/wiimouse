/*!
 * \file feeprom_types.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _FEEPROM_TYPES_H_
#define _FEEPROM_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "feeprom.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define FEEPROM_PAGE_COUNT 2
#define FEEPROM_PAGE_SIZE 0x400
#define FEEPROM_ENTRY_COUNT SETTINGS_MGR_ENTRY_COUNT
#define FEEPROM_ENTRY_TABLE_HEADER SETTINGS_MGR_ENTRY_NULL

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef enum {
    FEEPROM_ENTRY_FLAG_PROTECTED                     = ( 1 << 0), // entry cannot be overwritten unless FORCE_WRITE or FORCE_UPDATE flag used
    FEEPROM_ENTRY_FLAG_FORCE_UPDATE                  = ( 1 << 1), // force entry overwrite on firmware update
    FEEPROM_ENTRY_FLAG_FORCE_WRITE                   = ( 1 << 2), // force entry overwrite during program execution

    FEEPROM_ENTRY_FLAG_NULL                          = 0xFFFF
} FEEPROM_EntryFlag;


PUBLIC typedef uint16 FEEPROM_EntryKey;


PROTECTED typedef enum {
    PAGE_STATUS_ERASED = 0xFFFF,
    PAGE_STATUS_WRITTEN = 1
} FeepromPageStatus;

PROTECTED typedef enum {
    PAGE_FLAG_IS_TABLE = (1 << 0),
} FeepromPageFlags;


#pragma pack(push, 2)

PROTECTED typedef struct {
    uint16 size;
    FEEPROM_EntryKey key;
    uint16 allocated;
    FEEPROM_EntryFlag flags;
    union {
        uint16 ptrH;
        uint16 ptrL;
        uint16 *ptr;
    } data;
} FeepromTableEntry;

PROTECTED typedef struct {
    FeepromPageStatus status;
    FeepromPageFlags flags;
} FeepromPageHeader;

PROTECTED typedef struct {
    FeepromPageHeader pageHeader;
    uint16 entryCount;
    uint16 pageCount;
    uint16 size;
    FeepromTableEntry entryTable[FEEPROM_ENTRY_COUNT];
} FeepromTableHeader;
#pragma pack(pop)




/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern FeepromTableHeader *feepromTableHeader;
PROTECTED extern FeepromTableHeader feepromBaseHeader;



#endif /* FEEPROM_TYPES_H_ */
