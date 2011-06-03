/*!
 * \file packet_mgr_task.c
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
#include <string.h>
#include <stdio.h>

#include "os.h"
#include "util/xml/lib_xml.h"
#include "util/list/lib_array_list.h"

#include "composite_usb/composite_usb.h"

#include "packet_mgr_task.h"
#include "packet_mgr/parser/packet_mgr_parser.h"


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
PRIVATE OS_TaskProtoType PacketProcessorTask;
PRIVATE inline void ProcessInputPackets( void );
PRIVATE inline void ProcessOutputPackets( void );
PRIVATE bool WritePacketTag(bool IsStartTag, uint32 PacketId);


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED extern PacketMgrInputBufferInfo packetMgrInputBuffer;
PROTECTED extern PacketMgrOutputBufferInfo packetMgrOutputBuffer;
PROTECTED extern pLIB_ARRAY_LIST_List packetMgrTagListenerList;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************
PROTECTED Result PacketMgrCreateTask( void )
{
    Result result;

    if( RESULT_IS_ERROR(result, OS_TASK_MGR_Add(OS_TASK_PACKET_MGR,
                                                    PACKET_MGR_TASK_NAME,
                                                    PacketProcessorTask,
                                                    PACKET_MGR_STACK_SIZE,
                                                    PACKET_MGR_TASK_PRIORITY,
                                                    NULL,
                                                    NULL)) )
    {
        LOG_Printf("Failed to create the packet mgr task\n");
    }


    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


//*****************************************************************************//
PRIVATE void PacketProcessorTask(void *Params)
{
	LOG_Printf("Starting PacketProcessorTask\n");

    UNUSED(Params);

    for(;;)
    {
    	// TODO: this gets its own task
        ProcessInputPackets();
        // TODO: this gets its own task
        ProcessOutputPackets();
    }
}


//*****************************************************************************//
PRIVATE inline void ProcessInputPackets( void )
{
    Result result;
    LIB_ARRAY_LIST_Iterator iterator;
    pPacketMgrTagListenerInfo listener;
    pLIB_XML_Tag tag;
    uint32 packetId;

    tag = NULL;
    packetId = 0;

    OS_TAKE_MUTEX(packetMgrInputBuffer.Mutex);

    // TODO: should be a semaphore
    if( packetMgrInputBuffer.PacketsAvailable > 0 )
    {
        if( RESULT_IS_SUCCESS(result, PacketMgrParsePacket(&tag, &packetId)) )
        {
            if( LIB_ARRAY_LIST_IteratorInit(packetMgrTagListenerList, &iterator) )
            {
                while( LIB_ARRAY_LIST_IteratorHasNext(&iterator) )
                {
                    listener = (pPacketMgrTagListenerInfo) LIB_ARRAY_LIST_IteratorNext(&iterator);

                    if( strncmp(listener->Tag, tag->Tag, LIB_XML_MAX_TAG_LEN) == 0 )
                    {
                        listener->CallBack(tag, packetId);
                    }
                }
            }
        }
    }

    OS_GIVE_MUTEX(packetMgrInputBuffer.Mutex);
}


//*****************************************************************************//
PRIVATE inline void ProcessOutputPackets( void )
{
    Result result;
    uint32 pi, byteSize;


    OS_TAKE_MUTEX(packetMgrOutputBuffer.Mutex);

    pi = packetMgrOutputBuffer.FirstPacketIndex;

    // TODO: should be a semaphore
    if( packetMgrOutputBuffer.PacketsAvailable > 0 )
    {
        WritePacketTag(TRUE, packetMgrOutputBuffer.PacketInfo[pi].Id);

        if( RESULT_IS_ERROR(result, COMPOSITE_USB_WriteVirCom(packetMgrOutputBuffer.Buffer,
                                                              packetMgrOutputBuffer.PacketInfo[pi].StartIndex,
                                                              packetMgrOutputBuffer.PacketInfo[pi].EndIndex,
                                                              PACKET_MGR_OUTPUT_BUFFER_SIZE)) )
        {
        }

        if( packetMgrOutputBuffer.PacketInfo[pi].StartIndex < packetMgrOutputBuffer.PacketInfo[pi].EndIndex )
        {
            byteSize = packetMgrOutputBuffer.PacketInfo[pi].EndIndex - packetMgrOutputBuffer.PacketInfo[pi].StartIndex;
        }
        else
        {
            byteSize = PACKET_MGR_OUTPUT_BUFFER_SIZE - packetMgrOutputBuffer.PacketInfo[pi].StartIndex + packetMgrOutputBuffer.PacketInfo[pi].EndIndex;
        }

        WritePacketTag(FALSE, 0);

        packetMgrOutputBuffer.PacketsAvailable--;
        packetMgrOutputBuffer.FirstPacketIndex = (packetMgrOutputBuffer.FirstPacketIndex+1)%PACKET_MGR_OUTPUT_MAX_PACKETS;
        packetMgrOutputBuffer.BytesUsed -= byteSize;

    }


    OS_GIVE_MUTEX(packetMgrOutputBuffer.Mutex);
}


//*****************************************************************************//
PRIVATE bool WritePacketTag(bool IsStartTag, uint32 PacketId)
{
    Result result;
    bool success = TRUE;
    char tag[24];
    uint32 len;


    if( IsStartTag )
    {
        if( sprintf(tag, PACKET_START_TAG, (unsigned int)PacketId) < 0 )
        {
            return FALSE;
        }
    }
    else
    {
        strcpy(tag, PACKET_END_TAG);
    }

    len = strlen(tag);

    if( RESULT_IS_ERROR(result, COMPOSITE_USB_WriteVirCom(tag, 0, len, 0)) )
    {
        success = FALSE;
    }


    return success;
}





