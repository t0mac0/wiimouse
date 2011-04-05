/*!
 * \file lib_xml.h
 *
 * \brief 
 *
 *
 * \date Apr 2, 2011
 * \author Dan Riedler
 *
 */

#ifndef _LIB_XML_H_
#define _LIB_XML_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define LIB_XML_MAX_TAG_LEN 16

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/


PUBLIC typedef struct {
    char Tag[LIB_XML_MAX_TAG_LEN];
    void *Data;
    uint32 ChildCount;
} LIB_XML_Tag, *pLIB_XML_Tag;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PUBLIC extern bool LIB_XML_ParseUint32(pLIB_XML_Tag Tag, uint32 *Val);
PUBLIC extern bool LIB_XML_AddUint32(pLIB_XML_Tag Tag, uint32 Val);

PUBLIC extern bool LIB_XML_ParseBool(pLIB_XML_Tag Tag, bool *Val);
PUBLIC extern bool LIB_XML_AddBool(pLIB_XML_Tag Tag, bool Val);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* LIB_XML_H_ */
