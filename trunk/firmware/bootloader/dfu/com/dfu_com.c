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
#include "usb/hw_usb.h"

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
PRIVATE uint32 readCount = 0;

PRIVATE DFU_Command *commandBuffer = (DFU_Command*)&DfuMalBuffer[0];
PRIVATE DFU_Response *responseBuffer = (DFU_Response*)&DfuMalBuffer[DFU_COMMAND_SIZE];


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuComReceiveCommand( void )
{
    uint32 bytesRead;

    bytesRead = HW_USB_Read(VIR_COM_READ_EP, (uint8*)&DfuMalBuffer[readCount]);


    readCount += bytesRead;

    if(DfuMalWriteEnabled)
    {
        DfuActionWriteSectionChunk(responseBuffer, readCount);
        readCount = ((DfuMalWriteEnabled == FALSE) ?  0 : readCount);
    }
    else if(DfuMalReadEnabled)
    {
        DfuActionReadSectionChunk(&bytesRead);
        readCount = ((DfuMalReadEnabled == FALSE) ?  0 : readCount);
    }
    else if(readCount >= DFU_COMMAND_SIZE)
    {
        readCount = 0;
        DfuSmStateTransition(commandBuffer, responseBuffer);
    }
}


/******************************************************************************/
PROTECTED void DfuComSendResponse( void )
{
    HW_USB_Write(VIR_COM_WRITE_EP, (uint8*)responseBuffer, sizeof(DFU_Response));
}


/******************************************************************************/
PROTECTED void DfuComSendData( uint32 ByteCount )
{

    uint32 bytesSent = 0;
    uint32 bytesToSend;

    while(bytesSent < ByteCount)
    {
        bytesToSend = ((ByteCount-bytesSent) < DFU_COM_TRANSFER_SIZE) ? (ByteCount-bytesSent) : DFU_COM_TRANSFER_SIZE;
        HW_USB_Write(VIR_COM_WRITE_EP, (uint8*)&DfuMalBuffer[bytesSent], bytesToSend);
        bytesSent += bytesToSend;
    }
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

