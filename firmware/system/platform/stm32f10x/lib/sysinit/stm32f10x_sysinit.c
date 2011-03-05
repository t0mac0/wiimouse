/*!
 * \file stm32f10x_sysinit.c
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "stm32f10x_sysinit.h"

#ifdef _SysInit

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*****************************************************************************/
void SysInit_Init (void)
{
    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSION bit */
    RCC->CR |= (uint32)0x00000001;

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
    RCC->CFGR &= (uint32)0xF8FF0000;
#else
    RCC->CFGR &= (uint32)0xF0FF0000;
#endif /* STM32F10X_CL */

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32)0xFF80FFFF;

#ifdef STM32F10X_CL
    /* Reset PLL2ON and PLL3ON bits */
    RCC->CR &= (uint32)0xEBFFFFFF;

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x00FF0000;

    /* Reset CFGR2 register */
    RCC->CFGR2 = 0x00000000;
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;

    /* Reset CFGR2 register */
    RCC->CFGR2 = 0x00000000;
#else
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
#endif /* STM32F10X_CL */

#if defined (STM32F10X_HD) || (defined STM32F10X_XL) || (defined STM32F10X_HD_VL)
#ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM */
#endif


#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->ExceptionTableOffset = 0; /* Vector Table Relocation in Internal FLASH. */
#endif
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
