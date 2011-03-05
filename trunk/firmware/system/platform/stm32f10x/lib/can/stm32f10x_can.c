/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_can.c
* Author             : MCD Application Team
* Date First Issued  : 09/29/2006
* Description        : This file provides all the CAN firmware functions.
********************************************************************************
* History:
* 04/02/2007: V0.2
* 02/05/2007: V0.1
* 09/29/2006: V0.01
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_can.h"
#include "../rcc/stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* CAN Master Control Register bits */
#define CAN_MCR_INRQ     ((uint32)0x00000001) /* Initialization request */
#define CAN_MCR_SLEEP    ((uint32)0x00000002) /* Sleep mode request */
#define CAN_MCR_TXFP     ((uint32)0x00000004) /* Transmit FIFO priority */
#define CAN_MCR_RFLM     ((uint32)0x00000008) /* Receive FIFO locked mode */
#define CAN_MCR_NART     ((uint32)0x00000010) /* No automatic retransmission */
#define CAN_MCR_AWUM     ((uint32)0x00000020) /* Automatic wake up mode */
#define CAN_MCR_ABOM     ((uint32)0x00000040) /* Automatic bus-off management */
#define CAN_MCR_TTCM     ((uint32)0x00000080) /* time triggered communication */

/* CAN Master Status Register bits */
#define CAN_MSR_INAK     ((uint32)0x00000001)    /* Initialization acknowledge */
#define CAN_MSR_WKUI     ((uint32)0x00000008)    /* Wake-up interrupt */
#define CAN_MSR_SLAKI    ((uint32)0x00000010)    /* Sleep acknowledge interrupt */

/* CAN Transmit Status Register bits */
#define CAN_TSR_RQCP0    ((uint32)0x00000001)    /* Request completed mailbox0 */
#define CAN_TSR_TXOK0    ((uint32)0x00000002)    /* Transmission OK of mailbox0 */
#define CAN_TSR_ABRQ0    ((uint32)0x00000080)    /* Abort request for mailbox0 */
#define CAN_TSR_RQCP1    ((uint32)0x00000100)    /* Request completed mailbox1 */
#define CAN_TSR_TXOK1    ((uint32)0x00000200)    /* Transmission OK of mailbox1 */
#define CAN_TSR_ABRQ1    ((uint32)0x00008000)    /* Abort request for mailbox1 */
#define CAN_TSR_RQCP2    ((uint32)0x00010000)    /* Request completed mailbox2 */
#define CAN_TSR_TXOK2    ((uint32)0x00020000)    /* Transmission OK of mailbox2 */
#define CAN_TSR_ABRQ2    ((uint32)0x00800000)    /* Abort request for mailbox2 */
#define CAN_TSR_TME0     ((uint32)0x04000000)    /* Transmit mailbox 0 empty */
#define CAN_TSR_TME1     ((uint32)0x08000000)    /* Transmit mailbox 1 empty */
#define CAN_TSR_TME2     ((uint32)0x10000000)    /* Transmit mailbox 2 empty */

/* CAN Receive FIFO 0 Register bits */
#define CAN_RF0R_FULL0   ((uint32)0x00000008)    /* FIFO 0 full */
#define CAN_RF0R_FOVR0   ((uint32)0x00000010)    /* FIFO 0 overrun */
#define CAN_RF0R_RFOM0   ((uint32)0x00000020)    /* Release FIFO 0 output mailbox */

/* CAN Receive FIFO 1 Register bits */
#define CAN_RF1R_FULL1   ((uint32)0x00000008)    /* FIFO 1 full */
#define CAN_RF1R_FOVR1   ((uint32)0x00000010)    /* FIFO 1 overrun */
#define CAN_RF1R_RFOM1   ((uint32)0x00000020)    /* Release FIFO 1 output mailbox */

/* CAN Error Status Register bits */
#define CAN_ESR_EWGF     ((uint32)0x00000001)    /* Error warning flag */
#define CAN_ESR_EPVF     ((uint32)0x00000002)    /* Error passive flag */
#define CAN_ESR_BOFF     ((uint32)0x00000004)    /* Bus-off flag */

/* CAN Mailbox Transmit Request */
#define CAN_TMIDxR_TXRQ    ((uint32)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define CAN_FMR_FINIT ((uint32)0x00000001) /* Filter init mode */

