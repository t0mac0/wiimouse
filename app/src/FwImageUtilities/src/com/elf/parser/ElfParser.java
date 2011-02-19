package com.elf.parser;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import com.elf.ElfFile;
import com.elf.ElfProgram;
import com.elf.header.ElfFileHeader;
import com.elf.header.ElfProgramHeader;
import com.elf.header.ElfSectionHeader;


public class ElfParser {

	private static final int DESTINATION_MSK = 0xF0000000;

	public static ElfFile ParseElfFile(String path) throws Exception
	{
		ElfFile elfFile;
		
		File file = new File(path);
		byte buffer[];

		if(!file.exists())
		{
			throw new Exception("File not found: " + path);
		}
		else if(!file.isFile())
		{
			throw new Exception("Path doesn't point to a file: "+path);
		}

		buffer = new byte[(int) file.length()];

		bufferFile(buffer, file);

		elfFile = parseElfFile(buffer);

		return elfFile;
	}

	private static void bufferFile(byte[] buffer, File elfFile) throws IOException
	{
		InputStream reader = new FileInputStream(elfFile);
		int c, i;

		try
		{
			i = 0;
			while ((c = reader.read()) != -1)
			{
				buffer[i++] = (byte) c;
			}
			reader.close();
		} 
		catch(IOException ex)
		{
			reader.close();
			throw(ex);
		}
	}
	
	private static ElfFile parseElfFile(byte[] buffer) throws Exception
	{
		ElfFile elfFile;
		ElfFileHeader fileHeader;
		List<ElfProgramHeader> programHeaders;
		List<ElfSectionHeader> sectionHeaders;
		List<ElfProgram> programs;
		
		fileHeader = new ElfFileHeader(buffer);
		
		programHeaders = parseProgramHeaders(buffer,fileHeader);
		sectionHeaders = parseSectionHeaders(buffer,fileHeader);
		programs = createPrograms(programHeaders, sectionHeaders, buffer);
		
		elfFile = new ElfFile(fileHeader, programs);
		
		return elfFile;
	}
	
	private static List<ElfProgramHeader> parseProgramHeaders(byte[] buffer, ElfFileHeader fileHeader)
	{
		List<ElfProgramHeader> programHeaders = new ArrayList<ElfProgramHeader>();
		int offset;
		
		offset = fileHeader.getE_phoff();
		for(int i = 0; i < fileHeader.getE_phnum(); i++)
		{
			programHeaders.add(new ElfProgramHeader(buffer, offset));
			offset += fileHeader.getE_phentsize();
		}
		
		return programHeaders;
	}
	
	private static List<ElfSectionHeader> parseSectionHeaders(byte[] buffer, ElfFileHeader fileHeader)
	{
		List<ElfSectionHeader> sectionHeaders = new ArrayList<ElfSectionHeader>();
		int offset;
		
		offset = fileHeader.getE_shoff();
		for(int i = 0; i < fileHeader.getE_shnum(); i++)
		{
			sectionHeaders.add(new ElfSectionHeader(buffer, offset));
			offset += fileHeader.getE_shentsize();
		}
		
		return sectionHeaders;
	}
	
	private static List<ElfProgram> createPrograms(List<ElfProgramHeader> programHeaders, List<ElfSectionHeader> sectionHeaders, byte[] buffer) throws Exception
	{
		List<ElfProgram> programs = new ArrayList<ElfProgram>();
		List<ElfSectionHeader> tmpSectionHeaders = new ArrayList<ElfSectionHeader>();
		List<Byte> programData;
		
		for(ElfProgramHeader programHeader :  programHeaders)
		{
			tmpSectionHeaders.clear();
			
			for(ElfSectionHeader sectionHeader : sectionHeaders)
			{
				if( ((sectionHeader.getSh_flags() & ElfSectionHeader.SHF_ALLOC) > 0) &&
						((sectionHeader.getSh_addr() & DESTINATION_MSK) == (programHeader.getP_vaddr() & DESTINATION_MSK)) )
				{
					tmpSectionHeaders.add(sectionHeader);
				}
			}
			
			programData = populateProgramData(tmpSectionHeaders, buffer);
			programs.add(new ElfProgram(programHeader, tmpSectionHeaders, programData));
		}
		
		return programs;
	}
	
	private static List<Byte> populateProgramData(List<ElfSectionHeader> sectionHeaders, byte[] buffer)
	{
		int offset, bytesPopulated;	
		List<Byte> programData;
		
		programData = new ArrayList<Byte>();
		bytesPopulated = 0;
		
		for( ElfSectionHeader sectionHeader : sectionHeaders )
		{
			offset = sectionHeader.getSh_offset();
			
			for( int i = 0; i < sectionHeader.getSh_size(); i++)
			{
				programData.add(buffer[offset + i]);
				bytesPopulated++;
			}
		}
		
		return programData;
		
	}

	
}
