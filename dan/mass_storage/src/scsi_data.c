/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : scsi_data.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Initialization of the SCSI data
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_scsi.h"
#include "memory.h"


uint8 Page00_Inquiry_Data[] =
  {
    0x00, /* PERIPHERAL QUALIFIER & PERIPHERAL DEVICE TYPE*/
    0x00,
    0x00,
    0x00,
    0x00 /* Supported Pages 00*/
  };
uint8 Standard_Inquiry_Data[] =
  {
    0x00,          /* Direct Access Device */
    0x80,          /* RMB = 1: Removable Medium */
    0x00,          /* Version: No conformance claim to standard */
    0x02,

    0x1F,          /* Additional Length */
    'F',
   	 'S',
   	  'L',
   	  ' ',
   	  ' ',
   	  'U',
   	  'S',
   	  'B',
   	  ' ',
   	  'B',
   	  'o',
   	  'o',
   	  't',
   	  'l',
   	  'o',
   	  'a',
   	  'd',
   	  'e',
       'r',
   	  ' ',
   	  ' ',
   	  ' ',
   	  ' ',
   	  ' ',
   	  0x30,        // 32 '0'
   	  0x30,        // 33 '0'
   	  0x30,        // 34 '0'
   	  0x31,        // 35 '1'
  };

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
uint8 Mode_Sense6_data[] =
  {
    0x03,
    0x00,
    0x00,
    0x00,
  };

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

uint8 Mode_Sense10_data[] =
  {
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  };
uint8 Scsi_Sense_Data[] =
  {
    0x70, /*RespCode*/
    0x00, /*SegmentNumber*/
    NO_SENSE, /* Sens_Key*/
    0x00,
    0x00,
    0x00,
    0x00, /*Information*/
    0x0A, /*AdditionalSenseLength*/
    0x00,
    0x00,
    0x00,
    0x00, /*CmdInformation*/
    NO_SENSE, /*Asc*/
    0x00, /*ASCQ*/
    0x00, /*FRUC*/
    0x00, /*TBD*/
    0x00,
    0x00 /*SenseKeySpecific*/
  };



/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
