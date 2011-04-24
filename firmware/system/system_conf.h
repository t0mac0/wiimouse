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
#define DEVICE_START_ADDR           0x08004000

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
