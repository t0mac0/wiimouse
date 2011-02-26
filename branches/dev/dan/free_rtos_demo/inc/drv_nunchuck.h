/********************************************************************************
Wii Nunchuk Driver
 
Name: drv_nunchuck.h

This is a driver for the Wii Nunchuck.


Author: Dan Riedler
Created: 2-11-10
 
*********************************************************************************/
#ifndef _DRV_NUNCHUCK_H_
#define _DRV_NUNCHUCK_H_

#include "stm32f10x_type.h"



bool nunchuck_ready( void );

/********************************************************************************
Nunchuck Initialization	

Name: nunchuck_init

Description:

Initializes the Nunchuck.

*********************************************************************************/
bool nunchuck_init( void );

/********************************************************************************
Read Nunchuck Data	

Name: nunchuck_read

Description:

Reads data from the nunchuck and stores in static buffer.

*********************************************************************************/
bool nunchuck_read( void );

/********************************************************************************
Get Nunchuck Joystick Position

Name: nunchuck_get_joystick

Description:

Returns the last read joystick position.

NOTE: nunchuck_read() should be called before using this function.

*********************************************************************************/
void nunchuck_get_joystick( u8 *x_val, u8 *y_val );

/********************************************************************************
Get Nunchuck Accelerometer Data

Name: nunchuck_get_accelerometer

Description:

Returns the last read accelerometer data.

NOTE: nunchuck_read() should be called before using this function.

*********************************************************************************/
void nunchuck_get_accelerometer( u16 *x_val, u16 *y_val, u16 *z_val );

/********************************************************************************
Get Nunchuck Button Values

Name: nunchuck_get_buttons

Description:

Returns the last read button values.

NOTE: nunchuck_read() should be called before using this function.

*********************************************************************************/
void nunchuck_get_buttons( u8 *btn_val );

/********************************************************************************
Z Nunchuck Button Pressed

Name: nunchuck_z_pressed

Description:

Returns TRUE if the last read value of the Z button was pressed, FALSE else.

NOTE: nunchuck_read() should be called before using this function.

*********************************************************************************/
bool nunchuck_z_pressed( void );

/********************************************************************************
C Nunchuck Button Pressed

Name: nunchuck_c_pressed

Description:

Returns TRUE if the last read value of the C button was pressed, FALSE else.

NOTE: nunchuck_read() should be called before using this function.

*********************************************************************************/
bool nunchuck_c_pressed( void );



#endif // _DRV_NUNCHUCK_H_
