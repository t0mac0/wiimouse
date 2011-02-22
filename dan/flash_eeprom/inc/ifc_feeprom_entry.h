/*
 * ifc_flash_eeprom_entry.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#ifndef IFC_FEEPROM_ENTRY_H_
#define IFC_FEEPROM_ENTRY_H_


typedef uint16 FEEPROM_EntryFlag;
enum {
	FEEPROM_ENTRY_PROTECTED = ( 1 << 0),  	// entry cannot be overwritten unless FORCE_WRITE or FORCE_UPDATE flag used
	FEEPROM_ENTRY_FORCE_UPDATE = ( 1 << 1), // force entry overwrite on firmware update
	FEEPROM_ENTRY_FORCE_WRITE = ( 1 << 2),  // force entry overwrite during program execution
} ;

typedef uint16 FEEPROM_EntryKey;
enum {
	FEEPROM_ENTRY_DFU_MODE = 1,
	FEEPROM_ENTRY_TEST = 47,
	FEEPROM_ENTRY_TEST2 = 2344,
	FEEPROM_ENTRY_TEST3 = 456,
	FEEPROM_ENTRY_TEST4 = 124,

	FEEPROM_ENTRY_COUNT = 5,  // should come next to last

	FEEPROM_ENTRY_TABLE_HEADER = 0xFFFF // should come last (not an actual entry into table)
} ;


#endif /* IFC_FLASH_EEPROM_ENTRY_H_ */
