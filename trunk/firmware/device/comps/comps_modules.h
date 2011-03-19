/*!
 * \file comps_modules.h
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPS_MODULES_H_
#define _COMPS_MODULES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "comps_conf.h"


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
#ifdef COMPS_MOD_COMPOSITE_USB
    COMPS_COMPOSITE_USB,
#endif
    COMPS_MODULE_COUNT   // this must come second to last
} COMPS_ModuleId;


PROTECTED typedef struct {
    COMPS_ModuleId Id;
    pModulePowerUpPrototype PowerUp;
    pModulePowerDownPrototype PowerDown;
    pModuleInitPrototype Init;
    pGetResutCodeStrPrototype GetResutCodeStr;
    bool IsInitialized;
    bool IsPoweredUp;
} CompsModules;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern CompsModules compsModules[COMPS_MODULE_COUNT];


#endif /* COMPS_MODULES_H_ */
