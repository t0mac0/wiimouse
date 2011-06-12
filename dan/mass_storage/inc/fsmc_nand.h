/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : fsmc_nand.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Header for fsmc_nand.c file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSMC_NAND_H
#define __FSMC_NAND_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_lib.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8 Maker_ID;
  uint8 Device_ID;
  uint8 Third_ID;
  uint8 Fourth_ID;
}NAND_IDTypeDef;

typedef struct 
{
  uint16 Zone;
  uint16 Block;
  uint16 Page;
} NAND_ADDRESS;

/* Exported constants --------------------------------------------------------*/
/* NAND Area definition  for STM3210E-EVAL Board RevD */
#define CMD_AREA                   (uint32)(1<<16)  /* A16 = CLE  high */
#define ADDR_AREA                  (uint32)(1<<17)  /* A17 = ALE high */

#define DATA_AREA                  ((uint32)0x00000000)

/* FSMC NAND memory command */
#define	NAND_CMD_AREA_A            ((uint8)0x00)
#define	NAND_CMD_AREA_B            ((uint8)0x01)
#define NAND_CMD_AREA_C            ((uint8)0x50)
#define NAND_CMD_AREA_TRUE1        ((uint8)0x30)

#define NAND_CMD_WRITE0            ((uint8)0x80)
#define NAND_CMD_WRITE_TRUE1       ((uint8)0x10)
	
#define NAND_CMD_ERASE0            ((uint8)0x60)
#define NAND_CMD_ERASE1            ((uint8)0xD0)

#define NAND_CMD_READID            ((uint8)0x90)
#define NAND_CMD_STATUS            ((uint8)0x70)
#define NAND_CMD_LOCK_STATUS       ((uint8)0x7A)
#define NAND_CMD_RESET             ((uint8)0xFF)

/* NAND memory status */
#define NAND_VALID_ADDRESS         ((uint32)0x00000100)
#define NAND_INVALID_ADDRESS       ((uint32)0x00000200)
#define NAND_TIMEOUT_ERROR         ((uint32)0x00000400)
#define NAND_BUSY                  ((uint32)0x00000000)
#define NAND_ERROR                 ((uint32)0x00000001)
#define NAND_READY                 ((uint32)0x00000040)

/* FSMC NAND memory parameters */
#define NAND_PAGE_SIZE             ((uint16)0x0200) /* 512 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((uint16)0x0020) /* 32x512 bytes pages per block */
#define NAND_ZONE_SIZE             ((uint16)0x0400) /* 1024 Block per zone */
#define NAND_SPARE_AREA_SIZE       ((uint16)0x0010) /* last 16 bytes as spare area */
#define NAND_MAX_ZONE              ((uint16)0x0004) /* 4 zones of 1024 block */

/* FSMC NAND memory address computation */
#define ADDR_1st_CYCLE(ADDR)       (uint8)((ADDR)& 0xFF)               /* 1st addressing cycle */
#define ADDR_2nd_CYCLE(ADDR)       (uint8)(((ADDR)& 0xFF00) >> 8)      /* 2nd addressing cycle */
#define ADDR_3rd_CYCLE(ADDR)       (uint8)(((ADDR)& 0xFF0000) >> 16)   /* 3rd addressing cycle */
#define ADDR_4th_CYCLE(ADDR)       (uint8)(((ADDR)& 0xFF000000) >> 24) /* 4th addressing cycle */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FSMC_NAND_Init(void);
void FSMC_NAND_ReadID(NAND_IDTypeDef* NAND_ID);
uint32 FSMC_NAND_WriteSmallPage(uint8 *pBuffer, NAND_ADDRESS Address, uint32 NumPageToWrite);
uint32 FSMC_NAND_ReadSmallPage (uint8 *pBuffer, NAND_ADDRESS Address, uint32 NumPageToRead);
uint32 FSMC_NAND_WriteSpareArea(uint8 *pBuffer, NAND_ADDRESS Address, uint32 NumSpareAreaTowrite);
uint32 FSMC_NAND_ReadSpareArea(uint8 *pBuffer, NAND_ADDRESS Address, uint32 NumSpareAreaToRead);
uint32 FSMC_NAND_EraseBlock(NAND_ADDRESS Address);
uint32 FSMC_NAND_Reset(void);
uint32 FSMC_NAND_GetStatus(void);
uint32 FSMC_NAND_ReadStatus(void);
uint32 FSMC_NAND_AddressIncrement(NAND_ADDRESS* Address);

#endif /* __FSMC_NAND_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
