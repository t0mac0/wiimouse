/*!
 * \file os_evnt_mgr.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_EVNT_MGR_H_
#define _OS_EVNT_MGR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "os.h"
#include "os_evnt_mgr_result.h"
#include "os_evnt_mgr_types.h"
#include "os_evnt_mgr_events.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define OS_EVNT_MGR_EVENT_LIST_INIT_SIZE 5

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PROTECTED OsModuleInitPrototype EVNT_MGR_Init;

PUBLIC Result OS_EVNT_MGR_RegisterEventListener( OS_EVNT_MGR_EvntId EventId, pOS_EVNT_MGR_EventListener Listener);

PUBLIC Result OS_EVNT_MGR_GenerateEvent( OS_EVNT_MGR_EvntId EventId, void* Parameters );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* OS_EVNT_MGR_H_ */
