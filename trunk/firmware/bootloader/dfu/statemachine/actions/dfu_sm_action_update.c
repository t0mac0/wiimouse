/*!
 * \file dfu_sm_action_update.c
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


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define IS_DATA_OVERFLOW()( ((writeAddress - sectionStartAddress) + writeSize) > sectionSize )


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE void InitializeDataMembers( void );


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PRIVATE uint32 sectionStartAddress;
PRIVATE uint32 sectionsRemaining;
PRIVATE uint32 sectionSize;
PRIVATE uint32 writeSize;
PRIVATE uint32 writeAddress;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuActionBeginUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
    uint32 *mode;

    // determine if in DFU_UPDATE_MODE, return failure if not
    if( !DfuMalRead(DEVICE_MODE_ADDR, 4) )
    {
        print("failed to read DFU_MODE_ADDR\n");
        Response->Status = DFU_STATUS_FAILURE;
        return;
    }

    mode = (uint32*)DfuMalBuffer;

    if( *mode != DFU_MODE_UPDATE )
    {
        print("Error: attempting to update while not in update mode\n");
        Response->Status = DFU_STATUS_NOT_IN_UPDATE_MODE;
        return;
    }

    InitializeDataMembers();

    sectionsRemaining = Cmd->SectionsCount;


    Response->Status = DFU_STATUS_SUCCESS;

    print("ActionBeginUpdate: section count: %d\n", sectionsRemaining);

}


/******************************************************************************/
PROTECTED void DfuActionStartSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
    sectionsRemaining--;

    if(sectionsRemaining < 0)
    {
        Response->Status = DFU_STATUS_SECTION_OVERFLOW;
        print("ActionStartSectionUpdate: DFU_STATUS_SECTION_OVERFLOW\n");
        InitializeDataMembers();
    }
    else if( !DfuMalErase(Cmd->StartAddress, Cmd->Length) )
    {
        Response->Status = DFU_STATUS_INTERNAL_FLASH_ERASE_ERROR;
        print("ActionStartSectionUpdate: DFU_STATUS_INTERNAL_FLASH_ERASE_ERROR: Addr: %X, Length: %d\n",
        		Cmd->StartAddress, Cmd->Length);
        InitializeDataMembers();
    }
    else
    {
        writeAddress = sectionStartAddress = Cmd->StartAddress;
        sectionSize = Cmd->Length;


        Response->Status = DFU_STATUS_SUCCESS;

        print("ActionStartSectionUpdate: Start Address: %X, Size: %d\n", writeAddress, sectionSize);
    }

}


/******************************************************************************/
PROTECTED void DfuActionSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{

    writeAddress += Cmd->Offset;
    writeSize = Cmd->Length;

    if(IS_DATA_OVERFLOW()){
        print("ActionSectionUpdate: Error data overflow\n");
        Response->Status = DFU_STATUS_SECTION_DATA_OVERFLOW;
        InitializeDataMembers();
    }
    else
    {
        DfuMalWriteEnabled = TRUE;
        Response->Status = DFU_STATUS_SUCCESS;
        print("ActionSectionUpdate: writeAddress: %08X, size: %d\n", writeAddress, writeSize);
    }

}


/******************************************************************************/
PROTECTED void DfuActionWriteSectionChunk(DFU_Response *Response, uint32 BufferSize)
{

    if(BufferSize >= writeSize)
    {
        // write length bytes to writeAddress of destination here
        if( !DfuMalWrite(writeAddress, writeSize) )
        {
            print("ActionWriteSectionChunk: failed to write %d bytes to %08X\n", writeSize, writeAddress);
            Response->Status = DFU_STATUS_INTERNAL_FLASH_WRITE_ERROR;
        }
        else
        {
            print("ActionWriteSectionChunk: wrote %d bytes to %08X\n", writeSize, writeAddress);
            Response->Status = DFU_STATUS_SUCCESS;
        }


        DfuMalWriteEnabled = FALSE;
        DfuComSendResponse();
    }

}


/******************************************************************************/
PROTECTED void DfuActionEndSectionUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
    Response->Status = DFU_STATUS_SUCCESS;

    print("ActionEndSectionUpdate\n");

}


/******************************************************************************/
PROTECTED void DfuActionEndUpdate(DFU_Command *Cmd, DFU_Response *Response)
{
    Response->Status = DFU_STATUS_SUCCESS;

    print("ActionEndUpdate\n");

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

PRIVATE void InitializeDataMembers( void )
{
    sectionStartAddress = 0;
    sectionsRemaining = 0;
    sectionSize = 0;
    DfuMalWriteEnabled = FALSE;
    writeSize = 0;
    writeAddress = 0;
}
