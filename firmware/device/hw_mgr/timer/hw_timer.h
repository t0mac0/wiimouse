/*!
 * \file hw_timer.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "hw_mgr.h"
#include "hw_timer_result.h"
#include "hw_mgr_types.h"
#include "hw_timer_types.h"

#include "counter/hw_timer_counter.h"
#include "input_compare/hw_timer_ic.h"
#include "output_compare/hw_timer_oc.h"



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
PUBLIC HwModuleInitPrototype HW_TIMER_Init;

PUBLIC HwModulePowerUpPrototype HW_TIMER_PowerUp;

PUBLIC HwModulePowerDownPrototype HW_TIMER_PowerDown;

PUBLIC Result HW_TIMER_Start(HW_TIMER_BlockId Id);

PUBLIC Result HW_TIMER_Stop(HW_TIMER_BlockId Id);

PUBLIC Result HW_TIMER_Reset(HW_TIMER_BlockId Id);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_TIMER_H_ */
