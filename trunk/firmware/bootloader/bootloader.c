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
PUBLIC uint32 BootloaderVersion  __attribute ((section(".bootloader_version"))) = BOOTLOADER_VERSION;


PRIVATE pFunction Jump_To_Application;
PRIVATE uint32 JumpAddress;

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
int main(int argc, char *argv[])
{
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
        HW_Init();

        print("Bootloader Initializing...\n");

        DFU_Init();

    }

    for(;;);
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

