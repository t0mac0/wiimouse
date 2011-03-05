/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_tim1.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the functions prototypes for the 
*                      TIM1 firmware library.
********************************************************************************
* History:
* 04/02/2007: V0.2
* mm/dd/yyyy: V0.1
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
#ifndef __STM32F10x_TIM1_H
#define __STM32F10x_TIM1_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/

/* TIM1 Time Base Init structure definition */
typedef struct
{
  uint16 TIM1_Prescaler;
  uint16 TIM1_CounterMode;
  uint16 TIM1_Period;
  uint16 TIM1_ClockDivision;
  uint8 TIM1_RepetitionCounter;
} TIM1_TimeBaseInitTypeDef;

/* TIM1 Output Compare Init structure definition */
typedef struct
{
  uint16 TIM1_OCMode;
  uint16 TIM1_OutputState;
  uint16 TIM1_OutputNState;
  uint16 TIM1_Pulse;
  uint16 TIM1_OCPolarity;
  uint16 TIM1_OCNPolarity;
  uint16 TIM1_OCIdleState;
  uint16 TIM1_OCNIdleState;
} TIM1_OCInitTypeDef;

/* TIM1 Input Capture Init structure definition */
typedef struct
{
  uint16 TIM1_Channel;
  uint16 TIM1_ICPolarity;
  uint16 TIM1_ICSelection;
  uint16 TIM1_ICPrescaler;
  uint8 TIM1_ICFilter;
} TIM1_ICInitTypeDef;

/* BDTR structure definition */
typedef struct
{
  uint16 TIM1_OSSRState;
  uint16 TIM1_OSSIState;
  uint16 TIM1_LOCKLevel; 
  uint16 TIM1_DeadTime;
  uint16 TIM1_Break;
  uint16 TIM1_BreakPolarity;
  uint16 TIM1_AutomaticOutput;
} TIM1_BDTRInitTypeDef;

/* Exported constants --------------------------------------------------------*/
/* TIM1 Output Compare and PWM modes ----------------------------------------*/
#define TIM1_OCMode_Timing                 ((uint16)0x0000)
#define TIM1_OCMode_Active                 ((uint16)0x0010)
#define TIM1_OCMode_Inactive               ((uint16)0x0020)
#define TIM1_OCMode_Toggle                 ((uint16)0x0030)
#define TIM1_OCMode_PWM1                   ((uint16)0x0060)
#define TIM1_OCMode_PWM2                   ((uint16)0x0070)

#define IS_TIM1_OC_MODE(MODE) ((MODE == TIM1_OCMode_Timing) || \
                               (MODE == TIM1_OCMode_Active) || \
                               (MODE == TIM1_OCMode_Inactive) || \
                               (MODE == TIM1_OCMode_Toggle)|| \
                               (MODE == TIM1_OCMode_PWM1) || \
                               (MODE == TIM1_OCMode_PWM2))

#define IS_TIM1_OCM(MODE)((MODE == TIM1_OCMode_Timing) || \
                          (MODE == TIM1_OCMode_Active) || \
                          (MODE == TIM1_OCMode_Inactive) || \
                          (MODE == TIM1_OCMode_Toggle)|| \
                          (MODE == TIM1_OCMode_PWM1) || \
                          (MODE == TIM1_OCMode_PWM2) ||	\
                          (MODE == TIM1_ForcedAction_Active) || \
                          (MODE == TIM1_ForcedAction_InActive))
/* TIM1 One Pulse Mode ------------------------------------------------------*/
#define TIM1_OPMode_Single                 ((uint16)0x0001)
#define TIM1_OPMode_Repetitive             ((uint16)0x0000)

#define IS_TIM1_OPM_MODE(MODE) ((MODE == TIM1_OPMode_Single) || \
                                (MODE == TIM1_OPMode_Repetitive))

/* TIM1 Channel -------------------------------------------------------------*/
#define TIM1_Channel_1                     ((uint16)0x0000)
#define TIM1_Channel_2                     ((uint16)0x0001)
#define TIM1_Channel_3                     ((uint16)0x0002)
#define TIM1_Channel_4                     ((uint16)0x0003)

#define IS_TIM1_CHANNEL(CHANNEL) ((CHANNEL == TIM1_Channel_1) || \
                                  (CHANNEL == TIM1_Channel_2) || \
                                  (CHANNEL == TIM1_Channel_3) || \
                                  (CHANNEL == TIM1_Channel_4))

#define IS_TIM1_PWMI_CHANNEL(CHANNEL) ((CHANNEL == TIM1_Channel_1) || \
                                       (CHANNEL == TIM1_Channel_2))

#define IS_TIM1_COMPLEMENTARY_CHANNEL(CHANNEL) ((CHANNEL == TIM1_Channel_1) || \
                                                (CHANNEL == TIM1_Channel_2) || \
                                                (CHANNEL == TIM1_Channel_3))
