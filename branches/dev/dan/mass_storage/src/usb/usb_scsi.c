/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
 * File Name          : usb_scsi.c
 * Author             : MCD Application Team
 * Version            : V3.2.1
 * Date               : 07/05/2010
 * Description        : All processing related to the SCSI commands
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_scsi.h"
#include "mass_mal.h"
#include "usb_bot.h"
#include "usb_regs.h"
#include "memory.h"
//#include "nand_if.h"
#include "platform_config.h"
#include "usb_lib.h"
#include "printf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern uint8 Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
extern uint8 Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;


/********************************************************************
 *********************************************************************
 *       Capacity Info
 *********************************************************************
 ********************************************************************/
#define SCSICapacitySize    8

uint8 SCSI_ReadCapacity[SCSICapacitySize]=
{
		0x00,       // Last Logical Block0
		0x1E,       // Last Logical Block1
		0x45,       // Last Logical Block2
		0xFF,       // Last Logical Block3
		0x00,       // Bytes per Sector0
		0x00,       // Bytes per Sector1
		0x02,       // Bytes per Sector2
		0x00        // Bytes per Sector3
};


/********************************************************************
 *********************************************************************
 *       Format Capacity Info
 *********************************************************************
 ********************************************************************/
#define SCSICapacityFormatSize  20
uint8  SCSI_ReadFormatCapacity[SCSICapacityFormatSize]=
{
		0x00,       // Reserved
		0x00,       // Reserved
		0x00,       // Reserved
		0x10,       // Capacity List Length
		0x00,       // Number of Blocks0
		0x1E,       // Number of Blocks1
		0x46,       // Number of Blocks2
		0x00,       // Number of Blocks3
		0x02,       // Formatted Media
		0x00,       // Bytes per Sector0
		0x02,       // Bytes per Sector1
		0x00,       // Bytes per Sector2
		0x00,       // Number of Blocks0
		0x1E,       // Number of Blocks1
		0x46,       // Number of Blocks2
		0x00,       // Number of Blocks3
		0x00,       // Reserved
		0x00,       // Bytes per Sector0
		0x02,       // Bytes per Sector1
		0x00,       // Bytes per Sector2
};



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : SCSI_Inquiry_Cmd
 * Description    : SCSI Inquiry Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Inquiry_Cmd(uint8 lun)
{
	Transfer_Data_Request(Standard_Inquiry_Data, STANDARD_INQUIRY_DATA_LEN);
}

