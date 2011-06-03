/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_type.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the common data types used for the
*                      STM32F10x firmware library.
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
#ifndef __STM32F10x_TYPE_H
#define __STM32F10x_TYPE_H

#define __TYPES_DECLARACTION

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef signed long long  int64;
typedef signed long  int32;
typedef signed short int16;
typedef signed char  int8;

typedef volatile signed long long  vint64;
typedef volatile signed long  vint32;
typedef volatile signed short vint16;
typedef volatile signed char  vint8;

typedef unsigned long long uint64;
typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

typedef unsigned long long const ucint64;  /* Read Only */
typedef unsigned long  const ucint32;  /* Read Only */
typedef unsigned short const ucint16;  /* Read Only */
typedef unsigned char  const ucint8;   /* Read Only */

typedef volatile unsigned long long vuint64;
typedef volatile unsigned long  vuint32;
typedef volatile unsigned short vuint16;
typedef volatile unsigned char  vuint8;

typedef volatile unsigned long long const vucint64;  /* Read Only */
typedef volatile unsigned long  const vucint32;  /* Read Only */
typedef volatile unsigned short const vucint16;  /* Read Only */
typedef volatile unsigned char  const vucint8;   /* Read Only */

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) ((STATE == DISABLE) || (STATE == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define __IO volatile

#define UINT8_MAX    ((uint8)255)
#define INT8_MAX     ((int8)127)
#define INT8_MIN     ((int8)-128)
#define UINT16_MAX   ((uint16)65535u)
#define INT16_MAX    ((int16)32767)
#define INT16_MIN    ((int16)-32768)
#define UINT32_MAX   ((uint32)4294967295uL)
#define INT32_MAX    ((int32)2147483647)
#define INT32_MIN    ((int32)2147483648uL)


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __STM32F10x_TYPE_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
