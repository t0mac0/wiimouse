
#include "stm32f10x_lib.h"
#include "stm32f10x_map.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "usart.h"
#include "bits.h"
#include "printf.h"

#define STACK_TOP 0x20000800

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

void putc( void* p, char c);


void nmi_handler(void);
void hardfault_handler(void);
int main(void);
void Clk_Init (void);
void STM_EVAL_COMInit(USART_InitTypeDef* USART_InitStruct);
void myDelay(unsigned long delay );




// Define the vector table
unsigned int * myvectors[4]
   __attribute__ ((section("vectors")))= {
   	(unsigned int *)	0x20000800,	// stack pointer
   	(unsigned int *) 	main,		// code entry point
   	(unsigned int *)	nmi_handler,		// NMI handler (not really)
   	(unsigned int *)	hardfault_handler		// hard fault handler (let's hope not)
};

// VARIABLES


/*************************************************************************
 * Function Name: main
 * Parameters: none
 * Return: Int32U
 *
 * Description: The main subroutine
 *
 *************************************************************************/
int main(void)
{
	int i;


	*NVIC_CCR = *NVIC_CCR | 0x200; /* Set STKALIGN in NVIC */
	// Init clock system
	  Clk_Init();

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);


	  /* USARTx configured as follow:
	        - BaudRate = 115200 baud
	        - Word Length = 8 Bits
	        - One Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	  */

	  InitUSART2();

	  init_printf(0,putc);

	  i = 0;

	  while(1)
		{
		  i++;
		  printf("Printf() function seems %s. (This has been printed: %d times)\n", "to be working...", i);

	            GPIOC->BRR |= 0x00001000;
	            myDelay(500000);
	            GPIOC->BSRR |= 0x00001000;
	            myDelay(500000);

	      }
}
void nmi_handler(void)
{
	return ;
}

void hardfault_handler(void)
{
	return ;
}
//Functions definitions
void myDelay(unsigned long delay )
{
  while(delay) delay--;
}

/*************************************************************************
 * Function Name: Clk_Init
 * Parameters: Int32U Frequency
 * Return: Int32U
 *
 * Description: Init clock system
 *
 *************************************************************************/

void Clk_Init (void)
{
  // 1. Cloking the controller from internal HSI RC (8 MHz)
  RCC_HSICmd(ENABLE);
  // wait until the HSI is ready
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  // 2. Enable ext. high frequency OSC
  RCC_HSEConfig(RCC_HSE_ON);
  // wait until the HSE is ready
  while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
  // 3. Init PLL
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); // 72MHz
//  RCC_PLLConfig(RCC_PLLSource_HSE_Div2,RCC_PLLMul_9); // 72MHz
  RCC_PLLCmd(ENABLE);
  // wait until the PLL is ready
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  // 4. Set system clock divders
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  RCC_ADCCLKConfig(RCC_PCLK2_Div8);
  RCC_PCLK2Config(RCC_HCLK_Div1);
  RCC_PCLK1Config(RCC_HCLK_Div2);
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  // Flash 1 wait state
  *(vuint32 *)0x40022000 = 0x12;
  // 5. Clock system from PLL
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
void putc( void* p, char ch)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (unsigned char) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}

}
