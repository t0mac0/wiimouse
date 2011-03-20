/*!
 * \file composite_usb_ep_conf_stm32f10x.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPOSITE_USB_EP_CONF_STM32F10X_H_
#define _COMPOSITE_USB_EP_CONF_STM32F10_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
// number of end-points
#define EP_NUM                          (5)



/* buffer table base address */
#define BTABLE_ADDRESS      (0x00)

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x40)
#define ENDP0_TXADDR        (0x80)

#define ENDP1_TXADDR        (0x120)

#define ENDP2_TXADDR        (0x100)
#define ENDP3_RXADDR        (0x110)
#define ENDP4_TXADDR        (0x0C0)

#define HID_MOUSE_REPORT_EP_NUM     1
#define HID_MOUSE_REPORT_EP         EP1_IN
#define VIR_COM_WRITE_EP_NUM        4
#define VIR_COM_WRITE_EP            EP4_IN
#define VIR_COM_READ_EP_NUM         3
#define VIR_COM_READ_EP             EP3_OUT

/* CTR service routines */
/* associated to defined endpoints */
/*#define  EP1_IN_Callback   NOP_Process*/
#define  EP2_IN_Callback   NOP_Process
#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

#define  EP1_OUT_Callback   NOP_Process
#define  EP2_OUT_Callback   NOP_Process
/*#define  EP3_OUT_Callback   NOP_Process*/
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


#endif /* COMPOSITE_USB_EP_CONF_STM32F10_H_ */
