/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_tim.h
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file contains all the functions prototypes for the 
*                      TIM firmware library.
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
#ifndef __STM32F10x_TIM_H
#define __STM32F10x_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

typedef struct
{
  uint16 TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint16 TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  uint16 TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */

  uint16 TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  uint8 TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF.
                                       @note This parameter is valid only for TIM1 and TIM8. */
} TIM_TimeBaseInitTypeDef;

/**
  * @brief  TIM Output Compare Init structure definition
  */

typedef struct
{
  uint16 TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16 TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

  uint16 TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16 TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16 TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16 TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16 TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

  uint16 TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
} TIM_OCInitTypeDef;

/**
  * @brief  TIM Input Capture Init structure definition
  */

typedef struct
{

  uint16 TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  uint16 TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint16 TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint16 TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint16 TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef;

/**
  * @brief  BDTR structure definition
  * @note   This sturcture is used only with TIM1 and TIM8.
  */

typedef struct
{

  uint16 TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state */

  uint16 TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16 TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref Lock_level */

  uint16 TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16 TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not.
                                      This parameter can be a value of @ref Break_Input_enable_disable */

  uint16 TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref Break_Polarity */

  uint16 TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not.
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BDTRInitTypeDef;

/** @defgroup TIM_Exported_constants
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2) || \
                                   ((PERIPH) == TIM3) || \
                                   ((PERIPH) == TIM4) || \
                                   ((PERIPH) == TIM5) || \
                                   ((PERIPH) == TIM6) || \
                                   ((PERIPH) == TIM7) || \
                                   ((PERIPH) == TIM8) || \
                                   ((PERIPH) == TIM9) || \
                                   ((PERIPH) == TIM10)|| \
                                   ((PERIPH) == TIM11)|| \
                                   ((PERIPH) == TIM12)|| \
                                   ((PERIPH) == TIM13)|| \
                                   ((PERIPH) == TIM14)|| \
                                   ((PERIPH) == TIM15)|| \
                                   ((PERIPH) == TIM16)|| \
                                   ((PERIPH) == TIM17))


/* LIST1: TIM 1 and 8 */
#define IS_TIM_LIST1_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM8))

/* LIST2: TIM 1, 8, 15 16 and 17 */
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17))


/* LIST3: TIM 1, 2, 3, 4, 5 and 8 */
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8))


/* LIST4: TIM 1, 2, 3, 4, 5, 8, 15, 16 and 17 */
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15)|| \
                                     ((PERIPH) == TIM16)|| \
                                     ((PERIPH) == TIM17))


/* LIST5: TIM 1, 2, 3, 4, 5, 8 and 15 */
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM15))

/* LIST6: TIM 1, 2, 3, 4, 5, 8, 9, 12 and 15 */
#define IS_TIM_LIST6_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM9) || \
                                      ((PERIPH) == TIM12)|| \
                                      ((PERIPH) == TIM15))


/* LIST7: TIM 1, 2, 3, 4, 5, 6, 7, 8, 9, 12 and 15 */
#define IS_TIM_LIST7_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM6) || \
                                      ((PERIPH) == TIM7) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM9) || \
                                      ((PERIPH) == TIM12)|| \
                                      ((PERIPH) == TIM15))


/* LIST8: TIM 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15, 16 and 17 */
#define IS_TIM_LIST8_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM9) || \
                                      ((PERIPH) == TIM10)|| \
                                      ((PERIPH) == TIM11)|| \
                                      ((PERIPH) == TIM12)|| \
                                      ((PERIPH) == TIM13)|| \
                                      ((PERIPH) == TIM14)|| \
                                      ((PERIPH) == TIM15)|| \
                                      ((PERIPH) == TIM16)|| \
                                      ((PERIPH) == TIM17))


/* LIST9: TIM 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, and 17 */
#define IS_TIM_LIST9_PERIPH(PERIPH)  (((PERIPH) == TIM1) || \
                                      ((PERIPH) == TIM2) || \
                                      ((PERIPH) == TIM3) || \
                                      ((PERIPH) == TIM4) || \
                                      ((PERIPH) == TIM5) || \
                                      ((PERIPH) == TIM6) || \
                                      ((PERIPH) == TIM7) || \
                                      ((PERIPH) == TIM8) || \
                                      ((PERIPH) == TIM15)|| \
                                      ((PERIPH) == TIM16)|| \
                                      ((PERIPH) == TIM17))


