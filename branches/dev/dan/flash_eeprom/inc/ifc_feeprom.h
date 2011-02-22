/*
 * ifc_flash_eeprom.h
 *
 *  Created on: Feb 19, 2011
 *      Author: Reed
 */

#ifndef IFC_FEEPROM_H_
#define IFC_FEEPROM_H_

#include "stm32f10x_type.h"
#include "ifc_feeprom_entry.h"

#define intToShort(x) (x & 0xFFFF),((x >> 16) & 0xFFFF)


typedef enum {
	FEEPROM_STATUS_SUCCESS,
	FEEPROM_STATUS_FAILURE,
} FEEPROM_Status;


#define FEEPROM_SUCCESS(result, func) ( (result=func) == FEEPROM_STATUS_SUCCESS )

#define FEEPROM_ADD_ENTRY(key, data, size, flag)


FEEPROM_Status FEEPROM_Init( void );

FEEPROM_Status FEEPROM_Write( FEEPROM_EntryKey key, void *data, uint16 size, FEEPROM_EntryFlag flags);

FEEPROM_Status FEEPROM_Read( FEEPROM_EntryKey key, void *data, uint16 size, uint16 *bytesRead);


#endif /* IFC_FLASH_EEPROM_H_ */
