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
#define MULTIPLY_FACTOR 0x8000uL
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
PRIVATE int32 calculateYIntercept(int32 a, int32 b, int32 c);
PRIVATE int32 calculateSlope(int32 a, int32 b, int32 c);


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
    normalizationCal.X.yIntMin = calculateYIntercept((int32)jsCal->Min, (int32)jsCal->Neutral, -127L);
    normalizationCal.X.yIntMax = calculateYIntercept((int32)jsCal->Max, (int32)jsCal->Neutral, 127L);
    normalizationCal.X.mMin = calculateSlope((int32)jsCal->Min, (int32)jsCal->Neutral, -127L);
    normalizationCal.X.mMax = calculateSlope((int32)jsCal->Max, (int32)jsCal->Neutral, 127L);

    jsCal = &Calibration->Joystick.Y;
    normalizationCal.Y.neutral = jsCal->Neutral;
    normalizationCal.Y.yIntMin = calculateYIntercept((int32)jsCal->Min, (int32)jsCal->Neutral, 127L);
    normalizationCal.Y.yIntMax = calculateYIntercept((int32)jsCal->Max, (int32)jsCal->Neutral, -127L);
    normalizationCal.Y.mMin = calculateSlope((int32)jsCal->Min, (int32)jsCal->Neutral, 127L);
    normalizationCal.Y.mMax = calculateSlope((int32)jsCal->Max, (int32)jsCal->Neutral, -127L);


    LOG_Printf("Joystick Normalized Calibration:\n");
    LOG_Printf("\tX neutral: %d\n", normalizationCal.X.neutral);
    LOG_Printf("\tX yIntMin: %d\n", normalizationCal.X.yIntMin);
    LOG_Printf("\tX yIntMax: %d\n", normalizationCal.X.yIntMax);
    LOG_Printf("\tX mMin: %d\n", normalizationCal.X.mMin);
    LOG_Printf("\tX mMax: %d\n", normalizationCal.X.mMax);
    LOG_Printf("\tY neutral: %d\n", normalizationCal.Y.neutral);
    LOG_Printf("\tY yIntMin: %d\n", normalizationCal.Y.yIntMin);
    LOG_Printf("\tY yIntMax: %d\n", normalizationCal.Y.yIntMax);
    LOG_Printf("\tY mMin: %d\n", normalizationCal.Y.mMin);
    LOG_Printf("\tY mMa: %d\n", normalizationCal.Y.mMax);

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

    //LOG_Printf("Joystick normalized data:\n");
    //LOG_Printf("X: %d\tY: %d\n", dataPt->Joystick.X, dataPt->Joystick.Y);

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


/*****************************************************************************/
PRIVATE int32 calculateYIntercept(int32 a, int32 b, int32 c)
{
    int32 top, bottom, quot;

    top = a*c*MULTIPLY_FACTOR;
    bottom = a-b;
    quot = (top/bottom);

    return (c*MULTIPLY_FACTOR) - quot;
}


/*****************************************************************************/
PRIVATE int32 calculateSlope(int32 a, int32 b, int32 c)
{
    int32 top, bottom, quot;

    top = c*MULTIPLY_FACTOR;
    bottom = a-b;
    quot = top/bottom;

    return quot;
}