/**
  * @}
  */

/** @defgroup TIM_Output_Compare_and_PWM_modes
  * @{
  */

#define TIM_OCMode_Timing                  ((uint16)0x0000)
#define TIM_OCMode_Active                  ((uint16)0x0010)
#define TIM_OCMode_Inactive                ((uint16)0x0020)
#define TIM_OCMode_Toggle                  ((uint16)0x0030)
#define TIM_OCMode_PWM1                    ((uint16)0x0060)
#define TIM_OCMode_PWM2                    ((uint16)0x0070)
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||    \
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode
  * @{
  */

#define TIM_OPMode_Single                  ((uint16)0x0008)
#define TIM_OPMode_Repetitive              ((uint16)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
  * @}
  */

/** @defgroup TIM_Channel
  * @{
  */

#define TIM_Channel_1                      ((uint16)0x0000)
#define TIM_Channel_2                      ((uint16)0x0004)
#define TIM_Channel_3                      ((uint16)0x0008)
#define TIM_Channel_4                      ((uint16)0x000C)
#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
/**
  * @}
  */

/** @defgroup TIM_Clock_Division_CKD
  * @{
  */

#define TIM_CKD_DIV1                       ((uint16)0x0000)
#define TIM_CKD_DIV2                       ((uint16)0x0100)
#define TIM_CKD_DIV4                       ((uint16)0x0200)
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode
  * @{
  */

#define TIM_CounterMode_Up                 ((uint16)0x0000)
#define TIM_CounterMode_Down               ((uint16)0x0010)
#define TIM_CounterMode_CenterAligned1     ((uint16)0x0020)
#define TIM_CounterMode_CenterAligned2     ((uint16)0x0040)
#define TIM_CounterMode_CenterAligned3     ((uint16)0x0060)
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Polarity
  * @{
  */

#define TIM_OCPolarity_High                ((uint16)0x0000)
#define TIM_OCPolarity_Low                 ((uint16)0x0002)
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity
  * @{
  */

#define TIM_OCNPolarity_High               ((uint16)0x0000)
#define TIM_OCNPolarity_Low                ((uint16)0x0008)
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_state
  * @{
  */

#define TIM_OutputState_Disable            ((uint16)0x0000)
#define TIM_OutputState_Enable             ((uint16)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_state
  * @{
  */

#define TIM_OutputNState_Disable           ((uint16)0x0000)
#define TIM_OutputNState_Enable            ((uint16)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
  * @}
  */

/** @defgroup TIM_Capture_Compare_state
  * @{
  */

#define TIM_CCx_Enable                      ((uint16)0x0001)
#define TIM_CCx_Disable                     ((uint16)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */

/** @defgroup TIM_Capture_Compare_N_state
  * @{
  */

#define TIM_CCxN_Enable                     ((uint16)0x0004)
#define TIM_CCxN_Disable                    ((uint16)0x0000)
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))
/**
  * @}
  */

/** @defgroup Break_Input_enable_disable
  * @{
  */

#define TIM_Break_Enable                   ((uint16)0x1000)
#define TIM_Break_Disable                  ((uint16)0x0000)
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))
/**
  * @}
  */

/** @defgroup Break_Polarity
  * @{
  */

#define TIM_BreakPolarity_Low              ((uint16)0x0000)
#define TIM_BreakPolarity_High             ((uint16)0x2000)
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))
/**
  * @}
  */

/** @defgroup TIM_AOE_Bit_Set_Reset
  * @{
  */

#define TIM_AutomaticOutput_Enable         ((uint16)0x4000)
#define TIM_AutomaticOutput_Disable        ((uint16)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
  * @}
  */

/** @defgroup Lock_level
  * @{
  */

