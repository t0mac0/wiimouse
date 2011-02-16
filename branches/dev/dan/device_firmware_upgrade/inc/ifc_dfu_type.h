/*
 * ifc_dfu_types.h
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */

#ifndef IFC_DFU_TYPE_H_
#define IFC_DFU_TYPE_H_

#include "stm32f10x_type.h"


#define CHUNK_SIZE 512

typedef enum _dfu_ModeType {
	DFU_MODE_UPDATE = 0xAEFDE14B,
	DFU_MODE_USER = 0x39FE72B6,
} DFU_ModeType;

typedef enum _DFU_CommandType {
	DFU_CMD_QUERY_DEVICE,
	DFU_CMD_INITIALIZE_UPDATE,
	DFU_CMD_BEGIN_UPDATE,
	DFU_CMD_START_SECTION_UPDATE,
	DFU_CMD_SECTION_UPDATE,
	DFU_CMD_END_SECTION_UPDATE,
	DFU_CMD_END_UPDATE,
	DFU_CMD_BEGIN_VALIDATION,
	DFU_CMD_START_SECTION_VALIDATION,
	DFU_CMD_SECTION_VALIDATE,
	DFU_CMD_END_SECTION_VALIDATION,
	DFU_CMD_END_VALIDATION,
	DFU_CMD_COMPLETE_UPDATE,
	DFU_CMD_NULL = 0xFF
} DFU_CommandType;

typedef enum _DFU_StatusType {
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
} DFU_StatusType;

typedef enum _DFU_DestinationType {
	DFU_DESTINATION_INTERNALFLASH,

	DFU_DESTINATION_COUNT,
	DFU_DESTINATION_UNKNOWN = -1
} DFU_DestinationType;

#pragma pack(push, 1)
typedef struct _DFU_Command {
	uint8 Command;
	uint32 Destination;
	uint32 StartAddress;
	uint32 SectionsCount;
	uint32 Length;
	uint32 Offset;
} DFU_Command;
#pragma  pack(pop)
#define DFU_COMMAND_SIZE sizeof(DFU_Command)


#pragma pack(push, 1)
typedef struct _DFU_Response {
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


typedef uint8 ImageChuck[CHUNK_SIZE];


#endif /* IFC_DFU_TYPES_H_ */
