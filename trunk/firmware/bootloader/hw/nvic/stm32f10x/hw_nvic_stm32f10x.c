/*!
 * \file hw_nvic_stm32f10x.c
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <platform_lib.h>
#include "nvic/hw_nvic.h"


#ifdef STM32F10X_MD

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


PUBLIC inline void HW_NVIC_Init( void )
{
    // flash vector table currently only supported
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, BOOTLOADER_VECTOR_TABLE_OFFSET);

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
