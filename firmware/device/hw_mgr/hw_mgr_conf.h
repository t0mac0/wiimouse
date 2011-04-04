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
#include "device_conf.h"
#include "hw_mgr_gpio_conf.h"

#ifdef DEV_MOD_HW_MGR


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
#define HW_MGR_MOD_USB
#define HW_MGR_MOD_TIMER
#define HW_MGR_MOD_I2C
#define HW_MGR_MOD_FLASH




#define DEFAULT_USART       HW_USART_2


#define NUNCHUCK_READ_TIMER HW_TIMER_2
#define NUNCHUCK_I2C        HW_I2C_2

#endif

#endif /* HW_CONFIG_H_ */
