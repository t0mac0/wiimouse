/*!
 * \file os_modules.h
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

#ifndef _OS_MODULES_H_
#define _OS_MODULES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "os.h"
#include "os_conf.h"
#include "os_types.h"


#include "task_mgr/os_task_mgr.h"
#include "sem_mgr/os_sem_mgr.h"
#include "mem_mgr/os_mem_mgr.h"
#include "evnt_mgr/os_evnt_mgr.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef enum {
#ifdef OS_MOD_TASK_MGR
OS_TASK_MGR,
#endif
#ifdef OS_MOD_MEM_MGR
OS_MEM_MGR,
#endif
#ifdef OS_MOD_SEM_MGR
OS_SEM_MGR,
#endif
#ifdef OS_MOD_EVNT_MGR
OS_EVNT_MGR,
#endif
    OS_MODULE_COUNT,   // this must come second to last
    OS_MAX_MODULE = 1024 // this must come last
} OS_ModuleId;


PROTECTED typedef struct {
    OS_ModuleId Id;
    pOsModuleInitPrototype Init;
    pGetResutCodeStrPrototype GetResutCodeStr;
    bool IsInitialized;
} OsModules;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern OsModules osModules[OS_MODULE_COUNT];


#endif /* OS_MODULES_H_ */
