/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
 * File Name          : flash_if.c
 * Author             : MCD Application Team
 * Version            : V3.2.1
 * Date               : 07/05/2010
 * Description        : specific media access Layer for internal flash
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"
#include "dfu_mal.h"
#include "stm32f10x_flash.h"
#include "printf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : FLASH_If_Init
 * Description    : Initializes the Media on the STM32
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint16 FLASH_If_Init(void)
{
	return MAL_OK;
}

/*******************************************************************************
 * Function Name  : FLASH_If_Erase
 * Description    : Erase sector
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint16 FLASH_If_Erase(uint32 SectorAddress, uint32 Length)
{
	uint32 i, addr, pageCount;

	addr = SectorAddress;
	pageCount = (((SectorAddress & FLASH_PAGE_MASK) + Length) / FLASH_PAGE_SIZE) + 1;

	for(i = 0; i < pageCount; i++ )
	{
		printf("Erasing: %X\n", addr & 0xFFFFFC00);
		FLASH_ErasePage((addr & 0xFFFFFC00)|FLASH_BASE);
		addr += FLASH_PAGE_SIZE;
	}

	return MAL_OK;
}


/*******************************************************************************
 * Function Name  : FLASH_If_Write
 * Description    : Write sectors
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint16 FLASH_If_Write(uint32 SectorAddress, uint32 DataLength, bool Erase)
{
	uint32 idx = 0;

	if  (DataLength & 0x3) /* Not an aligned data */
	{
		for (idx = DataLength; idx < ((DataLength & 0xFFFC) + 4); idx++)
		{
			DFU_MalBuffer[idx] = 0xFF;
		}
	}

	if(Erase)
	{
		FLASH_If_Erase(SectorAddress, DataLength);
	}
	/* Data received are Word multiple */

	for (idx = 0; idx <  DataLength; idx = idx + 4)
	{
		//if(idx < 64 )
		//printf("Writing address: %X with: %X\n", SectorAddress, *(uint32 *)(DFU_MalBuffer + idx));
		FLASH_ProgramWord(SectorAddress, *(uint32 *)(DFU_MalBuffer + idx));
		SectorAddress += 4;
	}
	return MAL_OK;
}

uint16 FLASH_If_Write_Value16 (uint32 SectorAddress, uint16 Value)
{
	//printf("writting 16bit to %08X: %X\n", SectorAddress,Value);
	FLASH_ProgramHalfWord(SectorAddress|FLASH_BASE, Value);
	//printf("validating: %X\n", *((uint16*)SectorAddress));
	return  MAL_OK;
}

uint16 FLASH_If_Write_Value32 (uint32 SectorAddress, uint32 Value)
{
	//printf("writting 32bit to %08X: %X\n", SectorAddress, Value);
	FLASH_ProgramWord(SectorAddress|FLASH_BASE, Value);
	//printf("validating: %X\n",*((uint32*)SectorAddress));
	return  MAL_OK;
}

/*******************************************************************************
 * Function Name  : FLASH_If_Read
 * Description    : Read sectors
 * Input          : None
 * Output         : None
 * Return         : buffer address pointer
 *******************************************************************************/
uint8 *FLASH_If_Read (uint32 SectorAddress, uint32 DataLength)
{
	uint32 idx;

	for( idx = 0; idx < DataLength; idx = idx + 4)
	{
		//if(idx < 64)
		//printf("Reading address\n",(uint32*)(SectorAddress+idx));
		*(uint32*)(DFU_MalBuffer + idx) = *(uint32*)(SectorAddress + idx);
	}
	return  DFU_MalBuffer;
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
