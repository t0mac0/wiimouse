/*!
 * \file nunchuck_ctl_types.h
 *
 * \brief 
 *
 *
 * \date May 29, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_CTL_TYPES_H_
#define _NUNCHUCK_CTL_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

PROTECTED typedef struct
{
    uint8 Min;
    uint8 Max;
    uint8 Neutral;
} NunchuckCtlJsAxisCal, *pNunchuckCtlJsAxisCal;

PROTECTED typedef struct
{
    NunchuckCtlJsAxisCal X;
    NunchuckCtlJsAxisCal Y;
} NunchuckCtlJoystickCal, *pNunchuckCtlJoystickCal;

PROTECTED typedef struct
{
    uint16 X;
    uint16 Y;
    uint16 Z;
} NunchuckCtlAcceleromterCal;


PROTECTED typedef struct
{
    NunchuckCtlJoystickCal Joystick;
    NunchuckCtlAcceleromterCal Accelerometer;
} NunchuckCtlCalibration, *pNunchuckCtlCalibration;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* NUNCHUCK_CTL_TYPES_H_ */
