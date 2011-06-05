/*!
 * \file bootloader.c
 *
 * \brief 
 *
 *
 * \date Apr 10, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "bootloader.h"
#include "lib_printf.h"
#include "hw/hw.h"
#include "dfu/dfu.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef  void (*pFunction)(void);


/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/

PRIVATE pFunction Jump_To_Application;
PRIVATE vuint32 JumpAddress;

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
int main(int argc, char *argv[])
{
	// initialize system registers
	HW_SYSINIT_Init();

	// initialize system clock
	HW_SYSCLK_SetClock(BOOTLOADER_CLOCK_RATE);

	// initialize interrupt vector table
	HW_NVIC_Init();

	// initialize USB
	HW_USB_Init();

	// Jump to firmware if present
	if( *((uint32*)DEVICE_MODE_ADDR) == DFU_MODE_USER )
	{
		JumpAddress = *(vuint32*) (DEVICE_START_ADDR+4);
		Jump_To_Application = (pFunction) JumpAddress;

		// Initialize user application's Stack Pointer
		SetMainStackPointer(*(vuint32*) DEVICE_START_ADDR);

		Jump_To_Application();
	}
	else
	{
		// initialize default USART
		HW_USART_DefaultInit();

		// initialize DFU
		DFU_Init();

		print("Bootloader waiting for commands.\n");

	}

	for(;;);

	return 0;
}



/******************************************************************************/
PUBLIC void print(char* msg, ...)
{
	va_list va;
	va_start(va,msg);
	LIB_PRINTF_PrintfVaArgs(HW_USART_DefaultOutputDest, msg, va);
	va_end(va);
}


/******************************************************************************/
PUBLIC void ASSERT_failed(uint8* file, uint32 line)
{
	print("Assertion Failed: File: %s, line: %d\n", file, line);
	UNUSED(file);
	UNUSED(line);
	while(1);
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

