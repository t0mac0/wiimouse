/*!
 * \file hw_mgr_gpio_conf.h
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_MGR_GPIO_CONF_H_
#define _HW_MGR_GPIO_CONF_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

//--------- USART Pin Configurations ----------------------------//

// Default USART port/pin
#define DEFAULT_USART_PORT    HW_GPIOA
#define DEFAULT_USART_TX_PIN  GPIOA_Pin_2
#define DEFAULT_USART_RX_PIN  GPIOA_Pin_3
/*!
 * \brief USART Pin Configuration
 */

//--------- USB Pin Configuration ----------------------------//
#define USB_DISCONNECT_PORT                 GPIOC
#define USB_DISCONNECT_PIN                  GPIO_Pin_11
#define USB_DISCONNECT_RCC_APB2Periph       RCC_APB2Periph_GPIOC

#define USB_ACTIVE_LED_PORT                 GPIOC
#define USB_ACTIVE_LED_PIN                  GPIO_Pin_12
#define USB_ACTIVE_LED_RCC_APB2Periph       RCC_APB2Periph_GPIOC


//--------- Nunchunk I2C Pin Configuration --------------------//
#define NUNCHUCK_I2C_PORT                   GPIOB
#define NUNCHUCK_I2C_SCL_PIN                GPIO_Pin_10
#define NUNCHUCK_I2C_SDA_PIN                GPIO_Pin_11


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/



#endif /* HW_MGR_GPIO_CONF_H_ */
