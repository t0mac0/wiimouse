/*
 * feeprom_page_mgr.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#ifndef FEEPROM_PAGE_MGR_H_
#define FEEPROM_PAGE_MGR_H_

#include "feeprom.h"

#define FEEPROM_GET_PAGE_BASE(n)  (  ((uint8*)&feepromBaseHeader + (n*FEEPROM_PAGE_SIZE)) )
#define FEEPROM_GET_PAGE_NUMBER(n) (  (uint32)n & 0xFFFFC000 )
#define FEEPROM_GET_PAGE_STATUS(n) ( ((FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(n))->status )
#define FEEPROM_GET_PAGE_FLAGS(n) ( ((FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(n))->flags )

FEEPROM_Status FeepromPageInit(void);

FEEPROM_Status FeepromPageGetBlank(FeepromPageHeader **pageHeader);

FEEPROM_Status FeepromPageGetNextBlank(FeepromPageHeader** nextPageHeader, FeepromPageHeader *nextToBeErasePage);

FEEPROM_Status FeepromPageErase(FeepromPageHeader *pageHeader);

FEEPROM_Status FeepromPageForceBlank(FeepromPageHeader **pageHeader);

FEEPROM_Status FeepromPageFindFreeSpace(void **pageOffset, uint16 size);

#endif /* FEEPROM_PAGE_MGR_H_ */
