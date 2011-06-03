/*!
 * \file nunchuck_com.c
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
#include "os.h"

#include "nunchuck_com.h"
#include "nunchuck/nunchuck_conf.h"

#include "hw_mgr/i2c/hw_i2c.h"

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
PRIVATE inline void ConvertData(pNunchuckData Data, uint8 *RawData);



/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE pNunchuckProfileDataFormatter dataFormatter;
PRIVATE uint8 slaveAddr;
PRIVATE uint8 scatchBuffer[NUNCHUCK_DATA_PACKET_SIZE];

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/****************************************************************************/
PROTECTED Result NunchuckComInit( pNunchuckComInfo ComInfo)
{
    Result result = NUNCHUCK_RESULT(SUCCESS);
    HW_I2C_ConfigInfo config;

    dataFormatter = ComInfo->DataFormatter;
    slaveAddr = ComInfo->SlaveAddress;

    config.AckAddrBitCount = NUNCHUCK_I2C_BIT_COUNT;
    config.AckEnable = NUNCHUCK_I2C_ACK_ENABLE;
    config.ClockSpeed = NUNCHUCK_I2C_FREQ;
    config.DutyCycle = NUNCHUCK_I2C_DUTY_CYCLE;
    config.Mode = HW_I2C_MODE_I2C;

    HW_I2C_Deinit(NUNCHUCK_I2C);

    HW_I2C_Init(NUNCHUCK_I2C, &config);

    return result;
}


/****************************************************************************/
PROTECTED Result NunchuckComDeInit( void )
{
    HW_I2C_Deinit(NUNCHUCK_I2C);

    return NUNCHUCK_RESULT(SUCCESS);
}


/****************************************************************************/
PROTECTED Result NunchuckComWrite(uint8 *Data, uint8 NumBytes )
{
    uint32 bytesWritten = 0;

    return HW_I2C_WriteSlave(NUNCHUCK_I2C, slaveAddr, Data, NumBytes, &bytesWritten);
}


/****************************************************************************/
PROTECTED Result NunchuckComReadReg(uint8 Register, uint8 *Buffer, uint8 NumBytes )
{
    uint32 bytesRead = 0;

    return HW_I2C_ReadSlave(NUNCHUCK_I2C, slaveAddr, Register, Buffer, NumBytes, &bytesRead);
}


/****************************************************************************/
PROTECTED Result NunchuckComReadData(pNunchuckData Data)
{
    Result result = NUNCHUCK_RESULT(SUCCESS);


    if( RESULT_IS_SUCCESS(result, NunchuckComReadReg(NUNCHUCK_DATA_REGISTER, scatchBuffer, NUNCHUCK_DATA_PACKET_SIZE)) )
    {
        ConvertData(Data, scatchBuffer);
    }

    return result;
}


/****************************************************************************
 *
 * Calibration Data Format
 *
 * Byte     Description
 *
 * 0        Accelerometer: X neutral low byte
 * 1        Accelerometer: Y neutral low byte
 * 2        Accelerometer: Z neutral low byte
 *
 * 4        Accelerometer: X neutral high byte (2 LSb only)
 * 5        Accelerometer: X neutral high byte (2 LSb only)
 * 6        Accelerometer: X neutral high byte (2 LSb only)
 *
 * 8        Joystick: X max
 * 9        Joystick: X min
 * 10       Joystick: X neutral
 *
 * 11       Joystick: Y max
 * 12       Joystick: Y min
 * 13       Joystick: Y neutral
 *
 ****************************************************************************/
