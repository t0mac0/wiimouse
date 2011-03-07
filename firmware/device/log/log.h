/*!
 * \file log.h
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

#ifndef _LOG_H_
#define _LOG_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "log_types.h"
#include "printf/lib_printf.h"



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
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*!****************************************************************************
 * /brief Log Initialization
 *
 * /param
 * /return
 ******************************************************************************/

#ifdef DEV_MOD_LOG

PUBLIC ModuleInitPrototype LOG_Init;

PUBLIC Result LOG_RegisterModule(uint32 ModId, uint32 SubModuleId, bool Enabled);

PUBLIC Result LOG_RegisterOutputDest(LOG_DestinationId DestId, void (*Dest)(void *, char), bool Enabled);

PUBLIC Result LOG(LOG_DestinationId DestId, uint32 ModId, uint32 SubModId, char* Format, ...);

PUBLIC Result LOG_CatchError(Result result);

PUBLIC Result LOG_Printf( char* Format, ...);

PUBLIC Result LOG_SetModuleEnabled(uint32 ModId, uint32 SubModuleId, bool Enabled);

PUBLIC Result LOG_SetOutputDestEnabled(LOG_DestinationId DestId, bool Enabled);

#else

#define LOG_Init() 0
#define LOG_RegisterModule(x,y,z)
#define LOG_RegisterOutputDest(x,y,z) 0
#define LOG(w,x,y,z,...)
#define LOG_CatchError(x)
#define LOG_Printf(x,...)
#define LOG_SetModuleEnabled(x,y,z)
#define LOG_SetOutputDestEnabled(x,y)

#endif


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* LOG_H_ */
