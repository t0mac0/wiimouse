/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
 * File Name          : mass_mal.c
 * Author             : MCD Application Team
 * Version            : V3.2.1
 * Date               : 07/05/2010
 * Description        : Medium Access Layer interface
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "platform_config.h"
#ifdef USE_STM3210E_EVAL
#include "stm32_eval_sdio_sd.h"
#else

#endif /* USE_STM3210E_EVAL */
//#include "fsmc_nand.h"
//#include "nand_if.h"
#include "mass_mal.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32 Mass_Memory_Size[2];
uint32 Mass_Block_Size[2];
uint32 Mass_Block_Count[2];
__IO uint32 Status = 0;

#ifdef USE_STM3210E_EVAL
SD_CardInfo SDCardInfo;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
 * Function Name  : MAL_Init
 * Description    : Initializes the Media on the STM32
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint16 MAL_Init(uint8 lun)
{
	uint16 status = MAL_OK;

	switch (lun)
	{
	case 0:
		//Status = SD_Init();
		break;
#ifdef USE_STM3210E_EVAL
	case 1:
		NAND_Init();
		break;
#endif
	default:
		return MAL_FAIL;
	}
	return status;
}
/*******************************************************************************
 * Function Name  : MAL_Write
 * Description    : Write sectors
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint16 MAL_Write(uint8 lun, uint32 Memory_Offset, uint32 *Writebuff, uint16 Transfer_Length)
{

	switch (lun)
	{
	case 0:
		//Status = SD_WriteBlock((uint8*)Writebuff, Memory_Offset, Transfer_Length);
#ifdef USE_STM3210E_EVAL
		if ( Status != SD_OK )
		{
			return MAL_FAIL;
		}
#endif /* USE_STM3210E_EVAL */      
		break;
#ifdef USE_STM3210E_EVAL
	case 1:
		NAND_Write(Memory_Offset, Writebuff, Transfer_Length);
		break;
#endif /* USE_STM3210E_EVAL */  
	default:
		return MAL_FAIL;
	}
	return MAL_OK;
}

/*******************************************************************************
 * Function Name  : MAL_Read
 * Description    : Read sectors
 * Input          : None
 * Output         : None
 * Return         : Buffer pointer
 *******************************************************************************/
uint16 MAL_Read(uint8 lun, uint32 Memory_Offset, uint32 *Readbuff, uint16 Transfer_Length)
{

	switch (lun)
	{
	case 0:
		//Status = SD_ReadBlock((uint8*)Readbuff, Memory_Offset, Transfer_Length);
#ifdef USE_STM3210E_EVAL      
		if ( Status != SD_OK )
		{
			return MAL_FAIL;
		}
#endif /* USE_STM3210E_EVAL */      
		break;
#ifdef USE_STM3210E_EVAL
	case 1:
		NAND_Read(Memory_Offset, Readbuff, Transfer_Length);
		;
		break;
#endif
	default:
		return MAL_FAIL;
	}
	return MAL_OK;
}

/*******************************************************************************
 * Function Name  : MAL_GetStatus
 * Description    : Get status
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint16 MAL_GetStatus (uint8 lun)
{
	//#ifdef USE_STM3210E_EVAL
	//  NAND_IDTypeDef NAND_ID;
	//  uint32 DeviceSizeMul = 0, NumberOfBlocks = 0;
	//#else
	//  uint32 temp_block_mul = 0;
	//  //SD_CSD SD_csd;
	//  uint32 DeviceSizeMul = 0;
	//#endif /* USE_STM3210E_EVAL */
	//
	//
	//  if (lun == 0)
	//  {
	//#ifdef USE_STM3210E_EVAL
	//    if (SD_Init() == SD_OK)
	//    {
	//      SD_GetCardInfo(&SDCardInfo);
	//      SD_SelectDeselect((uint32) (SDCardInfo.RCA << 16));
	//      DeviceSizeMul = (SDCardInfo.SD_csd.DeviceSizeMul + 2);
	//
	//      if(SDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
	//      {
	//        Mass_Block_Count[0] = (SDCardInfo.SD_csd.DeviceSize + 1) * 1024;
	//      }
	//      else
	//      {
	//        NumberOfBlocks  = ((1 << (SDCardInfo.SD_csd.RdBlockLen)) / 512);
	//        Mass_Block_Count[0] = ((SDCardInfo.SD_csd.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks/2));
	//      }
	//      Mass_Block_Size[0]  = 512;
	//
	//      Status = SD_SelectDeselect((uint32) (SDCardInfo.RCA << 16));
	//      Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
	//      if ( Status != SD_OK )
	//      {
	//        return MAL_FAIL;
	//      }
	//
	//      Status = SD_SetDeviceMode(SD_DMA_MODE);
	//      if ( Status != SD_OK )
	//      {
	//        return MAL_FAIL;
	//      }
	//
	//#else
	//    SD_GetCSDRegister(&SD_csd);
	//    DeviceSizeMul = SD_csd.DeviceSizeMul + 2;
	//    temp_block_mul = (1 << SD_csd.RdBlockLen)/ 512;
	//    Mass_Block_Count[0] = ((SD_csd.DeviceSize + 1) * (1 << (DeviceSizeMul))) * temp_block_mul;
	//    Mass_Block_Size[0] = 512;
	//    Mass_Memory_Size[0] = (Mass_Block_Count[0] * Mass_Block_Size[0]);
	//#endif /* USE_STM3210E_EVAL */
	//      Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
	//      STM_EVAL_LEDOn(LED2);
	//      return MAL_OK;
	//
	//#ifdef USE_STM3210E_EVAL
	//    }
	//#endif /* USE_STM3210E_EVAL */
	//  }
	//#ifdef USE_STM3210E_EVAL
	//  else
	//  {
	//    FSMC_NAND_ReadID(&NAND_ID);
	//    if (NAND_ID.Device_ID != 0 )
	//    {
	//      /* only one zone is used */
	//      Mass_Block_Count[1] = NAND_ZONE_SIZE * NAND_BLOCK_SIZE * NAND_MAX_ZONE ;
	//      Mass_Block_Size[1]  = NAND_PAGE_SIZE;
	//      Mass_Memory_Size[1] = (Mass_Block_Count[1] * Mass_Block_Size[1]);
	//      return MAL_OK;
	//    }
	//  }
	//#endif /* USE_STM3210E_EVAL */
	Mass_Block_Count[0] = 1 ;
	Mass_Block_Size[0]  = 1024;
	Mass_Memory_Size[0] = (Mass_Block_Count[0] * Mass_Block_Size[0]);
	return MAL_OK;
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