#define TIM_LOCKLevel_OFF                  ((uint16)0x0000)
#define TIM_LOCKLevel_1                    ((uint16)0x0100)
#define TIM_LOCKLevel_2                    ((uint16)0x0200)
#define TIM_LOCKLevel_3                    ((uint16)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))
/**
  * @}
  */

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state
  * @{
  */

#define TIM_OSSIState_Enable               ((uint16)0x0400)
#define TIM_OSSIState_Disable              ((uint16)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state
  * @{
  */

#define TIM_OSSRState_Enable               ((uint16)0x0800)
#define TIM_OSSRState_Disable              ((uint16)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Idle_State
  * @{
  */

#define TIM_OCIdleState_Set                ((uint16)0x0100)
#define TIM_OCIdleState_Reset              ((uint16)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Idle_State
  * @{
  */

#define TIM_OCNIdleState_Set               ((uint16)0x0200)
#define TIM_OCNIdleState_Reset             ((uint16)0x0000)
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Polarity
  * @{
  */

#define  TIM_ICPolarity_Rising             ((uint16)0x0000)
#define  TIM_ICPolarity_Falling            ((uint16)0x0002)
#define  TIM_ICPolarity_BothEdge           ((uint16)0x000A)
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling))
#define IS_TIM_IC_POLARITY_LITE(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                           ((POLARITY) == TIM_ICPolarity_Falling)|| \
                                           ((POLARITY) == TIM_ICPolarity_BothEdge))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Selection
  * @{
  */

#define TIM_ICSelection_DirectTI           ((uint16)0x0001) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI         ((uint16)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC                ((uint16)0x0003) /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Prescaler
  * @{
  */

#define TIM_ICPSC_DIV1                     ((uint16)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2                     ((uint16)0x0004) /*!< Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4                     ((uint16)0x0008) /*!< Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8                     ((uint16)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))
/**
  * @}
  */

/** @defgroup TIM_interrupt_sources
  * @{
  */

#define TIM_IT_Update                      ((uint16)0x0001)
#define TIM_IT_CC1                         ((uint16)0x0002)
#define TIM_IT_CC2                         ((uint16)0x0004)
#define TIM_IT_CC3                         ((uint16)0x0008)
#define TIM_IT_CC4                         ((uint16)0x0010)
#define TIM_IT_COM                         ((uint16)0x0020)
#define TIM_IT_Trigger                     ((uint16)0x0040)
#define TIM_IT_Break                       ((uint16)0x0080)
#define IS_TIM_IT(IT) ((((IT) & (uint16)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))
/**
  * @}
  */

/** @defgroup TIM_DMA_Base_address
  * @{
  */

#define TIM_DMABase_CR1                    ((uint16)0x0000)
#define TIM_DMABase_CR2                    ((uint16)0x0001)
#define TIM_DMABase_SMCR                   ((uint16)0x0002)
#define TIM_DMABase_DIER                   ((uint16)0x0003)
#define TIM_DMABase_SR                     ((uint16)0x0004)
#define TIM_DMABase_EGR                    ((uint16)0x0005)
#define TIM_DMABase_CCMR1                  ((uint16)0x0006)
#define TIM_DMABase_CCMR2                  ((uint16)0x0007)
#define TIM_DMABase_CCER                   ((uint16)0x0008)
#define TIM_DMABase_CNT                    ((uint16)0x0009)
#define TIM_DMABase_PSC                    ((uint16)0x000A)
#define TIM_DMABase_ARR                    ((uint16)0x000B)
#define TIM_DMABase_RCR                    ((uint16)0x000C)
#define TIM_DMABase_CCR1                   ((uint16)0x000D)
#define TIM_DMABase_CCR2                   ((uint16)0x000E)
#define TIM_DMABase_CCR3                   ((uint16)0x000F)
#define TIM_DMABase_CCR4                   ((uint16)0x0010)
#define TIM_DMABase_BDTR                   ((uint16)0x0011)
#define TIM_DMABase_DCR                    ((uint16)0x0012)
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
                               ((BASE) == TIM_DMABase_CR2) || \
                               ((BASE) == TIM_DMABase_SMCR) || \
                               ((BASE) == TIM_DMABase_DIER) || \
                               ((BASE) == TIM_DMABase_SR) || \
                               ((BASE) == TIM_DMABase_EGR) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) || \
                               ((BASE) == TIM_DMABase_CNT) || \
                               ((BASE) == TIM_DMABase_PSC) || \
                               ((BASE) == TIM_DMABase_ARR) || \
                               ((BASE) == TIM_DMABase_RCR) || \
                               ((BASE) == TIM_DMABase_CCR1) || \
                               ((BASE) == TIM_DMABase_CCR2) || \
                               ((BASE) == TIM_DMABase_CCR3) || \
                               ((BASE) == TIM_DMABase_CCR4) || \
                               ((BASE) == TIM_DMABase_BDTR) || \
                               ((BASE) == TIM_DMABase_DCR))
/**
  * @}
  */

/** @defgroup TIM_DMA_Burst_Length
  * @{
  */

#define TIM_DMABurstLength_1Byte           ((uint16)0x0000)
#define TIM_DMABurstLength_2Bytes          ((uint16)0x0100)
#define TIM_DMABurstLength_3Bytes          ((uint16)0x0200)
#define TIM_DMABurstLength_4Bytes          ((uint16)0x0300)
#define TIM_DMABurstLength_5Bytes          ((uint16)0x0400)
#define TIM_DMABurstLength_6Bytes          ((uint16)0x0500)
#define TIM_DMABurstLength_7Bytes          ((uint16)0x0600)
#define TIM_DMABurstLength_8Bytes          ((uint16)0x0700)
#define TIM_DMABurstLength_9Bytes          ((uint16)0x0800)
#define TIM_DMABurstLength_10Bytes         ((uint16)0x0900)
#define TIM_DMABurstLength_11Bytes         ((uint16)0x0A00)
#define TIM_DMABurstLength_12Bytes         ((uint16)0x0B00)
#define TIM_DMABurstLength_13Bytes         ((uint16)0x0C00)
#define TIM_DMABurstLength_14Bytes         ((uint16)0x0D00)
#define TIM_DMABurstLength_15Bytes         ((uint16)0x0E00)
#define TIM_DMABurstLength_16Bytes         ((uint16)0x0F00)
#define TIM_DMABurstLength_17Bytes         ((uint16)0x1000)
#define TIM_DMABurstLength_18Bytes         ((uint16)0x1100)
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Byte) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Bytes) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Bytes))
/**
  * @}
  */

