/*!
 * \file hw_i2c_stm32f10x.c
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "i2c/hw_i2c.h"
#include "util/timeout/util_timeout.h"
#include "util/delay/util_delay.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define I2C_EVENT_TIMEOUT 10000 // us



/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE uint32 HW_RCC_Apb1Periph[HW_I2C_COUNT] = {
        RCC_APB1Periph_I2C1,
        RCC_APB1Periph_I2C2
};

PRIVATE uint32 HW_RCC_Apb2Periph[HW_I2C_COUNT] = {
        RCC_APB2Periph_GPIOB,
        RCC_APB2Periph_GPIOB
};

PRIVATE uint16 SCL_Pin[HW_I2C_COUNT] = {
        GPIO_Pin_6,
        GPIO_Pin_10
};

PRIVATE uint16 SDA_Pin[HW_I2C_COUNT] = {
        GPIO_Pin_7,
        GPIO_Pin_11
};

PRIVATE uint16 I2C_Mode[] = {
        NULL,
        I2C_Mode_I2C,
        I2C_Mode_SMBusDevice,
        I2C_Mode_SMBusHost
};

PRIVATE uint16 I2C_AckAddrBitCount[] = {
        I2C_AcknowledgedAddress_7bit,
        I2C_AcknowledgedAddress_10bit
};

PRIVATE uint16 I2C_DutyCycle[] = {
        I2C_DutyCycle_2,
        I2C_DutyCycle_16_9
};


PRIVATE I2C_TypeDef* I2C_Base[HW_I2C_COUNT] = {
#ifdef I2C1
        I2C1,
#else
        NULL,
#endif
#ifdef I2C2
        I2C2,
#else
        NULL,
#endif
};

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//****************************************************************************/
PUBLIC Result HW_I2C_Init(uint32 BlockId, void* InitInfo )
{
    Result result = HW_I2C_RESULT(HW_I2C_RESULT_SUCCESS);
    HW_I2C_ConfigInfo *config;
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;

    config = InitInfo;

    // only I2C slave mode currently supported
    ASSERT(config->Mode == HW_I2C_MODE_I2C);


    RCC_APB2PeriphClockCmd(HW_RCC_Apb2Periph[BlockId], ENABLE);
    RCC_APB1PeriphClockCmd(HW_RCC_Apb1Periph[BlockId], ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

    GPIO_InitStructure.GPIO_Pin = SCL_Pin[BlockId];
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = SDA_Pin[BlockId];
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    I2C_InitStructure.I2C_Mode = I2C_Mode[config->Mode];
    I2C_InitStructure.I2C_OwnAddress1 = 0;
    I2C_InitStructure.I2C_Ack = (config->AckEnable) ? I2C_Ack_Enable : I2C_Ack_Disable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AckAddrBitCount[config->AckAddrBitCount];
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle[config->DutyCycle];
    I2C_InitStructure.I2C_ClockSpeed = config->ClockSpeed;


    I2C_Cmd(I2C_Base[BlockId], ENABLE);
    I2C_Init(I2C_Base[BlockId], &I2C_InitStructure);



    return result;
}


//****************************************************************************/
PUBLIC Result HW_I2C_PowerUp( uint32 BlockId )
{
    Result result = HW_I2C_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_I2C_PowerDown( uint32 BlockId )
{
    Result result = HW_I2C_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_I2C_ReadSlave(HW_I2C_BlockId Id, uint8 SlaveAddress, uint8 Register, uint8 *Buffer, uint32 BytesToRead, uint32 *BytesRead)
{
    Result result = HW_I2C_RESULT(HW_I2C_RESULT_SUCCESS);
    UTIL_TIMEOUT_Timer timeout;

    *BytesRead = 0;

    /*!< While the bus is busy */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_BUS_TIMEOUT);
        }
    }

    /*!< Send START condition */
    I2C_GenerateSTART(I2C_Base[Id], ENABLE);

    /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_MASTER_MODE_SELECT_TIMEOUT);
        }
    }

    /*!< Send Slave address for write */
    I2C_Send7bitAddress(I2C_Base[Id], SlaveAddress, I2C_Direction_Transmitter);

    /*!< Test on EV6 and clear it */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(!I2C_CheckEvent(I2C_Base[Id], I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_MASTER_TRANSMIITER_SELECT_TIMEOUT);
        }
    }

    /*!< Send the slaves internal address to read from: MSB of the address first */
    I2C_SendData(I2C_Base[Id], Register);

    /*!< Test on EV8 and clear it */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(I2C_GetFlagStatus(I2C_Base[Id],I2C_FLAG_BTF) == RESET)
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_SET_REGISTER_TIMEOUT);
        }
    }

    // TODO: remove this delay
    UTIL_DELAY(500);


    /*!< Send STRAT condition a second time */
    I2C_GenerateSTART(I2C_Base[Id], ENABLE);

    /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(!I2C_CheckEvent(I2C_Base[Id], I2C_EVENT_MASTER_MODE_SELECT))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_MASTER_MODE_SELECT_TIMEOUT);
        }
    }

    /*!< Send slave address for read */
    I2C_Send7bitAddress(I2C_Base[Id], SlaveAddress, I2C_Direction_Receiver);

    /*!< Test on EV6_3 and clear it (cleared by reading SR1 then writing to DR) */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(!I2C_CheckEvent(I2C_Base[Id], I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_RECEIVER_MODE_SELECT_TIMEOUT);
        }
    }


    while( *BytesRead < BytesToRead-1)
    {
        /* Wait for the byte to be received */
        UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
        while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE) == RESET)
        {
            if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
            {
                I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
                return HW_I2C_RESULT(HW_I2C_RESULT_RECEIVE_TIMEOUT);
            }
        }
        /*!< Read the byte received from the I2C device */
        Buffer[*BytesRead++] = I2C_ReceiveData(I2C_Base[Id]);
    }


    /*!< Disable Acknowledgement for last byte*/
    I2C_AcknowledgeConfig(I2C_Base[Id], DISABLE);


    /* Clear ADDR register by reading SR1 then SR2 register */
    (void)I2C_Base[Id]->SR2;

    /*!< Send STOP Condition */
    I2C_GenerateSTOP(I2C_Base[Id], ENABLE);

    /* Wait for the byte to be received */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(I2C_GetFlagStatus(I2C_Base[Id], I2C_FLAG_RXNE) == RESET)
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_RECEIVE_TIMEOUT);
        }
    }

    /*!< Read the byte received from the I2C device */
    Buffer[*BytesRead++] = I2C_ReceiveData(I2C_Base[Id]);


    /* Wait to make sure that STOP control bit has been cleared */
    //    timeout = TIMEOUT;
    //    while(I2C2->CR1 & I2C_CR1_STOP)
    //    {
    //      if((timeout--) == 0)
    //                        return -1;
    //    }

    /*!< Re-Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(I2C_Base[Id], ENABLE);


    return result;
}


//****************************************************************************/
PUBLIC Result HW_I2C_WriteSlave(HW_I2C_BlockId Id, uint8 SlaveAddress, uint8 *Buffer, uint32 BytesToWrite, uint32 *BytesWritten)
{
    Result result = HW_I2C_RESULT(HW_I2C_RESULT_SUCCESS);
    UTIL_TIMEOUT_Timer timeout;

    *BytesWritten = 0;

    /*!< While the bus is busy */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(I2C_GetFlagStatus(I2C_Base[Id], I2C_FLAG_BUSY))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_BUS_TIMEOUT);
        }
    }

    /*!< Send START condition */
    I2C_GenerateSTART(I2C_Base[Id], ENABLE);

    /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(!I2C_CheckEvent(I2C_Base[Id], I2C_EVENT_MASTER_MODE_SELECT))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_MASTER_MODE_SELECT_TIMEOUT);
        }
    }

    /*!< Send Slave address for write */
    I2C_Send7bitAddress(I2C_Base[Id], SlaveAddress, I2C_Direction_Transmitter);

    /*!< Test on EV6 and clear it */
    UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
    while(!I2C_CheckEvent(I2C_Base[Id], I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
        {
            I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
            return HW_I2C_RESULT(HW_I2C_RESULT_MASTER_TRANSMIITER_SELECT_TIMEOUT);
        }
    }

    while( *BytesWritten < BytesToWrite )
    {
        /*!< Send the EEPROM's internal address to read from: MSB of the address first */
        I2C_SendData(I2C_Base[Id], Buffer[*BytesWritten++]);

        /*!< Test on EV8 and clear it */
        UTIL_TIMEOUT_INIT(timeout, I2C_EVENT_TIMEOUT);
        while(!I2C_CheckEvent(I2C_Base[Id], I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if( UTIL_TIMEOUT_TIMED_OUT(timeout) )
            {
                I2C_GenerateSTOP(I2C_Base[Id], ENABLE);
                return HW_I2C_RESULT(HW_I2C_RESULT_TRANSMIT_TIMEOUT);
            }
        }
    }

    /*!< Send STOP Condition */
    I2C_GenerateSTOP(I2C_Base[Id], ENABLE);



    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

