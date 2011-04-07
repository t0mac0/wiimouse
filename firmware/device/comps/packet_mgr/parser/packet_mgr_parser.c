/*!
 * \file packet_mgr_parser.c
 *
 * \brief 
 *
 *
 * \date Apr 2, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <stdio.h>

#include "packet_mgr_parser.h"


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
PROTECTED extern PacketMgrInputBufferInfo packetMgrInputBuffer;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//****************************************************************************/
PROTECTED Result PacketMgrParsePacket(pLIB_XML_Tag *Tag, uint32 *PacketId)
{
    Result result = PACKET_MGR_RESULT(SUCCESS);
    uint32 packetSizeBytes;
    uint32 pi;
    pLIB_XML_Tag tag;

    tag = *Tag;
    pi = packetMgrInputBuffer.FirstPacketIndex;

    if( packetMgrInputBuffer.PacketInfo[pi].StartIndex < packetMgrInputBuffer.PacketInfo[pi].EndIndex )
    {
        packetSizeBytes = packetMgrInputBuffer.PacketInfo[pi].EndIndex - packetMgrInputBuffer.PacketInfo[pi].StartIndex;
    }
    else
    {
        packetSizeBytes = PACKET_MGR_INPUT_BUFFER_SIZE - packetMgrInputBuffer.PacketInfo[pi].StartIndex + packetMgrInputBuffer.PacketInfo[pi].EndIndex;
    }


    if( (tag = (pLIB_XML_Tag) AllocMemory(sizeof(LIB_XML_Tag) + packetSizeBytes)) == NULL )
    {
        result = PACKET_MGR_RESULT(MEM_ALLOC_FAIL);
    }
    else
    {
        tag->Data = (uint8*)tag + sizeof(LIB_XML_Tag);
        tag->ChildCount = 1;
        *PacketId = packetMgrInputBuffer.PacketInfo[pi].Id;

        if( packetMgrInputBuffer.PacketInfo[pi].StartIndex < packetMgrInputBuffer.PacketInfo[pi].EndIndex )
        {
            CopyMemory(tag->Data, &packetMgrInputBuffer.Buffer[packetMgrInputBuffer.PacketInfo[pi].StartIndex], packetSizeBytes);
        }
        else
        {
            packetSizeBytes = PACKET_MGR_INPUT_BUFFER_SIZE - packetMgrInputBuffer.PacketInfo[pi].StartIndex;

            CopyMemory(tag->Data, &packetMgrInputBuffer.Buffer[packetMgrInputBuffer.PacketInfo[pi].StartIndex], packetSizeBytes);
            CopyMemory(&((uint8*)tag->Data)[packetSizeBytes], packetMgrInputBuffer.Buffer, packetMgrInputBuffer.PacketInfo[pi].EndIndex);
        }

        if( sscanf(tag->Data, "<%s>", tag->Tag) != 1 )
        {
            result = PACKET_MGR_RESULT(BAD_PACKET);
        }
    }

    SetMemory(&packetMgrInputBuffer.PacketInfo[pi], PACKET_NULL_INDEX, sizeof(PacketMgrPacketInfo));
    packetMgrInputBuffer.FirstPacketIndex = (packetMgrInputBuffer.FirstPacketIndex+1)/PACKET_MGR_INPUT_MAX_PACKETS;
    packetMgrInputBuffer.PacketsAvailable--;
    packetMgrInputBuffer.BytesUsed -= packetSizeBytes;

    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

