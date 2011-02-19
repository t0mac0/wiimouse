package com.dfu;

import java.util.List;

import com.dfu.header.DfuImageHeader;

public class DfuImage extends DfuImageHeader {

	private List<DfuImageSection> imageSections;
	
	public DfuImage(DfuImageHeader header, List<DfuImageSection> imageSections) {
		this.imageSections = imageSections;
		
		this.setVendorId(header.getVendorId());
		this.setProductId(header.getProductId());
		this.setVersion(header.getVersion());
		this.setDeviceId(header.getDeviceId());
		this.setEntryPoint(header.getEntryPoint());
		this.setFileHeaderSize(header.getFileHeaderSize());
		this.setSectionHeaderCount(header.getSectionHeaderCount());
		this.setSectionHeaderOffset(header.getSectionHeaderOffset());
		this.setSectionHeaderSize(header.getSectionHeaderSize());
	}

	public DfuImageSection getImageSection(int index)
	{
		return imageSections.get(index);
	}
	
	public List<DfuImageSection> getImageSections(){
		return this.imageSections;
	}
	
	public int getImageSectionsCount(){
		return imageSections.size();
	}
}
