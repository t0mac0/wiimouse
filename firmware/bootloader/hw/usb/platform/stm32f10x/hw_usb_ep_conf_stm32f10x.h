/*!
 * \file hw_usb_ep_conf_stm32f10x.h
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_EP_CONF_STM32F10X_H_
#define _HW_USB_EP_CONF_STM32F10X_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

// number of end-points
#define EP_NUM      		(2)



/* buffer table base address */
#define BTABLE_ADDRESS      (0x00)

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x18)
#define ENDP0_TXADDR        (0x58)

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        (0x98)
#define ENDP2_RXADDR        (0xD8)


#define MASS_STORAGE_READ_EP_NUM         1
#define MASS_STORAGE_READ_EP             EP1_IN
#define MASS_STORAGE_WRITE_EP_NUM        2
#define MASS_STORAGE_WRITE_EP            EP2_OUT


/* CTR service routines */
/* associated to defined endpoints */
//#define  EP1_IN_Callback   NOP_Process
#define  EP2_IN_Callback   NOP_Process
#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

#define  EP1_OUT_Callback   NOP_Process
//#define  EP2_OUT_Callback   NOP_Process
#define  EP3_OUT_Callback   NOP_Process
#define  EP4_OUT_Callback   NOP_Process
#define  EP5_OUT_Callback   NOP_Process
#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process

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


#endif /* HW_USB_EP_CONF_STM32F10X_H_ */