/*******************************************************************************
 * Function Name  : SCSI_ReadFormatCapacity_Cmd
 * Description    : SCSI ReadFormatCapacity Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_ReadFormatCapacity_Cmd(uint8 lun)
{
	Transfer_Data_Request(SCSI_ReadFormatCapacity, SCSICapacityFormatSize);
}

/*******************************************************************************
 * Function Name  : SCSI_ReadCapacity10_Cmd
 * Description    : SCSI ReadCapacity10 Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_ReadCapacity10_Cmd(uint8 lun)
{
	Transfer_Data_Request(SCSI_ReadCapacity, SCSICapacitySize);
}

/*******************************************************************************
 * Function Name  : SCSI_ModeSense6_Cmd
 * Description    : SCSI ModeSense6 Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_ModeSense6_Cmd (uint8 lun)
{
	Transfer_Data_Request(Mode_Sense6_data, MODE_SENSE6_DATA_LEN);
}

/*******************************************************************************
 * Function Name  : SCSI_ModeSense10_Cmd
 * Description    : SCSI ModeSense10 Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_ModeSense10_Cmd (uint8 lun)
{
	Transfer_Data_Request(Mode_Sense10_data, MODE_SENSE10_DATA_LEN);
}

/*******************************************************************************
 * Function Name  : SCSI_RequestSense_Cmd
 * Description    : SCSI RequestSense Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_RequestSense_Cmd (uint8 lun)
{
	uint8 Request_Sense_data_Length;

	if (CBW.CB[4] <= REQUEST_SENSE_DATA_LEN)
	{
		Request_Sense_data_Length = CBW.CB[4];
	}
	else
	{
		Request_Sense_data_Length = REQUEST_SENSE_DATA_LEN;
	}
	Transfer_Data_Request(Scsi_Sense_Data, Request_Sense_data_Length);
}

/*******************************************************************************
 * Function Name  : Set_Scsi_Sense_Data
 * Description    : Set Scsi Sense Data routine.
 * Input          : uint8 Sens_Key
                   uint8 Asc.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Set_Scsi_Sense_Data(uint8 lun, uint8 Sens_Key, uint8 Asc)
{
	Scsi_Sense_Data[2] = Sens_Key;
	Scsi_Sense_Data[12] = Asc;
}

/*******************************************************************************
 * Function Name  : SCSI_Start_Stop_Unit_Cmd
 * Description    : SCSI Start_Stop_Unit Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Start_Stop_Unit_Cmd(uint8 lun)
{
	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
 * Function Name  : SCSI_Read10_Cmd
 * Description    : SCSI Read10 Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Read10_Cmd(uint8 lun , uint32 LBA , uint32 BlockNbr)
{
	if (Bot_State == BOT_IDLE)
	{

		if ((CBW.bmFlags & 0x80) != 0)
		{
			Bot_State = BOT_DATA_IN;
			Read_Memory(lun, LBA , BlockNbr);
		}
		else
		{
			Bot_Abort(BOTH_DIR);
			Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
			printf("SCSI_Read10_Cmd failed\n");
			Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
		}
		return;
	}
	else if (Bot_State == BOT_DATA_IN)
	{
		Read_Memory(lun , LBA , BlockNbr);
	}
}

/*******************************************************************************
 * Function Name  : SCSI_Write10_Cmd
 * Description    : SCSI Write10 Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Write10_Cmd(uint8 lun , uint32 LBA , uint32 BlockNbr)
{

	if (Bot_State == BOT_IDLE)
	{
		if ((CBW.bmFlags & 0x80) == 0)
		{
			Bot_State = BOT_DATA_OUT;
			SetEPRxStatus(ENDP2, EP_RX_VALID);
		}
		else
		{
			printf("SCSI_Write10_Cmd failed\n");
			Bot_Abort(DIR_IN);
			Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
			Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
		}
		return;
	}
	else if (Bot_State == BOT_DATA_OUT)
	{
		Write_Memory(lun , LBA , BlockNbr);
	}
}

/*******************************************************************************
 * Function Name  : SCSI_Verify10_Cmd
 * Description    : SCSI Verify10 Command routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Verify10_Cmd(uint8 lun)
{
	if ((CBW.dDataLength == 0) && !(CBW.CB[1] & BLKVFY))/* BLKVFY not set*/
	{
		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
	}
	else
	{
		printf("SCSI_Verify10_Cmd failed\n");
		Bot_Abort(BOTH_DIR);
		Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
		Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
	}
}
/*******************************************************************************
 * Function Name  : SCSI_Valid_Cmd
 * Description    : Valid Commands routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Valid_Cmd(uint8 lun)
{
	if (CBW.dDataLength != 0)
	{
		printf("SCSI_Valid_Cmd failed\n");
		Bot_Abort(BOTH_DIR);
		Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
		Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
	}
	else
		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}
/*******************************************************************************
 * Function Name  : SCSI_Valid_Cmd
 * Description    : Valid Commands routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_TestUnitReady_Cmd(uint8 lun)
{
	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}
/*******************************************************************************
 * Function Name  : SCSI_Format_Cmd
 * Description    : Format Commands routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Format_Cmd(uint8 lun)
{
	if (MAL_GetStatus(lun))
	{
		printf("SCSI_Format_Cmd failed\n");
		Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
		Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
		Bot_Abort(DIR_IN);
		return;
	}
#ifdef USE_STM3210E_EVAL
	else
	{
		NAND_Format();
		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
	}
#endif
}
/*******************************************************************************
 * Function Name  : SCSI_Invalid_Cmd
 * Description    : Invalid Commands routine
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void SCSI_Invalid_Cmd(uint8 lun)
{
	if (CBW.dDataLength == 0)
	{
		Bot_Abort(DIR_IN);
	}
	else
	{
		if ((CBW.bmFlags & 0x80) != 0)
		{
			Bot_Abort(DIR_IN);
		}
		else
		{
			Bot_Abort(BOTH_DIR);
		}
	}
	printf("SCSI_Invalid_Cmd failed\n");
	Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
	Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
}

/*******************************************************************************
 * Function Name  : SCSI_Address_Management
 * Description    : Test the received address.
 * Input          : uint8 Cmd : the command can be SCSI_READ10 or SCSI_WRITE10.
 * Output         : None.
 * Return         : Read\Write status (bool).
 *******************************************************************************/
//bool SCSI_Address_Management(uint8 lun , uint8 Cmd , uint32 LBA , uint32 BlockNbr)
//{
//
//  if ((LBA + BlockNbr) > Mass_Block_Count[lun] )
//  {
//    if (Cmd == SCSI_WRITE10)
//    {
//      Bot_Abort(BOTH_DIR);
//    }
//    Bot_Abort(DIR_IN);
//    Set_Scsi_Sense_Data(lun, ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
//    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//    return (FALSE);
//  }
//
//
//  if (CBW.dDataLength != BlockNbr * Mass_Block_Size[lun])
//  {
//    if (Cmd == SCSI_WRITE10)
//    {
//      Bot_Abort(BOTH_DIR);
//    }
//    else
//    {
//      Bot_Abort(DIR_IN);
//    }
//    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
//    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//    return (FALSE);
//  }
//  return (TRUE);
//}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
