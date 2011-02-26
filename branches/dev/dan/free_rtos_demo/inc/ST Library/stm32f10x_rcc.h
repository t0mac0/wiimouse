/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_rcc.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the functions prototypes for the
*                      RCC firmware library.
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
#ifndef __STM32F10x_RCC_H
#define __STM32F10x_RCC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u32 SYSCLK_Frequency;
  u32 HCLK_Frequency;
  u32 PCLK1_Frequency;
  u32 PCLK2_Frequency;
  u32 ADCCLK_Frequency;
}RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/
/* HSE configuration */
#define RCC_HSE_OFF                      ((u32)0x00000000)
#define RCC_HSE_ON                       ((u32)0x00010000)
#define RCC_HSE_Bypass                   ((u32)0x00040000)

#define IS_RCC_HSE(HSE) ((HSE == RCC_HSE_OFF) || (HSE == RCC_HSE_ON) || \
                         (HSE == RCC_HSE_Bypass))

/* PLL entry clock source */
#define RCC_PLLSource_HSI_Div2           ((u32)0x00000000)
#define RCC_PLLSource_HSE_Div1           ((u32)0x00010000)
#define RCC_PLLSource_HSE_Div2           ((u32)0x00030000)

#define IS_RCC_PLL_SOURCE(SOURCE) ((SOURCE == RCC_PLLSource_HSI_Div2) || \
                                   (SOURCE == RCC_PLLSource_HSE_Div1) || \
                                   (SOURCE == RCC_PLLSource_HSE_Div2))

/* PLL multiplication factor */
#define RCC_PLLMul_2                     ((u32)0x00000000)
#define RCC_PLLMul_3                     ((u32)0x00040000)
#define RCC_PLLMul_4                     ((u32)0x00080000)
#define RCC_PLLMul_5                     ((u32)0x000C0000)
#define RCC_PLLMul_6                     ((u32)0x00100000)
#define RCC_PLLMul_7                     ((u32)0x00140000)
#define RCC_PLLMul_8                     ((u32)0x00180000)
#define RCC_PLLMul_9                     ((u32)0x001C0000)
#define RCC_PLLMul_10                    ((u32)0x00200000)
#define RCC_PLLMul_11                    ((u32)0x00240000)
#define RCC_PLLMul_12                    ((u32)0x00280000)
#define RCC_PLLMul_13                    ((u32)0x002C0000)
#define RCC_PLLMul_14                    ((u32)0x00300000)
#define RCC_PLLMul_15                    ((u32)0x00340000)
#define RCC_PLLMul_16                    ((u32)0x00380000)

#define IS_RCC_PLL_MUL(MUL) ((MUL == RCC_PLLMul_2) || (MUL == RCC_PLLMul_3)   ||\
                             (MUL == RCC_PLLMul_4) || (MUL == RCC_PLLMul_5)   ||\
                             (MUL == RCC_PLLMul_6) || (MUL == RCC_PLLMul_7)   ||\
                             (MUL == RCC_PLLMul_8) || (MUL == RCC_PLLMul_9)   ||\
                             (MUL == RCC_PLLMul_10) || (MUL == RCC_PLLMul_11) ||\
                             (MUL == RCC_PLLMul_12) || (MUL == RCC_PLLMul_13) ||\
                             (MUL == RCC_PLLMul_14) || (MUL == RCC_PLLMul_15) ||\
                             (MUL == RCC_PLLMul_16))

/* System clock source */
#define RCC_SYSCLKSource_HSI             ((u32)0x00000000)
#define RCC_SYSCLKSource_HSE             ((u32)0x00000001)
#define RCC_SYSCLKSource_PLLCLK          ((u32)0x00000002)

#define IS_RCC_SYSCLK_SOURCE(SOURCE) ((SOURCE == RCC_SYSCLKSource_HSI) || \
                                      (SOURCE == RCC_SYSCLKSource_HSE) || \
                                      (SOURCE == RCC_SYSCLKSource_PLLCLK))

/* AHB clock source */
#define RCC_SYSCLK_Div1                  ((u32)0x00000000)
#define RCC_SYSCLK_Div2                  ((u32)0x00000080)
#define RCC_SYSCLK_Div4                  ((u32)0x00000090)
#define RCC_SYSCLK_Div8                  ((u32)0x000000A0)
#define RCC_SYSCLK_Div16                 ((u32)0x000000B0)
#define RCC_SYSCLK_Div64                 ((u32)0x000000C0)
#define RCC_SYSCLK_Div128                ((u32)0x000000D0)
#define RCC_SYSCLK_Div256                ((u32)0x000000E0)
#define RCC_SYSCLK_Div512                ((u32)0x000000F0)

