/*!
 * \file nunchuck_types.h
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_TYPES_H_
#define _NUNCHUCK_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PROTECTED typedef struct {
    uint8 X;
    uint8 Y;
} NunchuckJoystickData, *pNunchuckJoystickData;

PROTECTED typedef struct {
    int16 X;
    int16 Y;
    int16 Z;
} NunchuckAccelerometerData, *pNunchuckAccelerometerData;

PROTECTED typedef union {
    struct {
        uint8 Z : 1;
        uint8 C : 1;
        uint8 unused : 6;
    } Button;
    uint8 Buttons;
} NunchuckButtonData, *pNunchuckButtonData;

PROTECTED typedef struct {
    NunchuckJoystickData Joystick;
    NunchuckAccelerometerData Accelerometer;
    NunchuckButtonData Buttons;
} NunchuckData, *pNunchuckData;



/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* NUNCHUCK_TYPES_H_ */
