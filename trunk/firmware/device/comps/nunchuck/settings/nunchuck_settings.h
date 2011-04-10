/*!
 * \file nunchuck_settings.h
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

#ifndef _NUNCHUCK_SETTINGS_H_
#define _NUNCHUCK_SETTINGS_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck/nunchuck.h"
#include "nunchuck/profile/nunchuck_profile.h"

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
    uint8 Min;
    uint8 Max;
    uint8 Neutral;
    uint16 Sensitivity;
} NunchuckSettingsJoyCoordCal;

PROTECTED typedef struct {
    NunchuckSettingsJoyCoordCal X;
    NunchuckSettingsJoyCoordCal Y;
} NunchuckSettingsJoyCal;

PROTECTED typedef struct {
    uint16 Min;
    uint16 Max;
    uint16 Neutral;
    uint16 Sensitivity;
} NunchuckSettingsAccCoordCal;

PROTECTED typedef struct {
    NunchuckSettingsAccCoordCal X;
    NunchuckSettingsAccCoordCal Y;
    NunchuckSettingsAccCoordCal Z;
} NunchuckSettingsAccCal;

PROTECTED typedef struct {
    NunchuckSettingsJoyCal JoyStick;
    NunchuckSettingsAccCal Accelerometer;
} NunchuckSettingsCalibration;


PROTECTED typedef struct {
    NunchuckSettingsCalibration Calibration;
    // NunhuckSettingsUserInterface UI;
    uint8 SlaveAddress;
    uint8 DataFormatterIndex;
    uint8 DataPointsPerHidReport;
} NunchuckSettingsInfo;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED Result NunchuckSettingsInit( void );

PROTECTED Result NunchuckSettingsUpdate( void );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern NunchuckSettingsInfo NunchuckSettings;


#endif /* NUNCHUCK_SETTINGS_H_ */