#ifdef _CAN

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static ITStatus CheckITStatus(uint32 CAN_Reg, uint32 It_Bit);

/* Private function prototypes -----------------------------------------------*/



/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : CAN_DeInit
* Description    : Deinitializes the CAN peripheral registers to their default
*                  reset values.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_DeInit(void)
{
  /* Enable CAN reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN, ENABLE);
  /* Release CAN from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN, DISABLE);
}

/*******************************************************************************
* Function Name  : CAN_Init
* Description    : Initializes the CAN peripheral according to the specified
*                  parameters in the CAN_InitStruct.
* Input          : CAN_InitStruct: pointer to a CAN_InitTypeDef structure that
                   contains the configuration information for the CAN peripheral.
* Output         : None.
* Return         : Constant indicates initialization succeed which will be 
*                  CANINITFAILED or CANINITOK.
*******************************************************************************/
uint8 CAN_Init(CAN_InitTypeDef* CAN_InitStruct)
{
  uint8 InitStatus = 0;

  /* Check the parameters */
  ASSERT(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TTCM));
  ASSERT(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_ABOM));
  ASSERT(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_AWUM));
  ASSERT(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_NART));
  ASSERT(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_RFLM));
  ASSERT(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TXFP));
  ASSERT(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
  ASSERT(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
  ASSERT(IS_CAN_BS1(CAN_InitStruct->CAN_BS1));
  ASSERT(IS_CAN_BS2(CAN_InitStruct->CAN_BS2));
  ASSERT(IS_CAN_CLOCK(CAN_InitStruct->CAN_Clock));
  ASSERT(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));

  /* Request initialisation */
  CAN->MCR = CAN_MCR_INRQ;

  /* ...and check acknowledged */
  if ((CAN->MSR & CAN_MSR_INAK) == 0)
  {
    InitStatus = CANINITFAILED;
  }
  else
  {
    /* Set the time triggered communication mode */
    if (CAN_InitStruct->CAN_TTCM == ENABLE)
    {
      CAN->MCR |= CAN_MCR_TTCM;
    }
    else
    {
      CAN->MCR &= ~CAN_MCR_TTCM;
    }

    /* Set the automatic bus-off management */
    if (CAN_InitStruct->CAN_ABOM == ENABLE)
    {
      CAN->MCR |= CAN_MCR_ABOM;
    }
    else
    {
      CAN->MCR &= ~CAN_MCR_ABOM;
    }

    /* Set the automatic wake-up mode */
    if (CAN_InitStruct->CAN_AWUM == ENABLE)
    {
      CAN->MCR |= CAN_MCR_AWUM;
    }
    else
    {
      CAN->MCR &= ~CAN_MCR_AWUM;
    }

    /* Set the no automatic retransmission */
    if (CAN_InitStruct->CAN_NART == ENABLE)
    {
      CAN->MCR |= CAN_MCR_NART;
    }
    else
    {
      CAN->MCR &= ~CAN_MCR_NART;
    }

    /* Set the receive FIFO locked mode */
    if (CAN_InitStruct->CAN_RFLM == ENABLE)
    {
      CAN->MCR |= CAN_MCR_RFLM;
    }
    else
    {
      CAN->MCR &= ~CAN_MCR_RFLM;
    }

    /* Set the transmit FIFO priority */
    if (CAN_InitStruct->CAN_TXFP == ENABLE)
    {
      CAN->MCR |= CAN_MCR_TXFP;
    }
    else
    {
      CAN->MCR &= ~CAN_MCR_TXFP;
    }

    /* Set the bit timing register */
    CAN->BTR = (uint32)((uint32)CAN_InitStruct->CAN_Mode << 30) | ((uint32)CAN_InitStruct->CAN_SJW << 24) |
               ((uint32)CAN_InitStruct->CAN_BS1 << 16) | ((uint32)CAN_InitStruct->CAN_BS2 << 20) |
               ((uint32)CAN_InitStruct->CAN_Clock << 15) | ((uint32)CAN_InitStruct->CAN_Prescaler - 1);

    InitStatus = CANINITOK;

    /* Request leave initialisation */
    CAN->MCR &= ~CAN_MCR_INRQ;

    /* ...and check acknowledged */
    if ((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK)
    {
      InitStatus = CANINITFAILED;
    }
  }

  /* At this step, return the status of initialization */
  return InitStatus;
}

/*******************************************************************************
* Function Name  : CAN_FilterInit
* Description    : Initializes the CAN peripheral according to the specified
*                  parameters in the CAN_FilterInitStruct.
* Input          : CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef
*                  structure that contains the configuration information.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{
  uint16 FilterNumber_BitPos = 0;

  /* Check the parameters */
  ASSERT(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
  ASSERT(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
  ASSERT(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
  ASSERT(IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment));
  ASSERT(IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation));

  FilterNumber_BitPos = (uint16)((uint16)0x0001 << ((uint16)CAN_FilterInitStruct->CAN_FilterNumber));

  /* Initialisation mode for the filter */
  CAN->FMR |= CAN_FMR_FINIT;

  /* Filter Deactivation */
  CAN->FA0R &= ~(uint32)FilterNumber_BitPos;

  /* Filter Scale */
  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit)
  {
    /* 16-bit scale for the filter */
    CAN->FS0R &= ~(uint32)FilterNumber_BitPos;

    /* First 16-bit identifier and First 16-bit mask */
    /* Or First 16-bit identifier and Second 16-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR0 = ((uint32)((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdLow) << 16) |
        ((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdLow);

    /* Second 16-bit identifier and Second 16-bit mask */
    /* Or Third 16-bit identifier and Fourth 16-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = ((uint32)((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        ((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdHigh);
  }
  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit)
  {
    /* 32-bit scale for the filter */
    CAN->FS0R |= FilterNumber_BitPos;

    /* 32-bit identifier or First 32-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR0 = ((uint32)((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
        ((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdLow);

    /* 32-bit mask or Second 32-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = ((uint32)((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        ((uint32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdLow);

  }

  /* Filter Mode */
  if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
  {
    /*Id/Mask mode for the filter*/
    CAN->FM0R &= ~(uint32)FilterNumber_BitPos;
  }
  else /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
  {
    /*Identifier list mode for the filter*/
    CAN->FM0R |= (uint32)FilterNumber_BitPos;
  }

  /* Filter FIFO assignment */
  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_FilterFIFO0)
  {
    /* FIFO 0 assignation for the filter */
    CAN->FFA0R &= ~(uint32)FilterNumber_BitPos;
  }
  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_FilterFIFO1)
  {
    /* FIFO 1 assignation for the filter */
    CAN->FFA0R |= (uint32)FilterNumber_BitPos;
  }
  
  /* Filter activation */
  if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
  {
    CAN->FA0R |= FilterNumber_BitPos;
  }

  /* Leave the initialisation mode for the filter */
  CAN->FMR &= ~CAN_FMR_FINIT;
}