/* TIM1 Clock Division CKD --------------------------------------------------*/
#define TIM1_CKD_DIV1                      ((uint16)0x0000)
#define TIM1_CKD_DIV2                      ((uint16)0x0100)
#define TIM1_CKD_DIV4                      ((uint16)0x0200)

#define IS_TIM1_CKD_DIV(DIV) ((DIV == TIM1_CKD_DIV1) || \
                              (DIV == TIM1_CKD_DIV2) || \
                              (DIV == TIM1_CKD_DIV4))

/* TIM1 Counter Mode --------------------------------------------------------*/
#define TIM1_CounterMode_Up                ((uint16)0x0000)
#define TIM1_CounterMode_Down              ((uint16)0x0010)
#define TIM1_CounterMode_CenterAligned1    ((uint16)0x0020)
#define TIM1_CounterMode_CenterAligned2    ((uint16)0x0040)
#define TIM1_CounterMode_CenterAligned3    ((uint16)0x0060)

#define IS_TIM1_COUNTER_MODE(MODE) ((MODE == TIM1_CounterMode_Up) ||  \
                                    (MODE == TIM1_CounterMode_Down) || \
                                    (MODE == TIM1_CounterMode_CenterAligned1) || \
                                    (MODE == TIM1_CounterMode_CenterAligned2) || \
                                    (MODE == TIM1_CounterMode_CenterAligned3))

/* TIM1 Output Compare Polarity ---------------------------------------------*/
#define TIM1_OCPolarity_High               ((uint16)0x0000)
#define TIM1_OCPolarity_Low                ((uint16)0x0001)

#define IS_TIM1_OC_POLARITY(POLARITY) ((POLARITY == TIM1_OCPolarity_High) || \
                                       (POLARITY == TIM1_OCPolarity_Low))

/* TIM1 Output Compare N Polarity -------------------------------------------*/
#define TIM1_OCNPolarity_High              ((uint16)0x0000)
#define TIM1_OCNPolarity_Low               ((uint16)0x0001)

#define IS_TIM1_OCN_POLARITY(POLARITY) ((POLARITY == TIM1_OCNPolarity_High) || \
                                        (POLARITY == TIM1_OCNPolarity_Low))

/* TIM1 Output Compare states -----------------------------------------------*/
#define TIM1_OutputState_Disable           ((uint16)0x0000)
#define TIM1_OutputState_Enable            ((uint16)0x0001)

#define IS_TIM1_OUTPUT_STATE(STATE) ((STATE == TIM1_OutputState_Disable) || \
                                     (STATE == TIM1_OutputState_Enable))

/* TIM1 Output Compare N States ---------------------------------------------*/
#define TIM1_OutputNState_Disable          ((uint16)0x0000)
#define TIM1_OutputNState_Enable           ((uint16)0x0001)

#define IS_TIM1_OUTPUTN_STATE(STATE) ((STATE == TIM1_OutputNState_Disable) || \
                                      (STATE == TIM1_OutputNState_Enable))

/* Break Input enable/disable -----------------------------------------------*/
#define TIM1_Break_Enable                  ((uint16)0x1000)
#define TIM1_Break_Disable                 ((uint16)0x0000)

#define IS_TIM1_BREAK_STATE(STATE) ((STATE == TIM1_Break_Enable) || \
                                    (STATE == TIM1_Break_Disable))

/* Break Polarity -----------------------------------------------------------*/
#define TIM1_BreakPolarity_Low             ((uint16)0x0000)
#define TIM1_BreakPolarity_High            ((uint16)0x2000)

#define IS_TIM1_BREAK_POLARITY(POLARITY) ((POLARITY == TIM1_BreakPolarity_Low) || \
                                          (POLARITY == TIM1_BreakPolarity_High))

/* TIM1 AOE Bit Set/Reset ---------------------------------------------------*/
#define TIM1_AutomaticOutput_Enable        ((uint16)0x4000)
#define TIM1_AutomaticOutput_Disable       ((uint16)0x0000)

#define IS_TIM1_AUTOMATIC_OUTPUT_STATE(STATE) ((STATE == TIM1_AutomaticOutput_Enable) || \
                                               (STATE == TIM1_AutomaticOutput_Disable))
/* Lock levels --------------------------------------------------------------*/
#define TIM1_LOCKLevel_OFF                 ((uint16)0x0000)
#define TIM1_LOCKLevel_1                   ((uint16)0x0100)
#define TIM1_LOCKLevel_2                   ((uint16)0x0200)
#define TIM1_LOCKLevel_3                   ((uint16)0x0300)

