/*!
 * \file hw_gpio_stm32f10x.c
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
#include <platform_lib.h>
#include "gpio/hw_gpio.h"

#if (SYSTEM_PLATFORM == STM32F10X_MD )
#ifdef HW_MOD_GPIO
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
PUBLIC uint32 HW_GPIO_PortBase[HW_GPIO_COUNT] =
{
#ifdef _GPIOA
        GPIOA_BASE,
#else
        NULL
#endif
#ifdef _GPIOB
        GPIOB_BASE,
#else
        NULL
#endif
#ifdef _GPIOC
        GPIOC_BASE,
#else
        NULL
#endif
#ifdef _GPIOD
        GPIOD_BASE,
#else
        NULL
#endif
#ifdef _GPIOE
        GPIOE_BASE,
#else
        NULL
#endif
};


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
#endif
