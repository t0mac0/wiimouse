/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_iwdg.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the functions prototypes for the
*                      IWDG firmware library.
********************************************************************************
* History:
* 04/02/2007: V0.2
* 02/05/2007: V0.1
* 09/29/2006: V0.01
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IWDG_H
#define __STM32F10x_IWDG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Write access to IWDG_PR and IWDG_RLR registers */
#define IWDG_WriteAccess_Enable     ((uint16)0x5555)
#define IWDG_WriteAccess_Disable    ((uint16)0x0000)

#define IS_IWDG_WRITE_ACCESS(ACCESS) ((ACCESS == IWDG_WriteAccess_Enable) || \
                                      (ACCESS == IWDG_WriteAccess_Disable))

/* IWDG prescaler */
#define IWDG_Prescaler_4            ((uint8)0x00)
#define IWDG_Prescaler_8            ((uint8)0x01)
#define IWDG_Prescaler_16           ((uint8)0x02)
#define IWDG_Prescaler_32           ((uint8)0x03)
#define IWDG_Prescaler_64           ((uint8)0x04)
#define IWDG_Prescaler_128          ((uint8)0x05)
#define IWDG_Prescaler_256          ((uint8)0x06)

#define IS_IWDG_PRESCALER(PRESCALER) ((PRESCALER == IWDG_Prescaler_4)  || \
                                      (PRESCALER == IWDG_Prescaler_8)  || \
                                      (PRESCALER == IWDG_Prescaler_16) || \
                                      (PRESCALER == IWDG_Prescaler_32) || \
                                      (PRESCALER == IWDG_Prescaler_64) || \
                                      (PRESCALER == IWDG_Prescaler_128)|| \
                                      (PRESCALER == IWDG_Prescaler_256))

/* IWDG Flag */
#define IWDG_FLAG_PVU               ((uint16)0x0001)
#define IWDG_FLAG_RVU               ((uint16)0x0002)

#define IS_IWDG_FLAG(FLAG) ((FLAG == IWDG_FLAG_PVU) || (FLAG == IWDG_FLAG_RVU))

#define IS_IWDG_RELOAD(RELOAD) (RELOAD <= 0xFFF)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void IWDG_WriteAccessCmd(uint16 IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8 IWDG_Prescaler);
void IWDG_SetReload(uint16 Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16 IWDG_FLAG);

#endif /* __STM32F10x_IWDG_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