/** @defgroup TIM_DMA_sources
  * @{
  */

#define TIM_DMA_Update                     ((uint16)0x0100)
#define TIM_DMA_CC1                        ((uint16)0x0200)
#define TIM_DMA_CC2                        ((uint16)0x0400)
#define TIM_DMA_CC3                        ((uint16)0x0800)
#define TIM_DMA_CC4                        ((uint16)0x1000)
#define TIM_DMA_COM                        ((uint16)0x2000)
#define TIM_DMA_Trigger                    ((uint16)0x4000)
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Prescaler
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  ((uint16)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((uint16)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((uint16)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((uint16)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
  * @}
  */

/** @defgroup TIM_Internal_Trigger_Selection
  * @{
  */

#define TIM_TS_ITR0                        ((uint16)0x0000)
#define TIM_TS_ITR1                        ((uint16)0x0010)
#define TIM_TS_ITR2                        ((uint16)0x0020)
#define TIM_TS_ITR3                        ((uint16)0x0030)
#define TIM_TS_TI1F_ED                     ((uint16)0x0040)
#define TIM_TS_TI1FP1                      ((uint16)0x0050)
#define TIM_TS_TI2FP2                      ((uint16)0x0060)
#define TIM_TS_ETRF                        ((uint16)0x0070)
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                             ((SELECTION) == TIM_TS_ITR1) || \
                                             ((SELECTION) == TIM_TS_ITR2) || \
                                             ((SELECTION) == TIM_TS_ITR3) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) || \
                                             ((SELECTION) == TIM_TS_TI2FP2) || \
                                             ((SELECTION) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))
/**
  * @}
  */

/** @defgroup TIM_TIx_External_Clock_Source
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      ((uint16)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((uint16)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16)0x0040)
#define IS_TIM_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TIM_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI1ED))
/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Polarity
  * @{
  */
#define TIM_ExtTRGPolarity_Inverted        ((uint16)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((uint16)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode
  * @{
  */

#define TIM_PSCReloadMode_Update           ((uint16)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16)0x0001)
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
/**
  * @}
  */

/** @defgroup TIM_Forced_Action
  * @{
  */

#define TIM_ForcedAction_Active            ((uint16)0x0050)
#define TIM_ForcedAction_InActive          ((uint16)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_Encoder_Mode
  * @{
  */

#define TIM_EncoderMode_TI1                ((uint16)0x0001)
#define TIM_EncoderMode_TI2                ((uint16)0x0002)
#define TIM_EncoderMode_TI12               ((uint16)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
  * @}
  */


/** @defgroup TIM_Event_Source
  * @{
  */

#define TIM_EventSource_Update             ((uint16)0x0001)
#define TIM_EventSource_CC1                ((uint16)0x0002)
#define TIM_EventSource_CC2                ((uint16)0x0004)
#define TIM_EventSource_CC3                ((uint16)0x0008)
#define TIM_EventSource_CC4                ((uint16)0x0010)
#define TIM_EventSource_COM                ((uint16)0x0020)
#define TIM_EventSource_Trigger            ((uint16)0x0040)
#define TIM_EventSource_Break              ((uint16)0x0080)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */

/** @defgroup TIM_Update_Source
  * @{
  */

#define TIM_UpdateSource_Global            ((uint16)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TIM_UpdateSource_Regular           ((uint16)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))
/**
  * @}
  */

/** @defgroup TIM_Ouput_Compare_Preload_State
  * @{
  */

#define TIM_OCPreload_Enable               ((uint16)0x0008)
#define TIM_OCPreload_Disable              ((uint16)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
  * @}
  */

/** @defgroup TIM_Ouput_Compare_Fast_State
  * @{
  */

#define TIM_OCFast_Enable                  ((uint16)0x0004)
#define TIM_OCFast_Disable                 ((uint16)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))

/**
  * @}
  */

/** @defgroup TIM_Ouput_Compare_Clear_State
  * @{
  */

#define TIM_OCClear_Enable                 ((uint16)0x0080)
#define TIM_OCClear_Disable                ((uint16)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
  * @}
  */

