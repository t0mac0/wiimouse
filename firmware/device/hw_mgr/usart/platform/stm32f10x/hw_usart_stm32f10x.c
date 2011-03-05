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
#include <platform_lib.h>
#include "usart/hw_usart.h"
#include "gpio/hw_gpio.h"

#if (SYSTEM_PLATFORM == STM32F10X_MD)
#ifdef HW_MOD_USART
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
PRIVATE USART_TypeDef* usartBase[USART_COUNT] =
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

PRIVATE uint32 HW_RCC_ApbPeriphUsart[USART_COUNT] =
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
PUBLIC inline void HW_USART_DefaultInit( void )
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    ASSERT(usartBase[DEFAULT_USART]);
    ASSERT(HW_GPIO_PortBase[DEFAULT_USART_PORT]);
    ASSERT(HW_RCC_ApbPeriphGpio[DEFAULT_USART_PORT]);
    ASSERT(HW_RCC_ApbPeriphUsart[DEFAULT_USART_PORT]);

    // Enable clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(HW_RCC_ApbPeriphGpio[DEFAULT_USART_PORT], ENABLE);
    RCC_APB1PeriphClockCmd(HW_RCC_ApbPeriphUsart[DEFAULT_USART_PORT], ENABLE);

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

PUBLIC Result HW_USART_Init(uint32 BlockId, void* InitInfo )
{
    Result result = HW_USART_RESULT_INIT();

    UNUSED(BlockId);
    UNUSED(InitInfo);


    return result;
}

PUBLIC Result HW_USART_PowerUp( uint32 BlockId )
{
    Result result = HW_USART_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}

PUBLIC Result HW_USART_PowerDown( uint32 BlockId )
{
    Result result = HW_USART_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
#endif
