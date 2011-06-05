package com.dfu.downloader.transfer;

import com.dfu.downloader.type.DfuModeType;
import com.dfu.downloader.type.DfuStatusType;
import com.util.ConversionUtil;


// this must be synchronized with ifc_dfu_type.h: DFU_Response
public class DfuResponse extends DfuPacket {
	
	public static int RESPONSE_SIZE = 23;
	private DfuStatusType status;
	private DfuModeType mode;
	private int vendorId;
	private int productId;
	private int deviceId;
	private int fwVersion;
	private int bootloaderVersion;
	private int checkSum;
	private int length;
	
	public DfuResponse()
	{
		this.status = DfuStatusType.NULL;
		this.mode = DfuModeType.NULL;
		this.vendorId = 0;
		this.productId = 0;
		this.deviceId = 0;
		this.fwVersion = 0;
		this.checkSum = 0;
		this.length = 0;
	}
	
	public DfuResponse packetToObject(){
		status = DfuStatusType.getStatus(ConversionUtil.byteArrayToByte(packetBuffer, 0));
		vendorId = ConversionUtil.byteArrayToShortBE(packetBuffer, 1);
		productId = ConversionUtil.byteArrayToShortBE(packetBuffer, 3);
		deviceId = ConversionUtil.byteArrayToShortBE(packetBuffer, 5);
		fwVersion = ConversionUtil.byteArrayToShortBE(packetBuffer, 7);
		bootloaderVersion = ConversionUtil.byteArrayToShortBE(packetBuffer, 9);
		checkSum = ConversionUtil.byteArrayToIntBE(packetBuffer, 11);
		length = ConversionUtil.byteArrayToIntBE(packetBuffer, 15);
		mode = DfuModeType.getMode(ConversionUtil.byteArrayToIntBE(packetBuffer, 19));
		
		return this;
	}

	public DfuStatusType getStatus() {
		return status;
	}


	public int getVendorId() {
		return vendorId;
	}

	public int getProductId() {
		return productId;
	}

	public int getDeviceId() {
		return deviceId;
	}

	public int getFwVersion() {
		return fwVersion;
	}
	public int getBootloaderVersion() {
		return bootloaderVersion;
	}

	public int getCheckSum() {
		return checkSum;
	}

	public int getLength() {
		return length;
	}

	public boolean isSuccessful(){
		return (this.status == DfuStatusType.SUCCESS);
	}
	
	public String getErrorDescription(){
		return this.status.getDescription();
	}

	public DfuModeType getMode() {
		return mode;
	}
	
	
	
}
