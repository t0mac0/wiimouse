/*!
 * \file hw_usb_ep_stm32f10x.c
 *
 * \brief 
 *
 *
 * \date Apr 23, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <platform_lib.h>

#include "bootloader.h"
#include "usb/desc/hw_usb_desc_vir_com.h"
#include "usb/ep/hw_usb_ep_vir_com.h"
#include "usb/core/hw_usb_core.h"
#include "usb/pwr/hw_usb_pwr.h"


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
PRIVATE uint8 readBuffer[VIRTUAL_COM_PORT_DATA_SIZE];



//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

void SOF_Callback(void)
{
    static uint32 FrameCount = 0;

    if(bDeviceState == CONFIGURED)
    {
        if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
        {
            /* Reset the frame counter */
            FrameCount = 0;

            /* Check the data to be sent through IN pipe */
            //Handle_USBAsynchXfer();
        }
    }
}

/*******************************************************************************
 * Function Name  : EP1_IN_Callback
 * Description    :
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void EP1_IN_Callback (void)
{
}



/*******************************************************************************
 * Function Name  : EP4_OUT_Callback
 * Description    :
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void EP3_OUT_Callback(void)
{

    if( HwUsbVirComCallback != NULL )
    {
        uint16 readCount;

        /* Get the received data buffer and update the counter */
        readCount = HW_USB_Read(VIR_COM_READ_EP, readBuffer);

        HwUsbVirComCallback(readBuffer, readCount);
    }

    /* Enable the receive of data on EP3 */
    SetEPRxValid(VIR_COM_READ_EP_NUM);

}




//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

