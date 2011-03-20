/**
  ******************************************************************************
  * @file  stm32f10x_flash.c
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  This file provides all the FLASH firmware functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_flash.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH 
  * @brief FLASH driver modules
  * @{
  */ 

/** @defgroup FLASH_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */ 

/** @defgroup FLASH_Private_Defines
  * @{
  */ 

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask         ((uint32)0x00000038)
#define ACR_HLFCYA_Mask          ((uint32)0xFFFFFFF7)
#define ACR_PRFTBE_Mask          ((uint32)0xFFFFFFEF)

/* Flash Access Control Register bits */
#define ACR_PRFTBS_Mask          ((uint32)0x00000020)

/* Flash Control Register bits */
#define CR_PG_Set                ((uint32)0x00000001)
#define CR_PG_Reset              ((uint32)0x00001FFE)
#define CR_PER_Set               ((uint32)0x00000002)
#define CR_PER_Reset             ((uint32)0x00001FFD)
#define CR_MER_Set               ((uint32)0x00000004)
#define CR_MER_Reset             ((uint32)0x00001FFB)
#define CR_OPTPG_Set             ((uint32)0x00000010)
#define CR_OPTPG_Reset           ((uint32)0x00001FEF)
#define CR_OPTER_Set             ((uint32)0x00000020)
#define CR_OPTER_Reset           ((uint32)0x00001FDF)
#define CR_STRT_Set              ((uint32)0x00000040)
#define CR_LOCK_Set              ((uint32)0x00000080)

/* FLASH Mask */
#define RDPRT_Mask               ((uint32)0x00000002)
#define WRP0_Mask                ((uint32)0x000000FF)
#define WRP1_Mask                ((uint32)0x0000FF00)
#define WRP2_Mask                ((uint32)0x00FF0000)
#define WRP3_Mask                ((uint32)0xFF000000)

/* FLASH Keys */
#define RDP_Key                  ((uint16)0x00A5)
#define FLASH_KEY1               ((uint32)0x45670123)
#define FLASH_KEY2               ((uint32)0xCDEF89AB)

/* Delay definition */   
#define EraseTimeout             ((uint32)0x00000FFF)
#define ProgramTimeout           ((uint32)0x0000000F)

#ifdef _FLASH

/**
  * @}
  */ 

/** @defgroup FLASH_Private_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup FLASH_Private_Variables
  * @{
  */

/**
  * @}
  */ 

/** @defgroup FLASH_Private_FunctionPrototypes
  * @{
  */

static void delay(void);
/**
  * @}
  */

/** @defgroup FLASH_Private_Functions
  * @{
  */
/**
  * @brief  Sets the code latency value.
  * @param FLASH_Latency: specifies the FLASH Latency value.
  *   This parameter can be one of the following values:
  * @arg FLASH_Latency_0: FLASH Zero Latency cycle
  * @arg FLASH_Latency_1: FLASH One Latency cycle
  * @arg FLASH_Latency_2: FLASH Two Latency cycles
  * @retval : None
  */
void FLASH_SetLatency(uint32 FLASH_Latency)
{
  uint32 tmpreg = 0;
  
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_LATENCY(FLASH_Latency));
  
  /* Read the ACR register */
  tmpreg = FLASH->ACR;  
  
  /* Sets the Latency value */
  tmpreg &= ACR_LATENCY_Mask;
  tmpreg |= FLASH_Latency;
  
  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}

/**
  * @brief  Enables or disables the Half cycle flash access.
  * @param FLASH_HalfCycleAccess: specifies the FLASH Half cycle Access mode.
  *   This parameter can be one of the following values:
  * @arg FLASH_HalfCycleAccess_Enable: FLASH Half Cycle Enable
  * @arg FLASH_HalfCycleAccess_Disable: FLASH Half Cycle Disable
  * @retval : None
  */
void FLASH_HalfCycleAccessCmd(uint32 FLASH_HalfCycleAccess)
{
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_HALFCYCLEACCESS_STATE(FLASH_HalfCycleAccess));
  
  /* Enable or disable the Half cycle access */
  FLASH->ACR &= ACR_HLFCYA_Mask;
  FLASH->ACR |= FLASH_HalfCycleAccess;
}

