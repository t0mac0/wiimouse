/*!
 * \file hw_flash.h
 *
 * \brief 
 *
 *
 * \date Apr 3, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_FLASH_H_
#define _HW_FLASH_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "device.h"
#include "hw_mgr.h"
#include "hw_flash_result.h"
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


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
PUBLIC HwModuleInitPrototype HW_FLASH_Init;

PUBLIC HwModulePowerUpPrototype HW_FLASH_PowerUp;

PUBLIC HwModulePowerDownPrototype HW_FLASH_PowerDown;

PUBLIC Result HW_FLASH_Write32Bit(uint32 Address, uint32 *Data, uint32 WordCount);

PUBLIC Result HW_FLASH_Write16Bit(uint32 Address, uint16 *Data, uint32 WordCount);

PUBLIC Result HW_FLASH_Read32Bit(uint32 Address, uint32 *Data, uint32 WordCount);

PUBLIC Result HW_FLASH_Read16Bit(uint32 Address, uint16 *Data, uint32 WordCount);

PUBLIC Result HW_FLASH_ErasePages(uint32 FirstPage, uint32 PageCount);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* HW_FLASH_H_ */
