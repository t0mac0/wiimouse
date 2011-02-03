/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
 * File Name          : usb_prop.c
 * Author             : MCD Application Team
 * Version            : V3.2.1
 * Date               : 07/05/2010
 * Description        : All processings related to Custom HID Demo
 ********************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32 ProtocolValue;
__IO uint8 EXTI_Enable;

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
{
		EP_NUM,
		1
};

DEVICE_PROP Device_Property =
{
		CustomHID_init,
		CustomHID_Reset,
		CustomHID_Status_In,
		CustomHID_Status_Out,
		CustomHID_Data_Setup,
		CustomHID_NoData_Setup,
		CustomHID_Get_Interface_Setting,
		CustomHID_GetDeviceDescriptor,
		CustomHID_GetConfigDescriptor,
		CustomHID_GetStringDescriptor,
		0,
		0x40 /*MAX PACKET SIZE*/
};
USER_STANDARD_REQUESTS User_Standard_Requests =
{
		CustomHID_GetConfiguration,
		CustomHID_SetConfiguration,
		CustomHID_GetInterface,
		CustomHID_SetInterface,
		CustomHID_GetStatus,
		CustomHID_ClearFeature,
		CustomHID_SetEndPointFeature,
		CustomHID_SetDeviceFeature,
		CustomHID_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
		(uint8*)CustomHID_DeviceDescriptor,
		USB_DEVICE_DESCRIPTOR_SIZE
};

ONE_DESCRIPTOR Config_Descriptor =
{
		(uint8*)CustomHID_ConfigDescriptor,
		WII_MOUSE_CONFIGURATION_DESCRIPTOR_SIZE
};

ONE_DESCRIPTOR CustomHID_Report_Descriptor =
{
		(uint8 *)CustomHID_ReportDescriptor,
		HID_MOUSE_REPORT_DESCRIPTOR_SIZE
};

ONE_DESCRIPTOR CustomHID_Hid_Descriptor =
{
		(uint8*)CustomHID_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,
		HID_DESCRIPTOR_SIZE
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
		{(uint8*)CustomHID_StringLangID, CUSTOMHID_SIZ_STRING_LANGID},
		{(uint8*)CustomHID_StringVendor, CUSTOMHID_SIZ_STRING_VENDOR},
		{(uint8*)CustomHID_StringProduct, CUSTOMHID_SIZ_STRING_PRODUCT},
		{(uint8*)CustomHID_StringSerial, CUSTOMHID_SIZ_STRING_SERIAL}
};

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : CustomHID_init.
 * Description    : Custom HID init routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CustomHID_init(void)
{
	/* Update the serial number string descriptor with the data from the unique
  ID*/
	Get_SerialNum();

	pInformation->Current_Configuration = 0;
	/* Connect the device */
	PowerOn();

	/* Perform basic device initialization operations */
	USB_SIL_Init();

	bDeviceState = UNCONNECTED;
}

/*******************************************************************************
 * Function Name  : CustomHID_Reset.
 * Description    : Custom HID reset routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CustomHID_Reset(void)
{
	/* Set Joystick_DEVICE as not configured */
	pInformation->Current_Configuration = 0;
	pInformation->Current_Interface = 0;/*the default Interface*/

	/* Current Feature initialization */
	pInformation->Current_Feature = CustomHID_ConfigDescriptor[7];

#ifdef STM32F10X_CL   
	/* EP0 is already configured in DFU_Init() by USB_SIL_Init() function */

	/* Init EP1 IN as Interrupt endpoint */
	OTG_DEV_EP_Init(EP1_IN, OTG_DEV_EP_TYPE_INT, 2);

	/* Init EP1 OUT as Interrupt endpoint */
	OTG_DEV_EP_Init(EP1_OUT, OTG_DEV_EP_TYPE_INT, 2);
#else 
	SetBTABLE(BTABLE_ADDRESS);

	/* Initialize Endpoint 0 */
	SetEPType(ENDP0, EP_CONTROL);
	SetEPTxStatus(ENDP0, EP_TX_STALL);
	SetEPRxAddr(ENDP0, ENDP0_RXADDR);
	SetEPTxAddr(ENDP0, ENDP0_TXADDR);
	Clear_Status_Out(ENDP0);
	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxValid(ENDP0);

	/* Initialize Endpoint 1 */
	SetEPType(ENDP1, EP_INTERRUPT);
	SetEPTxAddr(ENDP1, ENDP1_TXADDR);
	SetEPTxCount(ENDP1, 3);
	SetEPRxStatus(ENDP1, EP_RX_DIS);
	SetEPTxStatus(ENDP1, EP_TX_NAK);

	/* Set this device to response on default address */
	SetDeviceAddress(0);
#endif /* STM32F10X_CL */

	bDeviceState = ATTACHED;
}
/*******************************************************************************
 * Function Name  : CustomHID_SetConfiguration.
 * Description    : Udpade the device state to configured and command the ADC
 *                  conversion.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CustomHID_SetConfiguration(void)
{
	if (pInformation->Current_Configuration != 0)
	{
		/* Device configured */
		bDeviceState = CONFIGURED;

	}
}
/*******************************************************************************
 * Function Name  : CustomHID_SetConfiguration.
 * Description    : Udpade the device state to addressed.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CustomHID_SetDeviceAddress (void)
{
	bDeviceState = ADDRESSED;
}
/*******************************************************************************
 * Function Name  : CustomHID_Status_In.
 * Description    : Joystick status IN routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CustomHID_Status_In(void)
{
}

/*******************************************************************************
 * Function Name  : CustomHID_Status_Out
 * Description    : Joystick status OUT routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void CustomHID_Status_Out (void)
{
}

/*******************************************************************************
 * Function Name  : CustomHID_Data_Setup
 * Description    : Handle the data class specific requests.
 * Input          : Request Nb.
 * Output         : None.
 * Return         : USB_UNSUPPORT or USB_SUCCESS.
 *******************************************************************************/
RESULT CustomHID_Data_Setup(uint8 RequestNo)
{
	uint8 *(*CopyRoutine)(uint16);

	CopyRoutine = NULL;

	if ((RequestNo == GET_DESCRIPTOR)
			&& (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
			&& (pInformation->USBwIndex0 == 0))
	{

		if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
		{
			CopyRoutine = CustomHID_GetReportDescriptor;
		}
		else if (pInformation->USBwValue1 == HID_HID_DESCRIPTOR_TYPE)
		{
			CopyRoutine = CustomHID_GetHIDDescriptor;
		}

	} /* End of GET_DESCRIPTOR */

	/*** GET_PROTOCOL ***/
	else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
			&& RequestNo == GET_PROTOCOL)
	{
		CopyRoutine = CustomHID_GetProtocolValue;
	}

	if (CopyRoutine == NULL)
	{
		return USB_UNSUPPORT;
	}

	pInformation->Ctrl_Info.CopyData = CopyRoutine;
	pInformation->Ctrl_Info.Usb_wOffset = 0;
	(*CopyRoutine)(0);
	return USB_SUCCESS;
}

/*******************************************************************************
 * Function Name  : CustomHID_NoData_Setup
 * Description    : handle the no data class specific requests
 * Input          : Request Nb.
 * Output         : None.
 * Return         : USB_UNSUPPORT or USB_SUCCESS.
 *******************************************************************************/
RESULT CustomHID_NoData_Setup(uint8 RequestNo)
{
	if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
			&& (RequestNo == SET_PROTOCOL))
	{
		return CustomHID_SetProtocol();
	}

	else
	{
		return USB_UNSUPPORT;
	}
}

/*******************************************************************************
 * Function Name  : CustomHID_GetDeviceDescriptor.
 * Description    : Gets the device descriptor.
 * Input          : Length
 * Output         : None.
 * Return         : The address of the device descriptor.
 *******************************************************************************/
uint8 *CustomHID_GetDeviceDescriptor(uint16 Length)
{
	return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
 * Function Name  : CustomHID_GetConfigDescriptor.
 * Description    : Gets the configuration descriptor.
 * Input          : Length
 * Output         : None.
 * Return         : The address of the configuration descriptor.
 *******************************************************************************/
uint8 *CustomHID_GetConfigDescriptor(uint16 Length)
{
	return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
 * Function Name  : CustomHID_GetStringDescriptor
 * Description    : Gets the string descriptors according to the needed index
 * Input          : Length
 * Output         : None.
 * Return         : The address of the string descriptors.
 *******************************************************************************/
uint8 *CustomHID_GetStringDescriptor(uint16 Length)
{
	uint8 wValue0 = pInformation->USBwValue0;
	if (wValue0 > 4)
	{
		return NULL;
	}
	else
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
	}
}

/*******************************************************************************
 * Function Name  : CustomHID_GetReportDescriptor.
 * Description    : Gets the HID report descriptor.
 * Input          : Length
 * Output         : None.
 * Return         : The address of the configuration descriptor.
 *******************************************************************************/
uint8 *CustomHID_GetReportDescriptor(uint16 Length)
{
	return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}

/*******************************************************************************
 * Function Name  : CustomHID_GetHIDDescriptor.
 * Description    : Gets the HID descriptor.
 * Input          : Length
 * Output         : None.
 * Return         : The address of the configuration descriptor.
 *******************************************************************************/
uint8 *CustomHID_GetHIDDescriptor(uint16 Length)
{
	return Standard_GetDescriptorData(Length, &CustomHID_Hid_Descriptor);
}

/*******************************************************************************
 * Function Name  : CustomHID_Get_Interface_Setting.
 * Description    : tests the interface and the alternate setting according to the
 *                  supported one.
 * Input          : - Interface : interface number.
 *                  - AlternateSetting : Alternate Setting number.
 * Output         : None.
 * Return         : USB_SUCCESS or USB_UNSUPPORT.
 *******************************************************************************/
RESULT CustomHID_Get_Interface_Setting(uint8 Interface, uint8 AlternateSetting)
{
	if (AlternateSetting > 0)
	{
		return USB_UNSUPPORT;
	}
	else if (Interface > 0)
	{
		return USB_UNSUPPORT;
	}
	return USB_SUCCESS;
}

/*******************************************************************************
 * Function Name  : CustomHID_SetProtocol
 * Description    : Joystick Set Protocol request routine.
 * Input          : None.
 * Output         : None.
 * Return         : USB SUCCESS.
 *******************************************************************************/
RESULT CustomHID_SetProtocol(void)
{
	uint8 wValue0 = pInformation->USBwValue0;
	ProtocolValue = wValue0;
	return USB_SUCCESS;
}

/*******************************************************************************
 * Function Name  : CustomHID_GetProtocolValue
 * Description    : get the protocol value
 * Input          : Length.
 * Output         : None.
 * Return         : address of the protcol value.
 *******************************************************************************/
uint8 *CustomHID_GetProtocolValue(uint16 Length)
{
	if (Length == 0)
	{
		pInformation->Ctrl_Info.Usb_wLength = 1;
		return NULL;
	}
	else
	{
		return (uint8 *)(&ProtocolValue);
	}
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
