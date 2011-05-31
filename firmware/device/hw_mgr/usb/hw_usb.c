/*!
 * \file hw_usb.c
 *
 * \brief 
 *
 *
 * \date Mar 18, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_usb.h"
#include "int/hw_int.h"

#ifdef HW_MGR_MOD_USB

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
PROTECTED pHW_USB_StateChangeCallback HwUsbStateChangeCallback;


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/****************************************************************************/
PUBLIC Result HW_USB_Init(uint32 BlockId, void* InitInfo )
{
    //Result result = HW_USB_RESULT_INIT();

    UNUSED(InitInfo);
    UNUSED(BlockId);

    HwUsbStateChangeCallback = NULL;

    LOG_Printf("Initializing HW USB\n");

    USB_Init();

    return HW_USB_RESULT(SUCCESS);
}

/****************************************************************************/
PUBLIC Result HW_USB_PowerUp( uint32 BlockId )
{
    Result result = HW_USB_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


/****************************************************************************/
PUBLIC Result HW_USB_PowerDown( uint32 BlockId )
{
    Result result = HW_USB_RESULT_INIT();

    UNUSED(BlockId);

    return result;
}


/****************************************************************************/
PUBLIC Result HW_USB_RegisterStateChangeCallback(pHW_USB_StateChangeCallback Callback)
{

	HwUsbStateChangeCallback = Callback;

    return HW_USB_RESULT(SUCCESS);
}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
