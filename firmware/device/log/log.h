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
PUBLIC ModuleInitPrototype LOG_Init;

PUBLIC Result LOG_RegisterModule(uint32 ModId, uint32 SubModuleId, bool Enabled);

PUBLIC Result LOG_RegisterOutputDest(LOG_DestinationId DestId, void (*Dest)(void *, char), bool Enabled);

#ifdef DEV_MOD_LOG
PUBLIC Result LOG(LOG_DestinationId DestId, uint32 ModId, uint32 SubModId, char* Format, ...);
#else
#define LOG(w,x,y,z,...)
#endif

PUBLIC Result LOG_CatchError(Result result);

PUBLIC Result LOG_Printf( char* Format, ...);

PUBLIC Result LOG_SetModuleEnabled(uint32 ModId, uint32 SubModuleId, bool Enabled);

PUBLIC Result LOG_SetOutputDestEnabled(LOG_DestinationId DestId, bool Enabled);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* LOG_H_ */