#define IS_TIM1_LOCK_LEVEL(LEVEL) ((LEVEL == TIM1_LOCKLevel_OFF) || \
                                   (LEVEL == TIM1_LOCKLevel_1) || \
                                   (LEVEL == TIM1_LOCKLevel_2) || \
                                   (LEVEL == TIM1_LOCKLevel_3))

/* OSSI: Off-State Selection for Idle mode states ---------------------------*/
#define TIM1_OSSIState_Enable              ((uint16)0x0400)
#define TIM1_OSSIState_Disable             ((uint16)0x0000)

#define IS_TIM1_OSSI_STATE(STATE) ((STATE == TIM1_OSSIState_Enable) || \
                                   (STATE == TIM1_OSSIState_Disable))

/* OSSR: Off-State Selection for Run mode states ----------------------------*/
#define TIM1_OSSRState_Enable              ((uint16)0x0800)
#define TIM1_OSSRState_Disable             ((uint16)0x0000)

#define IS_TIM1_OSSR_STATE(STATE) ((STATE == TIM1_OSSRState_Enable) || \
                                   (STATE == TIM1_OSSRState_Disable))

/* TIM1 Output Compare Idle State -------------------------------------------*/
#define TIM1_OCIdleState_Set               ((uint16)0x0001)
#define TIM1_OCIdleState_Reset             ((uint16)0x0000)

#define IS_TIM1_OCIDLE_STATE(STATE) ((STATE == TIM1_OCIdleState_Set) || \
                                     (STATE == TIM1_OCIdleState_Reset))

/* TIM1 Output Compare N Idle State -----------------------------------------*/
#define TIM1_OCNIdleState_Set              ((uint16)0x0001)
#define TIM1_OCNIdleState_Reset            ((uint16)0x0000)

#define IS_TIM1_OCNIDLE_STATE(STATE) ((STATE == TIM1_OCNIdleState_Set) || \
                                      (STATE == TIM1_OCNIdleState_Reset))

/* TIM1 Input Capture Polarity ----------------------------------------------*/
#define  TIM1_ICPolarity_Rising            ((uint16)0x0000)
#define  TIM1_ICPolarity_Falling           ((uint16)0x0001)

#define IS_TIM1_IC_POLARITY(POLARITY) ((POLARITY == TIM1_ICPolarity_Rising) || \
                                       (POLARITY == TIM1_ICPolarity_Falling))

/* TIM1 Input Capture Selection ---------------------------------------------*/
#define TIM1_ICSelection_DirectTI          ((uint16)0x0001)
#define TIM1_ICSelection_IndirectTI        ((uint16)0x0002)
#define TIM1_ICSelection_TRGI              ((uint16)0x0003)

#define IS_TIM1_IC_SELECTION(SELECTION) ((SELECTION == TIM1_ICSelection_DirectTI) || \
                                         (SELECTION == TIM1_ICSelection_IndirectTI) || \
                                         (SELECTION == TIM1_ICSelection_TRGI))

/* TIM1 Input Capture Prescaler ---------------------------------------------*/
#define TIM1_ICPSC_DIV1                    ((uint16)0x0000)
#define TIM1_ICPSC_DIV2                    ((uint16)0x0004)
#define TIM1_ICPSC_DIV4                    ((uint16)0x0008)
#define TIM1_ICPSC_DIV8                    ((uint16)0x000C)

#define IS_TIM1_IC_PRESCALER(PRESCALER) ((PRESCALER == TIM1_ICPSC_DIV1) || \
                                         (PRESCALER == TIM1_ICPSC_DIV2) || \
                                         (PRESCALER == TIM1_ICPSC_DIV4) || \
                                         (PRESCALER == TIM1_ICPSC_DIV8))
                                         
/* TIM1 Input Capture Filer Value ---------------------------------------------*/
#define IS_TIM1_IC_FILTER(ICFILTER) (ICFILTER <= 0xF)                                              

/* TIM1 interrupt sources ---------------------------------------------------*/
#define TIM1_IT_Update                     ((uint16)0x0001)
#define TIM1_IT_CC1                        ((uint16)0x0002)
#define TIM1_IT_CC2                        ((uint16)0x0004)
#define TIM1_IT_CC3                        ((uint16)0x0008)
#define TIM1_IT_CC4                        ((uint16)0x0010)
#define TIM1_IT_COM                        ((uint16)0x0020)
#define TIM1_IT_Trigger                    ((uint16)0x0040)
#define TIM1_IT_Break                      ((uint16)0x0080)

#define IS_TIM1_IT(IT) (((IT & (uint16)0xFF00) == 0x0000) && (IT != 0x0000))

#define IS_TIM1_GET_IT(IT) ((IT == TIM1_IT_Update) || \
                            (IT == TIM1_IT_CC1) || \
                            (IT == TIM1_IT_CC2) || \
                            (IT == TIM1_IT_CC3) || \
                            (IT == TIM1_IT_CC4) || \
                            (IT == TIM1_IT_COM) || \
                            (IT == TIM1_IT_Trigger) || \
                            (IT == TIM1_IT_Break))

