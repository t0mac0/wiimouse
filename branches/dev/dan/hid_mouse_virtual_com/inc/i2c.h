/*
 * i2c.h
 *
 *  Created on: Jan 30, 2011
 *      Author: Reed
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f10x_type.h"
#include "stm32f10x_i2c.h"

void InitI2C2( void );
uint32 ReadBufferI2C2(uint8* pBuffer, uint8 ReadAddr, uint16 NumByteToRead);
uint32 WriteBufferI2C2(uint8* pBuffer, uint16 NumByteToWrite);

#endif /* I2C_H_ */
