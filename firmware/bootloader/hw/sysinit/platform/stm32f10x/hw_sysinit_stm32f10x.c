/*!
 * \file hw_sysinit_stm32f10x.c
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
#include "sysinit/hw_sysinit.h"

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
PUBLIC inline void HW_SYSINIT_Init( void )
{
    SysInit_Init();
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif