/*!
 * \file stm32f10x.h
 *
 * \brief 
 *
 *
 * \date Mar 1, 2011
 * \author Dan Riedler
 *
 */

#ifndef _STM32F10X_H_
#define _STM32F10X_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "stm32f10x_types.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
/*******************************************************************************
 * Macro Name     : ASSERT_PARAM
 * Description    : The ASSERT_PARAM macro is used for function's parameters check.
 *                  It is used only if the library is compiled in DEBUG mode.
 * Input          : - expr: If expr is false, it calls ASSERT_failed function
 *                    which reports the name of the source file and the source
 *                    line number of the call that failed.
 *                    If expr is true, it returns no value.
 * Return         : None
 *******************************************************************************/
#ifndef ASSERT
#define ASSERT(expr)( (expr) ? (void)0 : ASSERT_failed((uint8 *)__FILE__, __LINE__) )
#endif
#ifndef ASSERT_PARAM
#define ASSERT_PARAM(expr) ((expr) ? (void)0 : ASSERT_failed((uint8 *)__FILE__, __LINE__))
#endif

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
void ASSERT_failed(uint8* file, uint32 line);


#endif /* STM32F10X_H_ */