/* TIM1 DMA Base address ----------------------------------------------------*/
#define TIM1_DMABase_CR1                   ((uint16)0x0000)
#define TIM1_DMABase_CR2                   ((uint16)0x0001)
#define TIM1_DMABase_SMCR                  ((uint16)0x0002)
#define TIM1_DMABase_DIER                  ((uint16)0x0003)
#define TIM1_DMABase_SR                    ((uint16)0x0004)
#define TIM1_DMABase_EGR                   ((uint16)0x0005)
#define TIM1_DMABase_CCMR1                 ((uint16)0x0006)
#define TIM1_DMABase_CCMR2                 ((uint16)0x0007)
#define TIM1_DMABase_CCER                  ((uint16)0x0008)
#define TIM1_DMABase_CNT                   ((uint16)0x0009)
#define TIM1_DMABase_PSC                   ((uint16)0x000A)
#define TIM1_DMABase_ARR                   ((uint16)0x000B)
#define TIM1_DMABase_RCR                   ((uint16)0x000C)
#define TIM1_DMABase_CCR1                  ((uint16)0x000D)
#define TIM1_DMABase_CCR2                  ((uint16)0x000E)
#define TIM1_DMABase_CCR3                  ((uint16)0x000F)
#define TIM1_DMABase_CCR4                  ((uint16)0x0010)
#define TIM1_DMABase_BDTR                  ((uint16)0x0011)
#define TIM1_DMABase_DCR                   ((uint16)0x0012)

#define IS_TIM1_DMA_BASE(BASE) ((BASE == TIM1_DMABase_CR1) || \
                                (BASE == TIM1_DMABase_CR2) || \
                                (BASE == TIM1_DMABase_SMCR) || \
                                (BASE == TIM1_DMABase_DIER) || \
                                (BASE == TIM1_DMABase_SR) || \
                                (BASE == TIM1_DMABase_EGR) || \
                                (BASE == TIM1_DMABase_CCMR1) || \
                                (BASE == TIM1_DMABase_CCMR2) || \
                                (BASE == TIM1_DMABase_CCER) || \
                                (BASE == TIM1_DMABase_CNT) || \
                                (BASE == TIM1_DMABase_PSC) || \
                                (BASE == TIM1_DMABase_ARR) || \
                                (BASE == TIM1_DMABase_RCR) || \
                                (BASE == TIM1_DMABase_CCR1) || \
                                (BASE == TIM1_DMABase_CCR2) || \
                                (BASE == TIM1_DMABase_CCR3) || \
                                (BASE == TIM1_DMABase_CCR4) || \
                                (BASE == TIM1_DMABase_BDTR) || \
                                (BASE == TIM1_DMABase_DCR))

/* TIM1 DMA Burst Length ----------------------------------------------------*/
#define TIM1_DMABurstLength_1Byte          ((uint16)0x0000)
#define TIM1_DMABurstLength_2Bytes         ((uint16)0x0100)
#define TIM1_DMABurstLength_3Bytes         ((uint16)0x0200)
#define TIM1_DMABurstLength_4Bytes         ((uint16)0x0300)
#define TIM1_DMABurstLength_5Bytes         ((uint16)0x0400)
#define TIM1_DMABurstLength_6Bytes         ((uint16)0x0500)
#define TIM1_DMABurstLength_7Bytes         ((uint16)0x0600)
#define TIM1_DMABurstLength_8Bytes         ((uint16)0x0700)
#define TIM1_DMABurstLength_9Bytes         ((uint16)0x0800)
#define TIM1_DMABurstLength_10Bytes        ((uint16)0x0900)
#define TIM1_DMABurstLength_11Bytes        ((uint16)0x0A00)
#define TIM1_DMABurstLength_12Bytes        ((uint16)0x0B00)
#define TIM1_DMABurstLength_13Bytes        ((uint16)0x0C00)
#define TIM1_DMABurstLength_14Bytes        ((uint16)0x0D00)
#define TIM1_DMABurstLength_15Bytes        ((uint16)0x0E00)
#define TIM1_DMABurstLength_16Bytes        ((uint16)0x0F00)
#define TIM1_DMABurstLength_17Bytes        ((uint16)0x1000)
#define TIM1_DMABurstLength_18Bytes        ((uint16)0x1100)

#define IS_TIM1_DMA_LENGTH(LENGTH) ((LENGTH == TIM1_DMABurstLength_1Byte) || \
                                    (LENGTH == TIM1_DMABurstLength_2Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_3Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_4Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_5Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_6Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_7Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_8Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_9Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_10Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_11Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_12Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_13Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_14Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_15Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_16Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_17Bytes) || \
                                    (LENGTH == TIM1_DMABurstLength_18Bytes))

