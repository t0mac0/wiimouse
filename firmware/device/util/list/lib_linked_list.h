/*!
 * \file lib_linked_list.h
 *
 * \brief 
 *
 *
 * \date Mar 8, 2011
 * \author Dan Riedler
 *
 */

#ifndef _LIB_LINKED_LIST_H_
#define _LIB_LINKED_LIST_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef struct {
    pVoid NextItem;
    pVoid Data;
    uint32 Size;
} LIB_LINKED_LIST_Item, *pLIB_LINKED_LIST_Item;


PUBLIC typedef struct {
    pLIB_LINKED_LIST_Item Head;
    pLIB_LINKED_LIST_Item Tail;
    uint32 ItemCount;
} LIB_LINKED_LIST_List, *pLIB_LINKED_LIST_List;


PUBLIC typedef struct {
    pLIB_LINKED_LIST_List List;
    uint32 CurrentPosition;
} LIB_LINKED_LIST_Iterator, *pLIB_LINKED_LIST_Iterator;
/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PUBLIC pLIB_LINKED_LIST_List LIB_LINKED_LIST_CreateList( void );

PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_CreateItem( pVoid Data, uint32 Size);

PUBLIC int32 LIB_LINKED_LIST_AddNewItem( pLIB_LINKED_LIST_List List, pVoid Data, uint32 Size);

PUBLIC int32 LIB_LINKED_LIST_AddItem( pLIB_LINKED_LIST_List List, pLIB_LINKED_LIST_Item Item);

PUBLIC int32 LIB_LINKED_LIST_AddItemAtPosition( pLIB_LINKED_LIST_List List, pLIB_LINKED_LIST_Item Item, uint32 Position);

PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_RemoveItem( pLIB_LINKED_LIST_List List);

PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_RemoveItemAtPosition( pLIB_LINKED_LIST_List List, uint32 Position);

PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_GetItemAtPosition( pLIB_LINKED_LIST_List List, uint32 Position);

PUBLIC void LIB_LINKED_LIST_ClearList( pLIB_LINKED_LIST_List List );

PUBLIC void LIB_LINKED_LIST_DestroyItem( pLIB_LINKED_LIST_Item Item);

PUBLIC void LIB_LINKED_LIST_DestroyList( pLIB_LINKED_LIST_List List );

PUBLIC uint32 LIB_LINKED_LIST_ListSize( pLIB_LINKED_LIST_List List );

PUBLIC bool LIB_LINKED_LIST_IteratorInit( pLIB_LINKED_LIST_List List, pLIB_LINKED_LIST_Iterator Iterator );

PUBLIC bool LIB_LINKED_LIST_IteratorHasNext( pLIB_LINKED_LIST_Iterator );

PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_IteratorNext( pLIB_LINKED_LIST_Iterator );

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* LIB_LINKED_LIST_H_ */
