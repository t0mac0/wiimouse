package com.elf;

import java.util.List;

import com.elf.header.ElfFileHeader;


public class ElfFile {

	private ElfFileHeader header;
	private List<ElfProgram> programs;
	
	public ElfFile(ElfFileHeader header, List<ElfProgram> programs) {
		this.header = header;
		this.programs = programs;
	}
	
	public int getEntryPoint()
	{
		return this.header.getE_entry();
	}
	
	public int getProgramCount()
	{
		return this.programs.size();
	}

	public List<ElfProgram> getPrograms()
	{
		return this.programs;
	}
}
