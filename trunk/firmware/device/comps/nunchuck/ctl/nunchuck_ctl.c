/*!
 * \file nunchuck_ctl.c
 *
 * \brief 
 *
 *
 * \date May 28, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"

#include "nunchuck_ctl.h"
#include "nunchuck/nunchuck_conf.h"
#include "nunchuck/com/nunchuck_com.h"
#include "nunchuck/profile/nunchuck_profile.h"
#include "nunchuck/processor/filter/nunchuck_filter.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE Result InitializeNunchuck( pNunchuckProfileInfo profile, pNunchuckCtlCalibration Calibration);


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
PROTECTED Result NunchuckCtlInit(void)
{
	return NUNCHUCK_RESULT(SUCCESS);
}


/*****************************************************************************/
PROTECTED Result NunchuckCtlConnect(void)
{

    Result result = NUNCHUCK_RESULT(SUCCESS);
    NunchuckCtlCalibration calibration;
    NunchuckComInfo comInfo;
    pNunchuckProfileInfo profile;


    profile = &NunchuckProfiles[NunchuckSettings.ProfileIndex];


    comInfo.SlaveAddress = profile->SlaveAddress;
    comInfo.DataFormatter = profile->DataFormatter;


    if( RESULT_IS_ERROR(result, NunchuckComInit(&comInfo)) )
    {
    }
    else if( RESULT_IS_ERROR(result, InitializeNunchuck(profile, &calibration)) )
    {
        NunchuckSettings.ProfileIndex = (NunchuckSettings.ProfileIndex+1)%NUNCHUCK_PROFILE_COUNT;
    }
    else if( RESULT_IS_ERROR(result, NunchuckFilterSetCalibration(&calibration)) )
    {
    }


	return result;
}


/*****************************************************************************/
PROTECTED Result NunchuckCtlDisconnect(void)
{
	return NunchuckComDeInit();
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

/*****************************************************************************/
PRIVATE Result InitializeNunchuck( pNunchuckProfileInfo profile, pNunchuckCtlCalibration Calibration )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);
    uint8 buffer[8];

    // Send first initialization code
    buffer[0] = 0xF0;
    buffer[1] = 0x55;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 2)) )
    {
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    // Send second initialization code
    buffer[0] = 0xFB;
    buffer[1] = 0x00;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 2)) )
    {
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    // Read device Id
    if( RESULT_IS_ERROR(result, NunchuckComReadReg(0xFA, buffer, 6)) )
    {
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    // Read Calibration
    if( RESULT_IS_ERROR(result, NunchuckComReadCalibration(Calibration)) )
    {
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    if( profile->UseEncryption )
    {
        // Enable encryption
        if( RESULT_IS_ERROR(result, NunchuckComEnableEncryption()) )
        {
            return result;
        }
        OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);
    }



    return result;
}