/**
  * @brief  Enables or disables the Prefetch Buffer.
  * @param FLASH_PrefetchBuffer: specifies the Prefetch buffer status.
  *   This parameter can be one of the following values:
  * @arg FLASH_PrefetchBuffer_Enable: FLASH Prefetch Buffer Enable
  * @arg FLASH_PrefetchBuffer_Disable: FLASH Prefetch Buffer Disable
  * @retval : None
  */
void FLASH_PrefetchBufferCmd(uint32 FLASH_PrefetchBuffer)
{
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_PREFETCHBUFFER_STATE(FLASH_PrefetchBuffer));
  
  /* Enable or disable the Prefetch Buffer */
  FLASH->ACR &= ACR_PRFTBE_Mask;
  FLASH->ACR |= FLASH_PrefetchBuffer;
}

/**
  * @brief  Unlocks the FLASH Program Erase Controller.
  * @param  None
  * @retval : None
  */
void FLASH_Unlock(void)
{
  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
}

/**
  * @brief  Locks the FLASH Program Erase Controller.
  * @param  None
  * @retval : None
  */
void FLASH_Lock(void)
{
  /* Set the Lock Bit to lock the FPEC and the FCR */
  FLASH->CR |= CR_LOCK_Set;
}

/**
  * @brief  Erases a specified FLASH page.
  * @param Page_Address: The page address to be erased.
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32 Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_ADDRESS(Page_Address));
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  
  if(status == FLASH_COMPLETE)
  { 
    /* if the previous operation is completed, proceed to erase the page */
    FLASH->CR|= CR_PER_Set;
    FLASH->AR = Page_Address; 
    FLASH->CR|= CR_STRT_Set;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status != FLASH_BUSY)
    {
      /* if the erase operation is completed, disable the PER Bit */
      FLASH->CR &= CR_PER_Reset;
    }
  }
  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all FLASH pages.
  * @param  None
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
     FLASH->CR |= CR_MER_Set;
     FLASH->CR |= CR_STRT_Set;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status != FLASH_BUSY)
    {
      /* if the erase operation is completed, disable the MER Bit */
      FLASH->CR &= CR_MER_Reset;
    }
  }	   
  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases the FLASH option bytes.
  * @param  None
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseOptionBytes(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    
    /* if the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    
    if(status == FLASH_COMPLETE)
    {
      /* if the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= CR_OPTER_Reset;
       
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= CR_OPTPG_Set;
      /* Enable the readout access */
      OB->RDP= RDP_Key; 
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
 
      if(status != FLASH_BUSY)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if (status != FLASH_BUSY)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }  
  }
  /* Return the erase status */
  return status;
}

/**
  * @brief  Programs a word at a specified address.
  * @param Address: specifies the address to be programmed.
  * @param Data: specifies the data to be programmed.
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramWord(uint32 Address, uint32 Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_ADDRESS(Address));
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new first 
    half word */
    FLASH->CR |= CR_PG_Set;
  
    *(vuint16*)Address = (uint16)Data;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
 
    if(status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new second 
      half word */
      *(vuint16*)(Address + 2) = Data >> 16;
    
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
        
      if(status != FLASH_BUSY)
      {
        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
      }
    }
    else
    {
      if (status != FLASH_BUSY)
      {
        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
      }
     }
  }
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified address.
  * @param Address: specifies the address to be programmed.
  * @param Data: specifies the data to be programmed.
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramHalfWord(uint32 Address, uint16 Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_ADDRESS(Address));
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new data */
    FLASH->CR |= CR_PG_Set;
  
    *(vuint16*)Address = Data;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }
  } 
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @param Address: specifies the address to be programmed.
  *   This parameter can be 0x1FFFF804 or 0x1FFFF806. 
  * @param Data: specifies the data to be programmed.
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramOptionByteData(uint32 Address, uint8 Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  ASSERT_PARAM(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Enables the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set; 
    *(vuint16*)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }    
  /* Return the Option Byte Data Program Status */
  return status;
}

