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
  uint32 SYSCLK_Frequency;
  uint32 HCLK_Frequency;
  uint32 PCLK1_Frequency;
  uint32 PCLK2_Frequency;
  uint32 ADCCLK_Frequency;
}RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/
/* HSE configuration */
#define RCC_HSE_OFF                      ((uint32)0x00000000)
#define RCC_HSE_ON                       ((uint32)0x00010000)
#define RCC_HSE_Bypass                   ((uint32)0x00040000)

#define IS_RCC_HSE(HSE) ((HSE == RCC_HSE_OFF) || (HSE == RCC_HSE_ON) || \
                         (HSE == RCC_HSE_Bypass))

/* PLL entry clock source */
#define RCC_PLLSource_HSI_Div2           ((uint32)0x00000000)
#define RCC_PLLSource_HSE_Div1           ((uint32)0x00010000)
#define RCC_PLLSource_HSE_Div2           ((uint32)0x00030000)

#define IS_RCC_PLL_SOURCE(SOURCE) ((SOURCE == RCC_PLLSource_HSI_Div2) || \
                                   (SOURCE == RCC_PLLSource_HSE_Div1) || \
                                   (SOURCE == RCC_PLLSource_HSE_Div2))

/* PLL multiplication factor */
#define RCC_PLLMul_2                     ((uint32)0x00000000)
#define RCC_PLLMul_3                     ((uint32)0x00040000)
#define RCC_PLLMul_4                     ((uint32)0x00080000)
#define RCC_PLLMul_5                     ((uint32)0x000C0000)
#define RCC_PLLMul_6                     ((uint32)0x00100000)
#define RCC_PLLMul_7                     ((uint32)0x00140000)
#define RCC_PLLMul_8                     ((uint32)0x00180000)
#define RCC_PLLMul_9                     ((uint32)0x001C0000)
#define RCC_PLLMul_10                    ((uint32)0x00200000)
#define RCC_PLLMul_11                    ((uint32)0x00240000)
#define RCC_PLLMul_12                    ((uint32)0x00280000)
#define RCC_PLLMul_13                    ((uint32)0x002C0000)
#define RCC_PLLMul_14                    ((uint32)0x00300000)
#define RCC_PLLMul_15                    ((uint32)0x00340000)
#define RCC_PLLMul_16                    ((uint32)0x00380000)

#define IS_RCC_PLL_MUL(MUL) ((MUL == RCC_PLLMul_2) || (MUL == RCC_PLLMul_3)   ||\
                             (MUL == RCC_PLLMul_4) || (MUL == RCC_PLLMul_5)   ||\
                             (MUL == RCC_PLLMul_6) || (MUL == RCC_PLLMul_7)   ||\
                             (MUL == RCC_PLLMul_8) || (MUL == RCC_PLLMul_9)   ||\
                             (MUL == RCC_PLLMul_10) || (MUL == RCC_PLLMul_11) ||\
                             (MUL == RCC_PLLMul_12) || (MUL == RCC_PLLMul_13) ||\
                             (MUL == RCC_PLLMul_14) || (MUL == RCC_PLLMul_15) ||\
                             (MUL == RCC_PLLMul_16))

/* System clock source */
#define RCC_SYSCLKSource_HSI             ((uint32)0x00000000)
#define RCC_SYSCLKSource_HSE             ((uint32)0x00000001)
#define RCC_SYSCLKSource_PLLCLK          ((uint32)0x00000002)

#define IS_RCC_SYSCLK_SOURCE(SOURCE) ((SOURCE == RCC_SYSCLKSource_HSI) || \
                                      (SOURCE == RCC_SYSCLKSource_HSE) || \
                                      (SOURCE == RCC_SYSCLKSource_PLLCLK))

/* AHB clock source */
#define RCC_SYSCLK_Div1                  ((uint32)0x00000000)
#define RCC_SYSCLK_Div2                  ((uint32)0x00000080)
#define RCC_SYSCLK_Div4                  ((uint32)0x00000090)
#define RCC_SYSCLK_Div8                  ((uint32)0x000000A0)
#define RCC_SYSCLK_Div16                 ((uint32)0x000000B0)
#define RCC_SYSCLK_Div64                 ((uint32)0x000000C0)
#define RCC_SYSCLK_Div128                ((uint32)0x000000D0)
#define RCC_SYSCLK_Div256                ((uint32)0x000000E0)
#define RCC_SYSCLK_Div512                ((uint32)0x000000F0)

#define IS_RCC_HCLK(HCLK) ((HCLK == RCC_SYSCLK_Div1) || (HCLK == RCC_SYSCLK_Div2) || \
                           (HCLK == RCC_SYSCLK_Div4) || (HCLK == RCC_SYSCLK_Div8) || \
                           (HCLK == RCC_SYSCLK_Div16) || (HCLK == RCC_SYSCLK_Div64) || \
                           (HCLK == RCC_SYSCLK_Div128) || (HCLK == RCC_SYSCLK_Div256) || \
                           (HCLK == RCC_SYSCLK_Div512))

