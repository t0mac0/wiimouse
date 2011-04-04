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

#ifndef EXTERN_C
  #define EXTERN_C extern
#endif /* EXTERN_C */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/* Exported types ------------------------------------------------------------*/
/******************************************************************************/
/*                          IP registers structures                           */
/******************************************************************************/

/*------------------------ Analog to Digital Converter -----------------------*/
typedef struct
{
  vuint32 SR;
  vuint32 CR1;
  vuint32 CR2;
  vuint32 SMPR1;
  vuint32 SMPR2;
  vuint32 JOFR1;
  vuint32 JOFR2;
  vuint32 JOFR3;
  vuint32 JOFR4;
  vuint32 HTR;
  vuint32 LTR;
  vuint32 SQR1;
  vuint32 SQR2;
  vuint32 SQR3;
  vuint32 JSQR;
  vuint32 JDR1;
  vuint32 JDR2;
  vuint32 JDR3;
  vuint32 JDR4;
  vuint32 DR;
} ADC_TypeDef;

/*------------------------ Backup Registers ----------------------------------*/
typedef struct
{
  uint32 RESERVED0;
  vuint16 DR1;
  uint16  RESERVED1;
  vuint16 DR2;
  uint16  RESERVED2;
  vuint16 DR3;
  uint16  RESERVED3;
  vuint16 DR4;
  uint16  RESERVED4;
  vuint16 DR5;
  uint16  RESERVED5;
  vuint16 DR6;
  uint16  RESERVED6;
  vuint16 DR7;
  uint16  RESERVED7;
  vuint16 DR8;
  uint16  RESERVED8;
  vuint16 DR9;
  uint16  RESERVED9;
  vuint16 DR10;
  uint16  RESERVED10;
  vuint16 RTCCR;
  uint16  RESERVED11;
  vuint16 CR;
  uint16  RESERVED12;
  vuint16 CSR;
  uint16  RESERVED13;
} BKP_TypeDef;

/*------------------------ Controller Area Network ---------------------------*/
typedef struct
{
  vuint32 TIR;
  vuint32 TDTR;
  vuint32 TDLR;
  vuint32 TDHR;
} CAN_TxMailBox_TypeDef;

typedef struct
{
  vuint32 RIR;
  vuint32 RDTR;
  vuint32 RDLR;
  vuint32 RDHR;
} CAN_FIFOMailBox_TypeDef;

typedef struct
{
  vuint32 FR0;
  vuint32 FR1;
} CAN_FilterRegister_TypeDef;

typedef struct
{
  vuint32 MCR;
  vuint32 MSR;
  vuint32 TSR;
  vuint32 RF0R;
  vuint32 RF1R;
  vuint32 IER;
  vuint32 ESR;
  vuint32 BTR;
  uint32 RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32 RESERVED1[12];
  vuint32 FMR;
  vuint32 FM0R;
  uint32 RESERVED2[1];
  vuint32 FS0R;
  uint32 RESERVED3[1];
  vuint32 FFA0R;
  uint32 RESERVED4[1];
  vuint32 FA0R;
  uint32 RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[14];
} CAN_TypeDef;

/*------------------------ DMA Controller ------------------------------------*/
typedef struct
{
  vuint32 CCR;
  vuint32 CNDTR;
  vuint32 CPAR;
  vuint32 CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  vuint32 ISR;
  vuint32 IFCR;
} DMA_TypeDef;

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

/*------------------------ Power Controller ----------------------------------*/
typedef struct
{
  vuint32 CR;
  vuint32 CSR;
} PWR_TypeDef;

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

