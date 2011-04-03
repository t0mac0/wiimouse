/*!
 * \file packet_mgr.h
 *
 * \brief 
 *
 *
 * \date Apr 2, 2011
 * \author Dan Riedler
 *
 */

#ifndef _PACKET_MGR_H_
#define _PACKET_MGR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "comps.h"
#include "xml/lib_xml.h"
#include "packet_mgr_types.h"
#include "packet_mgr_result.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

#define PACKET_START_TAG "<packet id=\"%u\">"
#define PACKET_END_TAG "</packet>"
#define PACKET_END_TAG_LEN 9

#define PACKET_NULL_INDEX 0xFFFFFFFF




/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PUBLIC ModuleInitPrototype PACKET_MGR_Init;

PUBLIC ModulePowerUpPrototype PACKET_MGR_PowerUp;

PUBLIC ModulePowerDownPrototype PACKET_MGR_PowerDown;

PUBLIC Result PACKET_MGR_AddPacket(pLIB_XML_Tag PacketData, uint32 PacketId);

PUBLIC Result PACKET_MGR_RegisterListener(CString Tag, pPACKET_MGR_ListenerCallback CallBack);



/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* PACKET_MGR_H_ */
