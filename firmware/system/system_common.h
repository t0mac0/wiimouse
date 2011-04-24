/*!
 * \file system_common.h
 *
 * \brief 
 *
 *
 * \date Feb 27, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SYSTEM_COMMON_H_
#define _SYSTEM_COMMON_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system_types.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

// specifies the parameter as input
#define IN
// specifies the parameter as output
#define OUT

// specifies the variable/function a Publicly accessible
#define PUBLIC
// specifies the variable/function a accessible only to current module and child modules
#define PROTECTED
// specifies the variable/function a accessible only to current module
#define PRIVATE static

#ifndef NULL
#define NULL 0
#endif


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

// ceiling function
#define CELING(x, n) ( (x + n - 1) / n )

// alignment functions, aligns x to a multiple of n
#define ALIGN(x, n) ( n * ((x + n - 1) / n) )

// finds the offset in bytes of the data member in a structure
#define OFFSETOF(s, m) ( (uint32)&(((s *)0)->m) )


// returns the maximum of two values
#define MAX(x, y) (  x > y ? x : y )

// returns the minimum of two values
#define MIN(x, y) ( x < y ? x : y )


#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define UNUSED(x)(x= x);


PUBLIC bool ZeroMemory(void *Mem, uint32 SizeBytes);

PUBLIC bool SetMemory(void *Mem, uint32 Value, uint32 SizeBytes);

PUBLIC bool CopyMemory(void *Dst, void *Src, uint32 SizeBytes);

PUBLIC pVoid AllocMemory( uint32 SizeBytes );

PUBLIC void FreeMemory( pVoid MemoryPointer );



#endif /* SYSTEM_COMMON_H_ */
