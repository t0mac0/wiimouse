/*!
 * \file stm32f10x_md_interrupts.c
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "composite_usb/isr/composite_usb_isr.h"
#include "util/timer/util_timer.h"
#include "nunchuck/nunchuck.h"

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
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/*******************************************************************************
 * Function Name  : USB_LP_CAN1_RX0_IRQHandler
 * Description    : This function handles USB Low Priority or CAN RX0 interrupts
 *                  requests.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
PUBLIC void USB_LP_CAN_RX0_IRQHandler( void )
{
	USB_Istr();
}


/******************************************************************************/
PUBLIC void TIM2_IRQHandler( void )
{
	//if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		// Read nunchuck
		NUNCHUCK_READER_ReadDataPoint();

	}
}


/******************************************************************************/
PUBLIC void TIM3_IRQHandler( void )
{
#ifdef DEV_UTIL_TIMER
#if( UTIL_TIMER != HW_TIMER_3 )
#error Utility timer not configured properly
#endif
	//if( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		if( UTIL_TIMER_Ticker == (1 << 30) )
			UTIL_TIMER_Ticker = 0;
		else
			UTIL_TIMER_Ticker++;

	}
#endif
}


/******************************************************************************/
PUBLIC void TIM4_IRQHandler( void )
{
	//if( TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

		// Send HID Report
		NUNCHUCK_HID_REPORTER_SendReport();
	}


}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

