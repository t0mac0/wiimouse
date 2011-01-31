
#include "stm32f10x_lib.h"
#include "core_cm3.h"
#include "usart.h"
#include "bits.h"
#include "printf.h"
#include "drv_nunchuck.h"
#include "delay.h"


void putc( void* p, char c);


void NVIC_Configuration(void);



// VARIABLES


/* Private function prototypes -----------------------------------------------*/



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
	uint8 x, y;

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

	  NVIC_Configuration();
	  I2C_ITConfig(I2C2,I2C_IT_ERR , ENABLE);

	  /* Setup SysTick Timer for 1 msec interrupts  */
	  if (SysTick_Config(SystemCoreClock / 1000))
	  {
	    /* Capture error */
	    while (1);
	  }

	  nunchuck_init();


	  i = 0;

	  while(1)
		{
		  //printf("Printf() function seems %s. (This has been printed: %d times)\n", "to be working...", i);
		  if(nunchuck_read())
		  {
		  nunchuck_get_joystick(&x, &y);

		  printf("X: %d, Y: %d, C: %d, Z: %d\n",
				  x, y, nunchuck_c_pressed(), nunchuck_z_pressed());
		  }
		  DelayMs(75);
	      }
}


void assert_failed(uint8* file, uint32 line)
{
	printf("Assert failed: file: %s, line: %d\n", file, line);
	while(1);
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

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}





