/*!
 * \file hw_timer_types.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_TIMER_TYPES_H_
#define _HW_TIMER_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_mgr.h"


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
HW_TIMER_MODE_NULL,
HW_TIMER_MODE_COUNTER,
HW_TIMER_MODE_INPUT_COMPARE,
HW_TIMER_MODE_OUTPUT_COMPARE,
} HW_TIMER_Mode;

PUBLIC typedef enum {
HW_TIMER_TYPE_BASIC,
HW_TIMER_TYPE_GENERAL,
HW_TIMER_TYPE_ADVANCED,
} HW_TIMER_Type;


PUBLIC typedef struct {
    HW_TIMER_Type Type;
    HW_TIMER_Mode Mode;
    void *config;
} HW_TIMER_ConfigInfo;



// generic Timer defines, depended on
// enabled hardware
PUBLIC typedef enum {
HW_TIMER_1,
HW_TIMER_2,
HW_TIMER_3,
HW_TIMER_4,
HW_TIMER_5,
HW_TIMER_6,
HW_TIMER_7,
HW_TIMER_8,
HW_TIMER_COUNT,
} HW_TIMER_BlockId;



/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_TIMER_TYPES_H_ */
