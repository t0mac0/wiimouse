/*!
 * \file hw_usb_core.h
 *
 * \brief 
 *
 *
 * \date Mar 19, 2011
 * \author Dan Riedler
 *
 */

#ifndef _HW_USB_CORE_H_
#define _HW_USB_CORE_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "bootloader.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define Type_Recipient (pInformation->USBbmRequestType & (REQUEST_TYPE | RECIPIENT))

#define Usb_rLength Usb_wLength
#define Usb_rOffset Usb_wOffset

#define USBwValue USBwValues.w
#define USBwValue0 USBwValues.bw.bb0
#define USBwValue1 USBwValues.bw.bb1
#define USBwIndex USBwIndexs.w
#define USBwIndex0 USBwIndexs.bw.bb0
#define USBwIndex1 USBwIndexs.bw.bb1
#define USBwLength USBwLengths.w
#define USBwLength0 USBwLengths.bw.bb0
#define USBwLength1 USBwLengths.bw.bb1


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/


typedef enum _CONTROL_STATE
{
  WAIT_SETUP,       /* 0 */
  SETTING_UP,       /* 1 */
  IN_DATA,          /* 2 */
  OUT_DATA,         /* 3 */
  LAST_IN_DATA,     /* 4 */
  LAST_OUT_DATA,    /* 5 */
  WAIT_STATUS_IN,   /* 7 */
  WAIT_STATUS_OUT,  /* 8 */
  STALLED,          /* 9 */
  PAUSE             /* 10 */
} CONTROL_STATE;    /* The state machine states of a control pipe */



typedef struct OneDescriptor
{
  uint8 *Descriptor;
  uint16 Descriptor_Size;
}
ONE_DESCRIPTOR, *PONE_DESCRIPTOR;



/* All the request process routines return a value of this type
   If the return value is not SUCCESS or NOT_READY,
   the software will STALL the correspond endpoint */
typedef enum _RESULT
{
  USB_SUCCESS = 0,    /* Process sucessfully */
  USB_ERROR,
  USB_UNSUPPORT,
  USB_NOT_READY       /* The process has not been finished, endpoint will be
                         NAK to further rquest */
} USB_RESULT;




/*-*-*-*-*-*-*-*-*-*-* Definitions for endpoint level -*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct _ENDPOINT_INFO
{
  /* When send data out of the device,
   CopyData() is used to get data buffer 'Length' bytes data
   if Length is 0,
    CopyData() returns the total length of the data
    if the request is not supported, returns 0
    (NEW Feature )
     if CopyData() returns -1, the calling routine should not proceed
     further and will resume the SETUP process by the class device
   if Length is not 0,
    CopyData() returns a pointer to indicate the data location
   Usb_wLength is the data remain to be sent,
   Usb_wOffset is the Offset of original data
  When receive data from the host,
   CopyData() is used to get user data buffer which is capable
   of Length bytes data to copy data from the endpoint buffer.
   if Length is 0,
    CopyData() returns the available data length,
   if Length is not 0,
    CopyData() returns user buffer address
   Usb_rLength is the data remain to be received,
   Usb_rPointer is the Offset of data buffer
  */
  uint16  Usb_wLength;
  uint16  Usb_wOffset;
  uint16  PacketSize;
  uint8   *(*CopyData)(uint16 Length);
}ENDPOINT_INFO;


/*-*-*-*-*-*-*-*-*-*-*-* Definitions for device level -*-*-*-*-*-*-*-*-*-*-*-*/


typedef struct _DEVICE
{
  uint8 Total_Endpoint;     /* Number of endpoints that are used */
  uint8 Total_Configuration;/* Number of configuration available */
}
DEVICE;



typedef union
{
  uint16 w;
  struct BW
  {
    uint8 bb1;
    uint8 bb0;
  }
  bw;
} uint16_uint8;



typedef struct _DEVICE_INFO
{
  uint8 USBbmRequestType;       /* bmRequestType */
  uint8 USBbRequest;            /* bRequest */
  uint16_uint8 USBwValues;         /* wValue */
  uint16_uint8 USBwIndexs;         /* wIndex */
  uint16_uint8 USBwLengths;        /* wLength */

  uint8 ControlState;           /* of type CONTROL_STATE */
  uint8 Current_Feature;
  uint8 Current_Configuration;   /* Selected configuration */
  uint8 Current_Interface;       /* Selected interface of current configuration */
  uint8 Current_AlternateSetting;/* Selected Alternate Setting of current
                                     interface*/

  ENDPOINT_INFO Ctrl_Info;
}DEVICE_INFO;