/*******************************************************************************
* Function Name  : CAN_StructInit
* Description    : Fills each CAN_InitStruct member with its default value.
* Input          : CAN_InitStruct: pointer to a CAN_InitTypeDef structure which
*                  will be initialized.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct)
{
  /* Reset CAN init structure parameters values */

  /* Initialize the time triggered communication mode */
  CAN_InitStruct->CAN_TTCM = DISABLE;

  /* Initialize the automatic bus-off management */
  CAN_InitStruct->CAN_ABOM = DISABLE;

  /* Initialize the automatic wake-up mode */
  CAN_InitStruct->CAN_AWUM = DISABLE;

  /* Initialize the no automatic retransmission */
  CAN_InitStruct->CAN_NART = DISABLE;

  /* Initialize the receive FIFO locked mode */
  CAN_InitStruct->CAN_RFLM = DISABLE;

  /* Initialize the transmit FIFO priority */
  CAN_InitStruct->CAN_TXFP = DISABLE;

  /* Initialize the CAN_Mode member */
  CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;

  /* Initialize the CAN_SJW member */
  CAN_InitStruct->CAN_SJW = CAN_SJW_0tq;

  /* Initialize the CAN_BS1 member */
  CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;

  /* Initialize the CAN_BS2 member */
  CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;

  /* Initialize the CAN_Clock member */
  CAN_InitStruct->CAN_Clock = CAN_Clock_APB;

  /* Initialize the CAN_Prescaler member */
  CAN_InitStruct->CAN_Prescaler = 1;
}

