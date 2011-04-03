/*!
 * \file hw_usb_sil.c
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "hw_usb_sil.h"
#include "usb/mem/hw_usb_mem.h"
#include "composite_usb/isr/composite_usb_isr.h"  // todo: bad includes

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


/*******************************************************************************
 * Function Name  : USB_SIL_Init
 * Description    : Initialize the USB Device IP and the Endpoint 0.
 * Input          : None.
 * Output         : None.
 * Return         : Status.
 *******************************************************************************/
uint32 USB_SIL_Init(void)
{

    // todo: platform specific
    /* USB interrupts initialization */
    /* clear pending interrupts */
    _SetISTR(0);
    wInterrupt_Mask = IMR_MSK;
    /* set interrupts mask */
    _SetCNTR(wInterrupt_Mask);


    return 0;
}

/*******************************************************************************
 * Function Name  : USB_SIL_Write
 * Description    : Write a buffer of data to a selected endpoint.
 * Input          : - bEpAddr: The address of the non control endpoint.
 *                  - pBufferPointer: The pointer to the buffer of data to be written
 *                    to the endpoint.
 *                  - wBufferSize: Number of data to be written (in bytes).
 * Output         : None.
 * Return         : Status.
 *******************************************************************************/
uint32 USB_SIL_Write(uint8 bEpAddr, uint8* pBufferPointer, uint32 wBufferSize)
{
    // TODO: USB limits buffer size to 1024 bytes, allow for multi-buffer copy
#ifndef STM32F10X_CL

    /* Use the memory interface function to write to the selected endpoint */
    UserToPMABufferCopy(pBufferPointer, GetEPTxAddr(bEpAddr & 0x7F), wBufferSize);

    /* Update the data length in the control register */
    SetEPTxCount((bEpAddr & 0x7F), wBufferSize);

#else

    /* Use the PCD interface layer function to write to the selected endpoint */
    PCD_EP_Write (bEpAddr, pBufferPointer, wBufferSize);

#endif /* STM32F10X_CL */

    return 0;
}

/*******************************************************************************
 * Function Name  : USB_SIL_Read
 * Description    : Write a buffer of data to a selected endpoint.
 * Input          : - bEpAddr: The address of the non control endpoint.
 *                  - pBufferPointer: The pointer to which will be saved the
 *                     received data buffer.
 * Output         : None.
 * Return         : Number of received data (in Bytes).
 *******************************************************************************/
uint32 USB_SIL_Read(uint8 bEpAddr, uint8* pBufferPointer)
{
    uint32 DataLength = 0;

#ifndef STM32F10X_CL

    /* Get the number of received data on the selected Endpoint */
    DataLength = GetEPRxCount(bEpAddr & 0x7F);

    /* Use the memory interface function to write to the selected endpoint */
    PMAToUserBufferCopy(pBufferPointer, GetEPRxAddr(bEpAddr & 0x7F), DataLength);

#else

    USB_OTG_EP *ep;

    /* Get the structure pointer of the selected Endpoint */
    ep = PCD_GetOutEP(bEpAddr);

    /* Get the number of received data */
    DataLength = ep->xfer_len;

    /* Use the PCD interface layer function to read the selected endpoint */
    PCD_EP_Read (bEpAddr, pBufferPointer, DataLength);

#endif /* STM32F10X_CL */

    /* Return the number of received data */
    return DataLength;
}


//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

