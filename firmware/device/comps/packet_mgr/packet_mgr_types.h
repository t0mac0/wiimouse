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

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef void (PACKET_MGR_ListenerCallback)(pLIB_XML_Tag PacketData, uint32 PacketId);
PUBLIC typedef void (*pPACKET_MGR_ListenerCallback)(pLIB_XML_Tag PacketData, uint32 PacketId);

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* PACKET_MGR_TYPES_H_ */