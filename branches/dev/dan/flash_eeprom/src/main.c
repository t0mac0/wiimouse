
#include "stm32f10x_lib.h"
#include "core_cm3.h"
#include "bits.h"
#include "printf.h"
#include "delay.h"
#include "hw_config.h"
#include "usart.h"
#include "hw_config.h"
#include "dfu_mal.h"
#include "ifc_feeprom.h"
#include "feeprom_test.h"

/* Private function prototypes -----------------------------------------------*/
typedef  void (*pFunction)(void);

uint8 DeviceState;
uint8 DeviceStatus[6];
pFunction Jump_To_Application;
uint32 JumpAddress;


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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

	InitUSART2();

	FEEPROM_Init();

	FEEPROM_ADD_ENTRY(FEEPROM_ENTRY_DFU_MODE, -1, 1, FEEPROM_ENTRY_FORCE_UPDATE);

	feepromTest();

	/* Main loop */
	while (1)
	{}
}


void assert_failed(uint8* file, uint32 line)
{
	printf("Assert failed: file: %s, line: %d\n", file, line);
	while(1);
}