/*------------------------ Real-Time Clock -----------------------------------*/
typedef struct
{
  vuint16 CRH;
  uint16 RESERVED0;
  vuint16 CRL;
  uint16 RESERVED1;
  vuint16 PRLH;
  uint16 RESERVED2;
  vuint16 PRLL;
  uint16 RESERVED3;
  vuint16 DIVH;
  uint16 RESERVED4;
  vuint16 DIVL;
  uint16 RESERVED5;
  vuint16 CNTH;
  uint16 RESERVED6;
  vuint16 CNTL;
  uint16 RESERVED7;
  vuint16 ALRH;
  uint16 RESERVED8;
  vuint16 ALRL;
  uint16 RESERVED9;
} RTC_TypeDef;

/*------------------------ Serial Peripheral Interface -----------------------*/
typedef struct
{
  vuint16 CR1;
  uint16 RESERVED0;
  vuint16 CR2;
  uint16 RESERVED1;
  vuint16 SR;
  uint16  RESERVED2;
  vuint16 DR;
  uint16  RESERVED3;
  vuint16 CRCPR;
  uint16 RESERVED4;
  vuint16 RXCRCR;
  uint16  RESERVED5;
  vuint16 TXCRCR;
  uint16  RESERVED6;
} SPI_TypeDef;

/*------------------------ SystemTick ----------------------------------------*/
typedef struct
{
  vuint32 CTRL;
  vuint32 LOAD;
  vuint32 VAL;
  vucint32 CALIB;
} SysTick_TypeDef;



/*------------------------ General Purpose Timer -----------------------------*/
typedef struct
{
  vuint16 CR1;
  uint16  RESERVED0;
  vuint16 CR2;
  uint16  RESERVED1;
  vuint16 SMCR;
  uint16  RESERVED2;
  vuint16 DIER;
  uint16  RESERVED3;
  vuint16 SR;
  uint16  RESERVED4;
  vuint16 EGR;
  uint16  RESERVED5;
  vuint16 CCMR1;
  uint16  RESERVED6;
  vuint16 CCMR2;
  uint16  RESERVED7;
  vuint16 CCER;
  uint16  RESERVED8;
  vuint16 CNT;
  uint16  RESERVED9;
  vuint16 PSC;
  uint16  RESERVED10;
  vuint16 ARR;
  uint16  RESERVED11;
  vuint16 RCR;
  uint16  RESERVED12;
  vuint16 CCR1;
  uint16  RESERVED13;
  vuint16 CCR2;
  uint16  RESERVED14;
  vuint16 CCR3;
  uint16  RESERVED15;
  vuint16 CCR4;
  uint16  RESERVED16;
  vuint16 BDTR;
  uint16  RESERVED17;
  vuint16 DCR;
  uint16  RESERVED18;
  vuint16 DMAR;
  uint16  RESERVED19;
} TIM_TypeDef;

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

/*------------------------ Window WATCHDOG -----------------------------------*/
typedef struct
{
  vuint32 CR;
  vuint32 CFR;
  vuint32 SR;
} WWDG_TypeDef;

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

#ifdef _TIM1
  #define TIM1                  ((TIM_TypeDef *) TIM1_BASE)
#endif /*_TIM1 */

#ifdef _TIM2
  #define TIM2                  ((TIM_TypeDef *) TIM2_BASE)
#endif /*_TIM2 */

#ifdef _TIM3
  #define TIM3                  ((TIM_TypeDef *) TIM3_BASE)
#endif /*_TIM3 */

#ifdef _TIM4
  #define TIM4                  ((TIM_TypeDef *) TIM4_BASE)
#endif /*_TIM4 */

#ifdef _RTC
  #define RTC                   ((RTC_TypeDef *) RTC_BASE)
#endif /*_RTC */

#ifdef _WWDG
  #define WWDG                  ((WWDG_TypeDef *) WWDG_BASE)
#endif /*_WWDG */

#ifdef _IWDG
  #define IWDG                  ((IWDG_TypeDef *) IWDG_BASE)
#endif /*_IWDG */

#ifdef _SPI2
  #define SPI2                  ((SPI_TypeDef *) SPI2_BASE)
#endif /*_SPI2 */

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

#ifdef _CAN
  #define CAN                   ((CAN_TypeDef *) CAN_BASE)
