/*!
 * \file hw_config.h
 *
 * \brief 
 *
 *
 * \date Mar 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_CONF_H_
#define _HW_CONF_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_mgr_gpio_conf.h"
#include "usart/hw_usart.h"



/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*!
 * \brief This defines which hardware modules to use
 *
 */
//-------- System Critical Modules  ------------//
#define HW_MGR_MOD_SYSCLK
#define HW_MGR_MOD_SYSINIT
#define HW_MGR_MOD_INT
#define HW_MGR_MOD_USART
#define HW_MGR_MOD_RCC
#define HW_MGR_MOD_GPIO

//-------- Non-System Critical Modules  -------//



#define DEFAULT_USART HW_USART_2

#endif /* HW_CONFIG_H_ */
