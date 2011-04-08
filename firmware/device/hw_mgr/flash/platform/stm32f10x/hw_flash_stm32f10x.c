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
PUBLIC Result HW_FLASH_Init(uint32 BlockId, void* InitInfo )
{
    UNUSED(BlockId);
    UNUSED(InitInfo);

    FLASH_Unlock();

    return  HW_FLASH_RESULT(SUCCESS);
}


//****************************************************************************/
PUBLIC Result HW_FLASH_PowerUp( uint32 BlockId )
{
    Result result = HW_FLASH_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_FLASH_PowerDown( uint32 BlockId )
{
    Result result = HW_FLASH_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


//****************************************************************************/
PUBLIC Result HW_FLASH_Write32Bit(uint32 Address, uint32 *Data, uint32 WordCount)
{
    Result result = HW_FLASH_RESULT(SUCCESS);
    uint32 i;


    for(i = 0; i < WordCount; i++)
    {
        if( FLASH_ProgramWord(Address|FLASH_BASE, Data[i]) != FLASH_COMPLETE )
        {
            result = HW_FLASH_RESULT(WRITE_FAIL);
            break;
        }
    }

    return result;
}


//****************************************************************************/
PUBLIC Result HW_FLASH_Write16Bit(uint32 Address, uint16 *Data, uint32 WordCount)
{
    Result result = HW_FLASH_RESULT(SUCCESS);
    uint32 i;


    for(i = 0; i < WordCount; i++)
    {
        if( FLASH_ProgramHalfWord(Address|FLASH_BASE, Data[i]) != FLASH_COMPLETE )
        {
            result = HW_FLASH_RESULT(WRITE_FAIL);
            break;
        }
    }

    return result;
}


//****************************************************************************/
PUBLIC Result HW_FLASH_Read32Bit(uint32 Address, uint32 *Data, uint32 WordCount)
{
    Result result = HW_FLASH_RESULT(SUCCESS);
    uint32 i;

    for( i= 0; i < WordCount; i++)
    {
        *(uint32*)(Data + i) = *(uint32*)(Address + i);
    };

    return result;
}


//****************************************************************************/
PUBLIC Result HW_FLASH_Read16Bit(uint32 Address, uint16 *Data, uint32 WordCount)
{
    Result result = HW_FLASH_RESULT(SUCCESS);
    uint32 i;

    for( i = 0; i < WordCount; i++)
    {
        *(uint16*)(Data + i) = *(uint16*)(Address + i);
    };

    return result;
}


//****************************************************************************/
PUBLIC Result HW_FLASH_ErasePages(uint32 FirstPage, uint32 PageCount)
{
    Result result = HW_FLASH_RESULT(SUCCESS);
    uint32 i;

    if( !IS_FLASH_ADDRESS(FirstPage) )
    {
        result = HW_FLASH_RESULT(INVALID_PAGE_ADDR);
    }
    else
    {
        for(i = 0; i < PageCount; i++ )
        {
            if( FLASH_ErasePage((FirstPage & 0xFFFFFC00)|FLASH_BASE) != FLASH_COMPLETE )
            {
                result = HW_FLASH_RESULT(ERASE_FAIL);
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

