
#include "FAT16.h"
#include "printf.h"

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


#pragma pack(push, 2)
typedef struct
{
	FAT16_FatEntry FirstEntry;
	FAT16_FatEntry SecondEntry;
	FAT16_FatEntry Status;
	FAT16_FatEntry Command;
	FAT16_FatEntry Response;
	FAT16_FatEntry Buffer;
} WiiMouseFat;
#pragma pack(pop)



char status[512];
char response[512];
char buffer[512];
char command[512];

/********************************************************************
 *       FAT16 Boot Sector
 ********************************************************************/


const FAT16_BootSectorInfo BootSector =
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

const FAT16_FatEntry WiiMouseAllocationTable[6] =
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

const FAT16_DirectoryEntryInfo RootDirSector[NUM_ROOT_DIR_ENTRIES] =
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


/*********************************************************
 * Name: FATReadLBA
 *
 * Desc: Read a Logical Block Address
 *
 * Parameter: FAT_LBA - Logical Block Address to Read
 *            pu8DataPointer - Pointer to array to store data read
 *
 * Return: None
 *
 **********************************************************/
void FATReadLBA(int FAT_LBA,char *pu8DataPointer)
{
	int i;

	printf("Reading Sector: %d\n", FAT_LBA);


	if( FAT_LBA == BOOT_SECTOR)
	{
		printf("BOOT_SECTOR\n");
		// Write Boot Sector info
		for(i=0; i < FAT16_BOOT_SECTOR_SIZE; i++)
		{
			*pu8DataPointer++ = ((char*)&BootSector)[i];
		}
	}
	else if( (FAT_LBA >= FAT0_SECTOR) && (FAT_LBA < ROOT_DIR_SECTOR))
	{
		i = 0;
		if((FAT_LBA == FAT0_SECTOR) || (FAT_LBA == FAT1_SECTOR))
		{
			printf("FAT\n");
		for(i = 0; i < FAT16_FAT_ENTRY_SIZE*6; i++)
		{
			*pu8DataPointer++ = ((char*)&WiiMouseAllocationTable)[i];
		}
		}
		// Rest of sector empty
		while (i++ < FAT16_BYTES_PER_SEC) {
			*pu8DataPointer++ = 0;
		}
	}
	else if( (FAT_LBA >= ROOT_DIR_SECTOR) && (FAT_LBA < STATUS_SECTOR))
	{
		// Write rest of file FAT structure
		i = 0;
		if( FAT_LBA == ROOT_DIR_SECTOR)
		{
			printf("ROOT_DIR_SECTOR\n");
		for(i=0; i<FAT16_DIRECTORY_ENTRY_SIZE*NUM_ROOT_DIR_ENTRIES;i++)
		{
			*pu8DataPointer++ = ((uint8*)RootDirSector)[i];
		}
		}
		// Rest of sector empty to signify no more files
		while (i++ < FAT16_BYTES_PER_SEC) {
			*pu8DataPointer++ = 0;
		}
	}
	else
	{
		char *ptr = NULL;
		switch(FAT_LBA)
		{
		case STATUS_SECTOR:
			ptr = status;
			break;
		case COMMAND_SECTOR:
			ptr = command;
			break;
		case RESPONSE_SECTOR:
			ptr = response;
			break;
		case BUFFER_SECTOR:
			ptr = buffer;
		default:
break;
		}

		i = 0;
		if( ptr == NULL)
		{
			while (i++ < FAT16_BYTES_PER_SEC) {
				*pu8DataPointer++ = 0;
			}
		}
		else
		{
			while (i++ < FAT16_BYTES_PER_SEC) {
				*pu8DataPointer++ = *ptr++;
			}
		}
	}

}


void FATWriteLBA(int FAT_LBA,char *pu8DataPointer, int offset, int byteCount)
{
	char *ptr = NULL;
	uint32 i ;
	switch(FAT_LBA)
	{
	case STATUS_SECTOR:
		ptr = status+offset;
		break;
	case COMMAND_SECTOR:
		ptr = command+offset;
		break;
	case RESPONSE_SECTOR:
		ptr = response+offset;
		break;
	case BUFFER_SECTOR:
		ptr = buffer+offset;
	default:
break;
	}

	i = 0;
	if( ptr != NULL)
	{
		while (i++ < byteCount) {
			*ptr++ = *pu8DataPointer++;
		}
	}
}

void FATInit(void)
{
	sprintf(status, "%s\xA", "Initialized status data....\n");
	sprintf(command, "%s\xA", "Initialized command data....\n");
	sprintf(response, "%s\xA", "Initialized response data....\n");
	sprintf(buffer, "%s\xA", "Initialized buffer data....\n");
}
