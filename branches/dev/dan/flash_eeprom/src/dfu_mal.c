/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : dfu_mal.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Generic media access Layer
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "dfu_mal.h"
#include "flash_if.h"
#include "platform_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16 (*pMAL_Init) (void);
uint16 (*pMAL_Erase) (uint32 SectorAddress, uint32 Length);
uint16 (*pMAL_Write) (uint32 SectorAddress, uint32 DataLength, bool Erase);
uint8  *(*pMAL_Read)  (uint32 SectorAddress, uint32 DataLength);
uint8  DFU_MalBuffer[MAL_BUFFER_SIZE]; /* RAM Buffer for Downloaded Data */
//extern ONE_DESCRIPTOR DFU_String_Descriptor[7];

bool DFU_MalWriteEnabled;
bool DFU_MalReadEnabled;


static const uint16  TimingTable[5][2] =
  {
    { 3000 ,  20 }, /* SPI Flash */
    { 1000 ,  25 }, /* NOR Flash M29W128F */
    {  100 , 104 }, /* Internal Flash */
    { 1000 ,  25 }, /* NOR Flash M29W128G */
    { 1000 ,  45 }  /* NOR Flash S29GL128 */
  };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16 MAL_Init(void)
{

  FLASH_If_Init(); /* Internal Flash */

  return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Erase
* Description    : Erase sector
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16 MAL_Erase(uint32 SectorAddress, uint32 Length)
{

  switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Erase = FLASH_If_Erase;
      break;
      
    default:
      return MAL_FAIL;
  }
  return pMAL_Erase(SectorAddress, Length);
}

/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16 MAL_Write (uint32 SectorAddress, uint32 DataLength)
{

  switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Write = FLASH_If_Write;
      break;

    default:
      return MAL_FAIL;
  }
  return pMAL_Write(SectorAddress, DataLength, FALSE);
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint8 *MAL_Read (uint32 SectorAddress, uint32 DataLength)
{

  switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Read = FLASH_If_Read;
      break;
      
    default:
      return 0;
  }
  return pMAL_Read (SectorAddress, DataLength);
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16 MAL_GetStatus(uint32 SectorAddress , uint8 Cmd, uint8 *buffer)
{
  uint8 x = (SectorAddress  >> 26) & 0x03 ; /* 0x000000000 --> 0 */
  /* 0x640000000 --> 1 */
  /* 0x080000000 --> 2 */

  uint8 y = Cmd & 0x01;

    
  SET_POLLING_TIMING(TimingTable[x][y]);  /* x: Erase/Write Timing */
  /* y: Media              */
  return MAL_OK;
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