/**
  * @brief  Write protects the desired pages
  * @param FLASH_Pages: specifies the address of the pages to be 
  *   write protected. This parameter can be:
  * @arg For STM32F10Xxx Medium-density devices (FLASH page size equal to 1 KB)
  * A value between FLASH_WRProt_Pages0to3 and FLASH_WRProt_Pages124to127
  * @arg For STM32F10Xxx High-density devices (FLASH page size equal to 2 KB) 
  * A value between FLASH_WRProt_Pages0to1 and  FLASH_WRProt_Pages60to61 
  * or FLASH_WRProt_Pages62to255 
  * @arg FLASH_WRProt_AllPages
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EnableWriteProtection(uint32 FLASH_Pages)
{
  uint16 WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
  
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_WRPROT_PAGE(FLASH_Pages));
  
  FLASH_Pages = (uint32)(~FLASH_Pages);
  WRP0_Data = (uint16)(FLASH_Pages & WRP0_Mask);
  WRP1_Data = (uint16)((FLASH_Pages & WRP1_Mask) >> 8);
  WRP2_Data = (uint16)((FLASH_Pages & WRP2_Mask) >> 16);
  WRP3_Data = (uint16)((FLASH_Pages & WRP3_Mask) >> 24);
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTPG_Set;
    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    
    if((status == FLASH_COMPLETE)&& (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;
     
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
          
    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  } 
  /* Return the write protection operation Status */
  return status;       
}

/**
  * @brief  Enables or disables the read out protection.
  *   If the user has already programmed the other option bytes before 
  *   calling this function, he must re-program them since this 
  *   function erases all option bytes.
  * @param Newstate: new state of the ReadOut Protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  ASSERT_PARAM(IS_FUNCTIONAL_STATE(NewState));
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
      /* if the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= CR_OPTER_Reset;
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= CR_OPTPG_Set; 
      if(NewState != DISABLE)
      {
        OB->RDP = 0x00;
      }
      else
      {
        OB->RDP = RDP_Key;  
      }
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(EraseTimeout); 
    
      if(status != FLASH_BUSY)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else 
    {
      if(status != FLASH_BUSY)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= CR_OPTER_Reset;
      }
    }
  }
  /* Return the protection operation Status */
  return status;      
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP /
  *   RST_STDBY.
  * @param OB_IWDG: Selects the IWDG mode
  *   This parameter can be one of the following values:
  * @arg OB_IWDG_SW: Software IWDG selected
  * @arg OB_IWDG_HW: Hardware IWDG selected
  * @param OB_STOP: Reset event when entering STOP mode.
  *   This parameter can be one of the following values:
  * @arg OB_STOP_NoRST: No reset generated when entering in STOP
  * @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param OB_STDBY: Reset event when entering Standby mode.
  *   This parameter can be one of the following values:
  * @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
  * @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_UserOptionByteConfig(uint16 OB_IWDG, uint16 OB_STOP, uint16 OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE; 
  /* Check the parameters */
  ASSERT_PARAM(IS_OB_IWDG_SOURCE(OB_IWDG));
  ASSERT_PARAM(IS_OB_STOP_SOURCE(OB_STOP));
  ASSERT_PARAM(IS_OB_STDBY_SOURCE(OB_STDBY));
  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set; 
           
    OB->USER = ( OB_IWDG | OB_STOP |OB_STDBY) | (uint16)0xF8;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }    
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @param  None
  * @retval : The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
  *   and RST_STDBY(Bit2).
  */