/** @defgroup TIM_Trigger_Output_Source
  * @{
  */

#define TIM_TRGOSource_Reset               ((uint16)0x0000)
#define TIM_TRGOSource_Enable              ((uint16)0x0010)
#define TIM_TRGOSource_Update              ((uint16)0x0020)
#define TIM_TRGOSource_OC1                 ((uint16)0x0030)
#define TIM_TRGOSource_OC1Ref              ((uint16)0x0040)
#define TIM_TRGOSource_OC2Ref              ((uint16)0x0050)
#define TIM_TRGOSource_OC3Ref              ((uint16)0x0060)
#define TIM_TRGOSource_OC4Ref              ((uint16)0x0070)
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
/**
  * @}
  */

/** @defgroup TIM_Slave_Mode
  * @{
  */

#define TIM_SlaveMode_Reset                ((uint16)0x0004)
#define TIM_SlaveMode_Gated                ((uint16)0x0005)
#define TIM_SlaveMode_Trigger              ((uint16)0x0006)
#define TIM_SlaveMode_External1            ((uint16)0x0007)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))
/**
  * @}
  */

/** @defgroup TIM_Master_Slave_Mode
  * @{
  */

#define TIM_MasterSlaveMode_Enable         ((uint16)0x0080)
#define TIM_MasterSlaveMode_Disable        ((uint16)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
  * @}
  */

/** @defgroup TIM_Flags
  * @{
  */

#define TIM_FLAG_Update                    ((uint16)0x0001)
#define TIM_FLAG_CC1                       ((uint16)0x0002)
#define TIM_FLAG_CC2                       ((uint16)0x0004)
#define TIM_FLAG_CC3                       ((uint16)0x0008)
#define TIM_FLAG_CC4                       ((uint16)0x0010)
#define TIM_FLAG_COM                       ((uint16)0x0020)
#define TIM_FLAG_Trigger                   ((uint16)0x0040)
#define TIM_FLAG_Break                     ((uint16)0x0080)
#define TIM_FLAG_CC1OF                     ((uint16)0x0200)
#define TIM_FLAG_CC2OF                     ((uint16)0x0400)
#define TIM_FLAG_CC3OF                     ((uint16)0x0800)
#define TIM_FLAG_CC4OF                     ((uint16)0x1000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))


#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint16)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Filer_Value
  * @{
  */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Filter
  * @{
  */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)










/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint16)0x0001)            /*!<Counter enable */
#define  TIM_CR1_UDIS                        ((uint16)0x0002)            /*!<Update disable */
#define  TIM_CR1_URS                         ((uint16)0x0004)            /*!<Update request source */
#define  TIM_CR1_OPM                         ((uint16)0x0008)            /*!<One pulse mode */
#define  TIM_CR1_DIR                         ((uint16)0x0010)            /*!<Direction */

#define  TIM_CR1_CMS                         ((uint16)0x0060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint16)0x0020)            /*!<Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint16)0x0040)            /*!<Bit 1 */

