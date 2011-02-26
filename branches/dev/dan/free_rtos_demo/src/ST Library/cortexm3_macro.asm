/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : cortexm3_macro.s
* Author             : MCD Application Team
* Date First Issued  : 02/19/2007
* Description        : Instruction wrappers for special Cortex-M3 instructions.
*******************************************************************************
; History:
; 04/02/2007: V0.2
; 02/19/2007: V0.1
*******************************************************************************
; THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
; AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
; INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
; CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
; INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
    .syntax unified
    .cpu cortex-m3
    .fpu softvfp
    .thumb
    
.section    .text

  /* Exported functions */
  .global __WFI
  .global __WFE
  .global __SEV
  .global __ISB
  .global __DSB
  .global __DMB
  .global __SVC
  .global __MRS_CONTROL
  .global __MSR_CONTROL
  .global __MRS_PSP
  .global __MSR_PSP
  .global __MRS_MSP
  .global __MSR_MSP
  .global __SETPRIMASK
  .global __RESETPRIMASK
  .global __SETFAULTMASK
  .global __RESETFAULTMASK
  .global __BASEPRICONFIG
  .global __GetBASEPRI
  .global __REV_HalfWord
  .global __REV_Word

/*******************************************************************************
; Function Name  : __WFI
; Description    : Assembler function for the WFI instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __WFI, %function
__WFI:
 
    WFI
    BX r14

/*******************************************************************************
; Function Name  : __WFE
; Description    : Assembler function for the WFE instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __WFE, %function
__WFE:

    WFE
    BX r14

/*******************************************************************************
; Function Name  : __SEV
; Description    : Assembler function for the SEV instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __SEV, %function
__SEV:

    SEV
    BX r14

/*******************************************************************************
; Function Name  : __ISB
; Description    : Assembler function for the ISB instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __ISB, %function
__ISB:

    ISB
    BX r14

/*******************************************************************************
; Function Name  : __DSB
; Description    : Assembler function for the DSB instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __DSB, %function
__DSB:

    DSB
    BX r14

/*******************************************************************************
; Function Name  : __DMB
; Description    : Assembler function for the DMB instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __DMB, %function
__DMB:

    DMB
    BX r14

/*******************************************************************************
; Function Name  : __SVC
; Description    : Assembler function for the SVC instruction.
; Input          : None
; Return         : None
*******************************************************************************/
.type   __SVC, %function
__SVC:

    SVC 0x01
    BX r14

/*******************************************************************************
; Function Name  : __MRS_CONTROL
; Description    : Assembler function for the MRS instruction.
; Input          : None
; Return         : - r0 : Cortex-M3 CONTROL register value.
*******************************************************************************/
.type   __MRS_CONTROL, %function
__MRS_CONTROL:

  MRS r0, CONTROL
  BX r14

/*******************************************************************************
; Function Name  : __MSR_CONTROL
; Description    : Assembler function for the MSR instruction.
; Input          : - r0 : Cortex-M3 CONTROL register new value.  
; Return         : None
*******************************************************************************/
.type   __MSR_CONTROL, %function
__MSR_CONTROL:

  MSR CONTROL, r0
  ISB
  BX r14

/*******************************************************************************
; Function Name  : __MRS_PSP
; Description    : Assembler function for the MRS instruction.
; Input          : None
; Return         : - r0 : Process Stack value.
*******************************************************************************/
.type   __MRS_PSP, %function
__MRS_PSP:

  MRS r0, PSP
  BX r14

/*******************************************************************************
; Function Name  : __MSR_PSP
; Description    : Assembler function for the MSR instruction.
; Input          : - r0 : Process Stack new value.
; Return         : None
*******************************************************************************/
.type   __MSR_PSP, %function
__MSR_PSP:

    MSR psp, r0 /* set Process Stack value */
    BX r14

/*******************************************************************************
; Function Name  : __MRS_MSP
; Description    : Assembler function for the MRS instruction.
; Input          : None
; Return         : - r0 : Main Stack value.
*******************************************************************************/
.type   __MRS_MSP, %function
__MRS_MSP:

  MRS r0, MSP
  BX r14

/*******************************************************************************
; Function Name  : __MSR_MSP
; Description    : Assembler function for the MSR instruction.
; Input          : - r0 : Main Stack new value.
; Return         : None
*******************************************************************************/
.type   __MSR_MSP, %function
__MSR_MSP:

    MSR MSP, r0  /* set Main Stack value */
    BX r14

/*******************************************************************************
; Function Name  : __SETPRIMASK
; Description    : Assembler function to set the PRIMASK.
; Input          : None 
; Return         : None
*******************************************************************************/
.type   __SETPRIMASK, %function
__SETPRIMASK:

  CPSID i
  BX r14

/*******************************************************************************
; Function Name  : __RESETPRIMASK
; Description    : Assembler function to reset the PRIMASK.
; Input          : None 
; Return         : None
*******************************************************************************/
.type   __RESETPRIMASK, %function
__RESETPRIMASK:

  CPSIE i
  BX r14

/*******************************************************************************
; Function Name  : __SETFAULTMASK
; Description    : Assembler function to set the FAULTMASK.
; Input          : None 
; Return         : None
*******************************************************************************/
.type   __SETFAULTMASK, %function
__SETFAULTMASK:

  CPSID f
  BX r14

/*******************************************************************************
; Function Name  : __RESETFAULTMASK
; Description    : Assembler function to reset the FAULTMASK.
; Input          : None 
; Return         : None
*******************************************************************************/
.type   __RESETFAULTMASK, %function
__RESETFAULTMASK:

  CPSIE f
  BX r14

/*******************************************************************************
; Function Name  : __BASEPRICONFIG
; Description    : Assembler function to set the Base Priority.
; Input          : - r0 : Base Priority new value  
; Return         : None
*******************************************************************************/
.type   __BASEPRICONFIG, %function
__BASEPRICONFIG:

  MSR BASEPRI, r0
  BX r14

/*******************************************************************************
; Function Name  : __GetBASEPRI
; Description    : Assembler function to get the Base Priority value.
; Input          : None 
; Return         : - r0 : Base Priority value 
*******************************************************************************/
.type   __GetBASEPRI, %function
__GetBASEPRI:

  MRS r0, BASEPRI_MAX
  BX r14

/*******************************************************************************
; Function Name  : __REV_HalfWord
; Description    : Reverses the byte order in HalfWord(16-bit) input variable.
; Input          : - r0 : specifies the input variable
; Return         : - r0 : holds tve variable value after byte reversing.
*******************************************************************************/
.type   __REV_HalfWord, %function
__REV_HalfWord :
 
  REV16 r0, r0
  BX r14

/*******************************************************************************
; Function Name  : __REV_Word
; Description    : Reverses the byte order in Word(32-bit) input variable.
; Input          : - r0 : specifies the input variable
; Return         : - r0 : holds tve variable value after byte reversing.
********************************************************************************/
.type   __REV_Word, %function
__REV_Word:
 
  REV r0, r0
  BX r14
  

  
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE*****/
