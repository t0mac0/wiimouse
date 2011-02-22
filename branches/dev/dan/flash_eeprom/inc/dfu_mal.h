/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : dfu_mal.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Header for dfu_mal.c file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DFU_MAL_H
#define __DFU_MAL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "dfu_mal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define MAL_OK   0
#define MAL_FAIL 1
#define MAX_USED_MEDIA 3
#define MAL_MASK 0xFC000000

#define INTERNAL_FLASH_BASE 0x08000000

#define MAL_MEMORY_SECTIONS_COUNT 1

#define MAL_BUFFER_SIZE 1024

/* utils macro ---------------------------------------------------------------*/
#define _1st_BYTE(x)  (uint8)((x)&0xFF)             /* 1st addressing cycle */
#define _2nd_BYTE(x)  (uint8)(((x)&0xFF00)>>8)      /* 2nd addressing cycle */
#define _3rd_BYTE(x)  (uint8)(((x)&0xFF0000)>>16)   /* 3rd addressing cycle */
#define _4th_BYTE(x)  (uint8)(((x)&0xFF000000)>>24) /* 4th addressing cycle */
/* Exported macro ------------------------------------------------------------*/
#define SET_POLLING_TIMING(x)   buffer[1] = _1st_BYTE(x);\
                                buffer[2] = _2nd_BYTE(x);\
                                buffer[3] = _3rd_BYTE(x);  

/* Exported functions ------------------------------------------------------- */

uint16 MAL_Init (void);
uint16 MAL_Erase (uint32 SectorAddress, uint32 Length);
uint16 MAL_Write (uint32 SectorAddress, uint32 DataLength);
uint8  *MAL_Read (uint32 SectorAddress, uint32 DataLength);
uint16 MAL_GetStatus(uint32 SectorAddress ,uint8 Cmd, uint8 *buffer);

extern uint8  DFU_MalBuffer[MAL_BUFFER_SIZE]; /* RAM Buffer for Downloaded Data */

extern bool DFU_MalWriteEnabled;
extern bool DFU_MalReadEnabled;

#endif /* __DFU_MAL_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
