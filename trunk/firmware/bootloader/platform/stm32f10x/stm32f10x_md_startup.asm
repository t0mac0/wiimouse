/**
 ******************************************************************************
 * @file      startup_stm32f10x_md.s
 * @author    MCD Application Team
 * @version   V3.4.0
 * @date      10/15/2010
 * @brief     STM32F10x Medium Density Devices vector table for RIDE7 toolchain.
 *            This module performs:
 *                - Set the initial SP
 *                - Set the initial PC == Reset_Handler,
 *                - Set the vector table entries with the exceptions ISR address
 *                - Configure the clock system
 *                - Branches to main in the C library (which eventually
 *                  calls main()).
 *            After Reset the Cortex-M3 processor is in Thread mode,
 *            priority is Privileged, and the Stack is set to Main.
 *******************************************************************************
 * @copy
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
 */
#ifdef STM32F10X_MD

  .syntax unified
    .cpu cortex-m3
    .fpu softvfp
    .thumb

.macro DEFAULT_ISR_HANDLER name=
  .weak \name
     .thumb_set \name, Default_Handler
.endm


.global g_pfnVectors
.global Default_Handler



/* start address for the initialization values of the .data section.
defined in linker script */
.word   _sidata
/* start address for the .data section. defined in linker script */
.word   _sdata
/* end address for the .data section. defined in linker script */
.word   _edata
/* start address for the .bss section. defined in linker script */
.word   _sbss
/* end address for the .bss section. defined in linker script */
.word   _ebss

.equ  BootRAM, 0xF108F85F
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section    .text.Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b LoopCopyDataInit

CopyDataInit:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]
    adds    r1, r1, #4

LoopCopyDataInit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds    r2, r0, r1
    cmp r2, r3
    bcc CopyDataInit
    ldr r2, =_sbss
    b   LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
    movs    r3, #0
    str r3, [r2], #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss
/* Call the clock system intitialization function.*/
/*  bl  SystemInit */
/* Call the application's entry point.*/
    bl  main
    bx  lr
.size   Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt. This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section    .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b   Infinite_Loop
    .size   Default_Handler, .-Default_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
    .section    .isr_vector,"a",%progbits
    .type   g_pfnVectors, %object
    .size   g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
    .word   _estack
    .word   Reset_Handler
  .word NMIException
  .word HardFaultException
  .word MemManageException
  .word BusFaultException
  .word UsageFaultException
  .word 0 // Reserved
  .word 0 // Reserved
  .word 0 // Reserved
  .word 0 // Reserved
  .word SVCHandler
  .word DebugMonitor
  .word 0 // Reserved
  .word PendSVHandler
  .word SysTickHandler
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word TAMPER_IRQHandler
  .word RTC_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  .word DMAChannel1_IRQHandler
  .word DMAChannel2_IRQHandler
  .word DMAChannel3_IRQHandler
  .word DMAChannel4_IRQHandler
  .word DMAChannel5_IRQHandler
  .word DMAChannel6_IRQHandler
  .word DMAChannel7_IRQHandler
  .word ADC_IRQHandler
  .word USB_HP_CAN_TX_IRQHandler
  .word USB_LP_CAN_RX0_IRQHandler
  .word CAN_RX1_IRQHandler
  .word CAN_SCE_IRQHandler
  .word EXTI9_5_IRQHandler
  .word TIM1_BRK_IRQHandler
  .word TIM1_UP_IRQHandler
  .word TIM1_TRG_COM_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM4_IRQHandler
  .word I2C1_EV_IRQHandler
  .word I2C1_ER_IRQHandler
  .word I2C2_EV_IRQHandler
  .word I2C2_ER_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_IRQHandler
  .word EXTI15_10_IRQHandler
  .word RTCAlarm_IRQHandler
  .word USBWakeUp_IRQHandler
  .word TIM8_BRK_IRQHandler
  .word TIM8_UP_IRQHandler
  .word TIM8_TRG_COM_IRQHandler
  .word TIM8_CC_IRQHandler
  .word ADC3_IRQHandler
  .word FSMC_IRQHandler
  .word SDIO_IRQHandler
  .word TIM5_IRQHandler
  .word SPI3_IRQHandler
  .word UART4_IRQHandler
  .word UART5_IRQHandler
  .word TIM6_IRQHandler
  .word TIM7_IRQHandler
  .word DMA2_Channel1_IRQHandler
  .word DMA2_Channel2_IRQHandler
  .word DMA2_Channel3_IRQHandler
  .word DMA2_Channel4_5_IRQHandler
