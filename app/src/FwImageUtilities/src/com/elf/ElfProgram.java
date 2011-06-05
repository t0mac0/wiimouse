package com.elf;

import java.util.ArrayList;
import java.util.List;

import com.elf.header.ElfProgramHeader;
import com.elf.header.ElfSectionHeader;


public class ElfProgram {

	private ElfProgramHeader programHeader;
	private List<ElfSectionHeader> sectionHeaders;
	
	private List<Byte> programData;
	
	public ElfProgram(ElfProgramHeader programHeader, List<ElfSectionHeader> sectionHeaders, List<Byte> programData) throws Exception
	{
		this.programHeader = programHeader;
		this.programData = programData;
		this.sectionHeaders = new ArrayList<ElfSectionHeader>();
		
		for(ElfSectionHeader header : sectionHeaders)
			this.sectionHeaders.add(header);
	}

	public ElfProgramHeader getProgramHeader() {
		return programHeader;
	}

	public List<ElfSectionHeader> getSectionHeaders() {
		return sectionHeaders;
	}

	public ElfSectionHeader getSectionHeader(int i) {
		return sectionHeaders.get(i);
	}
	
	public List<Byte> getProgramData() {
		return programData;
	}
	
	public int getVirtualAddress()
	{
		return programHeader.getP_vaddr();
	}
	
	public int getPhysicalAddress()
	{
		int addr;
		int offset = 0x7FFFFFFF;
		
		for(ElfSectionHeader header : sectionHeaders)
		{
			addr = header.getSh_addr()&0x00FFFFFF;
			if(addr < offset)
			{
				offset = addr;
			}
		}
		return programHeader.getP_paddr() + offset;
	}
	
	public int getMemorySize()
	{
		int size = 0;
		
		for(ElfSectionHeader header : sectionHeaders)
		{
			size += header.getSh_size();
		}		
		
		return size;
	}
	
	public byte[] getProgramDataBuffer()
	{
		byte buffer[] = new byte[this.programData.size()];
		
		for(int i = 0; i < programData.size(); i++)
		{
			buffer[i] = programData.get(i);
		}
		
		return buffer;
	}
	


}