/* TIM1 DMA sources ---------------------------------------------------------*/
#define TIM1_DMA_Update                    ((uint16)0x0100)
#define TIM1_DMA_CC1                       ((uint16)0x0200)
#define TIM1_DMA_CC2                       ((uint16)0x0400)
#define TIM1_DMA_CC3                       ((uint16)0x0800)
#define TIM1_DMA_CC4                       ((uint16)0x1000)
#define TIM1_DMA_COM                       ((uint16)0x2000)
#define TIM1_DMA_Trigger                   ((uint16)0x4000)

#define IS_TIM1_DMA_SOURCE(SOURCE) (((SOURCE & (uint16)0x80FF) == 0x0000) && (SOURCE != 0x0000))

/* TIM1 External Trigger Prescaler ------------------------------------------*/
#define TIM1_ExtTRGPSC_OFF                 ((uint16)0x0000)
#define TIM1_ExtTRGPSC_DIV2                ((uint16)0x1000)
#define TIM1_ExtTRGPSC_DIV4                ((uint16)0x2000)
#define TIM1_ExtTRGPSC_DIV8                ((uint16)0x3000)

#define IS_TIM1_EXT_PRESCALER(PRESCALER) ((PRESCALER == TIM1_ExtTRGPSC_OFF) || \
                                          (PRESCALER == TIM1_ExtTRGPSC_DIV2) || \
                                          (PRESCALER == TIM1_ExtTRGPSC_DIV4) || \
                                          (PRESCALER == TIM1_ExtTRGPSC_DIV8))

/* TIM1 Internal Trigger Selection ------------------------------------------*/
#define TIM1_TS_ITR0                       ((uint16)0x0000)
#define TIM1_TS_ITR1                       ((uint16)0x0010)
#define TIM1_TS_ITR2                       ((uint16)0x0020)
#define TIM1_TS_ITR3                       ((uint16)0x0030)
#define TIM1_TS_TI1F_ED	                   ((uint16)0x0040)
#define TIM1_TS_TI1FP1                     ((uint16)0x0050)
#define TIM1_TS_TI2FP2                     ((uint16)0x0060)
#define TIM1_TS_ETRF                       ((uint16)0x0070)

#define IS_TIM1_TRIGGER_SELECTION(SELECTION) ((SELECTION == TIM1_TS_ITR0) || \
                                              (SELECTION == TIM1_TS_ITR1) || \
                                              (SELECTION == TIM1_TS_ITR2) || \
                                              (SELECTION == TIM1_TS_ITR3) || \
                                              (SELECTION == TIM1_TS_TI1F_ED) || \
                                              (SELECTION == TIM1_TS_TI1FP1) || \
                                              (SELECTION == TIM1_TS_TI2FP2) || \
                                              (SELECTION == TIM1_TS_ETRF))

#define IS_TIM1_INTERNAL_TRIGGER_SELECTION(SELECTION) ((SELECTION == TIM1_TS_ITR0) || \
                                                       (SELECTION == TIM1_TS_ITR1) || \
                                                       (SELECTION == TIM1_TS_ITR2) || \
                                                       (SELECTION == TIM1_TS_ITR3))

#define IS_TIM1_TIX_TRIGGER_SELECTION(SELECTION) ((SELECTION == TIM1_TS_TI1F_ED) || \
                                                  (SELECTION == TIM1_TS_TI1FP1) || \
                                                  (SELECTION == TIM1_TS_TI2FP2))

/* TIM1 External Trigger Polarity -------------------------------------------*/
#define TIM1_ExtTRGPolarity_Inverted       ((uint16)0x8000)
#define TIM1_ExtTRGPolarity_NonInverted    ((uint16)0x0000)

#define IS_TIM1_EXT_POLARITY(POLARITY) ((POLARITY == TIM1_ExtTRGPolarity_Inverted) || \
                                        (POLARITY == TIM1_ExtTRGPolarity_NonInverted))

/* TIM1 Prescaler Reload Mode -----------------------------------------------*/
#define TIM1_PSCReloadMode_Update          ((uint16)0x0000)
#define TIM1_PSCReloadMode_Immediate       ((uint16)0x0001)

#define IS_TIM1_PRESCALER_RELOAD(RELOAD) ((RELOAD == TIM1_PSCReloadMode_Update) || \
                                          (RELOAD == TIM1_PSCReloadMode_Immediate))

/* TIM1 Forced Action -------------------------------------------------------*/
#define TIM1_ForcedAction_Active           ((uint16)0x0050)
#define TIM1_ForcedAction_InActive         ((uint16)0x0040)

#define IS_TIM1_FORCED_ACTION(ACTION) ((ACTION == TIM1_ForcedAction_Active) || \
                                       (ACTION == TIM1_ForcedAction_InActive))

