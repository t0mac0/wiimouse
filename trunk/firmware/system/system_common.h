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

#define NULL 0


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





#endif /* SYSTEM_COMMON_H_ */
