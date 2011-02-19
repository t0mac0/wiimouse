package com.dfu.downloader.transfer;

import com.dfu.downloader.type.DfuCommandType;
import com.util.ConversionUtil;


//this must be synchronized with ifc_dfu_types.h: DFU_Command
public class DfuCommand extends DfuPacket {
	
	public static int COMMAND_SIZE = 17;
	
	private DfuCommandType command;
	private int startAddress;
	private int sectionCount;
	private int length;
	private int offset;
	
	public DfuCommand() {
		this.command = DfuCommandType.NULL;
		this.startAddress = 0;
		this.sectionCount = 0;
		this.length = 0;
		this.offset = 0;
	}
	
	public DfuCommand(DfuCommandType command) {
		this.command = command;
		this.startAddress = 0;
		this.sectionCount = 0;
		this.length = 0;
	}
	
	public byte[] objectToPacket(){
		
		ConversionUtil.byteToByteArray(packetBuffer,  0, command.getCommand());
		ConversionUtil.intToByteArrayBE(packetBuffer, 1, startAddress);
		ConversionUtil.intToByteArrayBE(packetBuffer, 5, sectionCount);
		ConversionUtil.intToByteArrayBE(packetBuffer, 9, length);
		ConversionUtil.intToByteArrayBE(packetBuffer, 13, offset);
		
		return this.packetBuffer;
	}


	public void setCommand(DfuCommandType command) {
		this.command = command;
	}

	public void setStartAddress(int startAddress) {
		this.startAddress = startAddress;
	}

	public void setSectionCount(int sectionCount) {
		this.sectionCount = sectionCount;
	}

	public void setLength(int length) {
		this.length = length;
	}
	
	public void setOffset(int offset) {
		this.offset = offset;
	}


}
