/*
 * feeprom_mem_utils.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#ifndef FEEPROM_MEM_MGR_H_
#define FEEPROM_MEM_MGR_H_

#include "feeprom.h"

FEEPROM_Status FeepromMemWrite(FEEPROM_EntryKey key, void *data, uint16 size, FEEPROM_EntryFlag flags);

FEEPROM_Status FeepromMemRead(FEEPROM_EntryKey key, void *data, uint16 size, uint16 *bytesRead);


#endif /* FEEPROM_MEM_UTILS_H_ */
