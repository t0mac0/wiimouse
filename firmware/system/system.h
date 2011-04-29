/*!
 * \file system.h
 *
 * \brief 
 *
 *
 * \date Feb 27, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system_conf.h"
#include "system_common.h"
#include "system_types.h"
#include "system_privileged_calls.h"



/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#ifdef ASSERT
#undef ASSERT
#endif
#ifdef ASSERT_PARAM
#undef ASSERT_PARAM
#endif

#ifdef  DEBUG
/*!******************************************************************************
 * \brief     : ASSERT_PARAM
 * Description    : The ASSERT_PARAM macro is used for function's parameters check.
 *                  It is used only if the library is compiled in DEBUG mode.
 * \param        : - expr: If expr is false, it calls ASSERT_failed function
 *                    which reports the name of the source file and the source
 *                    line number of the call that failed.
 *                    If expr is true, it returns no value.
 * \return       : None
 *******************************************************************************/
#define ASSERT(expr) ((expr) ? (void)0 : ASSERT_failed((uint8 *)__FILE__, __LINE__))
#define ASSERT_PARAM(expr) ((expr) ? (void)0 : ASSERT_failed((uint8 *)__FILE__, __LINE__))

#else

#define ASSERT(expr)
#define ASSERT_PARAM(expr) ((void)0)

#endif /* DEBUG */

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PUBLIC void ASSERT_failed(uint8* file, uint32 line);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* SYSTEM_H_ */
