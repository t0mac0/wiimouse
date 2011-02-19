/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_desc.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Descriptor Header for Virtual COM Port Device
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"
#include "usb.h"
#include "usb_hid.h"
#include "usb_cdc.h"
#include "usb_hid_mouse.h"
#include "usb_conf.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#pragma pack(push, 1)
typedef struct _DEVICE_CONFIGURATION_DESCRIPTOR{
	USB_CONFIGURATION_DESCRIPTOR 	ConfigDesc;

	// HID Mouse Interface
	USB_INTERFACE_DESCRIPTOR 		HidIfcDesc;
	HID_DESCRIPTOR 					HidDesc;
	USB_ENDPOINT_DESCRIPTOR 		HidEpDesc;

	// Virtual Com Interface
	INTERFACE_ASSOCIATION_DESCRIPTOR CdcIfcAssDesc;
	USB_INTERFACE_DESCRIPTOR 		CdcIfcDesc;
	CDC_HEADER_DESCRIPTOR 			CdcHeaderDesc;
	CDC_CM_DESCRIPTOR 				CdcCmDesc;
	CDC_ACM_DESCRIPTOR				CdcAcmDesc;
	CDC_UNION_IFC_DESCRIPTOR		CdcUnionIfcDesc;
	USB_ENDPOINT_DESCRIPTOR			CdcEpDesc;
	USB_INTERFACE_DESCRIPTOR		CdcDataIfcDesc;
	USB_ENDPOINT_DESCRIPTOR			CdcDataEpOutDesc;
	USB_ENDPOINT_DESCRIPTOR			CdcDataEpInDesc;

} DEVICE_CONFIGURATION_DESCRIPTOR;
#define DEVICE_CONFIGURATION_DESCRIPTOR_SIZE (sizeof(DEVICE_CONFIGURATION_DESCRIPTOR))
#pragma pack(pop)


#define CDC_IFC_NUM 1
#define CDC_DATA_IFC_NUM 2
#define HID_IFC_NUM 0



#define CUSTOMHID_OFF_HID_DESC    (USB_CONFIGURATION_DESCRIPTOR_SIZE + USB_INTERFACE_DESCRIPTOR_SIZE)

#define VIRTUAL_COM_PORT_DATA_SIZE              64
#define VIRTUAL_COM_PORT_INT_SIZE               8

//#define VIRTUAL_COM_PORT_SIZ_CONFIG_DESC        67
#define VIRTUAL_COM_PORT_SIZ_STRING_LANGID      4
#define VIRTUAL_COM_PORT_SIZ_STRING_VENDOR      38
#define VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT     50
#define VIRTUAL_COM_PORT_SIZ_STRING_SERIAL      26


/* Exported functions ------------------------------------------------------- */
extern const uint8 Virtual_Com_Port_DeviceDescriptor[USB_DEVICE_DESCRIPTOR_SIZE];
extern const uint8 Virtual_Com_Port_ConfigDescriptor[DEVICE_CONFIGURATION_DESCRIPTOR_SIZE];
extern const uint8 CustomHID_ReportDescriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE];

extern const uint8 Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID];
extern const uint8 Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR];
extern const uint8 Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT];
extern uint8 Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
