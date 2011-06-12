
#include "FAT16.h"
#include "printf.h"

#define ADD_DIRECTORY_ENTRY(_name, _ext, _attr, _start, _size)		\
		{																	\
	_name,														    \
	_ext,															\
	_attr,															\
	0,																\
	0,																\
	0,																\
	0xFFFF,															\
	0xFFFF,															\
	0,																\
	0,																\
	0xFFFF,															\
	_start,															\
	_size															\
		}



#define BOOT_SEC_OEM_NAME {'M','S','D','O','S','5','.','0'}
#define BOOT_SEC_VOL_LBL {'N','O',' ','N','A','M','E',' ',' ',' ',' '}
#define BOOT_SEC_SYS_TYPE {'F','A','T','1','6',' ',' ',' '}



#define STATUS_NAME			{'S', 't','a','t','u','s',' ', ' '}
#define STATUS_EXT			{'t', 'x', 't'}

#define COMMAND_NAME		{'C', 'o','m','m','a','n','d', ' '}
#define COMMAND_EXT			{'t', 'x', 't'}

#define RESPONSE_NAME		{'R', 'e','s','p','o','n','s', 'e'}
#define RESPONSE_EXT		{'t', 'x', 't'}

#define BUFFER_NAME			{'B', 'u','f','f','e','r',' ', ' '}
#define BUFFER_EXT			{'t', 'x', 't'}

#define VOLUME_NAME			{'W', 'i', 'i', 'M','o','u','s','e'}
#define VOLUME_EXT			{' ', ' ', ' '}



#define BOOT_SECTOR			0
#define FAT0_SECTOR			2
#define FAT1_SECTOR			(FAT0_SECTOR + FAT16_SEC_PER_FAT)
#define ROOT_DIR_SECTOR		(FAT1_SECTOR + FAT16_SEC_PER_FAT)
#define STATUS_SECTOR		(ROOT_DIR_SECTOR + 1)
#define COMMAND_SECTOR		(STATUS_SECTOR + 1)
#define RESPONSE_SECTOR     (COMMAND_SECTOR + 1)
#define BUFFER_SECTOR		(RESPONSE_SECTOR + 1)


/********************************************************************
 *       FAT16 Boot Sector
 ********************************************************************/


const FAT16_BootSectorInfo BootSector =
{
		{0xEB, 0x3C, 0x90},  			// Jump instruction.
		BOOT_SEC_OEM_NAME,				// OEM Name
		FAT16_BYTES_PER_SEC,			// Bytes per sector.
		FAT16_SEC_PER_CLUSTER,			// Sectors per cluster.
		2,		      					// Reserved sector count
		2,		        				// Number of file allocation tables
		512,	        				// Maximum number of root directory entries
		0,								// Total sectors
		FAT16_MEDIA_DES_FIXED_DISK,		// Media descriptor
		FAT16_SEC_PER_FAT, 				// Sectors per File Allocation Table
		63,								// Sectors per track
		255,							// Number of heads
		249,							// Number of heads
		TOTAL_SECTORS,					// Total sectors
		0,            					// Physical drive number
		1,            					// Reserved ("current head")
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
const FAT16_FatEntry FileAllocationTable[NUM_FAT_ENTRIES]=
{
		0xFFF8,									// 0 - Special entry 1
		FAT16_ENTRY_LAST_CLUSTER,				// 1 - Special entry 2
		0,										// 2 - fat 0
		0,										// 3 - fat 1
		0,										// 4 - root directory
		FAT16_ENTRY_LAST_CLUSTER,				// 5 - Status.txt
		FAT16_ENTRY_LAST_CLUSTER,				// 6 - Command.txt
		FAT16_ENTRY_LAST_CLUSTER,				// 7 - Response.txt
		FAT16_ENTRY_LAST_CLUSTER,				// 8 - Buffer.txt
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
				STATUS_SECTOR,
				FAT16_BYTES_PER_SEC),

				ADD_DIRECTORY_ENTRY(
						COMMAND_NAME,
						COMMAND_EXT,
						FAT16_FILE_ATTR_ARCHIVE,
						COMMAND_SECTOR,
						FAT16_BYTES_PER_SEC),

						ADD_DIRECTORY_ENTRY(
								RESPONSE_NAME,
								RESPONSE_EXT,
								FAT16_FILE_ATTR_ARCHIVE,
								RESPONSE_SECTOR,
								FAT16_BYTES_PER_SEC),

								ADD_DIRECTORY_ENTRY(
										BUFFER_NAME,
										BUFFER_EXT,
										FAT16_FILE_ATTR_ARCHIVE,
										BUFFER_SECTOR,
										FAT16_BYTES_PER_SEC),

										ADD_DIRECTORY_ENTRY(
												VOLUME_NAME,
												VOLUME_EXT,
												FAT16_FILE_ATTR_VOLUME_LABEL,
												0,
												0)
};




/*********************************************************
 * Name: GetASCIIValue
 *
 * Desc: Converts hex value to ASCII character
 *
 * Parameter: hex value to convert
 *
 * Return: unsigned char, ASCII character
 *
 **********************************************************/
unsigned char GetASCIIValue (unsigned char value)
{
	if(value <= 9) {
		return (unsigned char)(value + '0');
	} else if(value <= 0xF) {
		return (unsigned char)(value - 0xA + 'A');
	} else
		return 'Z';
}


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

	switch (FAT_LBA) {

	// Boot Sector
	case BOOT_SECTOR:
		// Write Boot Sector info
		for(i=0; i < FAT16_BOOT_SECTOR_SIZE; i++)
		{
			*pu8DataPointer++ = ((char*)&BootSector)[i];
		}
		break;

		// FAT Table Sector
	case FAT0_SECTOR:
	case FAT1_SECTOR:
		// Write FAT Table Sector
		for(i=0; i < FAT16_FAT_ENTRY_SIZE*NUM_FAT_ENTRIES; i++)
			*pu8DataPointer++ = FileAllocationTable[i];

		// Rest of sector empty
		while (i++ < FAT16_BYTES_PER_SEC) {
			*pu8DataPointer++ = 0;
		}
		break;

		// Root Directory Sector
	case ROOT_DIR_SECTOR:
		// Write rest of file FAT structure
		for(i=0; i<FAT16_DIRECTORY_ENTRY_SIZE*NUM_ROOT_DIR_ENTRIES;i++)
		{
			*pu8DataPointer++ = ((uint8*)RootDirSector)[i];
		}

		// Rest of sector empty to signify no more files
		while (i++ < FAT16_BYTES_PER_SEC) {
			*pu8DataPointer++ = 0;
		}
		break;



	case STATUS_SECTOR:
		sprintf(pu8DataPointer, "%s", "Status sector data\n\nYAY!\n");
		break;
	case COMMAND_SECTOR:
		sprintf(pu8DataPointer, "%s", "Command sector data\n\nFucking shit yea!\n");
		break;
	case RESPONSE_SECTOR:
		sprintf(pu8DataPointer, "%s", "Response sector data\n\nBitch niggas!\n");
		break;
	case BUFFER_SECTOR:
		sprintf(pu8DataPointer, "%s", "BUffer sector data\n\nLooks like everything is working...\n");break;
		// All other sectors empty
	default:
		i = 0;
		while (i++ < FAT16_BYTES_PER_SEC) {
			*pu8DataPointer++ = 0;
		}
		break;
	}

}

