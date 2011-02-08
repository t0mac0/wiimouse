/*
 * dfu_type.h
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */

#ifndef DFU_TYPE_H_
#define DFU_TYPE_H_

#include "ifc_dfu_type.h"


typedef enum _dfu_ModeType {
	DFU_MODE_UPDATE = 0xAEFDE14B,
	DFU_MODE_USER = 0x39FE72B6,
} dfu_ModeType;



#endif /* DFU_TYPE_H_ */
