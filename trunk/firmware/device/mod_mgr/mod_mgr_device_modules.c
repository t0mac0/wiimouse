/*!
 * \file mod_mgr_device_modules.c
 *
 * \brief 
 *
 *
 * \date Mar 4, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "mod_mgr_device_modules.h"

#ifdef DEV_MOD_HW_MGR
#include "hw_mgr.h"
#endif

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/


#define ADD_MODULE(_name)                                \
{                                                        \
    (MOD_MGR_ModuleId)MOD_MGR_##_name,                   \
    (pModuleInitPrototype)&_name##_Init,                 \
    (pGetResutCodeStrPrototype)&_name##_GetResultCodeStr,\
    FALSE                                                \
}


/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
ModMgrModules modMgrModules[MOD_MGR_MODULE_COUNT] = {
#ifdef DEV_MOD_HW_MGR
        ADD_MODULE(HW_MGR),                                     // Hardware Module
#endif
};



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

