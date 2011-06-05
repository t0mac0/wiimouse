/*!
 * \file system_conf.h
 *
 * \brief 
 *
 *
 * \date Feb 27, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SYSTEM_CONF_H_
#define _SYSTEM_CONF_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
// Specifies the hardware architecture being used
#ifndef STM32F10X_MD
#error A SYSTEM_PLATFORM has not been defined. This should be a preprocessor directive specifying the hardware architecture. Supported architectures are: STM32F10X_MD
#endif

/* In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application */
#define HSE_VALUE    ((uint32)8000000) /* Value of the External oscillator in Hz*/

#define BOOTLOADER_START_ADDR       0x08000000
#define BOOTLOADER_VERSION_ADDR     (BOOTLOADER_START_ADDR + 0x130)

#define DEVICE_START_ADDR           0x08004000

#define DEVICE_MODE_ADDR            (DEVICE_START_ADDR + 0x130)
#define DEVICE_VERSION_ADDR         (DEVICE_START_ADDR + 0x134)

#define USB_VENDOR_ID               0xF46D
#define USB_PRODUCT_ID              0x052B
#define USB_BOOTLOADER_ID           0x0001
#define USB_DEVICE_ID               0x0002

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


#endif /* SYSTEM_CONF_H_ */
