/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_map.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the peripheral register's definitions
*                      and memory mapping.
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
#ifndef __STM32F10x_MAP_H
#define __STM32F10x_MAP_H

#ifndef EXT
  #define EXT extern
#endif /* EXT */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "stm32f10x_type.h"
#include "cortexm3_macro.h"

/* Exported types ------------------------------------------------------------*/
/******************************************************************************/
/*                          IP registers structures                           */
/******************************************************************************/


/*------------------------ External Interrupt/Event Controller ---------------*/
typedef struct
{
  vuint32 IMR;
  vuint32 EMR;
  vuint32 RTSR;
  vuint32 FTSR;
  vuint32 SWIER;
  vuint32 PR;
} EXTI_TypeDef;

/*------------------------ FLASH and Option Bytes Registers ------------------*/
typedef struct
{
  vuint32 ACR;
  vuint32 KEYR;
  vuint32 OPTKEYR;
  vuint32 SR;
  vuint32 CR;
  vuint32 AR;
  vuint32 RESERVED;
  vuint32 OBR;
  vuint32 WRPR;
} FLASH_TypeDef;

typedef struct
{
  vuint16 RDP;
  vuint16 USER;
  vuint16 Data0;
  vuint16 Data1;
  vuint16 WRP0;
  vuint16 WRP1;
  vuint16 WRP2;
  vuint16 WRP3;
} OB_TypeDef;

/*------------------------ General Purpose and Alternate Function IO ---------*/
typedef struct
{
  vuint32 CRL;
  vuint32 CRH;
  vuint32 IDR;
  vuint32 ODR;
  vuint32 BSRR;
  vuint32 BRR;
  vuint32 LCKR;
} GPIO_TypeDef;

typedef struct
{
  vuint32 EVCR;
  vuint32 MAPR;
  vuint32 EXTICR[4];
} AFIO_TypeDef;

/*------------------------ Inter-integrated Circuit Interface ----------------*/
typedef struct
{
  vuint16 CR1;
  uint16 RESERVED0;
  vuint16 CR2;
  uint16 RESERVED1;
  vuint16 OAR1;
  uint16 RESERVED2;
  vuint16 OAR2;
  uint16 RESERVED3;
  vuint16 DR;
  uint16 RESERVED4;
  vuint16 SR1;
  uint16 RESERVED5;
  vuint16 SR2;
  uint16 RESERVED6;
  vuint16 CCR;
  uint16 RESERVED7;
  vuint16 TRISE;
  uint16 RESERVED8;
} I2C_TypeDef;

/*------------------------ Independent WATCHDOG ------------------------------*/
typedef struct
{
  vuint32 KR;
  vuint32 PR;
  vuint32 RLR;
  vuint32 SR;
} IWDG_TypeDef;

/*------------------------ Nested Vectored Interrupt Controller --------------*/
typedef struct
{
  vuint32 Enable[2];
  uint32 RESERVED0[30];
  vuint32 Disable[2];
  uint32 RSERVED1[30];
  vuint32 Set[2];
  uint32 RESERVED2[30];
  vuint32 Clear[2];
  uint32 RESERVED3[30];
  vuint32 Active[2];
  uint32 RESERVED4[62];
  vuint32 Priority[11];
} NVIC_TypeDef;

typedef struct
{
  vuint32 CPUID;
  vuint32 IRQControlState;
  vuint32 ExceptionTableOffset;
  vuint32 AIRC;
  vuint32 SysCtrl;
  vuint32 ConfigCtrl;
  vuint32 SystemPriority[3];
  vuint32 SysHandlerCtrl;
  vuint32 ConfigFaultStatus;
  vuint32 HardFaultStatus;
  vuint32 DebugFaultStatus;
  vuint32 MemoryManageFaultAddr;
  vuint32 BusFaultAddr;
} SCB_TypeDef;

/*------------------------ Reset and Clock Controller ------------------------*/
typedef struct
{
  vuint32 CR;
  vuint32 CFGR;
  vuint32 CIR;
  vuint32 APB2RSTR;
  vuint32 APB1RSTR;
  vuint32 AHBENR;
  vuint32 APB2ENR;
  vuint32 APB1ENR;
  vuint32 BDCR;
  vuint32 CSR;
} RCC_TypeDef;

/*----------------- Universal Synchronous Asynchronous Receiver Transmitter --*/
typedef struct
{
  vuint16 SR;
  uint16 RESERVED0;
  vuint16 DR;
  uint16 RESERVED1;
  vuint16 BRR;
  uint16 RESERVED2;
  vuint16 CR1;
  uint16 RESERVED3;
  vuint16 CR2;
  uint16 RESERVED4;
  vuint16 CR3;
  uint16 RESERVED5;
  vuint16 GTPR;
  uint16 RESERVED6;
} USART_TypeDef;

/******************************************************************************/
/*                       Peripheral memory map                                */
/******************************************************************************/
/* Peripheral and SRAM base address in the alias region */
#define PERIPH_BB_BASE        ((uint32)0x42000000)
#define SRAM_BB_BASE          ((uint32)0x22000000)

/* Peripheral and SRAM base address in the bit-band region */
#define SRAM_BASE             ((uint32)0x20000000)
#define PERIPH_BASE           ((uint32)0x40000000)

/* Flash refisters base address */
#define FLASH_BASE            ((uint32)0x40022000)
/* Flash Option Bytes base address */
#define OB_BASE               ((uint32)0x1FFFF800)

/* Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define CAN_BASE              (APB1PERIPH_BASE + 0x6400)
#define BKP_BASE              (APB1PERIPH_BASE + 0x6C00)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)

#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)

#define DMA_BASE              (AHBPERIPH_BASE + 0x0000)
#define DMA_Channel1_BASE     (AHBPERIPH_BASE + 0x0008)
#define DMA_Channel2_BASE     (AHBPERIPH_BASE + 0x001C)
#define DMA_Channel3_BASE     (AHBPERIPH_BASE + 0x0030)
#define DMA_Channel4_BASE     (AHBPERIPH_BASE + 0x0044)
#define DMA_Channel5_BASE     (AHBPERIPH_BASE + 0x0058)
#define DMA_Channel6_BASE     (AHBPERIPH_BASE + 0x006C)
#define DMA_Channel7_BASE     (AHBPERIPH_BASE + 0x0080)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)

/* System Control Space memory map */
#define SCS_BASE              ((uint32)0xE000E000)

#define SysTick_BASE          (SCS_BASE + 0x0010)
#define NVIC_BASE             (SCS_BASE + 0x0100)
#define SCB_BASE              (SCS_BASE + 0x0D00)


/******************************************************************************/
/*                            IPs' declaration                                */
/******************************************************************************/

/*------------------- Non Debug Mode -----------------------------------------*/
#ifndef DEBUG

#ifdef _USART2
  #define USART2                ((USART_TypeDef *) USART2_BASE)
#endif /*_USART2 */

#ifdef _USART3
  #define USART3                ((USART_TypeDef *) USART3_BASE)
#endif /*_USART3 */

#ifdef _I2C1
  #define I2C1                  ((I2C_TypeDef *) I2C1_BASE)
#endif /*_I2C1 */

#ifdef _I2C2
  #define I2C2                  ((I2C_TypeDef *) I2C2_BASE)
#endif /*_I2C2 */

#ifdef _AFIO
  #define AFIO                  ((AFIO_TypeDef *) AFIO_BASE)
#endif /*_AFIO */

#ifdef _EXTI
  #define EXTI                  ((EXTI_TypeDef *) EXTI_BASE)
#endif /*_EXTI */

#ifdef _GPIOA
  #define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#endif /*_GPIOA */

#ifdef _GPIOB
  #define GPIOB                 ((GPIO_TypeDef *) GPIOB_BASE)
#endif /*_GPIOB */

#ifdef _GPIOC
  #define GPIOC                 ((GPIO_TypeDef *) GPIOC_BASE)
#endif /*_GPIOC */

#ifdef _GPIOD
  #define GPIOD                 ((GPIO_TypeDef *) GPIOD_BASE)
#endif /*_GPIOD */

#ifdef _GPIOE
  #define GPIOE                 ((GPIO_TypeDef *) GPIOE_BASE)
#endif /*_GPIOE */

#ifdef _USART1
  #define USART1                ((USART_TypeDef *) USART1_BASE)
#endif /*_USART1 */

#ifdef _DMA
  #define DMA                   ((DMA_TypeDef *) DMA_BASE)
#endif /*_DMA */


#ifdef _FLASH
  #define FLASH                 ((FLASH_TypeDef *) FLASH_BASE)
  #define OB                    ((OB_TypeDef *) OB_BASE) 
#endif /*_FLASH */

#ifdef _RCC
  #define RCC                   ((RCC_TypeDef *) RCC_BASE)
#endif /*_RCC */

#ifdef _SysTick
  #define SysTick               ((SysTick_TypeDef *) SysTick_BASE)
#endif /*_SysTick */

#ifdef _NVIC
  #define NVIC                  ((NVIC_TypeDef *) NVIC_BASE)
#endif /*_NVIC */

#ifdef _SCB
  #define SCB                   ((SCB_TypeDef *) SCB_BASE)
#endif /*_SCB */
/*----------------------  Debug Mode -----------------------------------------*/
#else   /* DEBUG */

#ifdef _USART2
  EXT USART_TypeDef           *USART2;
#endif /*_USART2 */

#ifdef _USART3
  EXT USART_TypeDef           *USART3;
#endif /*_USART3 */

#ifdef _AFIO
  EXT AFIO_TypeDef            *AFIO;
#endif /*_AFIO */

#ifdef _EXTI
  EXT EXTI_TypeDef            *EXTI;
#endif /*_EXTI */

#ifdef _GPIOA
  EXT GPIO_TypeDef            *GPIOA;
#endif /*_GPIOA */

#ifdef _GPIOB
  EXT GPIO_TypeDef            *GPIOB;
#endif /*_GPIOB */

#ifdef _GPIOC
  EXT GPIO_TypeDef            *GPIOC;
#endif /*_GPIOC */

#ifdef _GPIOD
  EXT GPIO_TypeDef            *GPIOD;
#endif /*_GPIOD */

#ifdef _GPIOE
  EXT GPIO_TypeDef            *GPIOE;
#endif /*_GPIOE */

#ifdef _USART1
  EXT USART_TypeDef           *USART1;
#endif /*_USART1 */


#ifdef _FLASH
  EXT FLASH_TypeDef            *FLASH;
  EXT OB_TypeDef               *OB;  
#endif /*_FLASH */

#ifdef _RCC
  EXT RCC_TypeDef             *RCC;
#endif /*_RCC */

#ifdef _SysTick
  EXT SysTick_TypeDef         *SysTick;
#endif /*_SysTick */

#ifdef _NVIC
  EXT NVIC_TypeDef            *NVIC;
#endif /*_NVIC */

#ifdef _SCB
  EXT SCB_TypeDef             *SCB;
#endif /*_SCB */

#endif  /* DEBUG */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __STM32F10x_MAP_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