/* TIM1 Encoder Mode --------------------------------------------------------*/ 
#define TIM1_EncoderMode_TI1               ((uint16)0x0001)
#define TIM1_EncoderMode_TI2               ((uint16)0x0002)
#define TIM1_EncoderMode_TI12              ((uint16)0x0003)

#define IS_TIM1_ENCODER_MODE(MODE) ((MODE == TIM1_EncoderMode_TI1) || \
                                    (MODE == TIM1_EncoderMode_TI2) || \
                                    (MODE == TIM1_EncoderMode_TI12))

/* TIM1 Event Source --------------------------------------------------------*/
#define TIM1_EventSource_Update            ((uint16)0x0001)
#define TIM1_EventSource_CC1               ((uint16)0x0002)
#define TIM1_EventSource_CC2               ((uint16)0x0004)
#define TIM1_EventSource_CC3               ((uint16)0x0008)
#define TIM1_EventSource_CC4               ((uint16)0x0010)
#define TIM1_EventSource_COM               ((uint16)0x0020)
#define TIM1_EventSource_Trigger           ((uint16)0x0040)
#define TIM1_EventSource_Break             ((uint16)0x0080)

#define IS_TIM1_EVENT_SOURCE(SOURCE) (((SOURCE & (uint16)0xFF00) == 0x0000) && (SOURCE != 0x0000))
                                      

/* TIM1 Update Source -------------------------------------------------------*/
#define TIM1_UpdateSource_Global           ((uint16)0x0000)
#define TIM1_UpdateSource_Regular          ((uint16)0x0001)

#define IS_TIM1_UPDATE_SOURCE(SOURCE) ((SOURCE == TIM1_UpdateSource_Global) || \
                                       (SOURCE == TIM1_UpdateSource_Regular))

/* TIM1 Ouput Compare Preload State ------------------------------------------*/
#define TIM1_OCPreload_Enable              ((uint16)0x0001)
#define TIM1_OCPreload_Disable             ((uint16)0x0000)

#define IS_TIM1_OCPRELOAD_STATE(STATE) ((STATE == TIM1_OCPreload_Enable) || \
                                        (STATE == TIM1_OCPreload_Disable))

/* TIM1 Ouput Compare Fast State ---------------------------------------------*/
#define TIM1_OCFast_Enable                 ((uint16)0x0001)
#define TIM1_OCFast_Disable                ((uint16)0x0000)

#define IS_TIM1_OCFAST_STATE(STATE) ((STATE == TIM1_OCFast_Enable) || \
                                     (STATE == TIM1_OCFast_Disable))

/* TIM1 Trigger Output Source -----------------------------------------------*/ 
#define TIM1_TRGOSource_Reset              ((uint16)0x0000)
#define TIM1_TRGOSource_Enable             ((uint16)0x0010)
#define TIM1_TRGOSource_Update             ((uint16)0x0020)
#define TIM1_TRGOSource_OC1                ((uint16)0x0030)
#define TIM1_TRGOSource_OC1Ref             ((uint16)0x0040)
#define TIM1_TRGOSource_OC2Ref             ((uint16)0x0050)
#define TIM1_TRGOSource_OC3Ref             ((uint16)0x0060)
#define TIM1_TRGOSource_OC4Ref             ((uint16)0x0070)

#define IS_TIM1_TRGO_SOURCE(SOURCE) ((SOURCE == TIM1_TRGOSource_Reset) || \
                                     (SOURCE == TIM1_TRGOSource_Enable) || \
                                     (SOURCE == TIM1_TRGOSource_Update) || \
                                     (SOURCE == TIM1_TRGOSource_OC1) || \
                                     (SOURCE == TIM1_TRGOSource_OC1Ref) || \
                                     (SOURCE == TIM1_TRGOSource_OC2Ref) || \
                                     (SOURCE == TIM1_TRGOSource_OC3Ref) || \
                                     (SOURCE == TIM1_TRGOSource_OC4Ref))

/* TIM1 Slave Mode ----------------------------------------------------------*/
#define TIM1_SlaveMode_Reset               ((uint16)0x0004)
#define TIM1_SlaveMode_Gated               ((uint16)0x0005)
#define TIM1_SlaveMode_Trigger             ((uint16)0x0006)
#define TIM1_SlaveMode_External1           ((uint16)0x0007)

#define IS_TIM1_SLAVE_MODE(MODE) ((MODE == TIM1_SlaveMode_Reset) || \
                                  (MODE == TIM1_SlaveMode_Gated) || \
                                  (MODE == TIM1_SlaveMode_Trigger) || \
                                  (MODE == TIM1_SlaveMode_External1))

/* TIM1 TIx External Clock Source -------------------------------------------*/
#define TIM1_TIxExternalCLK1Source_TI1     ((uint16)0x0050)
#define TIM1_TIxExternalCLK1Source_TI2     ((uint16)0x0060)
#define TIM1_TIxExternalCLK1Source_TI1ED   ((uint16)0x0040)

