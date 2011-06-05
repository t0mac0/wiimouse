/*!
 * \file packet_mgr.c
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
#include <string.h>

#include "packet_mgr.h"
#include "task/packet_mgr_task.h"
#include "os.h"
#include "composite_usb.h"

#include "util/xml/lib_xml.h"
#include "util/list/lib_array_list.h"




#include "flash/hw_flash.h"
#include "int/hw_int.h"


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
PRIVATE COMPOSITE_USB_ReadVirComCallBack VirComReadCallback;
PRIVATE inline void AddTag(CString Tag, bool isStartTag);


/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/
PROTECTED PacketMgrInputBufferInfo packetMgrInputBuffer;
PROTECTED PacketMgrOutputBufferInfo packetMgrOutputBuffer;

PROTECTED pLIB_ARRAY_LIST_List packetMgrTagListenerList;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//****************************************************************************/
PUBLIC Result PACKET_MGR_Init( void )
{
    Result result = PACKET_MGR_RESULT(SUCCESS);

    LOG_Printf("Initializing Packet Mgr component\n");

    ZeroMemory(&packetMgrInputBuffer, sizeof(PacketMgrInputBufferInfo));
    ZeroMemory(&packetMgrOutputBuffer, sizeof(PacketMgrOutputBufferInfo));
    SetMemory(&packetMgrInputBuffer.PacketInfo, PACKET_NULL_INDEX, sizeof(PacketMgrPacketInfo)*PACKET_MGR_INPUT_MAX_PACKETS);

    packetMgrTagListenerList = NULL;


    if( RESULT_IS_ERROR(result, OS_CREATE_MUTEX(&packetMgrInputBuffer.Mutex)) )
    {
        LOG_Printf("Failed to create read buffer mutex\n");
    }
    else if( RESULT_IS_ERROR(result, OS_CREATE_MUTEX(&packetMgrOutputBuffer.Mutex)) )
    {
        LOG_Printf("Failed to create write buffer mutex\n");
    }
    else if( RESULT_IS_ERROR(result, COMPOSITE_USB_RegisterReadVirComCallback(VirComReadCallback)) )
    {
        LOG_Printf("Failed to register virtual com read callback\n");
    }
    else if( RESULT_IS_ERROR(result, PacketMgrCreateTask()) )
    {
        LOG_Printf("Failed to create the packet mgr task\n");
    }
    else if( (packetMgrTagListenerList = LIB_ARRAY_LIST_CreateList(sizeof(PacketMgrTagListenerInfo), 1)) == NULL )
    {
        result = PACKET_MGR_RESULT(CREATE_LIS_LIST_FAIL);
        LOG_Printf("Failed to create array list\n");
    }

    return result;
}


//****************************************************************************/
PUBLIC Result PACKET_MGR_PowerUp( void )
{
    Result result = PACKET_MGR_RESULT_INIT();

    return result;
}


//****************************************************************************/
PUBLIC Result PACKET_MGR_PowerDown( void )
{
    Result result = PACKET_MGR_RESULT_INIT();

    return result;
}


//****************************************************************************/
PUBLIC Result PACKET_MGR_AddPacket(pLIB_XML_Tag PacketData, uint32 PacketId)
{
    Result result = PACKET_MGR_RESULT(SUCCESS);
    uint32 packetSize, dataSize, pi, byteCount;

    dataSize = strnlen(PacketData->Data, PACKET_MGR_OUTPUT_BUFFER_SIZE);
    packetSize = strnlen(PacketData->Tag, LIB_XML_MAX_TAG_LEN)*2 + 5 + dataSize;
    pi = packetMgrOutputBuffer.NextPacketIndex;


    OS_TAKE_MUTEX(packetMgrOutputBuffer.Mutex);


    if( (packetMgrOutputBuffer.BytesUsed + packetSize <= PACKET_MGR_OUTPUT_BUFFER_SIZE) &&
            (packetMgrOutputBuffer.PacketsAvailable < PACKET_MGR_OUTPUT_MAX_PACKETS))
    {
        packetMgrOutputBuffer.PacketInfo[pi].StartIndex = packetMgrOutputBuffer.FirstFreeIndex;

        AddTag(PacketData->Tag, TRUE);

        if( packetMgrOutputBuffer.FirstFreeIndex + dataSize <= PACKET_MGR_OUTPUT_BUFFER_SIZE )
        {
            CopyMemory(&packetMgrOutputBuffer.Buffer[packetMgrOutputBuffer.FirstFreeIndex], PacketData->Data, dataSize);
        }
        else
        {
            byteCount = PACKET_MGR_OUTPUT_BUFFER_SIZE - packetMgrOutputBuffer.FirstFreeIndex;
            CopyMemory(&packetMgrOutputBuffer.Buffer[packetMgrOutputBuffer.FirstFreeIndex], PacketData->Data, byteCount);

            packetMgrOutputBuffer.FirstFreeIndex = dataSize - byteCount;
            CopyMemory(packetMgrOutputBuffer.Buffer, &((uint8*)PacketData->Data)[byteCount], packetMgrOutputBuffer.FirstFreeIndex);
        }

        AddTag(PacketData->Tag, FALSE);

        packetMgrOutputBuffer.PacketInfo[pi].Id = PacketId;
        packetMgrOutputBuffer.PacketInfo[pi].EndIndex = packetMgrOutputBuffer.FirstFreeIndex;
        packetMgrOutputBuffer.NextPacketIndex = (packetMgrOutputBuffer.NextPacketIndex+1)%PACKET_MGR_OUTPUT_MAX_PACKETS;
        packetMgrOutputBuffer.BytesUsed += packetSize;
    }
    else
    {
        result = PACKET_MGR_RESULT(OUT_BUF_FULL);
        LOG_Printf("Warning: PacketMgr Input Buffer Full\n");
    }

    OS_GIVE_MUTEX(packetMgrOutputBuffer.Mutex);


    return result;
}


