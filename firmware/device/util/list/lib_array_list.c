/*!
 * \file lib_array_list.c
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
#include "lib_array_list.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define ADD_ARRAY_LIST_ITEM(_list, _pos, _item)( CopyMemory((pVoid)((uint32)_list->Items + (_pos)*_list->ItemSize), (_item), _list->ItemSize) )
/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/
PRIVATE bool increaseCapacity(pLIB_ARRAY_LIST_List *List);

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


//*****************************************************************************//
PUBLIC pLIB_ARRAY_LIST_List LIB_ARRAY_LIST_CreateList( uint32 ItemSize, uint32 InitialCapacity )
{
    pLIB_ARRAY_LIST_List list = NULL;

    if( (list = (pLIB_ARRAY_LIST_List) AllocMemory(sizeof(LIB_ARRAY_LIST_List) + (ItemSize*InitialCapacity))) != NULL )
    {
        list->ItemCount = 0;
        list->ItemSize = ItemSize;
        list->Capacity = InitialCapacity;
        list->Items = (pLIB_ARRAY_LIST_Item)(list + sizeof(LIB_ARRAY_LIST_List));
    }

    return list;
}


//*****************************************************************************//
PUBLIC int32 LIB_ARRAY_LIST_AddItem( pLIB_ARRAY_LIST_List List, pVoid Item)
{
    int32 position = -1;

    if( List == NULL || Item == NULL )
    {
        return -1;
    }

    if( List->ItemCount == List->Capacity )
    {
        ASSERT(increaseCapacity(&List));
    }

    position = List->ItemCount;
    ADD_ARRAY_LIST_ITEM(List, position, Item);
    List->ItemCount++;

    return position;
}


//*****************************************************************************//
PUBLIC int32  LIB_ARRAY_LIST_AddItemAtPosition( pLIB_ARRAY_LIST_List List, pLIB_ARRAY_LIST_Item Item, uint32 Position)
{
    int32 position = -1;

    if( List == NULL || Item == NULL || Position > List->ItemCount )
    {
        return -1;
    }

    if( List->ItemCount == List->Capacity )
    {
        ASSERT(increaseCapacity(&List));
    }

    for( position= (signed)List->ItemCount-1; position > (signed)Position; position-- )
    {
        ADD_ARRAY_LIST_ITEM(List, position+1, List->Items + position*List->ItemSize );
    }

    ADD_ARRAY_LIST_ITEM(List, position, Item);
    List->ItemCount++;

    return position;
}


//*****************************************************************************//
PUBLIC bool LIB_ARRAY_LIST_RemoveItem( pLIB_ARRAY_LIST_List List)
{
    uint32 i;

    if( List == NULL || List->ItemCount == 0 )
        return FALSE;

    for( i = 1; i < List->ItemCount; i++ )
    {
        ADD_ARRAY_LIST_ITEM(List, i-1, List->Items + i*List->ItemSize);
    }

    List->ItemCount--;

    return TRUE;
}


//*****************************************************************************//
PUBLIC bool LIB_ARRAY_LIST_RemoveItemAtPosition( pLIB_ARRAY_LIST_List List, uint32 Position)
{
    uint32 i;

    if( List == NULL || List->ItemCount == 0 || Position >= List->ItemCount )
        return FALSE;

    for( i = Position+1; i < List->ItemCount; i++ )
    {
        ADD_ARRAY_LIST_ITEM(List, i-1, List->Items + i*List->ItemSize);
    }

    List->ItemCount--;

    return TRUE;
}


//*****************************************************************************//
PUBLIC pLIB_ARRAY_LIST_Item LIB_ARRAY_LIST_GetItemAtPosition( pLIB_ARRAY_LIST_List List, uint32 Position)
{
    if( List == NULL || Position >= List->ItemCount )
        return NULL;

    return (pLIB_ARRAY_LIST_Item)(List->Items + Position * List->ItemSize);
}


//*****************************************************************************//
PUBLIC void LIB_ARRAY_LIST_ClearList( pLIB_ARRAY_LIST_List List )
{
    if( List == NULL)
        return;
    else {
        List->ItemCount = 0;
    }
}


//*****************************************************************************//
PUBLIC void LIB_ARRAY_LIST_DestroyList( pLIB_ARRAY_LIST_List List )
{
    if( List != NULL )
        FreeMemory(List);
}


//*****************************************************************************//
PUBLIC uint32 LIB_ARRAY_LIST_ListSize( pLIB_ARRAY_LIST_List List )
{
    if( List == NULL )
        return 0;
    else
        return List->ItemCount;
}


//*****************************************************************************//
PUBLIC bool LIB_ARRAY_LIST_IteratorInit( pLIB_ARRAY_LIST_List List, pLIB_ARRAY_LIST_Iterator Iterator )
{
    if( List == NULL || Iterator == NULL)
        return FALSE;

    Iterator->List = List;
    Iterator->CurrentPosition = 0;

    return TRUE;
}


//*****************************************************************************//
PUBLIC bool LIB_ARRAY_LIST_IteratorHasNext( pLIB_ARRAY_LIST_Iterator Iterator )
{
    if( Iterator == NULL )
        return FALSE;

    return (Iterator->CurrentPosition < Iterator->List->ItemCount);
}


//*****************************************************************************//
PUBLIC pLIB_ARRAY_LIST_Item LIB_ARRAY_LIST_IteratorNext( pLIB_ARRAY_LIST_Iterator Iterator )
{
    if( Iterator == NULL )
        return NULL;

    return LIB_ARRAY_LIST_GetItemAtPosition(Iterator->List, Iterator->CurrentPosition++);
}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

//*****************************************************************************//
PRIVATE bool increaseCapacity(pLIB_ARRAY_LIST_List *List)
{
    pLIB_ARRAY_LIST_List tmpList;
    uint32 newCapacity;

    newCapacity = (*List)->Capacity + LIB_ARRAY_LIST_INCREASE_AMOUNT;

    if( (tmpList = (pLIB_ARRAY_LIST_List) AllocMemory(sizeof(LIB_ARRAY_LIST_List) + newCapacity)) == NULL )
    {
        return FALSE;
    }

    tmpList->Items = (pVoid)(tmpList + sizeof(LIB_ARRAY_LIST_List));

    CopyMemory(tmpList->Items, (*List)->Items, (*List)->ItemSize*(*List)->ItemCount);

    tmpList->Capacity = newCapacity;
    tmpList->ItemCount = (*List)->ItemCount;
    tmpList->ItemSize = (*List)->ItemSize;

    FreeMemory(*List);

    *List = tmpList;

    return TRUE;
}