#define IS_TIM1_TIXCLK_SOURCE(SOURCE) ((SOURCE == TIM1_TIxExternalCLK1Source_TI1) || \
                                       (SOURCE == TIM1_TIxExternalCLK1Source_TI2) || \
                                       (SOURCE == TIM1_TIxExternalCLK1Source_TI1ED))

/* TIM1 Master Slave Mode ---------------------------------------------------*/
#define TIM1_MasterSlaveMode_Enable        ((uint16)0x0001)
#define TIM1_MasterSlaveMode_Disable       ((uint16)0x0000)

#define IS_TIM1_MSM_STATE(STATE) ((STATE == TIM1_MasterSlaveMode_Enable) || \
                                  (STATE == TIM1_MasterSlaveMode_Disable))

/* TIM1 Flags ---------------------------------------------------------------*/
#define TIM1_FLAG_Update                   ((uint16)0x0001)
#define TIM1_FLAG_CC1                      ((uint16)0x0002)
#define TIM1_FLAG_CC2                      ((uint16)0x0004)
#define TIM1_FLAG_CC3                      ((uint16)0x0008)
#define TIM1_FLAG_CC4                      ((uint16)0x0010)
#define TIM1_FLAG_COM                      ((uint16)0x0020)
#define TIM1_FLAG_Trigger                  ((uint16)0x0040)
#define TIM1_FLAG_Break                    ((uint16)0x0080)
#define TIM1_FLAG_CC1OF                    ((uint16)0x0200)
#define TIM1_FLAG_CC2OF                    ((uint16)0x0400)
#define TIM1_FLAG_CC3OF                    ((uint16)0x0800)
#define TIM1_FLAG_CC4OF                    ((uint16)0x1000)

#define IS_TIM1_GET_FLAG(FLAG) ((FLAG == TIM1_FLAG_Update) || \
                                (FLAG == TIM1_FLAG_CC1) || \
                                (FLAG == TIM1_FLAG_CC2) || \
                                (FLAG == TIM1_FLAG_CC3) || \
                                (FLAG == TIM1_FLAG_CC4) || \
                                (FLAG == TIM1_FLAG_COM) || \
                                (FLAG == TIM1_FLAG_Trigger) || \
                                (FLAG == TIM1_FLAG_Break) || \
                                (FLAG == TIM1_FLAG_CC1OF) || \
                                (FLAG == TIM1_FLAG_CC2OF) || \
                                (FLAG == TIM1_FLAG_CC3OF) || \
                                (FLAG == TIM1_FLAG_CC4OF))

#define IS_TIM1_CLEAR_FLAG(FLAG) (((FLAG & (uint16)0xE100) == 0x0000) && (FLAG != 0x0000))
                                  

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TIM1_DeInit(void);
void TIM1_TimeBaseInit(TIM1_TimeBaseInitTypeDef* TIM1_TimeBaseInitStruct);
void TIM1_OC1Init(TIM1_OCInitTypeDef* TIM1_OCInitStruct);
void TIM1_OC2Init(TIM1_OCInitTypeDef* TIM1_OCInitStruct);
void TIM1_OC3Init(TIM1_OCInitTypeDef* TIM1_OCInitStruct);
void TIM1_OC4Init(TIM1_OCInitTypeDef* TIM1_OCInitStruct);
void TIM1_BDTRConfig(TIM1_BDTRInitTypeDef *TIM1_BDTRInitStruct);
void TIM1_ICInit(TIM1_ICInitTypeDef* TIM1_ICInitStruct);
void TIM1_PWMIConfig(TIM1_ICInitTypeDef* TIM1_ICInitStruct);
void TIM1_TimeBaseStructInit(TIM1_TimeBaseInitTypeDef* TIM1_TimeBaseInitStruct);
void TIM1_OCStructInit(TIM1_OCInitTypeDef* TIM1_OCInitStruct);
void TIM1_ICStructInit(TIM1_ICInitTypeDef* TIM1_ICInitStruct);
void TIM1_BDTRStructInit(TIM1_BDTRInitTypeDef* TIM1_BDTRInitStruct);
void TIM1_Cmd(FunctionalState NewState);
void TIM1_CtrlPWMOutputs(FunctionalState Newstate);
void TIM1_ITConfig(uint16 TIM1_IT, FunctionalState NewState);
void TIM1_DMAConfig(uint16 TIM1_DMABase, uint16 TIM1_DMABurstLength);
void TIM1_DMACmd(uint16 TIM1_DMASource, FunctionalState Newstate);
void TIM1_InternalClockConfig(void);
void TIM1_ETRClockMode1Config(uint16 TIM1_ExtTRGPrescaler, uint16 TIM1_ExtTRGPolarity, 
                             uint16 ExtTRGFilter);
