/*!
 * \file dfu_sm_actions.c
 *
 * \brief 
 *
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <platform_lib.h>

#include "dfu/dfu.h"

#include "hw/flash/hw_flash.h"
#include"hw/nvic/hw_nvic.h"


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


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuActionQueryDevice(void)
{
	DfuComResponse.Status = DFU_STATUS_SUCCESS;

	DfuComResponse.Mode = *((uint32*)DEVICE_MODE_ADDR);
	DfuComResponse.FWVersion = (uint16)*((uint32*)DEVICE_VERSION_ADDR);
	DfuComResponse.BootloaderVersion = (uint16)*((uint32*)BOOTLOADER_VERSION_ADDR);

	DfuComResponse.VendorId = USB_VENDOR_ID;
	DfuComResponse.ProductId = USB_PRODUCT_ID;
	DfuComResponse.DeviceId = USB_DEVICE_ID;

	print("Device queried: \n");
	print("\tMode: %X\n", DfuComResponse.Mode);
	print("\tBootloader Version: %X\n", *((uint32*)BOOTLOADER_VERSION_ADDR));
	print("\tFW Version: %X\n", DfuComResponse.FWVersion);
	print("\tVendor Id: %X\n", DfuComResponse.VendorId);
	print("\tProduct Id: %X\n", DfuComResponse.ProductId);
	print("\tDevice Id: %X\n", DfuComResponse.DeviceId);

}


/******************************************************************************/
PROTECTED void DfuActionInitializeUpdate(void)
{
	print("Initializing device for firmware update...\n");

	// Erase firmware vector table and global settings
	DfuMalErase(DEVICE_START_ADDR, FLASH_PAGE_SIZE);

	// send DFU_STATUS_SUCCESS
	DfuComResponse.Status = DFU_STATUS_SUCCESS;

	// reset device
	print("Resetting device.\n");
	HW_NVIC_SystemReset();
}

/******************************************************************************/
PROTECTED void DfuActionCompleteUpdate(void)
{
	DfuComResponse.Status = DFU_STATUS_SUCCESS;

	print("Completed update.\n");

	// set device to DFU_MODE_USER in non-volatile flash
	if( !HW_FLASH_Write32Bit(DEVICE_MODE_ADDR, DFU_MODE_USER) )
	{
		print("Failed to set device to DFU_MODE_USER\n");
		DfuComResponse.Status = DFU_STATUS_INTERNAL_FLASH_WRITE_ERROR;


	}
	else
	{


		// reset device
		print("Resetting device.\n");
		HW_NVIC_SystemReset();
	}


}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

