package com.dfu.header;

import com.util.ConversionUtil;

public class DfuImageHeader {

	public static final int SIZE = 22;
	
	
	private int vendorId;
	private int productId;
	private int deviceId;
	private int version;
	private int entryPoint;
	private int sectionHeaderOffset;
	private int fileHeaderSize;
	private int sectionHeaderSize;
	private int sectionHeaderCount;
	
	public DfuImageHeader() {
		this.vendorId = 0;
		this.productId = 0;
		this.deviceId = 0;
		this.version = 0;
		this.entryPoint = 0;
		this.sectionHeaderOffset = 0;
		this.fileHeaderSize = 0;
		this.sectionHeaderSize = 0;
		this.sectionHeaderCount = 0;
	}
	
	public DfuImageHeader(byte[] buffer)
	{
		this.vendorId = ConversionUtil.byteArrayToShort(buffer, 0);
		this.productId = ConversionUtil.byteArrayToShort(buffer, 2);
		this.deviceId = ConversionUtil.byteArrayToShort(buffer, 4);
		this.version = ConversionUtil.byteArrayToShort(buffer, 6);
		this.entryPoint = ConversionUtil.byteArrayToInt(buffer, 8);
		this.sectionHeaderOffset = ConversionUtil.byteArrayToInt(buffer, 12);
		this.fileHeaderSize = ConversionUtil.byteArrayToShort(buffer, 16);
		this.sectionHeaderSize = ConversionUtil.byteArrayToShort(buffer, 18);
		this.sectionHeaderCount = ConversionUtil.byteArrayToShort(buffer, 20);
	}

	public int getVendorId() {
		return vendorId;
	}

	public void setVendorId(int vendorId) {
		this.vendorId = vendorId;
	}

	public int getProductId() {
		return productId;
	}

	public void setProductId(int productId) {
		this.productId = productId;
	}

	public int getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(int deviceId) {
		this.deviceId = deviceId;
	}

	public int getVersion() {
		return version;
	}

	public void setVersion(int version) {
		this.version = version;
	}

	public int getEntryPoint() {
		return entryPoint;
	}

	public void setEntryPoint(int entryPoint) {
		this.entryPoint = entryPoint;
	}

	public int getSectionHeaderOffset() {
		return sectionHeaderOffset;
	}

	public void setSectionHeaderOffset(int sectionHeaderOffset) {
		this.sectionHeaderOffset = sectionHeaderOffset;
	}

	public int getFileHeaderSize() {
		return fileHeaderSize;
	}

	public void setFileHeaderSize(int fileHeaderSize) {
		this.fileHeaderSize = fileHeaderSize;
	}

	public int getSectionHeaderSize() {
		return sectionHeaderSize;
	}

	public void setSectionHeaderSize(int sectionHeaderSize) {
		this.sectionHeaderSize = sectionHeaderSize;
	}

	public int getSectionHeaderCount() {
		return sectionHeaderCount;
	}

	public void setSectionHeaderCount(int sectionHeaderCount) {
		this.sectionHeaderCount = sectionHeaderCount;
	}

}
