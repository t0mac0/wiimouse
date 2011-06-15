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
#include "dfu/com/dfu_com.h"
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

PROTECTED bool DfuMalWriteEnabled;
PROTECTED bool DfuMalReadEnabled;

PROTECTED bool pageErased[256];

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED bool DfuMalInit (void)
{
	uint32 i;

	for(i = 0; i < 256; i++)
		pageErased[i] = FALSE;

	return HW_FLASH_Init();
}


/******************************************************************************/
PROTECTED bool DfuMalErase (uint32 SectorAddress, uint32 Length)
{
	uint32 numPages, tmpPages, i, index;
	uint32 address;


	if( SectorAddress < DEVICE_START_ADDR )
	{
		print("Error: Attempted to erase bootloader section memory\n");
		return FALSE;
	}

	tmpPages = CELING((Length - (SectorAddress & (FLASH_PAGE_SIZE-1)) ), FLASH_PAGE_SIZE) +
			CELING((SectorAddress & (FLASH_PAGE_SIZE-1) ), FLASH_PAGE_SIZE);

	print("Making sure %d pages haven't already been erased\n", tmpPages);

	address = (SectorAddress & ~(FLASH_PAGE_SIZE-1));
	index = (address - 0x08000000)/FLASH_PAGE_SIZE;
	numPages = tmpPages;
	for(i = index; i < index + numPages; i++)
	{
		if(pageErased[i])
		{
			tmpPages--;
			address += FLASH_PAGE_SIZE;
		}
	}

	print("Erasing: %d pages starting at: %X\n", tmpPages, address);
	index = (address - 0x08000000)/FLASH_PAGE_SIZE;

	for(i = index; i < index + tmpPages; i++)
	{
		if( !HW_FLASH_ErasePage(address))
		{
			print("Failed to erase page at: %X\n", address);
			return FALSE;
		}
		pageErased[i] = TRUE;
		address += FLASH_PAGE_SIZE;
	}

	return TRUE;
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
			if( !HW_FLASH_Write32Bit(address, ((uint32*)DfuComDataBuffer)[i]) )
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

	return HW_FLASH_Read32Bit(SectorAddress,(uint32*) DfuComDataBuffer, DataLength/sizeof(uint32));
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

