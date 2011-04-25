/*!
 * \file dfu_sm_action_validate.c
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
#define IS_DATA_OVERFLOW()( ((readAddress - sectionStartAddress) + readSize) > sectionSize )

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
PRIVATE __inline void UpdateCheckSum( uint32 *buffer, uint32 size );


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/

PRIVATE uint32 sectionStartAddress;
PRIVATE uint32 sectionsRemaining;
PRIVATE uint32 sectionSize;
PRIVATE uint32 readSize;
PRIVATE uint32 readAddress;

PRIVATE uint32 checkSum;



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/******************************************************************************/
PROTECTED void DfuActionBeginValidation(DFU_Command *Cmd, DFU_Response *Response)
{
    InitializeDataMembers();

    sectionsRemaining = Cmd->SectionsCount;

    Response->Status = DFU_STATUS_SUCCESS;

    print("ActionBeginValidation: section count: %d\n", sectionsRemaining);

}


/******************************************************************************/
PROTECTED void DfuActionStartSectionValidation(DFU_Command *Cmd, DFU_Response *Response)
{
    sectionsRemaining--;

    if(sectionsRemaining < 0)
    {
        Response->Status = DFU_STATUS_SECTION_OVERFLOW;
        print("ActionStartSectionValidation: DFU_STATUS_SECTION_OVERFLOW\n");
        InitializeDataMembers();
    }
    else
    {
        readAddress = sectionStartAddress = Cmd->StartAddress;
        sectionSize = Cmd->Length;
        Response->Status = DFU_STATUS_SUCCESS;

        print("ActionStartSectionValidation: size: %d\n", sectionSize);
    }

}


/******************************************************************************/
PROTECTED void DfuActionSectionValidate(DFU_Command *Cmd, DFU_Response *Response)
{

    readAddress += Cmd->Offset;
    readSize = Cmd->Length;

    if(IS_DATA_OVERFLOW()){
        print("ActionSectionValidation: Error data overflow\n");
        Response->Status = DFU_STATUS_SECTION_DATA_OVERFLOW;
        InitializeDataMembers();
    }
    else
    {
        DfuMalReadEnabled = TRUE;
        Response->Status = DFU_STATUS_SUCCESS;
        print("ActionSectionValidation: readAddress: %08X, size: %d\n", readAddress, readSize);
    }

}


/******************************************************************************/
PROTECTED void DfuActionReadSectionChunk(uint32 *BytesRead)
{
//  uint32 byteRead, i;

    // read length bytes to readAddress of destination here
    if( !DfuMalRead(readAddress, readSize) )
    {
        print("ActionReadSectionChunk: failed to read %d bytes from %08X\n", readSize, readAddress);
    }
    else
    {
        print("ActionReadSectionChunk: read %d bytes from %08X\n", readSize, readAddress);
    }


//  printf("After:\n");
//  for(i=48; i >= 48 && i < 72; i++)
//      printf("%X ", DFU_MalBuffer[i]);
//  printf("\n");

    //UpdateCheckSum((uint32*)Response, readSize/4);
    DfuMalReadEnabled = FALSE;

    DfuComSendData(readSize);

    *BytesRead = readSize;
}


/******************************************************************************/
PROTECTED void DfuActionEndSectionValidation(DFU_Command *Cmd, DFU_Response *Response)
{
    Response->Checksum = checkSum;
    Response->Status = DFU_STATUS_SUCCESS;

    print("ActionEndSectionValidation\n");


}


/******************************************************************************/
PROTECTED void DfuActionEndValidation(DFU_Command *Cmd, DFU_Response *Response)
{
    Response->Status = DFU_STATUS_SUCCESS;

    print("ActionEndValidation\n");

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


/******************************************************************************/
PRIVATE void InitializeDataMembers( void )
{
    sectionStartAddress = 0;
    sectionsRemaining = 0;
    sectionSize = 0;
    DfuMalReadEnabled = FALSE;
    readSize = 0;
    readAddress = 0;
    checkSum = 0;
}


/******************************************************************************/
PRIVATE __inline void UpdateCheckSum( uint32 *buffer, uint32 size )
{
    uint32 i;

    for( i = 0; i < size; i++)
    {
        checkSum += buffer[i];
    }
}
