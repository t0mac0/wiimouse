package com.dfu.downloader.type;



// this must be synchronized with ifc_dfu_type.h: DFU_ModeType
public enum DfuModeType {
	USER(0x39FE72B6),
	UPDATE(0xFFFFFFFF),
	NULL(0),
	USER_MODE_ADDR(0x08004130);
	
	private int val;
	
	DfuModeType(int val)
	{
		this.val = val;
	}
	
	public int getModeValue(){
		return this.val;
	}
	public static DfuModeType getMode(int val){
		
		for(DfuModeType status : DfuModeType.values()){
			if(status.getModeValue() == val){
				return status;
			}
		}
		return NULL;
	}
}
