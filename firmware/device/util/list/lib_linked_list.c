/*!
 * \file lib_linked_list.c
 *
 * \brief 
 *
 *
 * \date Mar 8, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "lib_linked_list.h"

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


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//*****************************************************************************//
PUBLIC pLIB_LINKED_LIST_List LIB_LINKED_LIST_CreateList( void )
{
    pLIB_LINKED_LIST_List list = NULL;

    if( (list = (pLIB_LINKED_LIST_List) AllocMemory(sizeof(LIB_LINKED_LIST_List))) != NULL )
    {
        list->Head = NULL;
        list->Tail = NULL;
        list->ItemCount = 0;
    }

    return list;
}


//*****************************************************************************//
PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_CreateItem( pVoid Data, uint32 Size)
{
    pLIB_LINKED_LIST_Item item = NULL;

    if( Data == NULL )
    {
        return NULL;
    }
    else if( (item = AllocMemory(sizeof(LIB_LINKED_LIST_Item) + Size)) != NULL )
    {
        item->Data = (pVoid)(item + sizeof(LIB_LINKED_LIST_Item));
        item->Size = Size;
        item->NextItem = NULL;
        CopyMemory(item->Data, Data, Size);
    }

    return item;
}


//*****************************************************************************//
PUBLIC int32 LIB_LINKED_LIST_AddNewItem( pLIB_LINKED_LIST_List List, pVoid Data, uint32 Size)
{
    int32 position = -1;
    pLIB_LINKED_LIST_Item item;

    if( (item = LIB_LINKED_LIST_CreateItem(Data, Size)) == NULL )
    {
        return -1;
    }
    else if( (position = LIB_LINKED_LIST_AddItem(List, item)) == -1 )
    {
        LIB_LINKED_LIST_DestroyItem( item);
    }

    return position;
}


//*****************************************************************************//
PUBLIC int32 LIB_LINKED_LIST_AddItem( pLIB_LINKED_LIST_List List, pLIB_LINKED_LIST_Item Item)
{
    int32 position = -1;

    if( List == NULL || Item == NULL )
    {
        return -1;
    }

    if( List->Head == NULL )
    {
        List->Head = Item;
        List->Tail = List->Head;
        List->ItemCount = 1;
        position = 0;
    }
    else
    {
        ASSERT(List->Tail != NULL);
        List->Tail->NextItem = Item;
        List->Tail = Item;
        List->Tail->NextItem = NULL;
        position = List->ItemCount;
        List->ItemCount++;
    }

    return position;
}


//*****************************************************************************//
PUBLIC int32  LIB_LINKED_LIST_AddItemAtPosition( pLIB_LINKED_LIST_List List, pLIB_LINKED_LIST_Item Item, uint32 Position)
{
    int32 position = -1;

    if( List == NULL || Item == NULL || Position > List->ItemCount)
    {
        return -1;
    }

    if( List->Head == NULL )
    {
        List->Head = Item;
        List->Tail = List->Head;
        List->ItemCount = 1;
        position = 0;
    }
    else if( Position == 0 )
    {
        Item->NextItem = List->Head;
        List->Head = Item;
        List->ItemCount++;
        position = 0;
    }
    else
    {
        uint32 i;
        pLIB_LINKED_LIST_Item tmpItem;

        tmpItem = List->Head;

        for( i = 0; i < Position-1; i++ )
        {
            tmpItem = tmpItem->NextItem;
        }

        Item->NextItem = tmpItem->NextItem;
        tmpItem->NextItem = Item;
        position = i+1;
        List->ItemCount++;
    }

    return position;
}


//*****************************************************************************//
PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_RemoveItem( pLIB_LINKED_LIST_List List)
{
    pLIB_LINKED_LIST_Item removedItem;

    if( List == NULL || List->Head == NULL )
        return NULL;

    removedItem = List->Head;
    List->Head = List->Head->NextItem;
    List->ItemCount--;

    return removedItem;
}


//*****************************************************************************//
PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_RemoveItemAtPosition( pLIB_LINKED_LIST_List List, uint32 Position)
{
    pLIB_LINKED_LIST_Item removedItem;

    if( List == NULL || Position >= List->ItemCount)
    {
        return NULL;
    }


    if( Position == 0 )
    {
        removedItem = List->Head;
        List->Head = List->Head->NextItem;
        List->ItemCount--;
    }
    else
    {
        uint32 i;
        pLIB_LINKED_LIST_Item tmpItem;

        tmpItem = List->Head;

        for( i = 0; i < Position-1; i++ )
        {
            tmpItem = tmpItem->NextItem;
        }

        removedItem = tmpItem->NextItem;

        if( removedItem == List->Tail )
        {
            List->Tail = tmpItem;
        }
        else
        {
            tmpItem->NextItem = removedItem->NextItem;
        }

        List->ItemCount--;
    }

    return removedItem;
}


//*****************************************************************************//
PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_GetItemAtPosition( pLIB_LINKED_LIST_List List, uint32 Position)
{
    uint32 i;
    pLIB_LINKED_LIST_Item item;

    if( List == NULL || Position >= List->ItemCount )
        return NULL;

    item = List->Head;

    for( i = 0; i < Position; i++ )
    {
        item = item->NextItem;
    }

    return item;
}


//*****************************************************************************//
PUBLIC void LIB_LINKED_LIST_ClearList( pLIB_LINKED_LIST_List List )
{
    if( List == NULL)
        return;
    else {
        pLIB_LINKED_LIST_Item item, next;

        item = List->Head;

        while( item != NULL )
        {
            next = item->NextItem;
            LIB_LINKED_LIST_DestroyItem(item);
            item = next;
        }

        List->Head = NULL;
        List->Tail = NULL;
        List->ItemCount = 0;
    }
}


//*****************************************************************************//
PUBLIC void LIB_LINKED_LIST_DestroyItem( pLIB_LINKED_LIST_Item Item)
{
    if( Item != NULL )
        FreeMemory(Item);
}


//*****************************************************************************//
PUBLIC void LIB_LINKED_LIST_DestroyList( pLIB_LINKED_LIST_List List )
{
    LIB_LINKED_LIST_ClearList(List);
    FreeMemory(List);
}


//*****************************************************************************//
PUBLIC uint32 LIB_LINKED_LIST_ListSize( pLIB_LINKED_LIST_List List )
{
    if( List == NULL )
        return 0;
    else
        return List->ItemCount;
}


//*****************************************************************************//
PUBLIC bool LIB_LINKED_LIST_IteratorInit( pLIB_LINKED_LIST_List List, pLIB_LINKED_LIST_Iterator Iterator )
{
    if( List == NULL || Iterator == NULL)
        return FALSE;

    Iterator->List = List;
    Iterator->CurrentPosition = 0;

    return TRUE;
}


//*****************************************************************************//
PUBLIC bool LIB_LINKED_LIST_IteratorHasNext( pLIB_LINKED_LIST_Iterator Iterator )
{
    if( Iterator == NULL )
        return FALSE;

    return (Iterator->CurrentPosition < Iterator->List->ItemCount);
}


//*****************************************************************************//
PUBLIC pLIB_LINKED_LIST_Item LIB_LINKED_LIST_IteratorNext( pLIB_LINKED_LIST_Iterator Iterator )
{
    if( Iterator == NULL )
        return NULL;

    return LIB_LINKED_LIST_GetItemAtPosition(Iterator->List, Iterator->CurrentPosition++);
}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

