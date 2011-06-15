/*!
 * \file dfu_com.c
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
#include "dfu/dfu.h"
#include "dfu/fat/dfu_fat.h"


#include "hw/usb/hw_usb.h"

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
PRIVATE HW_USB_MassStorageCallBack ReadCallback;
PRIVATE HW_USB_MassStorageCallBack WriteCallback;

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED uint8 DfuComDataBuffer[DFU_COM_TRANSFER_SIZE];
PROTECTED DFU_Response DfuComResponse;
PROTECTED DFU_Command DfuComCommand;

PRIVATE bool isTransferring;

//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuComInit(void)
{
	HW_USB_RegisterMassStorageReadCallback(ReadCallback);
	HW_USB_RegisterMassStorageWriteCallback(WriteCallback);

	isTransferring = FALSE;
}


/******************************************************************************/
PROTECTED void ReadCallback( uint32 StartBlockAddress, uint32 BlockCount )
{
	static uint32 currentAddress, bytesRead, maxBlock;

	if( !isTransferring )
	{
		currentAddress = StartBlockAddress;
		maxBlock = StartBlockAddress + BlockCount;
		bytesRead = 0;
		print("Starting read from: %X. to %X\n", currentAddress, maxBlock);
	}


	if( bytesRead == 0 )
	{
		DfuFatReadBlockAddress(currentAddress);
	}

	bytesRead += MASS_STORAGE_MAX_PACKET_SIZE;
	CSW.dDataResidue -= MASS_STORAGE_MAX_PACKET_SIZE;

	if( bytesRead == MASS_STORAGE_MAX_PACKET_SIZE )
	{
		currentAddress++;

		if( currentAddress < maxBlock )
		{
			bytesRead = 0;
		}
		else
		{
			isTransferring = FALSE;
			// REVISIT: this should NOT be accessed outside of the usb component
			Bot_State = BOT_DATA_IN_LAST;
		}
	}

	HW_USB_Write(MASS_STORAGE_READ_EP, DfuComDataBuffer + bytesRead, MASS_STORAGE_MAX_PACKET_SIZE, TRUE);
}


/******************************************************************************/
PROTECTED void WriteCallback( uint32 StartBlockAddress, uint32 BlockCount )
{
	static uint32 currentAddress, bytesWritten, maxBlock;
	uint32 usbBytesRead;

	if( !isTransferring )
	{
		currentAddress = StartBlockAddress;
		maxBlock = StartBlockAddress + BlockCount;
		bytesWritten = 0;
		print("Starting write to: %X. to %X\n", currentAddress, maxBlock);
	}


	usbBytesRead = HW_USB_Read(MASS_STORAGE_WRITE_EP, DfuComDataBuffer, FALSE);
	CSW.dDataResidue -= usbBytesRead;
	bytesWritten += usbBytesRead;

	if( currentAddress >= 0 )
	{

	}
	// REVISIT: this should NOT be accessed outside of the usb component
	SetEPRxStatus(MASS_STORAGE_WRITE_EP, EP_RX_VALID);

	if( bytesWritten >= MASS_STORAGE_MAX_PACKET_SIZE )
	{
		currentAddress++;

		if( currentAddress < maxBlock )
		{
			bytesWritten = 0;
		}
		else
		{
			isTransferring = FALSE;
			// REVISIT: this should NOT be accessed outside of the usb component
			Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
		}
	}


}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

