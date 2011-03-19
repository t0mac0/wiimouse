/*!
 * \file system_types.h
 *
 * \brief 
 *
 *
 * \date Feb 27, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SYSTEM_TYPES_H_
#define _SYSTEM_TYPES_H_


#include <platform_types.h>


/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

// The types will be used if not defined in the platform types header
// Note that at least all the types below should be declared in the platform types header

#ifndef __TYPES_DECLARACTION
#define __TYPES_DECLARACTION

typedef signed long  int32;
typedef signed short int16;
typedef signed char  int8;

typedef volatile signed long  vint32;
typedef volatile signed short vint16;
typedef volatile signed char  vint8;

typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

typedef unsigned long  const ucint32;  /* Read Only */
typedef unsigned short const ucint16;  /* Read Only */
typedef unsigned char  const ucint8;   /* Read Only */

typedef volatile unsigned long  vuint32;
typedef volatile unsigned short vuint16;
typedef volatile unsigned char  vuint8;

typedef volatile unsigned long  const vucint32;  /* Read Only */
typedef volatile unsigned short const vucint16;  /* Read Only */
typedef volatile unsigned char  const vucint8;   /* Read Only */

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) ((STATE == DISABLE) || (STATE == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define UINT8_MAX    ((uint8)255)
#define INT8_MAX     ((int8)127)
#define INT8_MIN     ((int8)-128)
#define UINT16_MAX   ((uint16)65535u)
#define INT16_MAX    ((int16)32767)
#define INT16_MIN    ((int16)-32768)
#define UINT32_MAX   ((uint32)4294967295uL)
#define INT32_MAX    ((int32)2147483647)
#define INT32_MIN    ((int32)2147483648uL)


#endif

typedef volatile bool vbool;
typedef const char* CString;
typedef void* pVoid;

#endif /* SYSTEM_TYPES_H_ */
