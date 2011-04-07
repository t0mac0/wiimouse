/*!
 * \file feeprom_table_mgr.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _FEEPROM_TABLE_MGR_H_
#define _FEEPROM_TABLE_MGR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "settings_mgr/feeprom/feeprom.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define FEEPROM_GET_TABLE_BASE() (feepromTableHeader )
#define FEEPROM_SET_TABLE_BASE(_base) (feepromTableHeader = _base)
#define FEEPROM_GET_TABLE_STATUS() (feepromTableHeader->pageHeader.status)



/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result FeepromTableInit( void );

PROTECTED Result FeepromTableUpdate(uint16 *data, uint16 size);

PROTECTED Result FeepromGetTableEntry(FeepromTableHeader *tableBase, FeepromTableEntry** entry, uint16 key);

PROTECTED Result FeepromTableWriteHeader(
        FeepromTableHeader *newTableHeader,
        FeepromTableHeader *tableHeaderBuffer
        );

PROTECTED Result FeepromDefrageTable( void );


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* FEEPROM_TABLE_MGR_H_ */