/*                            STM32F10x Medium Density devices. */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/
DEFAULT_ISR_HANDLER NMIException
DEFAULT_ISR_HANDLER HardFaultException
DEFAULT_ISR_HANDLER MemManageException
DEFAULT_ISR_HANDLER BusFaultException
DEFAULT_ISR_HANDLER UsageFaultException
DEFAULT_ISR_HANDLER SVCHandler
DEFAULT_ISR_HANDLER DebugMonitor
DEFAULT_ISR_HANDLER PendSVHandler
DEFAULT_ISR_HANDLER SysTickHandler
DEFAULT_ISR_HANDLER WWDG_IRQHandler
DEFAULT_ISR_HANDLER PVD_IRQHandler
DEFAULT_ISR_HANDLER TAMPER_IRQHandler
DEFAULT_ISR_HANDLER RTC_IRQHandler
DEFAULT_ISR_HANDLER FLASH_IRQHandler
DEFAULT_ISR_HANDLER RCC_IRQHandler
DEFAULT_ISR_HANDLER EXTI0_IRQHandler
DEFAULT_ISR_HANDLER EXTI1_IRQHandler
DEFAULT_ISR_HANDLER EXTI2_IRQHandler
DEFAULT_ISR_HANDLER EXTI3_IRQHandler
DEFAULT_ISR_HANDLER EXTI4_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel1_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel2_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel3_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel4_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel5_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel6_IRQHandler
DEFAULT_ISR_HANDLER DMAChannel7_IRQHandler
DEFAULT_ISR_HANDLER ADC_IRQHandler
DEFAULT_ISR_HANDLER USB_HP_CAN_TX_IRQHandler
DEFAULT_ISR_HANDLER USB_LP_CAN_RX0_IRQHandler
DEFAULT_ISR_HANDLER CAN_RX1_IRQHandler
DEFAULT_ISR_HANDLER CAN_SCE_IRQHandler
DEFAULT_ISR_HANDLER EXTI9_5_IRQHandler
DEFAULT_ISR_HANDLER TIM1_BRK_IRQHandler
DEFAULT_ISR_HANDLER TIM1_UP_IRQHandler
DEFAULT_ISR_HANDLER TIM1_TRG_COM_IRQHandler
DEFAULT_ISR_HANDLER TIM1_CC_IRQHandler
DEFAULT_ISR_HANDLER TIM2_IRQHandler
DEFAULT_ISR_HANDLER TIM3_IRQHandler
DEFAULT_ISR_HANDLER TIM4_IRQHandler
DEFAULT_ISR_HANDLER I2C1_EV_IRQHandler
DEFAULT_ISR_HANDLER I2C1_ER_IRQHandler
DEFAULT_ISR_HANDLER I2C2_EV_IRQHandler
DEFAULT_ISR_HANDLER I2C2_ER_IRQHandler
DEFAULT_ISR_HANDLER SPI1_IRQHandler
DEFAULT_ISR_HANDLER SPI2_IRQHandler
DEFAULT_ISR_HANDLER USART1_IRQHandler
DEFAULT_ISR_HANDLER USART2_IRQHandler
DEFAULT_ISR_HANDLER USART3_IRQHandler
DEFAULT_ISR_HANDLER EXTI15_10_IRQHandler
DEFAULT_ISR_HANDLER RTCAlarm_IRQHandler
DEFAULT_ISR_HANDLER USBWakeUp_IRQHandler
DEFAULT_ISR_HANDLER TIM8_BRK_IRQHandler
DEFAULT_ISR_HANDLER TIM8_UP_IRQHandler
DEFAULT_ISR_HANDLER TIM8_TRG_COM_IRQHandler
DEFAULT_ISR_HANDLER TIM8_CC_IRQHandler
DEFAULT_ISR_HANDLER ADC3_IRQHandler
DEFAULT_ISR_HANDLER FSMC_IRQHandler
DEFAULT_ISR_HANDLER SDIO_IRQHandler
DEFAULT_ISR_HANDLER TIM5_IRQHandler
DEFAULT_ISR_HANDLER SPI3_IRQHandler
DEFAULT_ISR_HANDLER UART4_IRQHandler
DEFAULT_ISR_HANDLER UART5_IRQHandler
DEFAULT_ISR_HANDLER TIM6_IRQHandler
DEFAULT_ISR_HANDLER TIM7_IRQHandler
DEFAULT_ISR_HANDLER DMA2_Channel1_IRQHandler
DEFAULT_ISR_HANDLER DMA2_Channel2_IRQHandler
DEFAULT_ISR_HANDLER DMA2_Channel3_IRQHandler
DEFAULT_ISR_HANDLER DMA2_Channel4_5_IRQHandler

#endif

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