/*******************************************************************************
* Function Name  : CAN_ITConfig
* Description    : Enables or disables the CAN interrupts.
* Input          : - CAN_IT: specifies the CAN interrupt sources to be enabled or
*                    disabled.
*                  - NewState: new state of the CAN interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_ITConfig(uint32 CAN_IT, FunctionalState NewState)
{
  /* Check the parameters */
  ASSERT(IS_CAN_IT(CAN_IT));
  ASSERT(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CAN interrupt */
    CAN->IER |= CAN_IT;
  }
  else
  {
    /* Disable the selected CAN interrupt */
    CAN->IER &= ~CAN_IT;
  }
}

/*******************************************************************************
* Function Name  : CAN_Transmit
* Description    : Initiates the transmission of a message.
* Input          : TxMessage: pointer to a structure which contains CAN Id, CAN
*                  DLC and CAN datas.
* Output         : None.
* Return         : The number of the mailbox that is used for transmission
*                  or CAN_NO_MB if there is no empty mailbox.
*******************************************************************************/
uint8 CAN_Transmit(CanTxMsg* TxMessage)
{
  uint8 TransmitMailbox = 0;

  /* Check the parameters */
  ASSERT(IS_CAN_STDID(TxMessage->StdId));
  ASSERT(IS_CAN_EXTID(TxMessage->StdId));
  ASSERT(IS_CAN_IDTYPE(TxMessage->IDE));
  ASSERT(IS_CAN_RTR(TxMessage->RTR));
  ASSERT(IS_CAN_DLC(TxMessage->DLC));

  /* Select one empty transmit mailbox */
  if ((CAN->TSR&CAN_TSR_TME0) == CAN_TSR_TME0)
  {
    TransmitMailbox = 0;
  }
  else if ((CAN->TSR&CAN_TSR_TME1) == CAN_TSR_TME1)
  {
    TransmitMailbox = 1;
  }
  else if ((CAN->TSR&CAN_TSR_TME2) == CAN_TSR_TME2)
  {
    TransmitMailbox = 2;
  }
  else
  {
    TransmitMailbox = CAN_NO_MB;
  }

  if (TransmitMailbox != CAN_NO_MB)
  {
    /* Set up the Id */
    TxMessage->StdId &= (uint32)0x000007FF;
    TxMessage->StdId = TxMessage->StdId << 21;
    TxMessage->ExtId &= (uint32)0x0003FFFF;
    TxMessage->ExtId <<= 3;

    CAN->sTxMailBox[TransmitMailbox].TIR &= CAN_TMIDxR_TXRQ;
    CAN->sTxMailBox[TransmitMailbox].TIR |= (TxMessage->StdId | TxMessage->ExtId |
                                            TxMessage->IDE | TxMessage->RTR);

    /* Set up the DLC */
    TxMessage->DLC &= (uint8)0x0000000F;
    CAN->sTxMailBox[TransmitMailbox].TDTR &= (uint32)0xFFFFFFF0;
    CAN->sTxMailBox[TransmitMailbox].TDTR |= TxMessage->DLC;

    /* Set up the data field */
    CAN->sTxMailBox[TransmitMailbox].TDLR = (((uint32)TxMessage->Data[3] << 24) | ((uint32)TxMessage->Data[2] << 16) |
                                            ((uint32)TxMessage->Data[1] << 8) | ((uint32)TxMessage->Data[0]));
    CAN->sTxMailBox[TransmitMailbox].TDHR = (((uint32)TxMessage->Data[7] << 24) | ((uint32)TxMessage->Data[6] << 16) |
                                            ((uint32)TxMessage->Data[5] << 8) | ((uint32)TxMessage->Data[4]));

    /* Request transmission */
    CAN->sTxMailBox[TransmitMailbox].TIR |= CAN_TMIDxR_TXRQ;
  }

  return TransmitMailbox;
}

