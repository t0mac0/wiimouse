/*!
 * \file hw_usb_mem.c
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
#include "hw_usb_mem.h"


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


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************

/*******************************************************************************
* Function Name  : UserToPMABufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf: pointer to user memory area.
*                  - wPMABufAddr: address into PMA.
*                  - wNBytes: no. of bytes to be copied.
* Output         : None.
* Return         : None .
*******************************************************************************/
void UserToPMABufferCopy(uint8 *pbUsrBuf, uint16 wPMABufAddr, uint16 wNBytes)
{
  uint32 n = (wNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  uint32 i, temp1, temp2;
  uint16 *pdwVal;
  pdwVal = (uint16 *)(wPMABufAddr * 2 + PMAAddr);
  for (i = n; i != 0; i--)
  {
    temp1 = (uint16) * pbUsrBuf;
    pbUsrBuf++;
    temp2 = temp1 | (uint16) * pbUsrBuf << 8;
    *pdwVal++ = temp2;
    pdwVal++;
    pbUsrBuf++;
  }
}
/*******************************************************************************
* Function Name  : PMAToUserBufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf    = pointer to user memory area.
*                  - wPMABufAddr = address into PMA.
*                  - wNBytes     = no. of bytes to be copied.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PMAToUserBufferCopy(uint8 *pbUsrBuf, uint16 wPMABufAddr, uint16 wNBytes)
{
  uint32 n = (wNBytes + 1) >> 1;/* /2*/
  uint32 i;
  uint32 *pdwVal;
  pdwVal = (uint32 *)(wPMABufAddr * 2 + PMAAddr);
  for (i = n; i != 0; i--)
  {
    *(uint16*)pbUsrBuf++ = *pdwVal++;
    pbUsrBuf++;
  }
}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************


#endif
