/*!
 * \file dfu_mal.c
 *
 * \brief 
 *
 * Note: This currently only supported internal flash. Memory types would be
 *       accessed here as well.
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <platform_lib.h>

#include "dfu_mal.h"
#include "flash/hw_flash.h"

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

PROTECTED uint8  DfuMalBuffer[DFU_MAL_BUFFER_SIZE]; /* RAM Buffer for Downloaded Data */

PROTECTED bool DfuMalWriteEnabled;
PROTECTED bool DfuMalReadEnabled;

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED bool DfuMalInit (void)
{
	return HW_FLASH_Init();
}


/******************************************************************************/
PROTECTED bool DfuMalErase (uint32 SectorAddress, uint32 Length)
{
	uint32 numPages;


	if( SectorAddress < DEVICE_START_ADDR )
	{
		print("Error: Attempting to erase bootloader section memory\n");
		return FALSE;
	}

	numPages = CELING((Length - (SectorAddress & (FLASH_PAGE_SIZE-1)) ), FLASH_PAGE_SIZE) +
			CELING((SectorAddress & (FLASH_PAGE_SIZE-1) ), FLASH_PAGE_SIZE);

	print("Erasing: %d pages starting at: %X\n", numPages, SectorAddress);

	return HW_FLASH_ErasePages(SectorAddress, numPages);
}


/******************************************************************************/
PROTECTED bool DfuMalWrite (uint32 SectorAddress, uint32 DataLength)
{
	bool result = TRUE;
	uint32 i, address;

	// if the DataLength isn't a multiple of 4, then return error
	if(DataLength&03)
	{
		return FALSE;
	}

	address = SectorAddress;

	for(i = 0; i < DataLength/sizeof(uint32); i++)
	{
		if(address != DEVICE_MODE_ADDR)
		{
			if( !HW_FLASH_Write32Bit(address, ((uint32*)DfuMalBuffer)[i]) )
			{
				result = FALSE;
				break;
			}
		}
		else
		{
			print("Skipping DEVICE_MODE_ADDR\n");
		}
		address += 4;
	}

	return result;
}


/******************************************************************************/
PROTECTED bool DfuMalRead (uint32 SectorAddress, uint32 DataLength)
{

	// if the DataLength isn't a multiple of 4, then return error
	if(DataLength&03)
	{
		return FALSE;
	}

	return HW_FLASH_Read32Bit(SectorAddress,(uint32*) DfuMalBuffer, DataLength/sizeof(uint32));
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

