/*!
 * \file device_types.h
 *
 * \brief 
 *
 *
 * \date Mar 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _DEVICE_TYPES_H_
#define _DEVICE_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system_types.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*!
 * \brief Device Result Type
 *
 * This is the data type for a result throughout the device. It has the
 * following format:

 * byte:  3                | 2                   | 1                   | 0
 * ---------------------------------------------------------------------------------------
 * bit :  31 .. 26   25 24 | 23 .. 20   19 .. 16 | 15 .. 10     9 8    |  7  ..   0
 * ---------------------------------------------------------------------------------------
 * desc:  Task Id  |     Module Id    |     Sub-Module Id   | Severity |  (Sub)Module specific code
 *
 * where:
 *
 *  Task Id - the Id of the task the result originated
 *  Module Id - the Id of module the result originated
 *  Severity - the severity of the code:
 *             00  - Information
 *             01  - Debug
 *             10  - Warning
 *             11  - Error
 *  Module specific code - An code specific to the originating module (code 0 is SUCCESS)
 *
 *  Note that this result type allows for:
 *    64 tasks
 *    64 modules
 *    1024 sub-modules
 *    4 severity types
 *    256 module specific codes
 *
 */
typedef uint32 Result;


/*!
 * \brief Severity of a result type
 */
typedef enum {
    RESULT_SEVERITY_SUCCESS = 0x0,
    RESULT_SEVERITY_INFO    = 0x1,
    RESULT_SEVERITY_WARN    = 0x2,
    RESULT_SEVERITY_ERROR   = 0x3
} ResultSeverity;


typedef Result (ModulePowerUpPrototype)( void );
typedef Result (*pModulePowerUpPrototype)( void );

typedef Result (ModulePowerDownPrototype)( void );
typedef Result (*pModulePowerDownPrototype)( void );

typedef Result (ModuleInitPrototype)( void );
typedef Result (*pModuleInitPrototype)( void );

typedef CString (GetResutCodeStrPrototype)(Result);
typedef CString (*pGetResutCodeStrPrototype)(Result);

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* DEVICE_TYPES_H_ */