#endif /*_CAN */

#ifdef _BKP
  #define BKP                   ((BKP_TypeDef *) BKP_BASE)
#endif /*_BKP */

#ifdef _PWR
  #define PWR                   ((PWR_TypeDef *) PWR_BASE)
#endif /*_PWR */

#ifdef _AFIO
  #define AFIO                  ((AFIO_TypeDef *) AFIO_BASE)
#endif /*_AFIO */

#ifdef _EXTI
  #define EXTI                 ((EXTI_TypeDef *) EXTI_BASE)
#endif /*_EXTERN_CI */

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

#ifdef _ADC1
  #define ADC1                  ((ADC_TypeDef *) ADC1_BASE)
#endif /*_ADC1 */

#ifdef _ADC2
  #define ADC2                  ((ADC_TypeDef *) ADC2_BASE)
#endif /*_ADC2 */

#ifdef _SPI1
  #define SPI1                  ((SPI_TypeDef *) SPI1_BASE)
#endif /*_SPI1 */

#ifdef _USART1
  #define USART1                ((USART_TypeDef *) USART1_BASE)
#endif /*_USART1 */

#ifdef _DMA
  #define DMA                   ((DMA_TypeDef *) DMA_BASE)
#endif /*_DMA */

#ifdef _DMA_Channel1
  #define DMA_Channel1          ((DMA_Channel_TypeDef *) DMA_Channel1_BASE)
#endif /*_DMA_Channel1 */

#ifdef _DMA_Channel2
  #define DMA_Channel2          ((DMA_Channel_TypeDef *) DMA_Channel2_BASE)
#endif /*_DMA_Channel2 */

#ifdef _DMA_Channel3
  #define DMA_Channel3          ((DMA_Channel_TypeDef *) DMA_Channel3_BASE)
#endif /*_DMA_Channel3 */

#ifdef _DMA_Channel4
  #define DMA_Channel4          ((DMA_Channel_TypeDef *) DMA_Channel4_BASE)
#endif /*_DMA_Channel4 */

#ifdef _DMA_Channel5
  #define DMA_Channel5          ((DMA_Channel_TypeDef *) DMA_Channel5_BASE)
#endif /*_DMA_Channel5 */

#ifdef _DMA_Channel6
  #define DMA_Channel6          ((DMA_Channel_TypeDef *) DMA_Channel6_BASE)
#endif /*_DMA_Channel6 */

#ifdef _DMA_Channel7
  #define DMA_Channel7          ((DMA_Channel_TypeDef *) DMA_Channel7_BASE)
