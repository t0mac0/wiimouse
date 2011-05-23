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
#include "nunchuck_com.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define NUNCHUCK_DATA_PACKET_SIZE 6
#define NUNCHUCK_DATA_REGISTER 0


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
PRIVATE NunchuckComInfo ComInfo;
PRIVATE uint8 scatchBuffer[NUNCHUCK_DATA_PACKET_SIZE];

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PROTECTED Result NunchuckComInit( pNunchuckComInfo InitInfo )
{
    Result result = NUNCHUCK_RESULT(SUCCESS);
    HW_I2C_ConfigInfo config;

    ComInfo.DataFormatter = InitInfo->DataFormatter;
    ComInfo.NunchuckSlaveAddr = InitInfo->NunchuckSlaveAddr;

    config.AckAddrBitCount = HW_I2C_ACK_ADDR_BIT_7;
    config.AckEnable = TRUE;
    config.ClockSpeed = 240000;
    config.DutyCycle = HW_I2C_DUTY_CYCLE_2;
    config.Mode = HW_I2C_MODE_I2C;

    HW_I2C_Deinit(NUNCHUCK_I2C);

    HW_I2C_Init(NUNCHUCK_I2C, &config);

    return result;
}


//****************************************************************************/
PROTECTED Result NunchuckComWrite(uint8 *Data, uint8 NumBytes )
{
    uint32 bytesWritten = 0;

    return HW_I2C_WriteSlave(NUNCHUCK_I2C, ComInfo.NunchuckSlaveAddr, Data, NumBytes, &bytesWritten);
}


//****************************************************************************/
PROTECTED Result NunchuckComReadReg(uint8 Register, uint8 *Buffer, uint8 NumBytes )
{
    uint32 bytesRead = 0;

    return HW_I2C_ReadSlave(NUNCHUCK_I2C, ComInfo.NunchuckSlaveAddr, Register, Buffer, NumBytes, &bytesRead);
}


//****************************************************************************/
PROTECTED Result NunchuckComReadData(pNunchuckData Data)
{
    Result result = NUNCHUCK_RESULT(SUCCESS);


    if( RESULT_IS_SUCCESS(result, NunchuckComReadReg(NUNCHUCK_DATA_REGISTER, scatchBuffer, NUNCHUCK_DATA_PACKET_SIZE)) )
    {
        ConvertData(Data, scatchBuffer);
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
    uint8 i;

    if(ComInfo.DataFormatter != NULL )
    {
        for(i = 0; i < NUNCHUCK_DATA_PACKET_SIZE; i++)
        {
            RawData[i] = ComInfo.DataFormatter(RawData[i]);
        }
    }

    Data->Joystick.X = RawData[0];
    Data->Joystick.Y = RawData[1];
    Data->Accelerometer.X = ((uint16)RawData[2] << 2) | (uint16)((RawData[5]&0x0C)>>2);
    Data->Accelerometer.Y = ((uint16)RawData[3] << 2) | (uint16)((RawData[5]&0x30)>>4);
    Data->Accelerometer.Z = ((uint16)RawData[4] << 2) | (uint16)((RawData[5]&0xC0)>>6);
    Data->Buttons.Buttons = RawData[5]&0x03;
}



