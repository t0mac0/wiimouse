/*!
 * \file composite_usb_isr_conf_stm32f10x.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPOSITE_USB_ISR_CONF_STM32F10X_H_
#define _COMPOSITE_USB_ISR_CONF_STM32F10X_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_SOFM  | CNTR_RESETM | CNTR_WKUPM | CNTR_SUSPM | CNTR_ERRM | CNTR_ESOFM)


/*#define CTR_CALLBACK*/
/*#define DOVR_CALLBACK*/
/*#define ERR_CALLBACK*/
/*#define WKUP_CALLBACK*/
/*#define SUSP_CALLBACK*/
/*#define RESET_CALLBACK*/
#define SOF_CALLBACK
/*#define ESOF_CALLBACK*/

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


#endif /* COMPOSITE_USB_ISR_CONF_STM32F10X_H_ */