//****************************************************************************/
PUBLIC Result PACKET_MGR_RegisterListener(CString Tag, pPACKET_MGR_ListenerCallback CallBack){
    Result result = PACKET_MGR_RESULT(SUCCESS);

    PacketMgrTagListenerInfo listenerInfo;

    CopyMemory(listenerInfo.Tag, (void*)Tag, LIB_XML_MAX_TAG_LEN);
    listenerInfo.CallBack = CallBack;

    if( LIB_ARRAY_LIST_AddItem(packetMgrTagListenerList, &listenerInfo) < 0 )
    {
        result = PACKET_MGR_RESULT(ADD_LISTENER_FAIL);
        LOG_Printf("Failed to add listener\n");
    }

    return result;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


//*****************************************************************************//
PRIVATE void VirComReadCallback(uint8 *Buffer, uint32 SizeBytes)
{
	// REVISIT: for testing only
	UNUSED(Buffer);
	UNUSED(SizeBytes);
	LOG_Printf("Going back too bootloader mode\n");

	HW_FLASH_ErasePages(DEVICE_START_ADDR, 2);
	HW_INT_SystemReset();

//    uint32 nextFreeIndex;
//    uint32 packetId, byteCount, pi;
//
//    // TODO: this should probably have a timeout
//    OS_TAKE_MUTEX(packetMgrInputBuffer.Mutex);
//
//    pi = packetMgrInputBuffer.NextPacketIndex;
//
//    if( packetMgrInputBuffer.BytesUsed + SizeBytes <= PACKET_MGR_INPUT_BUFFER_SIZE )
//    {
//        if( sscanf((char*)Buffer, PACKET_START_TAG, (unsigned int*)&packetId) == 1 )
//        {
//            if( packetMgrInputBuffer.PacketsAvailable < PACKET_MGR_INPUT_MAX_PACKETS )
//            {
//                packetMgrInputBuffer.PacketInfo[pi].StartIndex = packetMgrInputBuffer.FirstFreeIndex;
//                packetMgrInputBuffer.PacketInfo[pi].Id = packetId;
//            }
//            else
//            {
//                LOG_Printf("Warning: PacketMgr Input Buffer Full\n");
//            }
//        }
//        else if( strncmp((char*)Buffer, PACKET_END_TAG, PACKET_END_TAG_LEN) == 0 )
//        {
//            if( packetMgrInputBuffer.PacketInfo[pi].StartIndex != PACKET_NULL_INDEX )
//            {
//                packetMgrInputBuffer.PacketInfo[pi].EndIndex = packetMgrInputBuffer.FirstFreeIndex;
//                packetMgrInputBuffer.PacketsAvailable++;
//                packetMgrInputBuffer.NextPacketIndex = (packetMgrInputBuffer.NextPacketIndex+1)%PACKET_MGR_INPUT_MAX_PACKETS;
//            }
//            else
//            {
//                LOG_Printf("Warning: Received end packet tag without start tag\n");
//            }
//        }
//        else
//        {
//            nextFreeIndex = (packetMgrInputBuffer.FirstFreeIndex + SizeBytes) % PACKET_MGR_INPUT_BUFFER_SIZE;
//
//
//            if( packetMgrInputBuffer.FirstFreeIndex + SizeBytes <= PACKET_MGR_INPUT_BUFFER_SIZE )
//            {
//                CopyMemory(&packetMgrInputBuffer.Buffer[packetMgrInputBuffer.FirstFreeIndex], Buffer, SizeBytes);
//            }
//            else
//            {
//                byteCount =  PACKET_MGR_INPUT_BUFFER_SIZE - packetMgrInputBuffer.FirstFreeIndex;
//
//                CopyMemory(&packetMgrInputBuffer.Buffer[packetMgrInputBuffer.FirstFreeIndex], Buffer, byteCount);
//                CopyMemory(packetMgrInputBuffer.Buffer, &Buffer[byteCount], nextFreeIndex);
//            }
//
//            packetMgrInputBuffer.FirstFreeIndex = nextFreeIndex;
//            packetMgrInputBuffer.BytesUsed += SizeBytes;
//        }
//    }
//    else
//    {
//        LOG_Printf("Warning: PacketMgr Input Buffer Full\n");
//    }
//
//    OS_GIVE_MUTEX(packetMgrInputBuffer.Mutex);
}



//****************************************************************************/
PRIVATE inline void AddTag(CString Tag, bool isStartTag)
{
    uint32 i, index, len;
    char tag[LIB_XML_MAX_TAG_LEN+3];

    if( isStartTag )
    {
        strcpy(tag, "<");
    }
    else
    {
        strcpy(tag, "</");
    }
    strcat(tag, Tag);
    strcat(tag, ">");

    len = strlen(tag);
    index = packetMgrOutputBuffer.FirstFreeIndex;

    for(i = 0; i < len; i++)
    {
        packetMgrOutputBuffer.Buffer[index++] = tag[i];

        if( index == PACKET_MGR_OUTPUT_BUFFER_SIZE )
            index = 0;
    }

    packetMgrOutputBuffer.FirstFreeIndex = index;
}




