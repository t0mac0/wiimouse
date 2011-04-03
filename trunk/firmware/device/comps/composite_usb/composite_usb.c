/*!
 * \file composite_usb.c
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
#include "composite_usb.h"

#ifdef COMPS_MOD_COMPOSITE_USB

#include "ep/composite_usb_ep.h"
#include "usb/sil/hw_usb_sil.h"

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
PUBLIC Result COMPOSITE_USB_Init( void )
{
    Result result = COMPOSITE_USB_RESULT_INIT();

    LOG_Printf("Initializing Composite USB component\n");

    if( RESULT_IS_ERROR(result, CompositeUsbEpInit()))
    {

    }

    return result;
}

//****************************************************************************/
PUBLIC Result COMPOSITE_USB_PowerUp( void )
{
    Result result = COMPOSITE_USB_RESULT_INIT();

    return result;
}


//****************************************************************************/
PUBLIC Result COMPOSITE_USB_PowerDown( void )
{
    Result result = COMPOSITE_USB_RESULT_INIT();


    return result;
};


//****************************************************************************/
PUBLIC Result COMPOSITE_USB_SendHidMouseReport(HID_MOUSE_REPORT *Report)
{

    USB_SIL_Write(HID_MOUSE_REPORT_EP, (uint8*)Report, HID_MOUSE_REPORT_SIZE);
    SetEPTxValid(HID_MOUSE_REPORT_EP_NUM);

    return COMPOSITE_USB_RESULT(COMPOSITE_USB_RESULT_SUCCESS);
};


//****************************************************************************/
PUBLIC Result COMPOSITE_USB_WriteVirCom(void *Buffer, uint32 StartIndex, uint32 EndIndex, uint32 MaxSize)
{
    uint32 byteCount;

    if( StartIndex < EndIndex )
    {
        byteCount = EndIndex - StartIndex;
        USB_SIL_Write(VIR_COM_WRITE_EP, &((uint8*)Buffer)[StartIndex], byteCount);
        SetEPTxValid(VIR_COM_WRITE_EP_NUM);
    }
    else
    {
        byteCount = MaxSize - StartIndex;
        USB_SIL_Write(VIR_COM_WRITE_EP,  &((uint8*)Buffer)[StartIndex], byteCount);
        SetEPTxValid(VIR_COM_WRITE_EP_NUM);

        USB_SIL_Write(VIR_COM_WRITE_EP,  &((uint8*)Buffer)[0], EndIndex);
        SetEPTxValid(VIR_COM_WRITE_EP_NUM);
    }


    return COMPOSITE_USB_RESULT(COMPOSITE_USB_RESULT_SUCCESS);
};


//****************************************************************************/
PUBLIC Result COMPOSITE_USB_RegisterReadVirComCallback(pCOMPOSITE_USB_ReadVirComCallBack ReadVirCom)
{
    Result result = COMPOSITE_USB_RESULT_INIT();

    CompositeUsbVirComCallback = ReadVirCom;

    LOG_Printf("Registered Virtual COM Port Read Callback\n");

    return result;
};


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************



#endif
