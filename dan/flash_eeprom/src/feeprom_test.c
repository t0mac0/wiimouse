/*
 * feeprom_test.c
 *
 *  Created on: Feb 21, 2011
 *      Author: Reed
 */

#include "feeprom_test.h"
#include "printf.h"

#define TEST_DATA4	\
		{					\
	0x1,\
	0xFEED,\
	0xDEAD,\
	0xADD,\
	5,\
	6\
		}

FEEPROM_ADD_ENTRY(FEEPROM_ENTRY_TEST4, TEST_DATA4, 6, FEEPROM_ENTRY_FORCE_UPDATE);

void feepromTest()
{
	uint16 buffer[164];
	uint16 i, j;
	uint16 bytesRead;
	FEEPROM_EntryKey keys[] = {FEEPROM_ENTRY_DFU_MODE,FEEPROM_ENTRY_TEST,FEEPROM_ENTRY_TEST2,FEEPROM_ENTRY_TEST3,FEEPROM_ENTRY_TEST4};

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{
		FEEPROM_Read(keys[i], buffer, 64*2, &bytesRead);
		printf("Read key: %d\n", keys[i]);
		for(j = 0; j < bytesRead/2; j++)
		{
			printf("%X ", buffer[j]);
		}
		printf("\n");

		for(j = 0; j < bytesRead*3/2; j++)
		{
			buffer[j] = j;
		}
		printf("Writing key: %d\n", keys[i]);
		FEEPROM_Write(keys[i], buffer, bytesRead*3, FEEPROM_ENTRY_PROTECTED);

		for(j = 0; j < bytesRead*3/2; j++)
		{
			buffer[j] *=0;
		}

		printf("Read key: %d\n", keys[i]);
		FEEPROM_Read(keys[i], buffer, 64*2, &bytesRead);
		for(j = 0; j < bytesRead/2; j++)
		{
			printf("%X ", buffer[j]);
			buffer[j] *=2;
		}
		printf("\n");

		printf("Writing key: %d\n", keys[i]);
		FEEPROM_Write(keys[i], buffer, bytesRead*3, 0);

	}

	for(i = 0; i < FEEPROM_ENTRY_COUNT; i++)
	{

	}
}

