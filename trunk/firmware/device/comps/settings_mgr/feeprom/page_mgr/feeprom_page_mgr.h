/*!
 * \file feeprom_page_mgr.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _FEEPROM_PAGE_MGR_H_
#define _FEEPROM_PAGE_MGR_H_

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
#define FEEPROM_GET_PAGE_BASE(n)  (  ((uint8*)&feepromBaseHeader + (n*FEEPROM_PAGE_SIZE)) )
#define FEEPROM_GET_PAGE_NUMBER(n) (  (uint32)n & 0xFFFFC000 )
#define FEEPROM_GET_PAGE_STATUS(n) ( ((FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(n))->status )
#define FEEPROM_GET_PAGE_FLAGS(n) ( ((FeepromPageHeader*)FEEPROM_GET_PAGE_BASE(n))->flags )


/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result FeepromPageInit(void);

PROTECTED Result FeepromPageGetBlank(FeepromPageHeader **pageHeader);

PROTECTED Result FeepromPageGetNextBlank(FeepromPageHeader** nextPageHeader, FeepromPageHeader *nextToBeErasePage);

PROTECTED Result FeepromPageErase(FeepromPageHeader *pageHeader);

PROTECTED Result FeepromPageForceBlank(FeepromPageHeader **pageHeader);

PROTECTED Result FeepromPageFindFreeSpace(void **pageOffset, uint16 size);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* FEEPROM_PAGE_MGR_H_ */
