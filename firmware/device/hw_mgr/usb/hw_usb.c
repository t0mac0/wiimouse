/*!
 * \file hw_usb.c
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_usb.h"
#include "int/hw_int.h"

#ifdef HW_MGR_MOD_USB

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
void Set_USBClock(void);
void USB_Interrupts_Config(void);

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

//****************************************************************************/
PUBLIC Result HW_USB_Init(uint32 BlockId, void* InitInfo )
{
    Result result = HW_USART_RESULT_INIT();

    UNUSED(InitInfo);
    UNUSED(BlockId);

    USB_Interrupts_Config();

    Set_USBClock();

    USB_Init();

    return result;
}

//****************************************************************************/
PUBLIC Result HW_USB_PowerUp( uint32 BlockId )
{
    Result result = HW_USART_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_USB_PowerDown( uint32 BlockId )
{
    Result result = HW_USART_RESULT_INIT();

    UNUSED(BlockId);

    return result;
};






//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
/*******************************************************************************
 * Function Name  : Set_USBClock
 * Description    : Configures USB Clock input (48MHz)
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void Set_USBClock(void)
{

    /* Select USBCLK source */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

    /* Enable the USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);

}


/*******************************************************************************
 * Function Name  : USB_Interrupts_Config
 * Description    : Configures the USB interrupts
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    //  /* Enable USART Interrupt */
    //  NVIC_InitStructure.NVIC_IRQChannel = EVAL_COM1_IRQn;
    //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //  NVIC_Init(&NVIC_InitStructure);
}

#endif
