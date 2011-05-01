/*!
 * \file hw_flash_stm32f10x.c
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <platform_lib.h>
#include "flash/hw_flash.h"

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


//****************************************************************************/
PUBLIC bool HW_FLASH_Init(void )
{

    FLASH_Unlock();

    return  TRUE;
}


//****************************************************************************/
PUBLIC bool HW_FLASH_Write32Bit(uint32 Address, uint32 *Data, uint32 WordCount)
{
    bool result = TRUE;
    uint32 i;


    for(i = 0; i < WordCount; i++)
    {
        if( FLASH_ProgramWord(Address, Data[i]) != FLASH_COMPLETE )
        {
            result = FALSE;
            break;
        }
        Address += 4;
    }

    return result;
}


//****************************************************************************/
PUBLIC bool HW_FLASH_Write16Bit(uint32 Address, uint16 *Data, uint32 WordCount)
{
    bool result = TRUE;
    uint32 i;


    for(i = 0; i < WordCount; i++)
    {
        if( FLASH_ProgramHalfWord(Address, Data[i]) != FLASH_COMPLETE )
        {
            result = FALSE;
            break;
        }
        Address += 2;
    }

    return result;
}


//****************************************************************************/
PUBLIC bool HW_FLASH_Read32Bit(uint32 Address, uint32 *Data, uint32 WordCount)
{
    bool result = TRUE;
    uint32 i;

    for( i= 0; i < WordCount; i++)
    {
        *(uint32*)(Data + i) = *(uint32*)(Address);
        Address += 4;
    };

    return result;
}


//****************************************************************************/
PUBLIC bool HW_FLASH_Read16Bit(uint32 Address, uint16 *Data, uint32 WordCount)
{
    bool result = TRUE;
    uint32 i;

    for( i = 0; i < WordCount; i++)
    {
        *(uint16*)(Data + i) = *(uint16*)(Address);
        Address += 2;
    };

    return result;
}


//****************************************************************************/
PUBLIC bool HW_FLASH_ErasePages(uint32 FirstPage, uint32 PageCount)
{
    bool result = TRUE;
    uint32 i;

    if( !IS_FLASH_ADDRESS(FirstPage) )
    {
        result = FALSE;
    }
    else
    {
        for(i = 0; i < PageCount; i++ )
        {
            if( FLASH_ErasePage(FirstPage & 0xFFFFFC00) != FLASH_COMPLETE )
            {
                result = FALSE;
                break;
            }
            FirstPage += FLASH_PAGE_SIZE;
        }
    }

    return result;
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