uint32 FLASH_GetUserOptionByte(void)
{
  /* Return the User Option Byte */
  return (uint32)(FLASH->OBR >> 2);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes Register value.
  * @param  None
  * @retval : The FLASH Write Protection  Option Bytes Register value
  */
uint32 FLASH_GetWriteProtectionOptionByte(void)
{
  /* Return the Falsh write protection Register value */
  return (uint32)(FLASH->WRPR);
}

/**
  * @brief  Checks whether the FLASH Read Out Protection Status is set 
  *   or not.
  * @param  None
  * @retval : FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_GetReadOutProtectionStatus(void)
{
  FlagStatus readoutstatus = RESET;
  if ((FLASH->OBR & RDPRT_Mask) != (uint32)RESET)
  {
    readoutstatus = SET;
  }
  else
  {
    readoutstatus = RESET;
  }
  return readoutstatus;
}

/**
  * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
  * @param  None
  * @retval : FLASH Prefetch Buffer Status (SET or RESET).
  */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
  FlagStatus bitstatus = RESET;
  
  if ((FLASH->ACR & ACR_PRFTBS_Mask) != (uint32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
  return bitstatus; 
}

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param FLASH_IT: specifies the FLASH interrupt sources to be 
  *   enabled or disabled.
  *   This parameter can be any combination of the following values:
  * @arg FLASH_IT_ERROR: FLASH Error Interrupt
  * @arg FLASH_IT_EOP: FLASH end of operation Interrupt
  * @param NewState: new state of the specified Flash interrupts.
  *   This parameter can be: ENABLE or DISABLE.      
  * @retval : None 
  */
void FLASH_ITConfig(uint16 FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_IT(FLASH_IT)); 
  ASSERT_PARAM(IS_FUNCTIONAL_STATE(NewState));
  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32)FLASH_IT;
  }
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param FLASH_FLAG: specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  * @arg FLASH_FLAG_BSY: FLASH Busy flag           
  * @arg FLASH_FLAG_PGERR: FLASH Program error flag       
  * @arg FLASH_FLAG_WRPRTERR: FLASH Write protected error flag      
  * @arg FLASH_FLAG_EOP: FLASH End of Operation flag           
  * @arg FLASH_FLAG_OPTERR:  FLASH Option Byte error flag     
  * @retval : The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint16 FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;
  if(FLASH_FLAG == FLASH_FLAG_OPTERR) 
  {
    if((FLASH->OBR & FLASH_FLAG_OPTERR) != (uint32)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
   if((FLASH->SR & FLASH_FLAG) != (uint32)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus;
}

/**
  * @brief  Clears the FLASH’s pending flags.
  * @param FLASH_FLAG: specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  * @arg FLASH_FLAG_BSY: FLASH Busy flag           
  * @arg FLASH_FLAG_PGERR: FLASH Program error flag       
  * @arg FLASH_FLAG_WRPRTERR: FLASH Write protected error flag      
  * @arg FLASH_FLAG_EOP: FLASH End of Operation flag           
  * @retval : None
  */
void FLASH_ClearFlag(uint16 FLASH_FLAG)
{
  /* Check the parameters */
  ASSERT_PARAM(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;
  
  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP or FLASH_COMPLETE
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    flashstatus = FLASH_BUSY;
  }
  else 
  {  
    if(FLASH->SR & FLASH_FLAG_PGERR)
    { 
      flashstatus = FLASH_ERROR_PG;
    }
    else 
    {
      if(FLASH->SR & FLASH_FLAG_WRPRTERR)
      {
        flashstatus = FLASH_ERROR_WRP;
      }
      else
      {
        flashstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the Flash Status */
  return flashstatus;
}

/**
  * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
  * @param Timeout: FLASH progamming Timeout
  * @retval : FLASH Status: The returned value can be: FLASH_BUSY, 
  *   FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or 
  *   FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32 Timeout)
{ 
  FLASH_Status status = FLASH_COMPLETE;
   
  /* Check for the Flash Status */
  status = FLASH_GetStatus();
  /* Wait for a Flash operation to complete or a TIMEOUT to occur */
  while((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    delay();
    status = FLASH_GetStatus();
    Timeout--;
  }
  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

/**
  * @brief  Inserts a time delay.
  * @param  None
  * @retval : None
  */
static void delay(void)
{
  vuint32 i = 0;
  for(i = 0xFF; i != 0; i--)
  {
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
