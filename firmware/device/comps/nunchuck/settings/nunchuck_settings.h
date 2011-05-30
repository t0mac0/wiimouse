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
    uint32 Sensitivity;
} NunchuckSettingsAxisCoordCal;

PROTECTED typedef struct {
    NunchuckSettingsAxisCoordCal X;
    NunchuckSettingsAxisCoordCal Y;
} NunchuckSettingsJoyCal;


PROTECTED typedef struct {
    NunchuckSettingsAxisCoordCal X;
    NunchuckSettingsAxisCoordCal Y;
    NunchuckSettingsAxisCoordCal Z;
} NunchuckSettingsAccCal;

PROTECTED typedef struct {
    NunchuckSettingsJoyCal JoyStick;
    NunchuckSettingsAccCal Accelerometer;
} NunchuckSettingsCalibration;


PROTECTED typedef struct {
    NunchuckSettingsCalibration Calibration;
    // NunhuckSettingsUserInterface UI;
    uint8 ProfileIndex;
    uint8 DataPointsPerHidReport;
    uint8 HidReportInterval; // ms
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