#endif /*_DMA_Channel7 */

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
//#else   /* DEBUG */
//
//
//#ifdef _TIM2
//  EXTERN_C TIM_TypeDef             *TIM2;
//#endif /*_TIM2 */
//
//#ifdef _TIM3
//  EXTERN_C TIM_TypeDef             *TIM3;
//#endif /*_TIM3 */
//
//#ifdef _TIM4
//  EXTERN_C TIM_TypeDef             *TIM4;
//#endif /*_TIM4 */
//
//#ifdef _RTC
//  EXTERN_C RTC_TypeDef             *RTC;
//#endif /*_RTC */
//
//#ifdef _WWDG
//  EXTERN_C WWDG_TypeDef            *WWDG;
//#endif /*_WWDG */
//
//#ifdef _IWDG
//  EXTERN_C IWDG_TypeDef            *IWDG;
//#endif /*_IWDG */
//
//#ifdef _SPI2
//  EXTERN_C SPI_TypeDef             *SPI2;
//#endif /*_SPI2 */
//
//#ifdef _USART2
//  EXTERN_C USART_TypeDef           *USART2;
//#endif /*_USART2 */
//
//#ifdef _USART3
//  EXTERN_C USART_TypeDef           *USART3;
//#endif /*_USART3 */
//
//#ifdef _I2C1
//  EXTERN_C I2C_TypeDef             *I2C1;
//#endif /*_I2C1 */
//
//#ifdef _I2C2
//  EXTERN_C I2C_TypeDef             *I2C2;
//#endif /*_I2C2 */
//
//#ifdef _CAN
//  EXTERN_C CAN_TypeDef             *CAN;
//#endif /*_CAN */
//
//#ifdef _BKP
//  EXTERN_C BKP_TypeDef             *BKP;
//#endif /*_BKP */
//
//#ifdef _PWR
//  EXTERN_C PWR_TypeDef             *PWR;
//#endif /*_PWR */
//
//#ifdef _AFIO
//  EXTERN_C AFIO_TypeDef            *AFIO;
//#endif /*_AFIO */
//
//#ifdef _EXTI
//  EXTERN_C EXTI_TypeDef            *EXTI;
//#endif /*_EXTERN_CI */
//
//#ifdef _GPIOA
//  EXTERN_C GPIO_TypeDef            *GPIOA;
//#endif /*_GPIOA */
//
//#ifdef _GPIOB
//  EXTERN_C GPIO_TypeDef            *GPIOB;
//#endif /*_GPIOB */
//
//#ifdef _GPIOC
//  EXTERN_C GPIO_TypeDef            *GPIOC;
//#endif /*_GPIOC */
//
//#ifdef _GPIOD
//  EXTERN_C GPIO_TypeDef            *GPIOD;
//#endif /*_GPIOD */
//
//#ifdef _GPIOE
//  EXTERN_C GPIO_TypeDef            *GPIOE;
//#endif /*_GPIOE */
//
//#ifdef _ADC1
//  EXTERN_C ADC_TypeDef             *ADC1;
//#endif /*_ADC1 */
//
//#ifdef _ADC2
//  EXTERN_C ADC_TypeDef             *ADC2;
//#endif /*_ADC2 */
//
//#ifdef _TIM1
//  EXTERN_C TIM1_TypeDef            *TIM1;
//#endif /*_TIM1 */
//
//#ifdef _SPI1
//  EXTERN_C SPI_TypeDef             *SPI1;
//#endif /*_SPI1 */
//
//#ifdef _USART1
//  EXTERN_C USART_TypeDef           *USART1;
//#endif /*_USART1 */
//
//#ifdef _DMA
//  EXTERN_C DMA_TypeDef             *DMA;
//#endif /*_DMA */
//
//#ifdef _DMA_Channel1
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel1;
//#endif /*_DMA_Channel1 */
//
//#ifdef _DMA_Channel2
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel2;
//#endif /*_DMA_Channel2 */
//
//#ifdef _DMA_Channel3
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel3;
//#endif /*_DMA_Channel3 */
//
//#ifdef _DMA_Channel4
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel4;
//#endif /*_DMA_Channel4 */
//
//#ifdef _DMA_Channel5
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel5;
//#endif /*_DMA_Channel5 */
//
//#ifdef _DMA_Channel6
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel6;
//#endif /*_DMA_Channel6 */
//
//#ifdef _DMA_Channel7
//  EXTERN_C DMA_Channel_TypeDef     *DMA_Channel7;
//#endif /*_DMA_Channel7 */
//
//#ifdef _FLASH
//  EXTERN_C FLASH_TypeDef            *FLASH;
//  EXTERN_C OB_TypeDef               *OB;
//#endif /*_FLASH */
//
//#ifdef _RCC
//  EXTERN_C RCC_TypeDef             *RCC;
//#endif /*_RCC */
//
//#ifdef _SysTick
//  EXTERN_C SysTick_TypeDef         *SysTick;
//#endif /*_SysTick */
//
//#ifdef _NVIC
//  EXTERN_C NVIC_TypeDef            *NVIC;
//#endif /*_NVIC */
//
//#ifdef _SCB
//  EXTERN_C SCB_TypeDef             *SCB;
//#endif /*_SCB */
//
//#endif  /* DEBUG */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __STM32F10x_MAP_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
