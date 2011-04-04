/*!
 * \file device_common.h
 *
 * \brief 
 *
 *
 * \date Mar 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _DEVICE_COMMON_H_
#define _DEVICE_COMMON_H_


/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device_types.h"



/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define RESULT_TASK_ID_MASK           0xFC000000
#define RESULT_MODULE_ID_MASK         0x03F00000
#define RESULT_SUB_MODULE_ID_MASK     0x000FFC00
#define RESULT_SEVERITY_MASK          0x00000300
#define RESULT_CODE_MASK              0x000000FF

#define NULL_MOD              (0xFFFFFFFF)


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

#define GET_CURRENT_TASK_ID() (0)
#define RESULT(task_id, module_id, sub_module_id, code)( ((uint32)task_id<<26) | ((uint32)module_id<<20) | ((uint32)sub_module_id<<10)| ((uint32)code<<0) )
#define RESULT_TASK_ID(result)( (result&RESULT_TASK_ID_MASK) >> 26 )
#define RESULT_MODULE_ID(result)( (result&RESULT_MODULE_ID_MASK) >> 20 )
#define RESULT_SUB_MODULE_ID(result)( (result&RESULT_SUB_MODULE_ID_MASK) >> 10 )
#define RESULT_SEVERITY(result)( (result&RESULT_SEVERITY_MASK) >> 8 )
#define RESULT_CODE(result)( (result&RESULT_CODE_MASK) >> 0 )

#define RESULT_INFO(code)( ((uint32)RESULT_SEVERITY_INFO << 8) | code )
#define RESULT_WARN(code)( ((uint32)RESULT_SEVERITY_WARN << 8) | code )
#define RESULT_ERROR(code)( ((uint32)RESULT_SEVERITY_ERROR << 8) | code )

#define RESULT_IS_SUCCESS(result, func)( RESULT_SEVERITY((result=func)) == RESULT_SEVERITY_SUCCESS )
#define RESULT_IS_ERROR(result, func)( RESULT_SEVERITY((result=func)) == RESULT_SEVERITY_ERROR )

#define IS_RESULT_SUCCESS(result)( RESULT_SEVERITY(result) == RESULT_SEVERITY_SUCCESS )

#define UNUSED(x)(x= x);
/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* DEVICE_COMMON_H_ */