void TIM1_ETRClockMode2Config(uint16 TIM1_ExtTRGPrescaler, uint16 TIM1_ExtTRGPolarity, 
                             uint16 ExtTRGFilter);
void TIM1_ITRxExternalClockConfig(uint16 TIM1_InputTriggerSource);
void TIM1_TIxExternalClockConfig(uint16 TIM1_TIxExternalCLKSource, uint16 TIM1_ICPolarity, 
                                uint8 ICFilter);
void TIM1_SelectInputTrigger(uint16 TIM1_InputTriggerSource);
void TIM1_UpdateDisableConfig(FunctionalState Newstate);
void TIM1_UpdateRequestConfig(uint8 TIM1_UpdateSource);
void TIM1_SelectHallSensor(FunctionalState Newstate);
void TIM1_SelectOnePulseMode(uint16 TIM1_OPMode);
void TIM1_SelectOutputTrigger(uint16 TIM1_TRGOSource);
void TIM1_SelectSlaveMode(uint16 TIM1_SlaveMode);
void TIM1_SelectMasterSlaveMode(uint16 TIM1_MasterSlaveMode);
void TIM1_EncoderInterfaceConfig(uint16 TIM1_EncoderMode, uint16 TIM1_IC1Polarity, 
                                uint16 TIM1_IC2Polarity);
void TIM1_PrescalerConfig(uint16 Prescaler, uint16 TIM1_PSCReloadMode);
void TIM1_CounterModeConfig(uint16 TIM1_CounterMode);
void TIM1_ForcedOC1Config(uint16 TIM1_ForcedAction);
void TIM1_ForcedOC2Config(uint16 TIM1_ForcedAction);
void TIM1_ForcedOC3Config(uint16 TIM1_ForcedAction);
void TIM1_ForcedOC4Config(uint16 TIM1_ForcedAction);
void TIM1_ARRPreloadConfig(FunctionalState Newstate);
void TIM1_SelectCOM(FunctionalState Newstate);
void TIM1_SelectCCDMA(FunctionalState Newstate);
void TIM1_CCPreloadControl(FunctionalState Newstate);
void TIM1_OC1PreloadConfig(uint16 TIM1_OCPreload);
void TIM1_OC2PreloadConfig(uint16 TIM1_OCPreload);
void TIM1_OC3PreloadConfig(uint16 TIM1_OCPreload);
void TIM1_OC4PreloadConfig(uint16 TIM1_OCPreload);
void TIM1_OC1FastConfig(uint16 TIM1_OCFast);
void TIM1_OC2FastConfig(uint16 TIM1_OCFast);
void TIM1_OC3FastConfig(uint16 TIM1_OCFast);
void TIM1_OC4FastConfig(uint16 TIM1_OCFast);
void TIM1_GenerateEvent(uint16 TIM1_EventSource);
void TIM1_OC1PolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_OC1NPolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_OC2PolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_OC2NPolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_OC3PolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_OC3NPolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_OC4PolarityConfig(uint16 TIM1_OCPolarity);
void TIM1_CCxCmd(uint16 TIM1_Channel, FunctionalState Newstate);
void TIM1_CCxNCmd(uint16 TIM1_Channel, FunctionalState Newstate);
void TIM1_SelectOCxM(uint16 TIM1_Channel, uint16 TIM1_OCMode);
void TIM1_SetAutoreload(uint16 Autoreload);
void TIM1_SetCompare1(uint16 Compare1);
void TIM1_SetCompare2(uint16 Compare2);
void TIM1_SetCompare3(uint16 Compare3);
void TIM1_SetCompare4(uint16 Compare4);
void TIM1_SetIC1Prescaler(uint16 TIM1_IC1Prescaler);
void TIM1_SetIC2Prescaler(uint16 TIM1_IC2Prescaler);
void TIM1_SetIC3Prescaler(uint16 TIM1_IC3Prescaler);
void TIM1_SetIC4Prescaler(uint16 TIM1_IC4Prescaler);
void TIM1_SetClockDivision(uint16 TIM1_CKD);
uint16 TIM1_GetCapture1(void);
uint16 TIM1_GetCapture2(void);
uint16 TIM1_GetCapture3(void);
uint16 TIM1_GetCapture4(void);
uint16 TIM1_GetCounter(void);
uint16 TIM1_GetPrescaler(void);
FlagStatus TIM1_GetFlagStatus(uint16 TIM1_FLAG); 
void TIM1_ClearFlag(uint16 TIM1_Flag);
ITStatus TIM1_GetITStatus(uint16 TIM1_IT);
void TIM1_ClearITPendingBit(uint16 TIM1_IT);

#endif /*__STM32F10x_TIM1_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