#define IS_RCC_HCLK(HCLK) ((HCLK == RCC_SYSCLK_Div1) || (HCLK == RCC_SYSCLK_Div2) || \
                           (HCLK == RCC_SYSCLK_Div4) || (HCLK == RCC_SYSCLK_Div8) || \
                           (HCLK == RCC_SYSCLK_Div16) || (HCLK == RCC_SYSCLK_Div64) || \
                           (HCLK == RCC_SYSCLK_Div128) || (HCLK == RCC_SYSCLK_Div256) || \
                           (HCLK == RCC_SYSCLK_Div512))

/* APB1/APB2 clock source */
#define RCC_HCLK_Div1                    ((u32)0x00000000)
#define RCC_HCLK_Div2                    ((u32)0x00000400)
#define RCC_HCLK_Div4                    ((u32)0x00000500)
#define RCC_HCLK_Div8                    ((u32)0x00000600)
#define RCC_HCLK_Div16                   ((u32)0x00000700)

#define IS_RCC_PCLK(PCLK) ((PCLK == RCC_HCLK_Div1) || (PCLK == RCC_HCLK_Div2) || \
                           (PCLK == RCC_HCLK_Div4) || (PCLK == RCC_HCLK_Div8) || \
                           (PCLK == RCC_HCLK_Div16))

/* RCC Interrupt source */
#define RCC_IT_LSIRDY                    ((u8)0x01)
#define RCC_IT_LSERDY                    ((u8)0x02)
#define RCC_IT_HSIRDY                    ((u8)0x04)
#define RCC_IT_HSERDY                    ((u8)0x08)
#define RCC_IT_PLLRDY                    ((u8)0x10)
#define RCC_IT_CSS                       ((u8)0x80)

#define IS_RCC_IT(IT) (((IT & (u8)0xE0) == 0x00) && (IT != 0x00))
#define IS_RCC_GET_IT(IT) ((IT == RCC_IT_LSIRDY) || (IT == RCC_IT_LSERDY) || \
                           (IT == RCC_IT_HSIRDY) || (IT == RCC_IT_HSERDY) || \
                           (IT == RCC_IT_PLLRDY) || (IT == RCC_IT_CSS))
#define IS_RCC_CLEAR_IT(IT) (((IT & (u8)0x60) == 0x00) && (IT != 0x00))

/* USB clock source */
#define RCC_USBCLKSource_PLLCLK_1Div5    ((u8)0x00)
#define RCC_USBCLKSource_PLLCLK_Div1     ((u8)0x01)

#define IS_RCC_USBCLK_SOURCE(SOURCE) ((SOURCE == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      (SOURCE == RCC_USBCLKSource_PLLCLK_Div1))

/* ADC clock source */
#define RCC_PCLK2_Div2                   ((u32)0x00000000)
#define RCC_PCLK2_Div4                   ((u32)0x00004000)
#define RCC_PCLK2_Div6                   ((u32)0x00008000)
#define RCC_PCLK2_Div8                   ((u32)0x0000C000)

#define IS_RCC_ADCCLK(ADCCLK) ((ADCCLK == RCC_PCLK2_Div2) || (ADCCLK == RCC_PCLK2_Div4) || \
                               (ADCCLK == RCC_PCLK2_Div6) || (ADCCLK == RCC_PCLK2_Div8))

/* LSE configuration */
#define RCC_LSE_OFF                      ((u8)0x00)
#define RCC_LSE_ON                       ((u8)0x01)
#define RCC_LSE_Bypass                   ((u8)0x04)

#define IS_RCC_LSE(LSE) ((LSE == RCC_LSE_OFF) || (LSE == RCC_LSE_ON) || \
                         (LSE == RCC_LSE_Bypass))

/* RTC clock source */
#define RCC_RTCCLKSource_LSE             ((u32)0x00000100)
#define RCC_RTCCLKSource_LSI             ((u32)0x00000200)
#define RCC_RTCCLKSource_HSE_Div128      ((u32)0x00000300)

#define IS_RCC_RTCCLK_SOURCE(SOURCE) ((SOURCE == RCC_RTCCLKSource_LSE) || \
                                      (SOURCE == RCC_RTCCLKSource_LSI) || \
                                      (SOURCE == RCC_RTCCLKSource_HSE_Div128))

