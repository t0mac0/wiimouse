/*!
 * \file stm32f10x_sysclk.c
 *
 * \brief 
 *
 *
 * \date Mar 5, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "stm32f10x_sysclk.h"
#include "../rcc/stm32f10x_rcc.h"
#include "../flash/stm32f10x_flash.h"


#ifdef _SysClk

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
static void SetSysClockToHSE(void);
static void SetSysClockTo24(void);
static void SetSysClockTo36(void);
static void SetSysClockTo48(void);
static void SetSysClockTo56(void);
static void SetSysClockTo72(void);

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************
void SysClk_SetClock(uint32 Freq)
{
    // use internal oscillator
    switch(Freq)
    {
    case SYSCLK_FREQ_HSI:
        // TODO This currently only works on startup, need to be able to switch to HSI at runtime
        break;

    case SYSCLK_FREQ_HSE:
        SetSysClockToHSE();
        break;

    case SYSCLK_FREQ_24MHz:
        SetSysClockTo24();
        break;

    case SYSCLK_FREQ_36MHz:
        SetSysClockTo36();
        break;

    case SYSCLK_FREQ_48MHz:
        SetSysClockTo48();
        break;

    case  SYSCLK_FREQ_56MHz:
        SetSysClockTo56();
        break;

    case SYSCLK_FREQ_72MHz:
        SetSysClockTo72();
        break;

    default:
        ASSERT(0);
    }

}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
static void SetSysClockToHSE(void)
{
    vuint32 StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32)0x01;
    }
    else
    {
        HSEStatus = (uint32)0x00;
    }

    if (HSEStatus == (uint32)0x01)
    {

#if !defined STM32F10X_LD_VL && !defined STM32F10X_MD_VL && !defined STM32F10X_HD_VL
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32)((uint32)~FLASH_ACR_LATENCY);

#ifndef STM32F10X_CL
        FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_0;
#else
        if (HSE_VALUE <= 24000000)
        {
            FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_0;
        }
        else
        {
            FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_1;
        }
#endif /* STM32F10X_CL */
#endif

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE1_DIV1;

        /* Select HSE as system clock source */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32)RCC_CFGR_SW_HSE;

        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR & (uint32)RCC_CFGR_SWS) != (uint32)0x04)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
        ASSERT(0);
    }
}

/**
 * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2
 *          and PCLK1 prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @retval None
 */
static void SetSysClockTo24(void)
{
    vuint32 StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32)0x01;
    }
    else
    {
        HSEStatus = (uint32)0x00;
    }

    if (HSEStatus == (uint32)0x01)
    {
#if !defined STM32F10X_LD_VL && !defined STM32F10X_MD_VL && !defined STM32F10X_HD_VL
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 0 wait state */
        FLASH->ACR &= (uint32)((uint32)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_0;
#endif

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE1_DIV1;

#ifdef STM32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/
        /* PLL configuration: PLLCLK = PREDIV1 * 6 = 24 MHz */
        RCC->CFGR &= (uint32)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                RCC_CFGR_PLLMULL6);

        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 10 = 4 MHz */
        RCC->CFGR2 &= (uint32)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV10);

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while((RCC->CR & RCC_CR_PLL2RDY) == 0)
        {
        }
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
        /*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLXTPRE_PREDIV1_Div2 | RCC_CFGR_PLLMULL6);
#else
        /*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
#endif /* STM32F10X_CL */

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32)RCC_CFGR_SWS) != (uint32)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }
}

/**
 * @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2
 *          and PCLK1 prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @retval None
 */
static void SetSysClockTo36(void)
{
    vuint32 StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32)0x01;
    }
    else
    {
        HSEStatus = (uint32)0x00;
    }

    if (HSEStatus == (uint32)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 1 wait state */
        FLASH->ACR &= (uint32)((uint32)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_1;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE1_DIV1;

#ifdef STM32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 9 = 36 MHz */
        RCC->CFGR &= (uint32)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                RCC_CFGR_PLLMULL9);

        /*!< PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 10 = 4 MHz */

        RCC->CFGR2 &= (uint32)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV10);

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while((RCC->CR & RCC_CR_PLL2RDY) == 0)
        {
        }

#else
        /*  PLL configuration: PLLCLK = (HSE / 2) * 9 = 36 MHz */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL9);
#endif /* STM32F10X_CL */

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32)RCC_CFGR_SWS) != (uint32)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }
}

/**
 * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
 *          and PCLK1 prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @retval None
 */
static void SetSysClockTo48(void)
{
    vuint32 StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32)0x01;
    }
    else
    {
        HSEStatus = (uint32)0x00;
    }

    if (HSEStatus == (uint32)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 1 wait state */
        FLASH->ACR &= (uint32)((uint32)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_1;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE1_DIV2;

#ifdef STM32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->CFGR2 &= (uint32)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while((RCC->CR & RCC_CR_PLL2RDY) == 0)
        {
        }


        /* PLL configuration: PLLCLK = PREDIV1 * 6 = 48 MHz */
        RCC->CFGR &= (uint32)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                RCC_CFGR_PLLMULL6);
#else
    /*  PLL configuration: PLLCLK = HSE * 6 = 48 MHz */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL6);
#endif /* STM32F10X_CL */

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32)RCC_CFGR_SWS) != (uint32)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }
}


/**
 * @brief  Sets System clock frequency to 56MHz and configure HCLK, PCLK2
 *          and PCLK1 prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @retval None
 */
static void SetSysClockTo56(void)
{
    vuint32 StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32)0x01;
    }
    else
    {
        HSEStatus = (uint32)0x00;
    }

    if (HSEStatus == (uint32)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (uint32)((uint32)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_2;

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE1_DIV2;

#ifdef STM32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->CFGR2 &= (uint32)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while((RCC->CR & RCC_CR_PLL2RDY) == 0)
        {
        }


        /* PLL configuration: PLLCLK = PREDIV1 * 7 = 56 MHz */
        RCC->CFGR &= (uint32)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                RCC_CFGR_PLLMULL7);
#else
    /* PLL configuration: PLLCLK = HSE * 7 = 56 MHz */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL7);

#endif /* STM32F10X_CL */

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32)RCC_CFGR_SWS) != (uint32)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }
}


/**
 * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2
 *          and PCLK1 prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @retval None
 */
static void SetSysClockTo72(void)
{
    vuint32 StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32)0x01;
    }
    else
    {
        HSEStatus = (uint32)0x00;
    }

    if (HSEStatus == (uint32)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (uint32)((uint32)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32)FLASH_ACR_LATENCY_2;


        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32)RCC_CFGR_PPRE1_DIV2;

#ifdef STM32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->CFGR2 &= (uint32)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while((RCC->CR & RCC_CR_PLL2RDY) == 0)
        {
        }


        /* PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz */
        RCC->CFGR &= (uint32)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                RCC_CFGR_PLLMULL9);
#else
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
#endif /* STM32F10X_CL */

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32)((uint32)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32)RCC_CFGR_SWS) != (uint32)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }
}

#endif