#define  TIM_CR1_ARPE                        ((uint16)0x0080)            /*!<Auto-reload preload enable */

#define  TIM_CR1_CKD                         ((uint16)0x0300)            /*!<CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint16)0x0100)            /*!<Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint16)0x0200)            /*!<Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC                        ((uint16)0x0001)            /*!<Capture/Compare Preloaded Control */
#define  TIM_CR2_CCUS                        ((uint16)0x0004)            /*!<Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS                        ((uint16)0x0008)            /*!<Capture/Compare DMA Selection */

#define  TIM_CR2_MMS                         ((uint16)0x0070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint16)0x0010)            /*!<Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint16)0x0020)            /*!<Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint16)0x0040)            /*!<Bit 2 */

#define  TIM_CR2_TI1S                        ((uint16)0x0080)            /*!<TI1 Selection */
#define  TIM_CR2_OIS1                        ((uint16)0x0100)            /*!<Output Idle state 1 (OC1 output) */
#define  TIM_CR2_OIS1N                       ((uint16)0x0200)            /*!<Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2                        ((uint16)0x0400)            /*!<Output Idle state 2 (OC2 output) */
#define  TIM_CR2_OIS2N                       ((uint16)0x0800)            /*!<Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3                        ((uint16)0x1000)            /*!<Output Idle state 3 (OC3 output) */
#define  TIM_CR2_OIS3N                       ((uint16)0x2000)            /*!<Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4                        ((uint16)0x4000)            /*!<Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint16)0x0007)            /*!<SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint16)0x0001)            /*!<Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint16)0x0002)            /*!<Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint16)0x0004)            /*!<Bit 2 */

#define  TIM_SMCR_TS                         ((uint16)0x0070)            /*!<TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint16)0x0010)            /*!<Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint16)0x0020)            /*!<Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint16)0x0040)            /*!<Bit 2 */

#define  TIM_SMCR_MSM                        ((uint16)0x0080)            /*!<Master/slave mode */

#define  TIM_SMCR_ETF                        ((uint16)0x0F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint16)0x0100)            /*!<Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint16)0x0200)            /*!<Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint16)0x0400)            /*!<Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint16)0x0800)            /*!<Bit 3 */

#define  TIM_SMCR_ETPS                       ((uint16)0x3000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint16)0x1000)            /*!<Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint16)0x2000)            /*!<Bit 1 */

#define  TIM_SMCR_ECE                        ((uint16)0x4000)            /*!<External clock enable */
#define  TIM_SMCR_ETP                        ((uint16)0x8000)            /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((uint16)0x0001)            /*!<Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((uint16)0x0002)            /*!<Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((uint16)0x0004)            /*!<Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((uint16)0x0008)            /*!<Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((uint16)0x0010)            /*!<Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((uint16)0x0020)            /*!<COM interrupt enable */
#define  TIM_DIER_TIE                        ((uint16)0x0040)            /*!<Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((uint16)0x0080)            /*!<Break interrupt enable */
#define  TIM_DIER_UDE                        ((uint16)0x0100)            /*!<Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((uint16)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((uint16)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((uint16)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((uint16)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((uint16)0x2000)            /*!<COM DMA request enable */
#define  TIM_DIER_TDE                        ((uint16)0x4000)            /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF                          ((uint16)0x0001)            /*!<Update interrupt Flag */
#define  TIM_SR_CC1IF                        ((uint16)0x0002)            /*!<Capture/Compare 1 interrupt Flag */
#define  TIM_SR_CC2IF                        ((uint16)0x0004)            /*!<Capture/Compare 2 interrupt Flag */
#define  TIM_SR_CC3IF                        ((uint16)0x0008)            /*!<Capture/Compare 3 interrupt Flag */
#define  TIM_SR_CC4IF                        ((uint16)0x0010)            /*!<Capture/Compare 4 interrupt Flag */
#define  TIM_SR_COMIF                        ((uint16)0x0020)            /*!<COM interrupt Flag */
#define  TIM_SR_TIF                          ((uint16)0x0040)            /*!<Trigger interrupt Flag */
#define  TIM_SR_BIF                          ((uint16)0x0080)            /*!<Break interrupt Flag */
#define  TIM_SR_CC1OF                        ((uint16)0x0200)            /*!<Capture/Compare 1 Overcapture Flag */
#define  TIM_SR_CC2OF                        ((uint16)0x0400)            /*!<Capture/Compare 2 Overcapture Flag */
#define  TIM_SR_CC3OF                        ((uint16)0x0800)            /*!<Capture/Compare 3 Overcapture Flag */
#define  TIM_SR_CC4OF                        ((uint16)0x1000)            /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint8_t)0x01)               /*!<Update Generation */
#define  TIM_EGR_CC1G                        ((uint8_t)0x02)               /*!<Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint8_t)0x04)               /*!<Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint8_t)0x08)               /*!<Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint8_t)0x10)               /*!<Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint8_t)0x20)               /*!<Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint8_t)0x40)               /*!<Trigger Generation */
#define  TIM_EGR_BG                          ((uint8_t)0x80)               /*!<Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint16)0x0003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint16)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint16)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR1_OC1FE                     ((uint16)0x0004)            /*!<Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint16)0x0008)            /*!<Output Compare 1 Preload enable */

#define  TIM_CCMR1_OC1M                      ((uint16)0x0070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint16)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint16)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint16)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR1_OC1CE                     ((uint16)0x0080)            /*!<Output Compare 1Clear Enable */

#define  TIM_CCMR1_CC2S                      ((uint16)0x0300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint16)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint16)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR1_OC2FE                     ((uint16)0x0400)            /*!<Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint16)0x0800)            /*!<Output Compare 2 Preload enable */

#define  TIM_CCMR1_OC2M                      ((uint16)0x7000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint16)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint16)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint16)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR1_OC2CE                     ((uint16)0x8000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC                    ((uint16)0x000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint16)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint16)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR1_IC1F                      ((uint16)0x00F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint16)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint16)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint16)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint16)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR1_IC2PSC                    ((uint16)0x0C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint16)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint16)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR1_IC2F                      ((uint16)0xF000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint16)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint16)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint16)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint16)0x8000)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint16)0x0003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint16)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint16)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR2_OC3FE                     ((uint16)0x0004)            /*!<Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint16)0x0008)            /*!<Output Compare 3 Preload enable */

#define  TIM_CCMR2_OC3M                      ((uint16)0x0070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint16)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint16)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint16)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR2_OC3CE                     ((uint16)0x0080)            /*!<Output Compare 3 Clear Enable */

#define  TIM_CCMR2_CC4S                      ((uint16)0x0300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint16)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint16)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR2_OC4FE                     ((uint16)0x0400)            /*!<Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint16)0x0800)            /*!<Output Compare 4 Preload enable */

#define  TIM_CCMR2_OC4M                      ((uint16)0x7000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint16)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint16)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint16)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR2_OC4CE                     ((uint16)0x8000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC                    ((uint16)0x000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint16)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint16)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR2_IC3F                      ((uint16)0x00F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint16)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint16)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint16)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint16)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR2_IC4PSC                    ((uint16)0x0C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint16)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint16)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR2_IC4F                      ((uint16)0xF000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint16)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint16)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint16)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint16)0x8000)            /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint16)0x0001)            /*!<Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint16)0x0002)            /*!<Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((uint16)0x0004)            /*!<Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((uint16)0x0008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((uint16)0x0010)            /*!<Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint16)0x0020)            /*!<Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((uint16)0x0040)            /*!<Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((uint16)0x0080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((uint16)0x0100)            /*!<Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint16)0x0200)            /*!<Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((uint16)0x0400)            /*!<Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((uint16)0x0800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((uint16)0x1000)            /*!<Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint16)0x2000)            /*!<Capture/Compare 4 output Polarity */
#define  TIM_CCER_CC4NP                      ((uint16)0x8000)            /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT                         ((uint16)0xFFFF)            /*!<Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC                         ((uint16)0xFFFF)            /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR                         ((uint16)0xFFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP                         ((uint8_t)0xFF)               /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1                       ((uint16)0xFFFF)            /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2                       ((uint16)0xFFFF)            /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3                       ((uint16)0xFFFF)            /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4                       ((uint16)0xFFFF)            /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG                        ((uint16)0x00FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0                      ((uint16)0x0001)            /*!<Bit 0 */
#define  TIM_BDTR_DTG_1                      ((uint16)0x0002)            /*!<Bit 1 */
#define  TIM_BDTR_DTG_2                      ((uint16)0x0004)            /*!<Bit 2 */
#define  TIM_BDTR_DTG_3                      ((uint16)0x0008)            /*!<Bit 3 */
#define  TIM_BDTR_DTG_4                      ((uint16)0x0010)            /*!<Bit 4 */
#define  TIM_BDTR_DTG_5                      ((uint16)0x0020)            /*!<Bit 5 */
#define  TIM_BDTR_DTG_6                      ((uint16)0x0040)            /*!<Bit 6 */
#define  TIM_BDTR_DTG_7                      ((uint16)0x0080)            /*!<Bit 7 */