/*******************************************************************************
* Function Name  : CAN_TransmitStatus
* Description    : Check the transmission of a message.
* Input          : TransmitMailbox: the number of the mailbox that is used for
*                  transmission.
* Output         : None.
* Return         : CANTXOK if the CAN driver transmits the message, CANTXFAILED
*                  in an other case.
*******************************************************************************/
uint32 CAN_TransmitStatus(uint8 TransmitMailbox)
{
  /* RQCP, TXOK and TME bits */
  uint32 State = 0;

  /* Check the parameters */
  ASSERT(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));

  switch (TransmitMailbox)
  {
    case (0): State |= ((CAN->TSR & CAN_TSR_RQCP0) << 2);
      State |= ((CAN->TSR & CAN_TSR_TXOK0) >> 0);
      State |= ((CAN->TSR & CAN_TSR_TME0) >> 26);
      break;
    case (1): State |= ((CAN->TSR & CAN_TSR_RQCP1) >> 6);
      State |= ((CAN->TSR & CAN_TSR_TXOK1) >> 8);
      State |= ((CAN->TSR & CAN_TSR_TME1) >> 27);
      break;
    case (2): State |= ((CAN->TSR & CAN_TSR_RQCP2) >> 14);
      State |= ((CAN->TSR & CAN_TSR_TXOK2) >> 16);
      State |= ((CAN->TSR & CAN_TSR_TME2) >> 28);
      break;
    default:
      State = CANTXFAILED;
      break;
  }

  switch (State)
  {
      /* transmit pending  */
    case (0x0): State = CANTXPENDING;
      break;
      /* transmit failed  */
    case (0x5): State = CANTXFAILED;
      break;
      /* transmit succedeed  */
    case (0x7): State = CANTXOK;
      break;
    default:
      State = CANTXFAILED;
      break;
  }

  return State;
}

/*******************************************************************************
* Function Name  : CAN_CancelTransmit
* Description    : Cancels a transmit request.
* Input          : Mailbox number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_CancelTransmit(uint8 Mailbox)
{
  /* Check the parameters */
  ASSERT(IS_CAN_TRANSMITMAILBOX(Mailbox));

  /* abort transmission */
  switch (Mailbox)
  {
    case (0): CAN->TSR |= CAN_TSR_ABRQ0;
      break;
    case (1): CAN->TSR |= CAN_TSR_ABRQ1;
      break;
    case (2): CAN->TSR |= CAN_TSR_ABRQ2;
      break;
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : CAN_FIFORelease
* Description    : Release a FIFO.
* Input          : FIFONumber: FIFO to release, CAN_FIFO0 or CAN_FIFO1.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_FIFORelease(uint8 FIFONumber)
{
  /* Check the parameters */
  ASSERT(IS_CAN_FIFO(FIFONumber));

  /* Release FIFO0 */
  if (FIFONumber == CAN_FIFO0)
  {
    CAN->RF0R = CAN_RF0R_RFOM0;
  }
  /* Release FIFO1 */
  else /* FIFONumber == CAN_FIFO1 */
  {
    CAN->RF1R = CAN_RF1R_RFOM1;
  }
}

/*******************************************************************************
* Function Name  : CAN_MessagePending
* Description    : Return the number of pending messages.
* Input          : FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
* Output         : None.
* Return         : NbMessage which is the number of pending message.
*******************************************************************************/
uint8 CAN_MessagePending(uint8 FIFONumber)
{
  uint8 MessagePending=0;

  /* Check the parameters */
  ASSERT(IS_CAN_FIFO(FIFONumber));

  if (FIFONumber == CAN_FIFO0)
  {
    MessagePending = (uint8)(CAN->RF0R&(uint32)0x03);
  }
  else if (FIFONumber == CAN_FIFO1)
  {
    MessagePending = (uint8)(CAN->RF1R&(uint32)0x03);
  }
  else
  {
    MessagePending = 0;
  }
  return MessagePending;
}

/*******************************************************************************
* Function Name  : CAN_Receive
* Description    : Receives a message.
* Input          : FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
* Output         : RxMessage: pointer to a structure which contains CAN Id,
*                  CAN DLC, CAN datas and FMI number.
* Return         : None.
*******************************************************************************/
void CAN_Receive(uint8 FIFONumber, CanRxMsg* RxMessage)
{
  /* Check the parameters */
  ASSERT(IS_CAN_FIFO(FIFONumber));

  /* Get the Id */
  RxMessage->StdId = (uint32)0x000007FF & (CAN->sFIFOMailBox[FIFONumber].RIR >> 21);
  RxMessage->ExtId = (uint32)0x0003FFFF & (CAN->sFIFOMailBox[FIFONumber].RIR >> 3);

  RxMessage->IDE = (uint32)0x00000004 & CAN->sFIFOMailBox[FIFONumber].RIR;
  RxMessage->RTR = (uint32)0x00000002 & CAN->sFIFOMailBox[FIFONumber].RIR;

  /* Get the DLC */
  RxMessage->DLC = (uint32)0x0000000F & CAN->sFIFOMailBox[FIFONumber].RDTR;

  /* Get the FMI */
  RxMessage->FMI = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDTR >> 8);

  /* Get the data field */
  RxMessage->Data[0] = (uint32)0x000000FF & CAN->sFIFOMailBox[FIFONumber].RDLR;
  RxMessage->Data[1] = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDLR >> 8);
  RxMessage->Data[2] = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDLR >> 16);
  RxMessage->Data[3] = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDLR >> 24);

  RxMessage->Data[4] = (uint32)0x000000FF & CAN->sFIFOMailBox[FIFONumber].RDHR;
  RxMessage->Data[5] = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDHR >> 8);
  RxMessage->Data[6] = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDHR >> 16);
  RxMessage->Data[7] = (uint32)0x000000FF & (CAN->sFIFOMailBox[FIFONumber].RDHR >> 24);

  /* Release the FIFO */
  CAN_FIFORelease(FIFONumber);
}

