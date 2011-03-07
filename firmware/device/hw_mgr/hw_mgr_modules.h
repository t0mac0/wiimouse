/*!
 * \file hw_mgr_modules.h
 *
 * \brief 
 *
 *
 * \date Mar 4, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_MGR_MODULES_H_
#define _HW_MGR_MODULES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "hw_mgr.h"
#include "hw_mgr_conf.h"
#include "hw_mgr_types.h"

//--------- System Critical Modules -------------------------------//
#ifdef HW_MGR_MOD_SYSCLK
#include "sysclk/hw_sysclk.h"
#endif
#ifdef HW_MGR_MOD_SYSINIT
#include "sysinit/hw_sysinit.h"
#endif
#ifdef HW_MGR_MOD_INT
#include "int/hw_int.h"
#endif
#ifdef HW_MGR_MOD_USART
#include "usart/hw_usart.h"
#endif
#ifdef HW_MGR_MOD_RCC
#include "rcc/hw_rcc.h"
#endif
#ifdef HW_MGR_MOD_GPIO
#include "gpio/hw_gpio.h"
#endif

//--------- Non-System Critical Modules ---------------------------//
// included in the .c file


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
#ifdef HW_MGR_MOD_USART
    HW_MGR_USART,
#endif
    HW_MGR_MODULE_COUNT,   // this must come second to last
    HW_MGR_MAX_MODULE = 1024 // this must come last
} HW_MGR_ModuleId;


PROTECTED typedef struct {
    HW_MGR_ModuleId Id;
    pHwModulePowerUpPrototype PowerUp;
    pHwModulePowerDownPrototype PowerDown;
    pHwModuleInitPrototype Init;
    pGetResutCodeStrPrototype GetResutCodeStr;
    bool IsInitialized;
    bool IsPoweredUp;
} HwMgrModules;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
PROTECTED extern HwMgrModules hwMgrModules[HW_MGR_MODULE_COUNT];


#endif /* HW_MGR_MODULES_H_ */
