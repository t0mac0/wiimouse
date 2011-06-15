/*!
 * \file dfu_fat.c
 *
 * \brief 
 *
 *
 * \date Jun 15, 2011
 * \author Dan Riedler
 *
 */

/*-----------------------------------------------------------------------------
 Includes
------------------------------------------------------------------------------*/
#include "dfu/dfu.h"
#include "dfu/mal/dfu_mal.h"

#include "dfu_fat.h"


/*-----------------------------------------------------------------------------
 Defines
------------------------------------------------------------------------------*/

#define TOTAL_SECTORS				32768
#define NUM_ROOT_DIR_ENTRIES		5
#define NUM_FAT_ENTRIES				6

#define FAT16_BYTES_PER_SEC			DFU_COM_TRANSFER_SIZE
#define FAT16_SEC_PER_CLUSTER		1
#define FAT16_SEC_PER_FAT			1
#define FAT16_RESERVED_SEC_COUNT	1
#define FAT16_MAX_ROOT_ENTRY		512
#define FAT16_FAT_COUNT				2

#define FAT16_ROOT_SEC_COUNT		ALIGN(FAT16_MAX_ROOT_ENTRY * FAT16_DIRECTORY_ENTRY_SIZE, FAT16_BYTES_PER_SEC)
#define FAT16_FIRST_DATA_SEC		(FAT16_RESERVED_SEC_COUNT + FAT16_FAT_COUNT*FAT16_SEC_PER_FAT + FAT16_ROOT_SEC_COUNT)



#define BOOT_SEC_OEM_NAME {'M','S','D','O','S','5','.','0'}
#define BOOT_SEC_VOL_LBL {'N','O',' ','N','A','M','E',' ',' ',' ',' '}
#define BOOT_SEC_SYS_TYPE {'F','A','T','1','6',' ',' ',' '}



#define STATUS_NAME			{'S', 'T','A','T','U','S',' ', ' '} //MUST BE UPPERCASE!
#define STATUS_EXT			{'T', 'X', 'T'}

#define COMMAND_NAME		{'C', 'O','M','M','A','N','D', ' '}
#define COMMAND_EXT			{'T', 'X', 'T'}

#define RESPONSE_NAME		{'R', 'E','S','P','O','N','S', 'E'}
#define RESPONSE_EXT		{'T', 'X', 'T'}

#define BUFFER_NAME			{'B', 'U','F','F','E','R',' ', ' '}
#define BUFFER_EXT			{'T', 'X', 'T'}

#define VOLUME_NAME			{'W', 'I', 'I', 'M','O','U','S','E'}
#define VOLUME_EXT			{' ', ' ', ' '}



#define BOOT_SECTOR			0
#define FAT0_SECTOR			FAT16_RESERVED_SEC_COUNT
#define FAT1_SECTOR			(FAT0_SECTOR + FAT16_SEC_PER_FAT)
#define ROOT_DIR_SECTOR		(FAT1_SECTOR + FAT16_SEC_PER_FAT)

#define STATUS_SECTOR		FAT16_FIRST_DATA_SEC
#define STATUS_CLUSTER		2

#define COMMAND_SECTOR		(STATUS_SECTOR + FAT16_SEC_PER_CLUSTER)
#define COMMAND_CLUSTER		3

#define RESPONSE_SECTOR     (COMMAND_SECTOR + FAT16_SEC_PER_CLUSTER)
#define RESPONSE_CLUSTER	4

#define BUFFER_SECTOR		(RESPONSE_SECTOR + FAT16_SEC_PER_CLUSTER)
#define BUFFER_CLUSTER		5


/*-----------------------------------------------------------------------------
 Macros
------------------------------------------------------------------------------*/
#define ADD_DIRECTORY_ENTRY(_name, _ext, _attr, _start, _size)		\
{																	\
	_name,														    \
	_ext,															\
	_attr,															\
	0,																\
	0x4B,															\
	0x429C,															\
	0x3892,															\
	0x3892,															\
	0,																\
	0x429D,															\
	0x3892,															\
	_start,															\
	_size															\
}



/*-----------------------------------------------------------------------------
 Typedefs
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 Local Function Prototypes
------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 Data Members
------------------------------------------------------------------------------*/

