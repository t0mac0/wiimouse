package com.dfu.header;

import com.util.ConversionUtil;

public class DfuImageSectionHeader {

	public static final int SIZE = 20;
	
	private int virtualAddress;
	private int physicalAddress;
	private int fileOffset;
	private int size;
	private int checkSum;
	
	public DfuImageSectionHeader() 
	{
		this.virtualAddress = 0;
		this.physicalAddress = 0;
		this.fileOffset = 0;
		this.size = 0;
		this.checkSum = 0;
	}
	
	public DfuImageSectionHeader(byte[] buffer, int offset)
	{
		this.fileOffset = ConversionUtil.byteArrayToInt(buffer, offset + 0);
		this.virtualAddress = ConversionUtil.byteArrayToInt(buffer, offset + 4);
		this.physicalAddress = ConversionUtil.byteArrayToInt(buffer, offset + 8);
		this.size = ConversionUtil.byteArrayToInt(buffer, offset + 12);
		this.checkSum = ConversionUtil.byteArrayToInt(buffer, offset + 16);
	}

	public int getVirtualAddress() {
		return virtualAddress;
	}

	public void setVirtualAddress(int virtualAddress) {
		this.virtualAddress = virtualAddress;
	}

	public int getPhysicalAddress() {
		return physicalAddress;
	}

	public void setPhysicalAddress(int physicalAddress) {
		this.physicalAddress = physicalAddress;
	}

	public int getFileOffset() {
		return fileOffset;
	}

	public void setFileOffset(int fileOffset) {
		this.fileOffset = fileOffset;
	}

	public int getSize() {
		return size;
	}

	public void setSize(int size) {
		this.size = size;
	}

	public void setCheckSum(int checkSum) {
		this.checkSum = checkSum;
	}

	public int getCheckSum() {
		return checkSum;
	}

}
