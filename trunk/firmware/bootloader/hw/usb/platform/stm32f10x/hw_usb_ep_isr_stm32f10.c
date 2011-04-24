/*!
 * \file hw_usb_ep_isr_stm32f10.c
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
#include <platform_lib.h>

#include "usb/core/hw_usb_core.h"
#include "hw_usb_platform.h"


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
vuint16 SaveRState;
vuint16 SaveTState;


extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/*******************************************************************************
 * Function Name  : CTR_LP.
 * Description    : Low priority Endpoint Correct Transfer interrupt's service
 *                  routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CTR_LP(void)
{
    vuint16 wEPVal = 0;
    /* stay in loop while pending ints */
    while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
    {
        /* extract highest priority endpoint number */
        EPindex = (uint8)(wIstr & ISTR_EP_ID);
        if (EPindex == 0)
        {
            /* Decode and service control endpoint interrupt */
            /* calling related service routine */
            /* (Setup0_Process, In0_Process, Out0_Process) */

            /* save RX & TX status */
            /* and set both to NAK */


            SaveRState = _GetENDPOINT(ENDP0);
            SaveTState = SaveRState & EPTX_STAT;
            SaveRState &=  EPRX_STAT;

            _SetEPRxTxStatus(ENDP0,EP_RX_NAK,EP_TX_NAK);

            /* DIR bit = origin of the interrupt */

            if ((wIstr & ISTR_DIR) == 0)
            {
                /* DIR = 0 */

                /* DIR = 0      => IN  int */
                /* DIR = 0 implies that (EP_CTR_TX = 1) always  */


                _ClearEP_CTR_TX(ENDP0);
                In0_Process();

                /* before terminate set Tx & Rx status */

                _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
                return;
            }
            else
            {
                /* DIR = 1 */

                /* DIR = 1 & CTR_RX       => SETUP or OUT int */
                /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */

                wEPVal = _GetENDPOINT(ENDP0);

                if ((wEPVal &EP_SETUP) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */
                    Setup0_Process();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
                    return;
                }

                else if ((wEPVal & EP_CTR_RX) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0);
                    Out0_Process();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
                    return;
                }
            }
        }/* if(EPindex == 0) */
        else
        {
            /* Decode and service non control endpoints interrupt  */

            /* process related endpoint register */
            wEPVal = _GetENDPOINT(EPindex);
            if ((wEPVal & EP_CTR_RX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_RX(EPindex);

                /* call OUT service function */
                (*pEpInt_OUT[EPindex-1])();

            } /* if((wEPVal & EP_CTR_RX) */

            if ((wEPVal & EP_CTR_TX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_TX(EPindex);

                /* call IN service function */
                (*pEpInt_IN[EPindex-1])();
            } /* if((wEPVal & EP_CTR_TX) != 0) */

        }/* if(EPindex == 0) else */

    }/* while(...) */
}

/*******************************************************************************
 * Function Name  : CTR_HP.
 * Description    : High Priority Endpoint Correct Transfer interrupt's service
 *                  routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CTR_HP(void)
{
    uint32 wEPVal = 0;

    while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
    {
        _SetISTR((uint16)CLR_CTR); /* clear CTR flag */
        /* extract highest priority endpoint number */
        EPindex = (uint8)(wIstr & ISTR_EP_ID);
        /* process related endpoint register */
        wEPVal = _GetENDPOINT(EPindex);
        if ((wEPVal & EP_CTR_RX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_RX(EPindex);

            /* call OUT service function */
            (*pEpInt_OUT[EPindex-1])();

        } /* if((wEPVal & EP_CTR_RX) */
        else if ((wEPVal & EP_CTR_TX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_TX(EPindex);

            /* call IN service function */
            (*pEpInt_IN[EPindex-1])();


        } /* if((wEPVal & EP_CTR_TX) != 0) */

    }/* while(...) */
}



//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************

