#include "i2c.h"
#include "stm32f10x_lib.h"
#include "printf.h"

#include "FreeRTOS.h"
#include "task.h"


void InitI2C2( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;

	/*!< sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/*!< sEE_I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	/*!< GPIO configuration */
	/*!< Configure sEE_I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*!< Configure sEE_I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*!< I2C configuration */
	/* sEE_I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_ClockSpeed = 240000;

	/* sEE_I2C Peripheral Enable */
	I2C_Cmd(I2C2, ENABLE);
	/* Apply sEE_I2C configuration after enabling it */
	I2C_Init(I2C2, &I2C_InitStructure);

}

void ReInitI2C2( void )
{
	I2C_DeInit(I2C2);
	InitI2C2();
}

/**
  * @brief  Reads a block of data from the EEPROM.
  * @param  pBuffer : pointer to the buffer that receives the data read from
  *         the EEPROM.
  * @param  ReadAddr : EEPROM's internal address to start reading from.
  * @param  NumByteToRead : pointer to the variable holding number of bytes to
  *         be read from the EEPROM.
  *
  *        @note The variable pointed by NumByteToRead is reset to 0 when all the
  *              data are read from the EEPROM. Application should monitor this
  *              variable in order know when the transfer is complete.
  *
  * @note When number of data to be read is higher than 1, this function just
  *       configures the communication and enable the DMA channel to transfer data.
  *       Meanwhile, the user application may perform other tasks.
  *       When number of data to be read is 1, then the DMA is not used. The byte
  *       is read in polling mode.
  *
  * @retval sEE_OK (0) if operation is correctly performed, else return value
  *         different from sEE_OK (0) or the timeout user callback.
  */
u32 ReadBufferI2C2(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{
#define TIMEOUT 100000
#define NUNCHUCK_ADDR 0xA4

  u32 timeout;
  u16 bytesRead = 0;


  /*!< While the bus is busy */
  timeout = TIMEOUT;
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))
  {
    if((timeout--) == 0)
    {
    	printf("read: I2C_FLAG_BUSY\n");
    	I2C_GenerateSTOP(I2C2, ENABLE);
    	return -1;
    }
  }

  /*!< Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);

  /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
  timeout = TIMEOUT;
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((timeout--) == 0)
    {
    	printf("read: I2C_EVENT_MASTER_MODE_SELECT\n");
    	I2C_GenerateSTOP(I2C2, ENABLE);
    	return -1;
    }
  }

  /*!< Send EEPROM address for write */
  I2C_Send7bitAddress(I2C2, NUNCHUCK_ADDR, I2C_Direction_Transmitter);

  /*!< Test on EV6 and clear it */
  timeout = TIMEOUT;
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
	  if((timeout--) == 0)
	  {
		  printf("read: I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED\n");
		  I2C_GenerateSTOP(I2C2, ENABLE);
		  return -1;
	  }
  }


  /*!< Send the EEPROM's internal address to read from: MSB of the address first */
  I2C_SendData(I2C2, ReadAddr);

  /*!< Test on EV8 and clear it */
  timeout = TIMEOUT;
    while(I2C_GetFlagStatus(I2C2,I2C_FLAG_BTF) == RESET)
    {
    	if((timeout--) == 0)
    	{
    		printf("read: I2C_FLAG_BTF\n");
    		I2C_GenerateSTOP(I2C2, ENABLE);
    		return -1;
    	}
    }

    vTaskDelay(1);

    /*!< Send STRAT condition a second time */
    I2C_GenerateSTART(I2C2, ENABLE);

    /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
    timeout = TIMEOUT;
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
    {
    	if((timeout--) == 0)
    	{
    		printf("read: I2C_EVENT_MASTER_MODE_SELECT\n");
    		I2C_GenerateSTOP(I2C2, ENABLE);
    		return -1;
    	}
    }

    /*!< Send EEPROM address for read */
    I2C_Send7bitAddress(I2C2, NUNCHUCK_ADDR, I2C_Direction_Receiver);

    /*!< Test on EV6_3 and clear it (cleared by reading SR1 then writing to DR) */
    timeout = TIMEOUT;
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
  	  if((timeout--) == 0)
  	  {
  		printf("read: I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED\n");
  		I2C_GenerateSTOP(I2C2, ENABLE);
  		  return -1;
  	  }
    }


    while( bytesRead < NumByteToRead-1)
    {
		/* Wait for the byte to be received */
		timeout = TIMEOUT;
		while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE) == RESET)
		{
			if((timeout--) == 0)
			{
				printf("read:  I2C_FLAG_RXNE\n");
				I2C_GenerateSTOP(I2C2, ENABLE);
				return -1;
			}
		}
		/*!< Read the byte received from the EEPROM */
		pBuffer[bytesRead++] = I2C_ReceiveData(I2C2);
    }


    /*!< Disable Acknowledgement for last byte*/
    I2C_AcknowledgeConfig(I2C2, DISABLE);


    /* Clear ADDR register by reading SR1 then SR2 register */
    (void)I2C2->SR2;

    /*!< Send STOP Condition */
    I2C_GenerateSTOP(I2C2, ENABLE);

    /* Wait for the byte to be received */
    timeout = TIMEOUT;
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE) == RESET)
    {
    	if((timeout--) == 0)
    	{
			printf("read:  I2C_FLAG_RXNE\n");
			I2C_GenerateSTOP(I2C2, ENABLE);
			return -1;
    	}
    }

    /*!< Read the byte received from the EEPROM */
    pBuffer[bytesRead++] = I2C_ReceiveData(I2C2);


    /* Wait to make sure that STOP control bit has been cleared */
