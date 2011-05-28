/*!
 * \file packet_mgr_types.h
 *
 * \brief 
 *
 *
 * \date Apr 2, 2011
 * \author Dan Riedler
 *
 */

#ifndef _PACKET_MGR_TYPES_H_
#define _PACKET_MGR_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "xml/lib_xml.h"
#include "os.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define PACKET_MGR_INPUT_BUFFER_SIZE 1024
#define PACKET_MGR_INPUT_MAX_PACKETS 10

#define PACKET_MGR_OUTPUT_BUFFER_SIZE 1024
#define PACKET_MGR_OUTPUT_MAX_PACKETS 10


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef void (PACKET_MGR_ListenerCallback)(pLIB_XML_Tag PacketData, uint32 PacketId);
PUBLIC typedef void (*pPACKET_MGR_ListenerCallback)(pLIB_XML_Tag PacketData, uint32 PacketId);


PROTECTED typedef struct {
    uint32 StartIndex;
    uint32 EndIndex;
    uint32 Id;
} PacketMgrPacketInfo;

PROTECTED typedef struct {
    uint8 Buffer[PACKET_MGR_INPUT_BUFFER_SIZE];
    uint32 BytesUsed;
    uint32 FirstFreeIndex;
    uint32 PacketsAvailable;
    uint32 NextPacketIndex;
    uint32 FirstPacketIndex;
    PacketMgrPacketInfo PacketInfo[PACKET_MGR_INPUT_MAX_PACKETS];
    OS_Semaphore Mutex;
} PacketMgrInputBufferInfo;


PROTECTED typedef struct {
    uint8 Buffer[PACKET_MGR_OUTPUT_BUFFER_SIZE];
    uint32 BytesUsed;
    uint32 FirstFreeIndex;
    uint32 PacketsAvailable;
    uint32 NextPacketIndex;
    uint32 FirstPacketIndex;
    PacketMgrPacketInfo PacketInfo[PACKET_MGR_OUTPUT_MAX_PACKETS];
    OS_Semaphore Mutex;
} PacketMgrOutputBufferInfo;


PROTECTED typedef struct {
    char Tag[LIB_XML_MAX_TAG_LEN];
    pPACKET_MGR_ListenerCallback CallBack;
} PacketMgrTagListenerInfo, *pPacketMgrTagListenerInfo;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* PACKET_MGR_TYPES_H_ */
