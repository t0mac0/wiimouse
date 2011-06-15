/*!
 * \file hw_usb_bot.h
 *
 * \brief 
 *
 *
 * \date Jun 13, 2011
 * \author Dan Riedler
 *
 */
#ifndef _HW_USB_BOT_H_
#define _HW_USB_BOT_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "bootloader.h"
#include "hw/usb/desc/hw_usb_desc_mass_storage.h"

/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define BOT_IDLE                      0       /* Idle state */
#define BOT_DATA_OUT                  1       /* Data Out state */
#define BOT_DATA_IN                   2       /* Data In state */
#define BOT_DATA_IN_LAST              3       /* Last Data In Last */
#define BOT_CSW_Send                  4       /* Command Status Wrapper */
#define BOT_ERROR                     5       /* error state */

#define BOT_CBW_SIGNATURE             0x43425355
#define BOT_CSW_SIGNATURE             0x53425355
#define BOT_CBW_PACKET_LENGTH         31

#define CSW_DATA_LENGTH               0x000D

/* CSW Status Definitions */
#define CSW_CMD_PASSED                0x00
#define CSW_CMD_FAILED                0x01
#define CSW_PHASE_ERROR               0x02

#define SEND_CSW_DISABLE              0
#define SEND_CSW_ENABLE               1

#define DIR_IN                        0
#define DIR_OUT                       1
#define BOTH_DIR                      2
/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
typedef struct _Bulk_Only_CBW
{
  uint32 dSignature;
  uint32 dTag;
  uint32 dDataLength;
  uint8  bmFlags;
  uint8  bLUN;
  uint8  bCBLength;
  uint8  CB[16];
}
Bulk_Only_CBW;

/* Bulk-only Command Status Wrapper */
typedef struct _Bulk_Only_CSW
{
  uint32 dSignature;
  uint32 dTag;
  uint32 dDataResidue;
  uint8  bStatus;
}
Bulk_Only_CSW;

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/
void Mass_Storage_In (void);
void Mass_Storage_Out (void);
void CBW_Decode(void);
void Transfer_Data_Request(uint8* Data_Pointer, uint16 Data_Len);
void Set_CSW (uint8 CSW_Status, uint8 Send_Permission);
void Bot_Abort(uint8 Direction);

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/

extern uint8 Bulk_Data_Buff[MASS_STORAGE_MAX_PACKET_SIZE];  /* data buffer*/
extern uint8 Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;


#endif /* _HW_USB_BOT_H_ */
