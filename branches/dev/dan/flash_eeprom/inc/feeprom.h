/*
 * flash_eeprom.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#ifndef FEEPROM_H_
#define FEEPROM_H_

#include "flash_if.h"
#include "stm32f10x_flash.h"

#include "ifc_feeprom.h"
#include "ifc_feeprom_entry.h"

// todo move to more general file
#define FEEPROM_PAGE_COUNT 2
#define FEEPROM_PAGE_SIZE 0x4000

typedef uint16 FeepromPageStatus;
enum {
	PAGE_STATUS_ERASED = 0xFFFF,
	PAGE_STATUS_WRITTEN = 1
};

typedef uint16 FeepromPageFlags;
enum {
	PAGE_FLAG_IS_TABLE = (1 << 0),
};


#pragma pack(push, 2)

typedef struct {
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

typedef struct {
	FeepromPageStatus status;
	FeepromPageFlags flags;
} FeepromPageHeader;

typedef struct {
	FeepromPageHeader pageHeader;
	uint16 entryCount;
	uint16 pageCount;
	uint16 size;
	FeepromTableEntry entryTable[FEEPROM_ENTRY_COUNT];
} FeepromTableHeader;
#pragma pack(pop)

extern FeepromTableHeader *feepromTableHeader;
extern FeepromTableHeader feepromBaseHeader;

#endif /* FLASH_EEPROM_H_ */
