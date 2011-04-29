/*!
 * \file hw_sysclk_stm32f10x.c
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
#include "sysclk/hw_sysclk.h"

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
PUBLIC inline void HW_SYSCLK_SetClock( uint32 Freq )
{
    SysClk_SetClock(Freq);
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

#endif