/*******************************************************************************
* Function Name  : CAN_Sleep
* Description    : Enters the low power mode.
* Input          : None.
* Output         : None.
* Return         : CANSLEEPOK if sleep entered, CANSLEEPFAILED in an other case.
*******************************************************************************/
uint8 CAN_Sleep(void)
{
  uint8 SleepStatus = 0;

  /* Sleep mode entering request */
  CAN->MCR |= CAN_MCR_SLEEP;
  SleepStatus = CANSLEEPOK;

  /* Sleep mode status */
  if ((CAN->MCR&CAN_MCR_SLEEP) == 0)
  {
    /* Sleep mode not entered */
    SleepStatus = CANSLEEPFAILED;
  }

  /* At this step, sleep mode status */
  return SleepStatus;
}

/*******************************************************************************
* Function Name  : CAN_WakeUp
* Description    : Wakes the CAN up.
* Input          : None.
* Output         : None.
* Return         : CANWAKEUPOK if sleep mode left, CANWAKEUPFAILED in an other
*                  case.
*******************************************************************************/
uint8 CAN_WakeUp(void)
{
  uint8 WakeUpStatus = 0;

  /* Wake up request */
  CAN->MCR &= ~CAN_MCR_SLEEP;
  WakeUpStatus = CANWAKEUPFAILED;

  /* Sleep mode status */
  if ((CAN->MCR&CAN_MCR_SLEEP) == 0)
  {
    /* Sleep mode exited */
    WakeUpStatus = CANWAKEUPOK;
  }

  /* At this step, sleep mode status */
  return WakeUpStatus;
}