/* AHB peripheral */
#define RCC_AHBPeriph_DMA                ((u32)0x00000001)
#define RCC_AHBPeriph_SRAM               ((u32)0x00000004)
#define RCC_AHBPeriph_FLITF              ((u32)0x00000010)

#define IS_RCC_AHB_PERIPH(PERIPH) (((PERIPH & 0xFFFFFFEA) == 0x00) && (PERIPH != 0x00))

/* APB2 peripheral */
#define RCC_APB2Periph_AFIO              ((u32)0x00000001)
#define RCC_APB2Periph_GPIOA             ((u32)0x00000004)
#define RCC_APB2Periph_GPIOB             ((u32)0x00000008)
#define RCC_APB2Periph_GPIOC             ((u32)0x00000010)
#define RCC_APB2Periph_GPIOD             ((u32)0x00000020)
#define RCC_APB2Periph_GPIOE             ((u32)0x00000040)
#define RCC_APB2Periph_ADC1              ((u32)0x00000200)
#define RCC_APB2Periph_ADC2              ((u32)0x00000400)
#define RCC_APB2Periph_TIM1              ((u32)0x00000800)
#define RCC_APB2Periph_SPI1              ((u32)0x00001000)
#define RCC_APB2Periph_USART1            ((u32)0x00004000)
#define RCC_APB2Periph_ALL               ((u32)0x00005E7D)

#define IS_RCC_APB2_PERIPH(PERIPH) (((PERIPH & 0xFFFFA182) == 0x00) && (PERIPH != 0x00))

/* APB1 peripheral */
#define RCC_APB1Periph_TIM2              ((u32)0x00000001)
#define RCC_APB1Periph_TIM3              ((u32)0x00000002)
#define RCC_APB1Periph_TIM4              ((u32)0x00000004)
#define RCC_APB1Periph_WWDG              ((u32)0x00000800)
#define RCC_APB1Periph_SPI2              ((u32)0x00004000)
#define RCC_APB1Periph_USART2            ((u32)0x00020000)
#define RCC_APB1Periph_USART3            ((u32)0x00040000)
#define RCC_APB1Periph_I2C1              ((u32)0x00200000)
#define RCC_APB1Periph_I2C2              ((u32)0x00400000)
#define RCC_APB1Periph_USB               ((u32)0x00800000)
#define RCC_APB1Periph_CAN               ((u32)0x02000000)
#define RCC_APB1Periph_BKP               ((u32)0x08000000)
#define RCC_APB1Periph_PWR               ((u32)0x10000000)
#define RCC_APB1Periph_ALL               ((u32)0x1AE64807)

#define IS_RCC_APB1_PERIPH(PERIPH) (((PERIPH & 0xE519B7F8) == 0x00) && (PERIPH != 0x00))

/* Clock source to output on MCO pin */
#define RCC_MCO_NoClock                  ((u8)0x00)
#define RCC_MCO_SYSCLK                   ((u8)0x04)
#define RCC_MCO_HSI                      ((u8)0x05)
#define RCC_MCO_HSE                      ((u8)0x06)
#define RCC_MCO_PLLCLK_Div2              ((u8)0x07)

#define IS_RCC_MCO(MCO) ((MCO == RCC_MCO_NoClock) || (MCO == RCC_MCO_HSI) || \
                         (MCO == RCC_MCO_SYSCLK)  || (MCO == RCC_MCO_HSE) || \
                         (MCO == RCC_MCO_PLLCLK_Div2))

/* RCC Flag */
#define RCC_FLAG_HSIRDY                  ((u8)0x20)
#define RCC_FLAG_HSERDY                  ((u8)0x31)
#define RCC_FLAG_PLLRDY                  ((u8)0x39)
#define RCC_FLAG_LSERDY                  ((u8)0x41)
#define RCC_FLAG_LSIRDY                  ((u8)0x61)
#define RCC_FLAG_PINRST                  ((u8)0x7A)
#define RCC_FLAG_PORRST                  ((u8)0x7B)
#define RCC_FLAG_SFTRST                  ((u8)0x7C)
#define RCC_FLAG_IWDGRST                 ((u8)0x7D)
#define RCC_FLAG_WWDGRST                 ((u8)0x7E)
#define RCC_FLAG_LPWRRST                 ((u8)0x7F)

