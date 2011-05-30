/*!
 * \file nunchuck_filter_joy.c
 *
 * \brief 
 *
 *
 * \date Apr 9, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "nunchuck_filter_joy.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define MULTIPLY_FACTOR 0x8000
#define MULTIPLY_FACTOR_LOG 15

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct
{
    int32 mMin;
    int32 mMax;
    int32 yIntMin;
    int32 yIntMax;
    uint8 neutral;
} NormalizationCalParam;


typedef struct
{
    NormalizationCalParam X;
    NormalizationCalParam Y;
} NormalizationCal;


/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE inline void NormalizeData(pNunchuckJoystickData DataPt);



/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE NormalizationCal normalizationCal;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/*****************************************************************************/
PROTECTED void NunchuckFilterJoystickSetCalibration( pNunchuckCtlCalibration Calibration )
{
    pNunchuckCtlJsAxisCal jsCal;

    jsCal = &Calibration->Joystick.X;
    normalizationCal.X.neutral = jsCal->Neutral;
    normalizationCal.X.yIntMin = -127 - ((((int32)jsCal->Min * -127) * MULTIPLY_FACTOR) / ((int32)jsCal->Min - (int32)jsCal->Neutral));
    normalizationCal.X.yIntMax = -((((int32)jsCal->Neutral * 127) * MULTIPLY_FACTOR) / ((int32)jsCal->Max - (int32)jsCal->Neutral));
    normalizationCal.X.mMin = (-127 * MULTIPLY_FACTOR ) / ((int32)jsCal->Min - (int32)jsCal->Neutral);
    normalizationCal.X.mMax = ( 127 * MULTIPLY_FACTOR ) / ((int32)jsCal->Max - (int32)jsCal->Neutral);

    jsCal = &Calibration->Joystick.Y;
    normalizationCal.Y.neutral = jsCal->Neutral;
    normalizationCal.Y.yIntMin = 127 - ((((int32)jsCal->Min * 127) * MULTIPLY_FACTOR) / ((int32)jsCal->Min - (int32)jsCal->Neutral));
    normalizationCal.X.yIntMax = -((((int32)jsCal->Neutral * -127) * MULTIPLY_FACTOR) / ((int32)jsCal->Max - (int32)jsCal->Neutral));
    normalizationCal.Y.mMin = ( 127 * MULTIPLY_FACTOR ) / ((int32)jsCal->Min - (int32)jsCal->Neutral);
    normalizationCal.Y.mMax = (-127 * MULTIPLY_FACTOR ) / ((int32)jsCal->Max - (int32)jsCal->Neutral);
}

/*****************************************************************************/

// TODO: actually filter the joystick data
PROTECTED void NunchuckFilterJoystickData( void )
{
    uint8 newest;
    pNunchuckData dataPt;

    newest = NunchuckRawData.NextPoint - 1;
    if(newest > NunchuckRawData.TotalDataPtCount) newest = NunchuckRawData.TotalDataPtCount - 1;

    dataPt = &NunchuckRawData.DataPts[newest];

    NormalizeData(&dataPt->Joystick);


}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

/*****************************************************************************/
PRIVATE inline void NormalizeData(pNunchuckJoystickData DataPt)
{
    if( DataPt->X < normalizationCal.X.neutral )
    {
        DataPt->X = (uint8)((((int32)DataPt->X * normalizationCal.X.mMin) + normalizationCal.X.yIntMin) >> MULTIPLY_FACTOR_LOG);
    }
    else if( DataPt->X > normalizationCal.X.neutral )
    {
        DataPt->X = (uint8)((((int32)DataPt->X * normalizationCal.X.mMax) + normalizationCal.X.yIntMax) >> MULTIPLY_FACTOR_LOG);
    }
    else
    {
        DataPt->X = 0;
    }

    if( DataPt->Y < normalizationCal.Y.neutral )
    {
        DataPt->Y = (uint8)((((int32)DataPt->Y * normalizationCal.Y.mMin) + normalizationCal.Y.yIntMin) >> MULTIPLY_FACTOR_LOG);
    }
    else if( DataPt->Y > normalizationCal.Y.neutral )
    {
        DataPt->Y = (uint8)((((int32)DataPt->Y * normalizationCal.Y.mMax) + normalizationCal.Y.yIntMax) >> MULTIPLY_FACTOR_LOG);
    }
    else
    {
        DataPt->Y = 0;
    }
}