/*******************************************************************************
* Function Name  : CAN_GetFlagStatus
* Description    : Checks whether the CAN flag is set or not.
* Input          : CAN_FLAG: specifies the flag to check.
* Output         : None.
* Return         : The new state of CAN_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus CAN_GetFlagStatus(uint32 CAN_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  ASSERT(IS_CAN_FLAG(CAN_FLAG));

  /* Check the status of the specified CAN flag */
  if ((CAN->ESR & CAN_FLAG) != (uint32)RESET)
  {
    /* CAN_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* CAN_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the CAN_FLAG status */
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : CAN_ClearFlag
* Description    : Clears the CAN's pending flags.
* Input          : CAN_FLAG: specifies the flag to clear.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_ClearFlag(uint32 CAN_FLAG)
{
  /* Check the parameters */
  ASSERT(IS_CAN_FLAG(CAN_FLAG));

  /* Clear the selected CAN flags */
  CAN->ESR &= ~CAN_FLAG;
}

/*******************************************************************************
* Function Name  : CAN_GetITStatus
* Description    : Checks whether the CAN interrupt has occurred or not.
* Input          : CAN_IT: specifies the CAN interrupt source to check.
* Output         : None.
* Return         : The new state of CAN_IT (SET or RESET).
*******************************************************************************/
ITStatus CAN_GetITStatus(uint32 CAN_IT)
{
  ITStatus pendingbitstatus = RESET;

  /* Check the parameters */
  ASSERT(IS_CAN_IT(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_RQCP0:
      pendingbitstatus = CheckITStatus(CAN->TSR, CAN_TSR_RQCP0);
      break;
    case CAN_IT_RQCP1:
      pendingbitstatus = CheckITStatus(CAN->TSR, CAN_TSR_RQCP1);
      break;
    case CAN_IT_RQCP2:
      pendingbitstatus = CheckITStatus(CAN->TSR, CAN_TSR_RQCP2);
      break;
    case CAN_IT_FF0:
      pendingbitstatus = CheckITStatus(CAN->RF0R, CAN_RF0R_FULL0);
      break;
    case CAN_IT_FOV0:
      pendingbitstatus = CheckITStatus(CAN->RF0R, CAN_RF0R_FOVR0);
      break;
    case CAN_IT_FF1:
      pendingbitstatus = CheckITStatus(CAN->RF1R, CAN_RF1R_FULL1);
      break;
    case CAN_IT_FOV1:
      pendingbitstatus = CheckITStatus(CAN->RF1R, CAN_RF1R_FOVR1);
      break;
    case CAN_IT_EWG:
      pendingbitstatus = CheckITStatus(CAN->ESR, CAN_ESR_EWGF);
      break;
    case CAN_IT_EPV:
      pendingbitstatus = CheckITStatus(CAN->ESR, CAN_ESR_EPVF);
      break;
    case CAN_IT_BOF:
      pendingbitstatus = CheckITStatus(CAN->ESR, CAN_ESR_BOFF);
      break;
    case CAN_IT_SLK:
      pendingbitstatus = CheckITStatus(CAN->MSR, CAN_MSR_SLAKI);
      break;
    case CAN_IT_WKU:
      pendingbitstatus = CheckITStatus(CAN->MSR, CAN_MSR_WKUI);
      break;

    default :
      pendingbitstatus = RESET;
      break;
  }

  /* Return the CAN_IT status */
  return  pendingbitstatus;
}

/*******************************************************************************
* Function Name  : CAN_ClearITPendingBit
* Description    : Clears the CAN’s interrupt pending bits.
* Input          : CAN_IT: specifies the interrupt pending bit to clear.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_ClearITPendingBit(uint32 CAN_IT)
{
  /* Check the parameters */
  ASSERT(IS_CAN_IT(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_RQCP0:
      CAN->TSR = CAN_TSR_RQCP0; /* rc_w1*/
      break;
    case CAN_IT_RQCP1:
      CAN->TSR = CAN_TSR_RQCP1; /* rc_w1*/
      break;
    case CAN_IT_RQCP2:
      CAN->TSR = CAN_TSR_RQCP2; /* rc_w1*/
      break;
    case CAN_IT_FF0:
      CAN->RF0R = CAN_RF0R_FULL0; /* rc_w1*/
      break;
    case CAN_IT_FOV0:
      CAN->RF0R = CAN_RF0R_FOVR0; /* rc_w1*/
      break;
    case CAN_IT_FF1:
      CAN->RF1R = CAN_RF1R_FULL1; /* rc_w1*/
      break;
    case CAN_IT_FOV1:
      CAN->RF1R = CAN_RF1R_FOVR1; /* rc_w1*/
      break;
    case CAN_IT_EWG:
      CAN->ESR &= ~ CAN_ESR_EWGF; /* rw */
      break;
    case CAN_IT_EPV:
      CAN->ESR &= ~ CAN_ESR_EPVF; /* rw */
      break;
    case CAN_IT_BOF:
      CAN->ESR &= ~ CAN_ESR_BOFF; /* rw */
      break;
    case CAN_IT_WKU:
      CAN->MSR = CAN_MSR_WKUI;  /* rc_w1*/
      break;
    case CAN_IT_SLK:
      CAN->MSR = CAN_MSR_SLAKI;  /* rc_w1*/
      break;
    default :
      break;
  }
}

/*******************************************************************************
* Function Name  : CheckITStatus
* Description    : Checks whether the CAN interrupt has occurred or not.
* Input          : CAN_Reg: specifies the CAN interrupt register to check.
*                  It_Bit: specifies the interrupt source bit to check.
* Output         : None.
* Return         : The new state of the CAN Interrupt (SET or RESET).
*******************************************************************************/
static ITStatus CheckITStatus(uint32 CAN_Reg, uint32 It_Bit)
{
  ITStatus pendingbitstatus = RESET;

  if ((CAN_Reg & It_Bit) != (uint32)RESET)
  {
    /* CAN_IT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* CAN_IT is reset */
    pendingbitstatus = RESET;
  }

  return pendingbitstatus;
}

#endif
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
