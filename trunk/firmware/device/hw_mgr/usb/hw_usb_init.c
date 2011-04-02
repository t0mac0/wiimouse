/*!
 * \file hw_usb_init.c
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
#include "hw_usb_init.h"

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
void DisconnectPin_Config(void);

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
/*  The number of current endpoint, it will be used to specify an endpoint */
uint8   EPindex;
/*  The number of current device, it is an index to the Device_Table */
/* uint8    Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_INFO *pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_PROP *pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
uint16  SaveState ;
uint16  wInterrupt_Mask;
DEVICE_INFO Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*******************************************************************************
 * Function Name  : USB_Init
 * Description    : USB system initialization
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void USB_Init(void)
{
    DisconnectPin_Config();

    USB_Interrupts_Config();

    Set_USBClock();

    pInformation = &Device_Info;
    pInformation->ControlState = 2;
    pProperty = &Device_Property;
    pUser_Standard_Requests = &User_Standard_Requests;
    /* Initialize devices one by one */
    pProperty->Init();
}

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
    // TODO: PLATFORM specific
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
    // TODO: PLATFORM specific
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}


/*******************************************************************************
 * Function Name  : USB_Interrupts_Config
 * Description    : Configures the USB interrupts
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void DisconnectPin_Config(void)
{
    // TODO: PLATFORM specific
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(USB_DISCONNECT_RCC_APB2Periph, ENABLE);

    /* Configure USB pull-up pin */
    GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USB_ACTIVE_LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(USB_ACTIVE_LED, &GPIO_InitStructure);
}
