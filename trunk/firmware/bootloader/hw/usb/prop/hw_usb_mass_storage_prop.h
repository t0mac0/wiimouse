/*!
 * \file hw_usb_mass_storage_prop.h
 *
 * \brief 
 *
 *
 * \date Jun 13, 2011
 * \author Dan Riedler
 *
 */
#ifndef _HW_USB_MASS_STORAGE_PROP_H_
#define _HW_USB_MASS_STORAGE_PROP_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include <hw_usb_platform.h>

#include "bootloader.h"

#include "usb/core/hw_usb_core.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define Mass_Storage_GetConfiguration          NOP_Process
/* #define Mass_Storage_SetConfiguration          NOP_Process*/
#define Mass_Storage_GetInterface              NOP_Process
#define Mass_Storage_SetInterface              NOP_Process
#define Mass_Storage_GetStatus                 NOP_Process
/* #define Mass_Storage_ClearFeature              NOP_Process*/
#define Mass_Storage_SetEndPointFeature        NOP_Process
#define Mass_Storage_SetDeviceFeature          NOP_Process
/*#define Mass_Storage_SetDeviceAddress          NOP_Process*/

/* MASS Storage Requests*/
#define GET_MAX_LUN                0xFE
#define MASS_STORAGE_RESET         0xFF
#define LUN_DATA_LENGTH            1



/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


void MASS_init(void);
void MASS_Reset(void);
void Mass_Storage_SetConfiguration(void);
void Mass_Storage_ClearFeature(void);
void Mass_Storage_SetDeviceAddress (void);
void MASS_Status_In (void);
void MASS_Status_Out (void);
USB_RESULT MASS_Data_Setup(uint8);
USB_RESULT MASS_NoData_Setup(uint8);
USB_RESULT MASS_Get_Interface_Setting(uint8 Interface, uint8 AlternateSetting);
uint8 *MASS_GetDeviceDescriptor(uint16);
uint8 *MASS_GetConfigDescriptor(uint16);
uint8 *MASS_GetStringDescriptor(uint16);
uint8 *Get_Max_Lun(uint16 Length);

#endif /* _HW_USB_MASS_STORAGE_PROP_H_ */
