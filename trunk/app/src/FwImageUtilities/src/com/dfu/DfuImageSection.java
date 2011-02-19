package com.dfu;

import java.util.List;

import com.dfu.header.DfuImageSectionHeader;

public class DfuImageSection extends DfuImageSectionHeader {

	private List<Byte> imageData;
	private int dataPointer;
	
	public DfuImageSection(DfuImageSectionHeader header, List<Byte> imageData) 
	{
		this.imageData = imageData;
		this.dataPointer = 0;
		
		this.setFileOffset(header.getFileOffset());
		this.setPhysicalAddress(header.getPhysicalAddress());
		this.setSize(header.getSize());
		this.setVirtualAddress(header.getVirtualAddress());
	}

	public int readImageData(byte[] buffer, int size)
	{
		int bytesRead;
		
		bytesRead = 0;
		
		while( bytesRead < size && dataPointer < imageData.size())
		{
			buffer[bytesRead++] = imageData.get(dataPointer++);
		}
		
		return bytesRead;
	}
	
	public int dataBytesRemaining(){
		return imageData.size() - dataPointer;
	}
	
	public void resetDataPointer(){
		dataPointer = 0;
	}
}