//    timeout = TIMEOUT;
//    while(I2C2->CR1 & I2C_CR1_STOP)
//    {
//    	if((timeout--) == 0)
//    	    			  return -1;
//    }

    /*!< Re-Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(I2C2, ENABLE);

  /* If all operations OK, return sEE_OK (0) */
  return bytesRead;
}


u32 WriteBufferI2C2(u8* pBuffer, u16 NumByteToWrite)
{
#define TIMEOUT 100000
#define NUNCHUCK_ADDR 0xA4

  u32 timeout;
  u16 bytesWritten = 0;


  /*!< While the bus is busy */
  timeout = TIMEOUT;
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))
  {
    if((timeout--) == 0)
    {
    	printf("write: bus timeout\n");
    	I2C_GenerateSTOP(I2C2, ENABLE);
    	return -1;
    }
  }

  /*!< Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);

  /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
  timeout = TIMEOUT;
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((timeout--) == 0)
    {
    	printf("write: I2C_EVENT_MASTER_MODE_SELECT\n");
    	I2C_GenerateSTOP(I2C2, ENABLE);
    	return -1;
    }
  }

  /*!< Send EEPROM address for write */
  I2C_Send7bitAddress(I2C2, NUNCHUCK_ADDR, I2C_Direction_Transmitter);

  /*!< Test on EV6 and clear it */
  timeout = TIMEOUT;
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
	  if((timeout--) == 0)
	  {
		  printf("write: I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED\n");
		  I2C_GenerateSTOP(I2C2, ENABLE);
		  return -1;
	  }
  }

  while( bytesWritten < NumByteToWrite )
  {
	  /*!< Send the EEPROM's internal address to read from: MSB of the address first */
	  I2C_SendData(I2C2, pBuffer[bytesWritten++]);

	  /*!< Test on EV8 and clear it */
	  timeout = TIMEOUT;
	  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	  {
		  if((timeout--) == 0)
		  {
			  printf("write: I2C_EVENT_MASTER_BYTE_TRANSMITTED\n");
			  I2C_GenerateSTOP(I2C2, ENABLE);
			  return -1;
		  }
	  }
  }

  /*!< Send STOP Condition */
  I2C_GenerateSTOP(I2C2, ENABLE);


  return bytesWritten;
}