#define  TIM_BDTR_LOCK                       ((uint16)0x0300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0                     ((uint16)0x0100)            /*!<Bit 0 */
#define  TIM_BDTR_LOCK_1                     ((uint16)0x0200)            /*!<Bit 1 */

#define  TIM_BDTR_OSSI                       ((uint16)0x0400)            /*!<Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR                       ((uint16)0x0800)            /*!<Off-State Selection for Run mode */
#define  TIM_BDTR_BKE                        ((uint16)0x1000)            /*!<Break enable */
#define  TIM_BDTR_BKP                        ((uint16)0x2000)            /*!<Break Polarity */
#define  TIM_BDTR_AOE                        ((uint16)0x4000)            /*!<Automatic Output enable */
#define  TIM_BDTR_MOE                        ((uint16)0x8000)            /*!<Main Output enable */

/*******************  Bit definition for TIM_DCR register  ********************/
#define  TIM_DCR_DBA                         ((uint16)0x001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define  TIM_DCR_DBA_0                       ((uint16)0x0001)            /*!<Bit 0 */
#define  TIM_DCR_DBA_1                       ((uint16)0x0002)            /*!<Bit 1 */
#define  TIM_DCR_DBA_2                       ((uint16)0x0004)            /*!<Bit 2 */
#define  TIM_DCR_DBA_3                       ((uint16)0x0008)            /*!<Bit 3 */
#define  TIM_DCR_DBA_4                       ((uint16)0x0010)            /*!<Bit 4 */

#define  TIM_DCR_DBL                         ((uint16)0x1F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define  TIM_DCR_DBL_0                       ((uint16)0x0100)            /*!<Bit 0 */
#define  TIM_DCR_DBL_1                       ((uint16)0x0200)            /*!<Bit 1 */
#define  TIM_DCR_DBL_2                       ((uint16)0x0400)            /*!<Bit 2 */
#define  TIM_DCR_DBL_3                       ((uint16)0x0800)            /*!<Bit 3 */
#define  TIM_DCR_DBL_4                       ((uint16)0x1000)            /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define  TIM_DMAR_DMAB                       ((uint16)0xFFFF)            /*!<DMA register for burst accesses */







/**
  * @}
  */

/**
  * @}
  */

/** @defgroup TIM_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup TIM_Exported_Functions
  * @{
  */

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16 TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16 TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16 TIM_DMABase, uint16 TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16 TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16 TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16 TIM_TIxExternalCLKSource,
                                uint16 TIM_ICPolarity, uint16 ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16 TIM_ExtTRGPrescaler, uint16 TIM_ExtTRGPolarity,
                             uint16 ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16 TIM_ExtTRGPrescaler,
                             uint16 TIM_ExtTRGPolarity, uint16 ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16 TIM_ExtTRGPrescaler, uint16 TIM_ExtTRGPolarity,
                   uint16 ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16 Prescaler, uint16 TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16 TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16 TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16 TIM_EncoderMode,
                                uint16 TIM_IC1Polarity, uint16 TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16 TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16 TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16 TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16 TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16 TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16 TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16 TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16 TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16 TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16 TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16 TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16 TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16 TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16 TIM_Channel, uint16 TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16 TIM_Channel, uint16 TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16 TIM_Channel, uint16 TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16 TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16 TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16 TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16 TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16 TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16 Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16 Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16 Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16 Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16 Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16 Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16 TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16 TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16 TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16 TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16 TIM_CKD);
uint16 TIM_GetCapture1(TIM_TypeDef* TIMx);
uint16 TIM_GetCapture2(TIM_TypeDef* TIMx);
uint16 TIM_GetCapture3(TIM_TypeDef* TIMx);
uint16 TIM_GetCapture4(TIM_TypeDef* TIMx);
uint16 TIM_GetCounter(TIM_TypeDef* TIMx);
uint16 TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16 TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16 TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16 TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16 TIM_IT);

#endif /*__STM32F10x_TIM_H */
