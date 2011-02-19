
#include "stm32f10x_lib.h"
#include "core_cm3.h"
#include "bits.h"
#include "printf.h"
#include "drv_nunchuck.h"
#include "delay.h"
#include "hw_config.h"
#include "USB_Init.h"
#include "usb_hid_mouse.h"
#include "usb_sil.h"
#include "usb_regs.h"
#include "usart.h"
#include "hw_config.h"
#include "usb_conf.h"
#include "usb_desc.h"

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
	HID_MOUSE_REPORT report;
	char buffer[64];

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00008000);

	Set_System();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);


	InitUSART2();


	USB_Interrupts_Config();

	Set_USBClock();

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		printf("failed to setup sysTick\n");
		/* Capture error */
		while (1);
	}



	printf("Trying delay 1s\n");
	DelayMs(1000);
	printf("Delay over\n");
	USB_Init();

	nunchuck_init();


	while(1)
	{
		if( nunchuck_read())
		{
			nunchuck_get_joystick(&report.X, &report.Y);
			report.Buttons.Left = nunchuck_z_pressed();
			report.Buttons.Right = nunchuck_c_pressed();

			report.X -= 129;
			report.Y = 130 - report.Y;

			size = 0;
			snprintf(buffer, &size,
					"X: %d, Y: %d, Z: %d, C: %d\n",report.X, report.Y, report.Buttons.Left, report.Buttons.Right);

			//printf("%s", buffer);
			USB_SIL_Write(EP4_IN, (uint8*)buffer, size);
			SetEPTxValid(ENDP4);

			USB_SIL_Write(EP1_IN, (uint8*)&report, HID_MOUSE_REPORT_SIZE);
			SetEPTxValid(ENDP1);
		}

	}
}


void assert_failed(uint8* file, uint32 line)
{
	printf("Assert failed: file: %s, line: %d\n", file, line);
	while(1);
}





