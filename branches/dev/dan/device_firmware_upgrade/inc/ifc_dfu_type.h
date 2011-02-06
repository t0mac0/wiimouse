/*
 * ifc_dfu_types.h
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */

#ifndef IFC_DFU_TYPE_H_
#define IFC_DFU_TYPE_H_

#include "stm32f10x_type.h"

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
	DFU_CMD_VALIDATE_SECTION,
	DFU_CMD_END_SECTION_VALIDATION,
	DFU_CMD_END_VALIDATION,
	DFU_CMD_COMPLETE_UPDATE,
} DFU_CommandType;

typedef enum _DFU_SubCommandType {
	DFU_SUBCMD_GET_VENDOR_ID,
	DFU_SUBCMD_GET_PRODUCT_ID,
	DFU_SUBCMD_GET_DEVICE_ID,
	DFU_SUBCMD_GET_FW_VERSION,
} DFU_SubCommandType;

typedef enum _DFU_StatusType {
	DFU_STATUS_SUCCESS,
	DFU_STATUS_FAILURE,
	DFU_STATUS_STATE_TRANSISTION_ERROR,
	DFU_STATUS_INVALID_SUB_COMMAND,
} DFU_StatusType;


typedef struct _DFU_ImageHeader {
	uint16  VendorId;
	uint16  ProductId;
	uint16  DeviceId;
	uint16  FWVersion;
	uint16  SectionsCount;
	uint32  HashSum;
} DFU_ImageHeader;

typedef struct _DFU_ImageSection {
	uint16  SectionId;
	uint32  ImageHashsum;
	uint32  StartAddress;
	uint16  Length;
	uint32  Data[];
} DFU_ImageSection;

#pragma pack(push, 1)
typedef struct _DFU_Command {
	DFU_CommandType Command;
	DFU_SubCommandType SubCommand;
	union {
		uint32 Offset;
		uint32 StartAddress;
		uint32 SectionsCount;
	} u32;
	union {
		uint16 Length;
	} u16;
} DFU_Command;
#pragma  pack(pop)


#pragma pack(push, 1)
typedef struct _DFU_Response {
	DFU_StatusType Status;
	union {
		uint32 VendorId;
		uint32 ProductId;
		uint32 DeviceId;
		uint32 FWVersion;
		uint32 HashSum;
	} u32;
	union {
		uint16 Length;
	} u16;
} DFU_Response;
#pragma  pack(pop)


typedef uint8 ImageChuck[64];


#endif /* IFC_DFU_TYPES_H_ */