/* APB1/APB2 clock source */
#define RCC_HCLK_Div1                    ((uint32)0x00000000)
#define RCC_HCLK_Div2                    ((uint32)0x00000400)
#define RCC_HCLK_Div4                    ((uint32)0x00000500)
#define RCC_HCLK_Div8                    ((uint32)0x00000600)
#define RCC_HCLK_Div16                   ((uint32)0x00000700)

#define IS_RCC_PCLK(PCLK) ((PCLK == RCC_HCLK_Div1) || (PCLK == RCC_HCLK_Div2) || \
                           (PCLK == RCC_HCLK_Div4) || (PCLK == RCC_HCLK_Div8) || \
                           (PCLK == RCC_HCLK_Div16))

/* RCC Interrupt source */
#define RCC_IT_LSIRDY                    ((uint8)0x01)
#define RCC_IT_LSERDY                    ((uint8)0x02)
#define RCC_IT_HSIRDY                    ((uint8)0x04)
#define RCC_IT_HSERDY                    ((uint8)0x08)
#define RCC_IT_PLLRDY                    ((uint8)0x10)
#define RCC_IT_CSS                       ((uint8)0x80)

#define IS_RCC_IT(IT) (((IT & (uint8)0xE0) == 0x00) && (IT != 0x00))
#define IS_RCC_GET_IT(IT) ((IT == RCC_IT_LSIRDY) || (IT == RCC_IT_LSERDY) || \
                           (IT == RCC_IT_HSIRDY) || (IT == RCC_IT_HSERDY) || \
                           (IT == RCC_IT_PLLRDY) || (IT == RCC_IT_CSS))
#define IS_RCC_CLEAR_IT(IT) (((IT & (uint8)0x60) == 0x00) && (IT != 0x00))

/* USB clock source */
#define RCC_USBCLKSource_PLLCLK_1Div5    ((uint8)0x00)
#define RCC_USBCLKSource_PLLCLK_Div1     ((uint8)0x01)

#define IS_RCC_USBCLK_SOURCE(SOURCE) ((SOURCE == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      (SOURCE == RCC_USBCLKSource_PLLCLK_Div1))

/* ADC clock source */
#define RCC_PCLK2_Div2                   ((uint32)0x00000000)
#define RCC_PCLK2_Div4                   ((uint32)0x00004000)
#define RCC_PCLK2_Div6                   ((uint32)0x00008000)
#define RCC_PCLK2_Div8                   ((uint32)0x0000C000)

#define IS_RCC_ADCCLK(ADCCLK) ((ADCCLK == RCC_PCLK2_Div2) || (ADCCLK == RCC_PCLK2_Div4) || \
                               (ADCCLK == RCC_PCLK2_Div6) || (ADCCLK == RCC_PCLK2_Div8))

/* LSE configuration */
#define RCC_LSE_OFF                      ((uint8)0x00)
#define RCC_LSE_ON                       ((uint8)0x01)
#define RCC_LSE_Bypass                   ((uint8)0x04)

#define IS_RCC_LSE(LSE) ((LSE == RCC_LSE_OFF) || (LSE == RCC_LSE_ON) || \
                         (LSE == RCC_LSE_Bypass))

/* RTC clock source */
#define RCC_RTCCLKSource_LSE             ((uint32)0x00000100)
#define RCC_RTCCLKSource_LSI             ((uint32)0x00000200)
#define RCC_RTCCLKSource_HSE_Div128      ((uint32)0x00000300)

#define IS_RCC_RTCCLK_SOURCE(SOURCE) ((SOURCE == RCC_RTCCLKSource_LSE) || \
                                      (SOURCE == RCC_RTCCLKSource_LSI) || \
                                      (SOURCE == RCC_RTCCLKSource_HSE_Div128))

/* AHB peripheral */
#define RCC_AHBPeriph_DMA                ((uint32)0x00000001)
#define RCC_AHBPeriph_SRAM               ((uint32)0x00000004)
#define RCC_AHBPeriph_FLITF              ((uint32)0x00000010)

#define IS_RCC_AHB_PERIPH(PERIPH) (((PERIPH & 0xFFFFFFEA) == 0x00) && (PERIPH != 0x00))

/* APB2 peripheral */
#define RCC_APB2Periph_AFIO              ((uint32)0x00000001)
#define RCC_APB2Periph_GPIOA             ((uint32)0x00000004)
#define RCC_APB2Periph_GPIOB             ((uint32)0x00000008)
#define RCC_APB2Periph_GPIOC             ((uint32)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32)0x00000020)
#define RCC_APB2Periph_GPIOE             ((uint32)0x00000040)
#define RCC_APB2Periph_ADC1              ((uint32)0x00000200)
#define RCC_APB2Periph_ADC2              ((uint32)0x00000400)
#define RCC_APB2Periph_TIM1              ((uint32)0x00000800)
#define RCC_APB2Periph_SPI1              ((uint32)0x00001000)
#define RCC_APB2Periph_USART1            ((uint32)0x00004000)
#define RCC_APB2Periph_ALL               ((uint32)0x00005E7D)

