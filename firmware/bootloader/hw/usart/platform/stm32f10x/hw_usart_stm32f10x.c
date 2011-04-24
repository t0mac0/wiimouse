/*!
 * \file stm32f10x_usart.c
 *
 * \brief 
 *
 *
 * \date Mar 2, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "usart/hw_usart.h"
#include "gpio/hw_gpio.h"
#include "rcc/hw_rcc.h"

#ifdef STM32F10X_MD

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
PRIVATE USART_TypeDef* usartBase[HW_USART_COUNT] =
{
#ifdef USART1
        USART1,
#else
        NULL,
#endif
#ifdef USART2
        USART2,
#else
        NULL,
#endif
#ifdef USART3
        USART3,
#else
        NULL,
#endif
#ifdef USART4
        USART4,
#else
        NULL,
#endif
#ifdef USART5
        USART5,
#else
        NULL,
#endif
};

PRIVATE uint32 HW_RCC_ApbPeriphUsart[HW_USART_COUNT] =
{
#ifdef RCC_APB2Periph_USART1
        RCC_APB2Periph_USART1,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_USART2
        RCC_APB1Periph_USART2,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_USART3
        RCC_APB1Periph_USART3,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_USART4
        RCC_APB1Periph_USART4,
#else
        NULL,
#endif
#ifdef RCC_APB1Periph_USART5
        RCC_APB1Periph_USART5,
#else
        NULL,
#endif

};

//*****************************************************************************
//
// Exported Functions
//
//****************************************************************************



//****************************************************************************/
PUBLIC inline void HW_USART_DefaultInit( void )
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    ASSERT(usartBase[DEFAULT_USART] != NULL);
    ASSERT(HW_GPIO_PortBase[DEFAULT_USART_PORT] != NULL);
    ASSERT(HW_RCC_ApbPeriphGpio[DEFAULT_USART_PORT] != NULL);
    ASSERT(HW_RCC_ApbPeriphUsart[DEFAULT_USART] != NULL);

    // Enable clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(HW_RCC_ApbPeriphGpio[DEFAULT_USART_PORT], ENABLE);
    RCC_APB1PeriphClockCmd(HW_RCC_ApbPeriphUsart[DEFAULT_USART], ENABLE);

    USART_Cmd(usartBase[DEFAULT_USART], ENABLE);

    // Configure Tx pin
    GPIO_InitStructure.GPIO_Pin = DEFAULT_USART_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init ((GPIO_TypeDef*)HW_GPIO_PortBase[DEFAULT_USART_PORT], &GPIO_InitStructure);

    // Gonfigure Rx
    GPIO_InitStructure.GPIO_Pin = DEFAULT_USART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ;
    GPIO_Init ((GPIO_TypeDef*)HW_GPIO_PortBase[DEFAULT_USART_PORT], &GPIO_InitStructure);


    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_WordLength = DEFAULT_USART_WORD_LEN;
    USART_InitStructure.USART_StopBits = DEFAULT_USART_STOP_BITS;
    USART_InitStructure.USART_Parity = DEFAULT_USART_PARITY ;
    USART_InitStructure.USART_BaudRate = DEFAULT_USART_BUAD;
    USART_InitStructure.USART_HardwareFlowControl = DEFAULT_USART_FLOW_CTL;
    USART_InitStructure.USART_Mode = (USART_Mode_Tx|USART_Mode_Rx);


    USART_Init(usartBase[DEFAULT_USART], &USART_InitStructure);
}


//****************************************************************************/
PUBLIC bool HW_USART_WriteByte(HW_USART_BlockId Id, uint8 Byte)
{
    //ASSERT(usartBase[Id] != NULL);

    // TODO check if initialized and wrap with watch dog
    USART_SendData(usartBase[Id], (uint16)Byte);
    while(USART_GetFlagStatus(usartBase[Id], USART_FLAG_TXE) == RESET);

    return TRUE;
}


//****************************************************************************/
PUBLIC bool HW_USART_WriteBytes(HW_USART_BlockId Id, uint8* Bytes, uint32 Count)
{
    uint32 i;

    // TODO check if initialized and wrap with watch dog
    ASSERT(usartBase[Id] != NULL);

    for( i = 0; i < Count; i++ )
    {
        USART_SendData(usartBase[Id], (uint16)Bytes[i]);
        while(USART_GetFlagStatus(usartBase[Id], USART_FLAG_TXE) == RESET);
    }

    return TRUE;
}


//****************************************************************************/
PUBLIC bool HW_USART_ReadByte(HW_USART_BlockId Id, uint8 *Byte)
{
    // TODO check if initialized and wrap with watch dog
    ASSERT(usartBase[Id] != NULL);

    while(USART_GetFlagStatus(usartBase[Id], USART_FLAG_RXNE) == RESET);
    *Byte =  (uint8)USART_ReceiveData(usartBase[Id]);

    return TRUE;
}


//****************************************************************************/
PUBLIC bool HW_USART_ReadBytes(HW_USART_BlockId Id, uint8 *Bytes, uint32 Count)
{
    uint32 i;

    // TODO check if initialized and wrap with watch dog
    ASSERT(usartBase[Id] != NULL);

    for( i = 0; i < Count; i++ )
    {
        while(USART_GetFlagStatus(usartBase[Id], USART_FLAG_RXNE) == RESET);
        Bytes[i] =  (uint8)USART_ReceiveData(usartBase[Id]);
    }

    return TRUE;
}


//****************************************************************************/
PUBLIC void HW_USART_DefaultOutputDest(void *p, char ch)
{
    UNUSED(p);
    HW_USART_WriteByte(DEFAULT_USART, ch);
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif

