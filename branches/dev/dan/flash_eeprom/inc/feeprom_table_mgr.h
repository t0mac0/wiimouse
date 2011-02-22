/*
 * feeprom_table_mgr.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#ifndef FEEPROM_TABLE_MGR_H_
#define FEEPROM_TABLE_MGR_H_

#include "feeprom.h"

#define FEEPROM_GET_TABLE_BASE() (feepromTableHeader )
#define FEEPROM_SET_TABLE_BASE(_base) (feepromTableHeader = _base)
#define FEEPROM_GET_TABLE_STATUS() (feepromTableHeader->pageHeader.status)

FEEPROM_Status FeepromTableInit( void );

FEEPROM_Status FeepromTableUpdate(uint16 *data, uint16 size);

FEEPROM_Status FeepromGetTableEntry(FeepromTableHeader *tableBase, FeepromTableEntry** entry, uint16 key);

FEEPROM_Status FeepromTableWriteHeader(
		FeepromTableHeader *newTableHeader,
		FeepromTableHeader *tableHeaderBuffer
		);

FEEPROM_Status FeepromDefrageTable();

#endif /* FEEPROM_TABLE_MGR_H_ */
