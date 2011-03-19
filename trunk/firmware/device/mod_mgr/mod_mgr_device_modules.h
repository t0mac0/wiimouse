/*!
 * \file mod_mgr_devices.h
 *
 * \brief 
 *
 *
 * \date Mar 4, 2011
 * \author Dan Riedler
 *
 */

#ifndef _MOD_MGR_DEVICES_H_
#define _MOD_MGR_DEVICES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "mod_mgr.h"




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
 * \brief This creates a unique Id for every module used in the device.
 * The devices are in no particular order but must not exceed the maximum
 * device count.
 */
PUBLIC typedef enum {
#ifdef DEV_MOD_HW_MGR
    MOD_MGR_HW_MGR,
#endif
#ifdef DEV_MOD_OS
    MOD_MGR_OS,
#endif
#ifdef DEV_MOD_COMPS
    MOD_MGR_COMPS,
#endif
    MOD_MGR_MODULE_COUNT,

    // MODULES NOT INCLUDED IN COUNT


    MOD_MGR_MOD_MGR,
#ifdef DEV_MOD_LOG
    MOD_MGR_LOG,
#endif

    MOD_MGR_MAX_MODULE = 64 // this must come last
} MOD_MGR_ModuleId;


typedef struct {
    MOD_MGR_ModuleId Id;
    pModuleInitPrototype Init;
    pGetResutCodeStrPrototype GetResutCodeStr;
    bool Initialized;
} ModMgrModules;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern ModMgrModules modMgrModules[MOD_MGR_MODULE_COUNT];



#endif /* MOD_MGR_DEVICES_H_ */
