/*!
 * \file hw_usart.h
 *
 * \brief 
 *
 *
 * \date Mar 2, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USART_H_
#define _HW_USART_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "hw_mgr.h"
#include "hw_usart_result.h"
#include "hw_mgr_types.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct
{
    uint32 BaudRate;
    uint16 WordLength;
    uint16 StopBits;
    uint16 Parity;
    uint16 HardwareFlowControl;
    uint16 Mode;
} HW_USART_InitInfo, *pUSART_InitInfo;

// generic USART defines, depended on
// enabled hardware
typedef enum {
HW_USART_1,
HW_USART_2,
HW_USART_3,
HW_USART_4,
HW_USART_5,
HW_USART_COUNT
} HW_USART_BlockId;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

PUBLIC HwModuleInitPrototype HW_USART_Init;

PUBLIC HwModulePowerUpPrototype HW_USART_PowerUp;

PUBLIC HwModulePowerDownPrototype HW_USART_PowerDown;

PUBLIC inline void HW_USART_DefaultInit( void);

PUBLIC Result HW_USART_WriteByte(HW_USART_BlockId Id, uint8 Bytes);

PUBLIC Result HW_USART_WriteBytes(HW_USART_BlockId Id, uint8* Bytes, uint32 Count);

PUBLIC Result HW_USART_ReadByte(HW_USART_BlockId Id, uint8 *Byte);

PUBLIC Result HW_USART_ReadBytes(HW_USART_BlockId Id, uint8 *Bytes, uint32 Count);

PUBLIC LIB_PRINTF_PutChr HW_USART_DefaultOutputDest;

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_USART_H_ */
