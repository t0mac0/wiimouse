package com.dfu.downloader.type;

// This must be synchronized with ifc_dfu_type.h: DFU_StatusType
public enum DfuStatusType {
	NULL
		(-1, "Undefined status"),
	SUCCESS
		(0, "Operation successful"),
	FAILURE
		(1, "Operation failed"),
	STATE_TRANSISTION_ERROR
		(2, "Invalid state transition"),
	INVALID_SUB_COMMAND
		(3, "Invalid sub command"),
	SECTION_UPDATED_OVERFLOW
		(4, "Attempted to update more sections than initially specified"),
	SECTION_UPGRADE_DATA_OVERFLOW
		(5, "Attempted to updating more section data than initially specified"),
	INVALID_DESTINATION
		(6, "Invalid memory destination"),
	TOO_MANY_SECTIONS
		(7, "Attempted to update more memory sections than physically available"),
	INTERNAL_FLASH_WRITE_ERROR
		(8, "Error writing internal flash memory"),
	INTERNAL_FLASH_READ_ERROR
		(9, "Error reading internal flash memory"),
	NOT_IN_UPDATE_MODE
		(10, "Attemped to update while not in update mode"),
	INTERNAL_FLASH_ERASE_ERROR
		(11, "Error erasing internal flash memory");
	
	private int status;
	private String description;
	
	DfuStatusType(int status, String description)
	{
		this.status = status;
		this.description = description;
	}


	public String getDescription() {
		return description;
	}
	
	public int getStatusValue(){
		return status;
	}
	
	public void setStatusValue(int status){
		this.status = status;
	}

	public static DfuStatusType getStatus(int val){
		
		for(DfuStatusType status : DfuStatusType.values()){
			if(status.getStatusValue() == val){
				return status;
			}
		}
		return NULL;
	}
	
}
