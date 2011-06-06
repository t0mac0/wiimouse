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

#include "util/delay/util_delay.h"


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

    LOG_Printf("Initializing profile: %d\n", NunchuckSettings.ProfileIndex);


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

    if( !IS_RESULT_SUCCESS(result))
    {
    	UTIL_DELAY(250);
    }
    else
    {
    	LOG_Printf("Nunchuck Connected\n");
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

    //LOG_Printf("Sending first code\n");

    // Send first initialization code
    buffer[0] = 0xF0;
    buffer[1] = 0x55;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 2)) )
    {
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    //LOG_Printf("Sending second code\n");

    // Send second initialization code
    buffer[0] = 0xFB;
    buffer[1] = 0x00;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 2)) )
    {
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    //LOG_Printf("Reading device ID\n");

    // Read device Id
    if( RESULT_IS_ERROR(result, NunchuckComReadReg(0xFA, buffer, 6)) )
    {
        return result;
    }
    LOG_Printf("Nunchuck device ID: %X\n", buffer[3]);
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    //LOG_Printf("Reading Calibration\n");

    // Read Calibration
    if( RESULT_IS_ERROR(result, NunchuckComReadCalibration(Calibration)) )
    {
    	//LOG_Printf("failed to read calibration\n");
        return result;
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);



    if( profile->UseEncryption )
    {
    	//LOG_Printf("Enabling encryption\n");


        // Enable encryption
        if( RESULT_IS_ERROR(result, NunchuckComEnableEncryption()) )
        {
            return result;
        }
        OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);
    }



    return result;
}
