package com.elf;

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
		this.sectionHeaders = sectionHeaders;
		this.programData = programData;
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
		return programHeader.getP_paddr();
	}
	
	public int getMemorySize()
	{
		return programHeader.getP_memsz();
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
