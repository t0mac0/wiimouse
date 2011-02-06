
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

	if (((*(__IO uint32*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
	{ /* Jump to user application */

		JumpAddress = *(__IO uint32*) (ApplicationAddress + 4);
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





