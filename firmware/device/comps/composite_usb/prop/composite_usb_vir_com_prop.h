/*!
 * \file composite_usb_vir_com_prop.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _COMPOSITE_USB_VIR_COM_PROP_H_
#define _COMPOSITE_USB_VIR_COM_PROP_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "composite_usb.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04
#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct
{
  uint32 bitrate;
  uint8 format;
  uint8 paritytype;
  uint8 datatype;
}LINE_CODING;


/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
#define Virtual_Com_Port_GetConfiguration          NOP_Process
//#define Virtual_Com_Port_SetConfiguration          NOP_Process
#define Virtual_Com_Port_GetInterface              NOP_Process
#define Virtual_Com_Port_SetInterface              NOP_Process
#define Virtual_Com_Port_GetStatus                 NOP_Process
#define Virtual_Com_Port_ClearFeature              NOP_Process
#define Virtual_Com_Port_SetEndPointFeature        NOP_Process
#define Virtual_Com_Port_SetDeviceFeature          NOP_Process
//#define Virtual_Com_Port_SetDeviceAddress          NOP_Process

void Virtual_Com_Port_init(void);
void Virtual_Com_Port_Reset(void);
void Virtual_Com_Port_SetConfiguration(void);
void Virtual_Com_Port_SetDeviceAddress (void);
void Virtual_Com_Port_Status_In (void);
void Virtual_Com_Port_Status_Out (void);
USB_RESULT Virtual_Com_Port_Data_Setup(uint8);
USB_RESULT Virtual_Com_Port_NoData_Setup(uint8);
USB_RESULT Virtual_Com_Port_Get_Interface_Setting(uint8 Interface, uint8 AlternateSetting);
uint8 *Virtual_Com_Port_GetDeviceDescriptor(uint16 );
uint8 *Virtual_Com_Port_GetConfigDescriptor(uint16);
uint8 *Virtual_Com_Port_GetStringDescriptor(uint16);

uint8 *Virtual_Com_Port_GetLineCoding(uint16 Length);
uint8 *Virtual_Com_Port_SetLineCoding(uint16 Length);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* COMPOSITE_USB_VIR_COM_PROP_H_ */
