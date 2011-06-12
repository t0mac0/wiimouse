/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
 * File Name          : memory.c
 * Author             : MCD Application Team
 * Version            : V3.2.1
 * Date               : 07/05/2010
 * Description        : Memory management layer
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "FAT16.h"
#include "printf.h"
#include "memory.h"
#include "usb_scsi.h"
#include "usb_bot.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "hw_config.h"
#include "mass_mal.h"
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32 Block_Read_count = 0;
__IO uint32 Block_offset;
__IO uint32 Counter = 0;
uint32  Idx;
uint8 Data_Buffer[DATA_BUFFER_SIZE]; /* 512 bytes*/
uint8 TransferState = TXFR_IDLE;
/* Extern variables ----------------------------------------------------------*/
extern uint8 Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
extern uint16 Data_Len;
extern uint8 Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;
extern uint32 Mass_Memory_Size[2];
extern uint32 Mass_Block_Size[2];

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : Read_Memory
 * Description    : Handle the Read operation from the microSD card.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Read_Memory(uint8 lun, uint32 LBA, uint32 BlockNum)
{
	static uint32 currentLba, maxBlock, bytesRead;

	if (TransferState == TXFR_IDLE )
	{
		printf("Read: LBA: %X, BlockNum: %d. Data residue: %d\n", LBA, BlockNum, CSW.dDataResidue);
		currentLba = LBA;
		maxBlock = LBA + BlockNum;
		bytesRead = 0;
		TransferState = TXFR_ONGOING;
	}

	if (TransferState == TXFR_ONGOING )
	{
		if( bytesRead == 0)
		{
			FATReadLBA((int)currentLba,(char*)Data_Buffer);
		}
		printf("%d bytes read from lba: %d (residue : %d)\n", bytesRead, currentLba, CSW.dDataResidue);
		USB_SIL_Write(EP1_IN, (uint8*)(Data_Buffer + bytesRead), BULK_MAX_PACKET_SIZE);
		bytesRead += BULK_MAX_PACKET_SIZE;
		SetEPTxStatus(ENDP1, EP_TX_VALID);
		CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;

		if( bytesRead == DATA_BUFFER_SIZE )
		{
			currentLba++;

			if(currentLba < maxBlock )
			{
				bytesRead = 0;
			}
			else
			{
				Bot_State = BOT_DATA_IN_LAST;
				TransferState = TXFR_IDLE;
			}
		}
	}
}

/*******************************************************************************
 * Function Name  : Write_Memory
 * Description    : Handle the Write operation to the microSD card.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Write_Memory (uint8 lun, uint32 LBA, uint32 BlkNum)
{

	static uint32 end_lba, bytesRead;

	if (TransferState == TXFR_IDLE )
	{
		end_lba = LBA + BlkNum - 1;
		TransferState = TXFR_ONGOING;
		bytesRead = 0;

		printf("write: lba: %d, numblk: %d, end_lba: %d\n", LBA, BlkNum, end_lba);
	}

	if (TransferState == TXFR_ONGOING )
	{
//		// Host writing first file to Data sector of drive
//		if( LBA >= FATDataSec0)
//		{
//			printf("Host writing first file to Data sector of drive\n");
//		}
//		else
//		{
//			if( LBA == end_lba)
//			{
//				TransferState = TXFR_IDLE;
//				Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
//			}
//			else
//			{
//				CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;
//				SetEPRxStatus(ENDP2, EP_RX_VALID);
//
//
//
//				if( bytesRead >= DATA_BUFFER_SIZE)
//				{
//					bytesRead = 0;
//					LBA++;
//				}
//				else
//				{
//					bytesRead+=BULK_MAX_PACKET_SIZE;
//
//				}
//
//				printf("%d bytes read from LBA: %d\n",bytesRead, LBA );
//			}
//		}


	}

}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

