/*!
 * \file lib_array_list.h
 *
 * \brief 
 *
 *
 * \date Mar 8, 2011
 * \author Dan Riedler
 *
 */

#ifndef _LIB_ARRAY_LIST_H_
#define _LIB_ARRAY_LIST_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define LIB_ARRAY_LIST_INCREASE_AMOUNT 10

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef void* LIB_ARRAY_LIST_Item;
PUBLIC typedef LIB_ARRAY_LIST_Item* pLIB_ARRAY_LIST_Item;

PUBLIC typedef struct {
    LIB_ARRAY_LIST_Item Items;
    uint32 ItemCount;
    uint32 ItemSize;
    uint32 Capacity;
} LIB_ARRAY_LIST_List, *pLIB_ARRAY_LIST_List;


PUBLIC typedef struct {
    pLIB_ARRAY_LIST_List List;
    uint32 CurrentPosition;
} LIB_ARRAY_LIST_Iterator, *pLIB_ARRAY_LIST_Iterator;
/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PUBLIC pLIB_ARRAY_LIST_List LIB_ARRAY_LIST_CreateList( uint32 ItemSize, uint32 InitialCapacity );

PUBLIC int32 LIB_ARRAY_LIST_AddItem( pLIB_ARRAY_LIST_List List, pVoid Item);

PUBLIC int32 LIB_ARRAY_LIST_AddItemAtPosition( pLIB_ARRAY_LIST_List List, pLIB_ARRAY_LIST_Item Item, uint32 Position);

PUBLIC bool LIB_ARRAY_LIST_RemoveItem( pLIB_ARRAY_LIST_List List);

PUBLIC bool LIB_ARRAY_LIST_RemoveItemAtPosition( pLIB_ARRAY_LIST_List List, uint32 Position);

PUBLIC pLIB_ARRAY_LIST_Item LIB_ARRAY_LIST_GetItemAtPosition( pLIB_ARRAY_LIST_List List, uint32 Position);

PUBLIC void LIB_ARRAY_LIST_ClearList( pLIB_ARRAY_LIST_List List );

PUBLIC void LIB_ARRAY_LIST_DestroyList( pLIB_ARRAY_LIST_List List );

PUBLIC uint32 LIB_ARRAY_LIST_ListSize( pLIB_ARRAY_LIST_List List );

PUBLIC bool LIB_ARRAY_LIST_IteratorInit( pLIB_ARRAY_LIST_List List, pLIB_ARRAY_LIST_Iterator Iterator );

PUBLIC bool LIB_ARRAY_LIST_IteratorHasNext( pLIB_ARRAY_LIST_Iterator );

PUBLIC pLIB_ARRAY_LIST_Item LIB_ARRAY_LIST_IteratorNext( pLIB_ARRAY_LIST_Iterator );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* LIB_ARRAY_LIST_H_ */
