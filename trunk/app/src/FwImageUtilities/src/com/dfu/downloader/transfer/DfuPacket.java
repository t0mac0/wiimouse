package com.dfu.downloader.transfer;

public abstract class DfuPacket {
	public static final int PACKET_SIZE = 512;

	public static final int MAX_PACKET_SIZE = 60;
	
	protected byte packetBuffer[];
	
	public DfuPacket(){
		this.packetBuffer = new byte[PACKET_SIZE];
	}
	
	public byte[] getPacketBuffer(){
		return this.packetBuffer;
	}
	
}
