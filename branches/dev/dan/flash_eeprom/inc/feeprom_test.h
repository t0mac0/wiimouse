/*
 * feeprom_test.h
 *
 *  Created on: Feb 21, 2011
 *      Author: Reed
 */

#ifndef FEEPROM_TEST_H_
#define FEEPROM_TEST_H_

#include "ifc_feeprom.h"

#define TEST_DATA	\
{					\
	1,\
	2,\
	3,\
	4,\
	5,\
	6,\
	7,\
	8\
}

  FEEPROM_ADD_ENTRY(FEEPROM_ENTRY_TEST, TEST_DATA, 8, FEEPROM_ENTRY_FORCE_UPDATE);


#define TEST_DATA2	\
{					\
	1,\
	2,\
	3,\
	4\
}

  FEEPROM_ADD_ENTRY(FEEPROM_ENTRY_TEST2, TEST_DATA2, 4, FEEPROM_ENTRY_FORCE_UPDATE);

#define TEST_DATA3	\
{					\
	1,\
	2,\
	3,\
	4,\
	5,\
	6\
}

  FEEPROM_ADD_ENTRY(FEEPROM_ENTRY_TEST3, TEST_DATA3, 6, FEEPROM_ENTRY_FORCE_UPDATE);


  void feepromTest();


#endif /* FEEPROM_TEST_H_ */
