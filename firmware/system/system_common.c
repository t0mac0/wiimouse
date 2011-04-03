/*!
 * \file system_common.c
 *
 * \brief 
 *
 *
 * \date Mar 6, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system_common.h"

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
PUBLIC bool ZeroMemory(void *Mem, uint32 SizeBytes)
{
    uint32 i;

    if(Mem == NULL)
        return FALSE;

    for( i = 0; i < SizeBytes; i++ )
        ((uint8*)(Mem))[i] = 0;

    return TRUE;
}


//*****************************************************************************//
PUBLIC bool SetMemory(void *Mem, uint32 Value, uint32 SizeBytes)
{
    uint32 i;

    if(Mem == NULL)
        return FALSE;

    for( i = 0; i < SizeBytes; i++ )
        ((uint8*)(Mem))[i] = Value;

    return TRUE;
}


//*****************************************************************************//
PUBLIC bool CopyMemory(void *Dst, void *Src, uint32 SizeBytes)
{
    uint32 i;

    if( (Dst == NULL) || (Src == NULL) )
        return FALSE;

    for( i = 0; i < SizeBytes; i++ )
        ((uint8*)(Dst))[i] = ((uint8*)(Src))[i];

    return TRUE;
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

