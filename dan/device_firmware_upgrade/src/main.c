
#include "stm32f10x_lib.h"
#include "core_cm3.h"
#include "bits.h"
#include "printf.h"
#include "delay.h"
#include "hw_config.h"
#include "USB_Init.h"
#include "usb_sil.h"
#include "usb_regs.h"
#include "usart.h"
#include "hw_config.h"
#include "usb_conf.h"
#include "dfu_mal.h"
#include "usb_prop.h"
#include "dfu_state_machine.h"

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
	if(*((uint32*)DFU_MODE_ADDR) == DFU_MODE_USER)
	{ /* Jump to user application */

		JumpAddress = *(__IO uint32*) (ApplicationAddress+4);
		Jump_To_Application = (pFunction) JumpAddress;
		/* Initialize user application's Stack Pointer */
		__set_MSP(*(__IO uint32*) ApplicationAddress);
		Jump_To_Application();
	}

	/* Enter DFU mode */
	//DeviceState = STATE_dfuERROR;
	//DeviceStatus[0] = STATUS_ERRFIRMWARE;
	//DeviceStatus[4] = DeviceState;
	dfu_StateMachineInit();
	Set_System();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

	InitUSART2();

	printf("Addr: %08X =  %08X...\n", DFU_MODE_ADDR,  (*(__IO uint32*)DFU_MODE_ADDR));
	printf("Running in Update mode\n");

	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();

	/* Main loop */
	while (1)
	{}
}


void assert_failed(uint8* file, uint32 line)
{
	printf("Assert failed: file: %s, line: %d\n", file, line);
	while(1);
}





