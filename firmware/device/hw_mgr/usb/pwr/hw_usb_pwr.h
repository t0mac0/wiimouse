/*!
 * \file hw_usb_pwr.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_PWR_H_
#define _HW_USB_PWR_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "usb/hw_usb.h"
#include "usb/core/hw_usb_core.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef enum _RESUME_STATE
{
  RESUME_EXTERNAL,
  RESUME_INTERNAL,
  RESUME_LATER,
  RESUME_WAIT,
  RESUME_START,
  RESUME_ON,
  RESUME_OFF,
  RESUME_ESOF
} RESUME_STATE;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);
USB_RESULT PowerOn(void);
USB_RESULT PowerOff(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Cable_Config (FunctionalState NewState);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
extern  volatile HW_USB_StateType bDeviceState; /* USB device status */
extern  vbool fSuspendEnabled;  /* true when suspend is possible */

#endif /* HW_USB_PWR_H_ */