#define IS_RCC_APB2_PERIPH(PERIPH) (((PERIPH & 0xFFFFA182) == 0x00) && (PERIPH != 0x00))

/* APB1 peripheral */
#define RCC_APB1Periph_TIM2              ((uint32)0x00000001)
#define RCC_APB1Periph_TIM3              ((uint32)0x00000002)
#define RCC_APB1Periph_TIM4              ((uint32)0x00000004)
#define RCC_APB1Periph_WWDG              ((uint32)0x00000800)
#define RCC_APB1Periph_SPI2              ((uint32)0x00004000)
#define RCC_APB1Periph_USART2            ((uint32)0x00020000)
#define RCC_APB1Periph_USART3            ((uint32)0x00040000)
#define RCC_APB1Periph_I2C1              ((uint32)0x00200000)
#define RCC_APB1Periph_I2C2              ((uint32)0x00400000)
#define RCC_APB1Periph_USB               ((uint32)0x00800000)
#define RCC_APB1Periph_CAN               ((uint32)0x02000000)
#define RCC_APB1Periph_BKP               ((uint32)0x08000000)
#define RCC_APB1Periph_PWR               ((uint32)0x10000000)
#define RCC_APB1Periph_ALL               ((uint32)0x1AE64807)

#define IS_RCC_APB1_PERIPH(PERIPH) (((PERIPH & 0xE519B7F8) == 0x00) && (PERIPH != 0x00))

/* Clock source to output on MCO pin */
#define RCC_MCO_NoClock                  ((uint8)0x00)
#define RCC_MCO_SYSCLK                   ((uint8)0x04)
#define RCC_MCO_HSI                      ((uint8)0x05)
#define RCC_MCO_HSE                      ((uint8)0x06)
#define RCC_MCO_PLLCLK_Div2              ((uint8)0x07)

#define IS_RCC_MCO(MCO) ((MCO == RCC_MCO_NoClock) || (MCO == RCC_MCO_HSI) || \
                         (MCO == RCC_MCO_SYSCLK)  || (MCO == RCC_MCO_HSE) || \
                         (MCO == RCC_MCO_PLLCLK_Div2))

/* RCC Flag */
#define RCC_FLAG_HSIRDY                  ((uint8)0x20)
#define RCC_FLAG_HSERDY                  ((uint8)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8)0x39)
#define RCC_FLAG_LSERDY                  ((uint8)0x41)
#define RCC_FLAG_LSIRDY                  ((uint8)0x61)
#define RCC_FLAG_PINRST                  ((uint8)0x7A)
#define RCC_FLAG_PORRST                  ((uint8)0x7B)
#define RCC_FLAG_SFTRST                  ((uint8)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8)0x7E)
#define RCC_FLAG_LPWRRST                 ((uint8)0x7F)

#define IS_RCC_FLAG(FLAG) ((FLAG == RCC_FLAG_HSIRDY) || (FLAG == RCC_FLAG_HSERDY) || \
                           (FLAG == RCC_FLAG_PLLRDY) || (FLAG == RCC_FLAG_LSERDY) || \
                           (FLAG == RCC_FLAG_LSIRDY) || (FLAG == RCC_FLAG_PINRST) || \
                           (FLAG == RCC_FLAG_PORRST) || (FLAG == RCC_FLAG_SFTRST) || \
                           (FLAG == RCC_FLAG_IWDGRST)|| (FLAG == RCC_FLAG_WWDGRST)|| \
                           (FLAG == RCC_FLAG_LPWRRST))

#define IS_RCC_CALIBRATION_VALUE(VALUE) (VALUE <= 0x1F)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RCC_DeInit(void);
void RCC_HSEConfig(uint32 RCC_HSE);
void RCC_AdjustHSICalibrationValue(uint8 HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32 RCC_PLLSource, uint32 RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_SYSCLKConfig(uint32 RCC_SYSCLKSource);
uint8 RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32 RCC_HCLK);
void RCC_PCLK1Config(uint32 RCC_PCLK1);
void RCC_PCLK2Config(uint32 RCC_PCLK2);
void RCC_ITConfig(uint8 RCC_IT, FunctionalState NewState);
void RCC_USBCLKConfig(uint32 RCC_USBCLKSource);
void RCC_ADCCLKConfig(uint32 RCC_ADCCLK);
void RCC_LSEConfig(uint32 RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32 RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32 RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32 RCC_APB1Periph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(uint32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32 RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8 RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8 RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8 RCC_IT);
void RCC_ClearITPendingBit(uint8 RCC_IT);

#endif /* __STM32F10x_RCC_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
