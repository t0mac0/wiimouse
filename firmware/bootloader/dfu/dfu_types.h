/*!
 * \file dfu_types.h
 *
 * \brief 
 *
 *
 * \date Apr 17, 2011
 * \author Dan Riedler
 *
 */

#ifndef _DFU_TYPES_H_
#define _DFU_TYPES_H_

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "system.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/
#define CHUNK_SIZE 512


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/
PUBLIC typedef enum {
    DFU_MODE_UPDATE = 0xFFFFFFFF,
    DFU_MODE_USER = 0x39FE72B6,
} DFU_ModeType;

PUBLIC typedef enum {
    DFU_CMD_QUERY_DEVICE                = 0,
    DFU_CMD_INITIALIZE_UPDATE           = 1,
    DFU_CMD_BEGIN_UPDATE                = 2,
    DFU_CMD_START_SECTION_UPDATE        = 3,
    DFU_CMD_SECTION_UPDATE              = 4,
    DFU_CMD_END_SECTION_UPDATE          = 5,
    DFU_CMD_END_UPDATE                  = 6,
    DFU_CMD_BEGIN_VALIDATION            = 7,
    DFU_CMD_START_SECTION_VALIDATION    = 8,
    DFU_CMD_SECTION_VALIDATE            = 9,
    DFU_CMD_END_SECTION_VALIDATION      = 10,
    DFU_CMD_END_VALIDATION              = 11,
    DFU_CMD_COMPLETE_UPDATE             = 12,
    DFU_CMD_NULL                        = 0xFF
} DFU_CommandType;

PUBLIC typedef enum {
    DFU_STATUS_SUCCESS,
    DFU_STATUS_FAILURE,
    DFU_STATUS_STATE_TRANSISTION_ERROR,
    DFU_STATUS_INVALID_SUB_COMMAND,
    DFU_STATUS_SECTION_OVERFLOW,
    DFU_STATUS_SECTION_DATA_OVERFLOW,
    DFU_STATUS_INVALID_DESTINATION,
    DFU_STATUS_TOO_MANY_SECTIONS,
    DFU_STATUS_INTERNAL_FLASH_WRITE_ERROR,
    DFU_STATUS_INTERNAL_FLASH_READ_ERROR,
    DFU_STATUS_NOT_IN_UPDATE_MODE,
    DFU_STATUS_INTERNAL_FLASH_ERASE_ERROR,
} DFU_StatusType;

#pragma pack(push, 1)
PUBLIC typedef struct {
    uint8 Command;
    uint32 StartAddress;
    uint32 SectionsCount;
    uint32 Length;
    uint32 Offset;
} DFU_Command;
#pragma  pack(pop)
#define DFU_COMMAND_SIZE sizeof(DFU_Command)


#pragma pack(push, 1)
PUBLIC typedef struct {
    uint8 Status;
    uint16 VendorId;
    uint16 ProductId;
    uint16 DeviceId;
    uint16 FWVersion;
    uint32 Checksum;
    uint32 Length;
    uint32 Mode;
} DFU_Response;
#pragma  pack(pop)
#define DFU_RESPONSE_SIZE sizeof(DFU_Response)


PUBLIC typedef uint8 DFU_ImageChuck[CHUNK_SIZE];

/*-----------------------------------------------------------------------------
 Exported Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 External Data Members
------------------------------------------------------------------------------*/


#endif /* DFU_TYPES_H_ */