PRIVATE FAT16_BootSectorInfo BootSector =
{
		{0xEB, 0x3C, 0x90},  			// Jump instruction.
		BOOT_SEC_OEM_NAME,				// OEM Name
		FAT16_BYTES_PER_SEC,			// Bytes per sector.
		FAT16_SEC_PER_CLUSTER,			// Sectors per cluster.
		FAT16_RESERVED_SEC_COUNT,		// Reserved sector count
		FAT16_FAT_COUNT,		        // Number of file allocation tables
		FAT16_MAX_ROOT_ENTRY,	        // Maximum number of root directory entries
		TOTAL_SECTORS,					// Total sectors
		FAT16_MEDIA_DES_REMOVABLE,		// Media descriptor
		FAT16_SEC_PER_FAT, 				// Sectors per File Allocation Table
		63,								// Sectors per track
		255,							// Number of heads
		0,								// Hidden sectors
		0,								// Total sectors (FAT32)
		0,            					// Physical drive number
		0,            					// Reserved
		0x29,         					// Extended boot signature
		0x02DDA5BD,						// ID (serial number)
		BOOT_SEC_VOL_LBL,  				// Volume Label
		BOOT_SEC_SYS_TYPE,   			// FAT file system type
		{0},							// OS Bootcode
		0xAA55							// Boot sector signature
};


/********************************************************************
 *       FAT Table
 ********************************************************************/

PRIVATE FAT16_FatEntry DfuAllocationTable[NUM_FAT_ENTRIES] =
{
		0xFFF0,									// Special entry 1
		0xFF7F,									// Special entry 2
		FAT16_ENTRY_LAST_CLUSTER,				// Status.txt
		FAT16_ENTRY_LAST_CLUSTER,				// Command.txt
		FAT16_ENTRY_LAST_CLUSTER,				// Response.txt
		FAT16_ENTRY_LAST_CLUSTER,				// Buffer.txt
};



/********************************************************************
 *       FAT Root Directory Sector
 ********************************************************************/

PRIVATE const FAT16_DirectoryEntryInfo RootDirSector[NUM_ROOT_DIR_ENTRIES] =
{
	ADD_DIRECTORY_ENTRY(
			STATUS_NAME,
			STATUS_EXT,
			FAT16_FILE_ATTR_ARCHIVE,
			STATUS_CLUSTER,
			FAT16_BYTES_PER_SEC),

	ADD_DIRECTORY_ENTRY(
			COMMAND_NAME,
			COMMAND_EXT,
			FAT16_FILE_ATTR_ARCHIVE,
			COMMAND_CLUSTER,
			FAT16_BYTES_PER_SEC),

	ADD_DIRECTORY_ENTRY(
			RESPONSE_NAME,
			RESPONSE_EXT,
			FAT16_FILE_ATTR_ARCHIVE,
			RESPONSE_CLUSTER,
			FAT16_BYTES_PER_SEC),

	ADD_DIRECTORY_ENTRY(
			BUFFER_NAME,
			BUFFER_EXT,
			FAT16_FILE_ATTR_ARCHIVE,
			BUFFER_CLUSTER,
			FAT16_BYTES_PER_SEC),

	ADD_DIRECTORY_ENTRY(
			VOLUME_NAME,
			VOLUME_EXT,
			FAT16_FILE_ATTR_VOLUME_LABEL,
			0,
			0)
};


//*****************************************************************************
//
// Exported Functions
//
//*****************************************************************************


/******************************************************************************/
PROTECTED void DfuFatReadBlockAddress(uint32 BlockAddress)
{

	ZeroMemory(DfuComDataBuffer, DFU_COM_TRANSFER_SIZE);

	switch(BlockAddress)
	{
	case BOOT_SECTOR:
		CopyMemory(DfuComDataBuffer, &BootSector, FAT16_BOOT_SECTOR_SIZE);
		break;
	case FAT0_SECTOR:
	case FAT1_SECTOR:
		CopyMemory(DfuComDataBuffer, &DfuAllocationTable, NUM_FAT_ENTRIES*FAT16_FAT_ENTRY_SIZE);
		break;
	case ROOT_DIR_SECTOR:
		CopyMemory(DfuComDataBuffer, &RootDirSector, NUM_ROOT_DIR_ENTRIES*FAT16_DIRECTORY_ENTRY_SIZE);
		break;
	case RESPONSE_SECTOR:
		CopyMemory(DfuComDataBuffer, &DfuComResponse, sizeof(DFU_Response));
		break;
	default:
		if( BlockAddress >= BUFFER_SECTOR )
		{
//			if( !DfuMalRead() )
//			{
//
//			}
		}

	}

}


/******************************************************************************/
PROTECTED void DfuFatWriteBlockAddress(uint32 BlockAddress, uint32 ByteOffset, uint32 ByteCount)
{

}

//*****************************************************************************
//
// Local Functions
//
//*****************************************************************************
