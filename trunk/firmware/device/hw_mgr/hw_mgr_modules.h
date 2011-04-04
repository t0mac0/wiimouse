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
#include "sysclk/hw_sysclk.h"
#include "sysinit/hw_sysinit.h"
#include "int/hw_int.h"
#include "usart/hw_usart.h"
#include "rcc/hw_rcc.h"
#include "gpio/hw_gpio.h"



//--------- Non-System Critical Modules ---------------------------//
// included in the hw_mgr_modules.c file


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
    HW_MGR_USART,           // usart included in count, but always enabled since sys critical
#ifdef HW_MGR_MOD_USB
    HW_MGR_USB,
#endif
#ifdef HW_MGR_MOD_TIMER
    HW_MGR_TIMER,
#endif
#ifdef HW_MGR_MOD_I2C
    HW_MGR_I2C,
#endif
#ifdef HW_MGR_MOD_FLASH
    HW_MGR_FLASH,
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
