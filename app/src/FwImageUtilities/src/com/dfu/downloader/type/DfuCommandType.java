package com.dfu.downloader.type;

// this must be synchronized with ifc_dfu_type.h: DFU_CommandType
public enum DfuCommandType {
	QUERY_DEVICE			(0),
	INITIALIZE_UPDATE		(1),
	BEGIN_UPDATE			(2),
	START_SECTION_UPDATE	(3),
	SECTION_UPDATE			(4),
	END_SECTION_UPDATE		(5),
	END_UPDATE				(6),
	BEGIN_VALIDATION		(7),
	START_SECTION_VALIDATION(8),
	SECTION_VALIDATE		(9),
	END_SECTION_VALIDATION	(10),
	END_VALIDATION			(11),
	COMPLETE_UPDATE			(12),
	NULL					(-1);
	
	private int command;
	
	DfuCommandType(int command)
	{
		this.command = command;
	}

	public int getCommand() {
		return command;
	}
	
}
