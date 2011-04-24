/*!
 * \file hw_conf.h
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_CONF_H_
#define _HW_CONF_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

#define DEFAULT_USART HW_USART_2

// Default USART port/pin
#define DEFAULT_USART_PORT    HW_GPIOA
#define DEFAULT_USART_TX_PIN  GPIOA_Pin_2
#define DEFAULT_USART_RX_PIN  GPIOA_Pin_3


#define USB_DISCONNECT_PORT                 GPIOC
#define USB_DISCONNECT_PIN                  GPIO_Pin_11
#define USB_DISCONNECT_RCC_APB2Periph       RCC_APB2Periph_GPIOC

#define USB_ACTIVE_LED_PORT                 GPIOC
#define USB_ACTIVE_LED_PIN                  GPIO_Pin_12
#define USB_ACTIVE_LED_RCC_APB2Periph       RCC_APB2Periph_GPIOC

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_CONF_H_ */