typedef struct _DEVICE_PROP
{
  void (*Init)(void);        /* Initialize the device */
  void (*Reset)(void);       /* Reset routine of this device */

  /* Device dependent process after the status stage */
  void (*Process_Status_IN)(void);
  void (*Process_Status_OUT)(void);

  /* Procedure of process on setup stage of a class specified request with data stage */
  /* All class specified requests with data stage are processed in Class_Data_Setup
   Class_Data_Setup()
    responses to check all special requests and fills ENDPOINT_INFO
    according to the request
    If IN tokens are expected, then wLength & wOffset will be filled
    with the total transferring bytes and the starting position
    If OUT tokens are expected, then rLength & rOffset will be filled
    with the total expected bytes and the starting position in the buffer

    If the request is valid, Class_Data_Setup returns SUCCESS, else UNSUPPORT

   CAUTION:
    Since GET_CONFIGURATION & GET_INTERFACE are highly related to
    the individual classes, they will be checked and processed here.
  */
  USB_RESULT (*Class_Data_Setup)(uint8 RequestNo);

  /* Procedure of process on setup stage of a class specified request without data stage */
  /* All class specified requests without data stage are processed in Class_NoData_Setup
   Class_NoData_Setup
    responses to check all special requests and perform the request

   CAUTION:
    Since SET_CONFIGURATION & SET_INTERFACE are highly related to
    the individual classes, they will be checked and processed here.
  */
  USB_RESULT (*Class_NoData_Setup)(uint8 RequestNo);

  /*Class_Get_Interface_Setting
   This function is used by the file usb_core.c to test if the selected Interface
   and Alternate Setting (uint8 Interface, uint8 AlternateSetting) are supported by
   the application.
   This function is writing by user. It should return "SUCCESS" if the Interface
   and Alternate Setting are supported by the application or "UNSUPPORT" if they
   are not supported. */

  USB_RESULT  (*Class_Get_Interface_Setting)(uint8 Interface, uint8 AlternateSetting);

  uint8* (*GetDeviceDescriptor)(uint16 Length);
  uint8* (*GetConfigDescriptor)(uint16 Length);
  uint8* (*GetStringDescriptor)(uint16 Length);

  /* This field is not used in current library version. It is kept only for
   compatibility with previous versions */
  void* RxEP_buffer;

  uint8 MaxPacketSize;

}DEVICE_PROP;

typedef struct _USER_STANDARD_REQUESTS
{
  void (*User_GetConfiguration)(void);       /* Get Configuration */
  void (*User_SetConfiguration)(void);       /* Set Configuration */
  void (*User_GetInterface)(void);           /* Get Interface */
  void (*User_SetInterface)(void);           /* Set Interface */
  void (*User_GetStatus)(void);              /* Get Status */
  void (*User_ClearFeature)(void);           /* Clear Feature */
  void (*User_SetEndPointFeature)(void);     /* Set Endpoint Feature */
  void (*User_SetDeviceFeature)(void);       /* Set Device Feature */
  void (*User_SetDeviceAddress)(void);       /* Set Device Address */
}
USER_STANDARD_REQUESTS;



/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
uint8 Setup0_Process(void);
uint8 Post0_Process(void);
uint8 Out0_Process(void);
uint8 In0_Process(void);

USB_RESULT Standard_SetEndPointFeature(void);
USB_RESULT Standard_SetDeviceFeature(void);

uint8 *Standard_GetConfiguration(uint16 Length);
USB_RESULT Standard_SetConfiguration(void);
uint8 *Standard_GetInterface(uint16 Length);
USB_RESULT Standard_SetInterface(void);
uint8 *Standard_GetDescriptorData(uint16 Length, PONE_DESCRIPTOR pDesc);

uint8 *Standard_GetStatus(uint16 Length);
USB_RESULT Standard_ClearFeature(void);
void SetDeviceAddress(uint8);
void NOP_Process(void);


/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/
extern DEVICE_PROP Device_Property;
extern  USER_STANDARD_REQUESTS User_Standard_Requests;
extern  DEVICE  Device_Table;
extern DEVICE_INFO Device_Info;

/* cells saving status during interrupt servicing */
extern vuint16 SaveRState;
extern vuint16 SaveTState;


/*  The number of current endpoint, it will be used to specify an endpoint */
extern uint8    EPindex;
/*  The number of current device, it is an index to the Device_Table */
/*extern uint8  Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
extern DEVICE_INFO* pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
extern DEVICE_PROP* pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
extern USER_STANDARD_REQUESTS *pUser_Standard_Requests;

extern uint16   SaveState ;
extern uint16 wInterrupt_Mask;



#endif /* HW_USB_CORE_H_ */