#define IS_RCC_FLAG(FLAG) ((FLAG == RCC_FLAG_HSIRDY) || (FLAG == RCC_FLAG_HSERDY) || \
                           (FLAG == RCC_FLAG_PLLRDY) || (FLAG == RCC_FLAG_LSERDY) || \
                           (FLAG == RCC_FLAG_LSIRDY) || (FLAG == RCC_FLAG_PINRST) || \
                           (FLAG == RCC_FLAG_PORRST) || (FLAG == RCC_FLAG_SFTRST) || \
                           (FLAG == RCC_FLAG_IWDGRST)|| (FLAG == RCC_FLAG_WWDGRST)|| \
                           (FLAG == RCC_FLAG_LPWRRST))

#define IS_RCC_CALIBRATION_VALUE(VALUE) (VALUE <= 0x1F)


/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application

   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined  HSE_VALUE
 #ifdef STM32F10X_CL
  #define HSE_VALUE    ((u32)25000000) /*!< Value of the External oscillator in Hz */
 #else
  #define HSE_VALUE    ((u32)8000000) /*!< Value of the External oscillator in Hz */
 #endif /* STM32F10X_CL */
#endif /* HSE_VALUE */


/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value
   */
#define HSE_STARTUP_TIMEOUT   ((u16)0x0500) /*!< Time out for HSE start up */

#define HSI_VALUE    ((u32)8000000) /*!< Value of the Internal oscillator in Hz*/

#define  RCC_CFGR_SWS                        ((u32)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_PLLMULL                    ((u32)0x003C0000)        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLSRC                     ((u32)0x00010000)        /*!< PLL entry clock source */
#define  RCC_CFGR_PLLXTPRE                   ((u32)0x00020000)        /*!< HSE divider for PLL entry */
#define  RCC_CFGR_HPRE                       ((u32)0x000000F0)        /*!< HPRE[3:0] bits (AHB prescaler) */
#define  RCC_CFGR_PLLSRC_HSE                ((u32)0x00010000)        /*!< HSE clock selected as PLL entry clock source */
#define  RCC_CFGR_PLLMULL9                  ((u32)0x001C0000)        /*!< PLL input clock*9 */
#define  RCC_CR_PLLON                        ((u32)0x01000000)        /*!< PLL enable */
#define  RCC_CR_PLLRDY                       ((u32)0x02000000)        /*!< PLL clock ready flag */


#define  FLASH_ACR_PRFTBE                    ((u8)0x10)               /*!<Prefetch Buffer Enable */
#define  FLASH_ACR_LATENCY                   ((u8)0x03)               /*!<LATENCY[2:0] bits (Latency) */
#define  FLASH_ACR_LATENCY_2                 ((u8)0x02)               /*!<Bit 1 */

#define  RCC_CFGR_HPRE_DIV1                  ((u32)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2                  ((u32)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4                  ((u32)0x00000090)        /*!< SYSCLK divided by 4 */

#define  RCC_CFGR_PPRE1_DIV1                 ((u32)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE1_DIV2                 ((u32)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE1_DIV4                 ((u32)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE1_DIV8                 ((u32)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE1_DIV16                ((u32)0x00000700)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_PPRE2_DIV1                 ((u32)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE2_DIV2                 ((u32)0x00002000)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE2_DIV4                 ((u32)0x00002800)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE2_DIV8                 ((u32)0x00003000)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE2_DIV16                ((u32)0x00003800)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_SW                         ((u32)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_PLL                     ((u32)0x00000002)        /*!< PLL selected as system clock */

#define  RCC_CR_HSEON                        ((u32)0x00010000)        /*!< External High Speed clock enable */
#define  RCC_CR_HSERDY                       ((u32)0x00020000)        /*!< External High Speed clock ready flag */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RCC_DeInit(void);
void RCC_HSEConfig(u32 RCC_HSE);
void RCC_AdjustHSICalibrationValue(u8 HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(u32 RCC_PLLSource, u32 RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_SYSCLKConfig(u32 RCC_SYSCLKSource);
u8 RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(u32 RCC_HCLK);
void RCC_PCLK1Config(u32 RCC_PCLK1);
void RCC_PCLK2Config(u32 RCC_PCLK2);
void RCC_ITConfig(u8 RCC_IT, FunctionalState NewState);
void RCC_USBCLKConfig(u32 RCC_USBCLKSource);
void RCC_ADCCLKConfig(u32 RCC_ADCCLK);
void RCC_LSEConfig(u32 RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(u32 RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(u32 RCC_APB1Periph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(u32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(u32 RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(u8 RCC_MCO);
FlagStatus RCC_GetFlagStatus(u8 RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(u8 RCC_IT);
void RCC_ClearITPendingBit(u8 RCC_IT);

#endif /* __STM32F10x_RCC_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