PROTECTED Result NunchuckComReadCalibration(pNunchuckCtlCalibration Calibration)
{
    Result result = NUNCHUCK_RESULT(SUCCESS);
    uint8 buffer[14];


    if( RESULT_IS_ERROR(result, NunchuckComReadReg(0x20, buffer, 14)) )
    {
    }
    else
    {
    	uint8 i;
    	for(i = 0; i < 14; i++)
    		LOG_Printf("%d\n", buffer[i]);

        if( dataFormatter )
        {
        	for(i = 0; i < 14; i++)
        		buffer[i] = dataFormatter(buffer[i]);
        }

        Calibration->Accelerometer.X = ((uint16)(buffer[4]&0x03) << 2) | (uint16)buffer[0];
        Calibration->Accelerometer.Y = ((uint16)(buffer[5]&0x03) << 2) | (uint16)buffer[1];
        Calibration->Accelerometer.Z = ((uint16)(buffer[6]&0x03) << 2) | (uint16)buffer[2];

        Calibration->Joystick.X.Max = buffer[8];
        Calibration->Joystick.X.Min = buffer[9];
        Calibration->Joystick.X.Neutral = buffer[10];

        Calibration->Joystick.Y.Max = buffer[11];
        Calibration->Joystick.Y.Min = buffer[12];
        Calibration->Joystick.Y.Neutral = buffer[13];

        LOG_Printf("Nunchuck calibration:\n");
        LOG_Printf("\tAcc X: %d\n", Calibration->Accelerometer.X);
        LOG_Printf("\tAcc Y: %d\n", Calibration->Accelerometer.Y);
        LOG_Printf("\tAcc Z: %d\n", Calibration->Accelerometer.Z);

        LOG_Printf("\tJoy X Max: %d\n",Calibration->Joystick.X.Max);
        LOG_Printf("\tJoy X Min: %d\n",Calibration->Joystick.X.Min);
        LOG_Printf("\tJoy X Neutral: %d\n",Calibration->Joystick.X.Neutral);

        LOG_Printf("\tJoy Y Max: %d\n",Calibration->Joystick.Y.Max);
        LOG_Printf("\tJoy Y Min: %d\n",Calibration->Joystick.Y.Min);
        LOG_Printf("\tJoy Y Neutral: %d\n",Calibration->Joystick.Y.Neutral);
    }

    return result;
}

/****************************************************************************/
PROTECTED Result NunchuckComEnableEncryption( void )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);
    uint8 buffer[8] = {0};

    LOG_Printf("Sending Enable encryption code\n");
    // Enable encryption
    buffer[0] = 0xF0;
    buffer[1] = 0xAA;

    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 2)) )
    {
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);


    LOG_Printf("Sending first 6 bytes encryption code\n");
    // Send first 6 bytes of encryption code
    ZeroMemory(buffer, 7);
    buffer[0] = 0x40;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 7)) )
    {
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    LOG_Printf("Sending net 6 bytes encryption code\n");
    // Send next 6 bytes of encryption code
    ZeroMemory(buffer, 7);
    buffer[0] = 0x46;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 7)) )
    {
    }
    OS_TASK_MGR_Delay(NUNCHUCK_INIT_DELAY);

    LOG_Printf("Sending last 4 bytes encryption code\n");
    // Send last 4 bytes of encryption code
    ZeroMemory(buffer, 5);
    buffer[0] = 0x4C;
    if( RESULT_IS_ERROR(result, NunchuckComWrite(buffer, 5)) )
    {
    }


    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


/****************************************************************************

Nunchuck Data Packet format:

                    Bit
Byte    7   6   5   4   3   2   1   0
0                   SX<7:0>
1                   SY<7:0>
2                   AX<9:2>
3                   AY<9:2>
4                   AZ<9:2>
5      AZ<1:0> AY<1:0> AX<1:0> BC  BZ

****************************************************************************/
PRIVATE inline void ConvertData(pNunchuckData Data, uint8 *RawData)
{
    if( dataFormatter )
    {
    	uint8 i;

    	//LOG_Printf("Nunchuck data: ");
    	for(i = 0; i < NUNCHUCK_DATA_PACKET_SIZE; i++)
    	{
    		RawData[i] = dataFormatter(RawData[i]);
    		//LOG_Printf("%d ", RawData[i]);
    	}
    	//LOG_Printf("\n");
    }

    Data->Joystick.X = RawData[0];
    Data->Joystick.Y = RawData[1];
    Data->Accelerometer.X = ((uint16)RawData[2] << 2) | (uint16)((RawData[5]&0x0C)>>2);
    Data->Accelerometer.Y = ((uint16)RawData[3] << 2) | (uint16)((RawData[5]&0x30)>>4);
    Data->Accelerometer.Z = ((uint16)RawData[4] << 2) | (uint16)((RawData[5]&0xC0)>>6);
    Data->Buttons.Buttons = RawData[5]&0x03;
}



