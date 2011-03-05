/*!
 * \file system_config.h
 *
 * \brief 
 *
 *
 * \date Feb 27, 2011
 * \author Dan Riedler
 *
 */

#ifndef _SYSTEM_CONFIG_H_
#define _SYSTEM_CONFIG_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
// Specifies the hardware architecture being used
#ifndef SYSTEM_PLATFORM
#error SYSTEM_PLATFORM has not been defined. This should be a preprocessor directive specifying the hardware architecture (ex STM32F10X_MD)
#endif

/* In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application */
#define HSE_VALUE    ((uint32)8000000) /* Value of the External oscillator in Hz*/



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


#endif /* SYSTEM_CONFIG_H_ */
