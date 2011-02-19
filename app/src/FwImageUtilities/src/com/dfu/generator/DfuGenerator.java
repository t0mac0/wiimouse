package com.dfu.generator;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

import com.dfu.header.DfuImageHeader;
import com.dfu.header.DfuImageSectionHeader;
import com.elf.ElfFile;
import com.elf.ElfProgram;
import com.elf.parser.ElfParser;
import com.util.ConversionUtil;

public class DfuGenerator {

	private static final int SECTION_DATA_BOUNDARY = 0x100;

	public static void GenerateDfuImage(
			String elfInPath, 
			String dfuImageOutPath,
			int vendorId, 
			int productId, 
			int deviceId, 
			int version
			) throws Exception
	{
		ElfFile elfFile;
		FileOutputStream out;
		
		elfFile = ElfParser.ParseElfFile(elfInPath);
		
		out = new FileOutputStream(dfuImageOutPath);

		try {
			int writeCount = 0;
			
			writeCount = writeFileHeader(out, vendorId, productId, deviceId, version, elfFile, writeCount);
			writeCount = writeSections(out, elfFile, writeCount);
		} catch(Exception ex) {
			out.close();
			throw ex;
		}
		
		out.close();
	}
	
	private static int writeFileHeader(
			FileOutputStream out,
			int vendorId, 
			int productId, 
			int deviceId, 
			int version,
			ElfFile elfFile,
			int writeCount
			) throws IOException
	{
		byte buffer[];
		
		buffer = ConversionUtil.shortToByteArray((short)vendorId);
		out.write(buffer);
		
		buffer = ConversionUtil.shortToByteArray((short) productId);
		out.write(buffer);
		
		buffer = ConversionUtil.shortToByteArray((short) deviceId);
		out.write(buffer);
		
		buffer = ConversionUtil.shortToByteArray((short) version);
		out.write(buffer);
		
		buffer = ConversionUtil.intToByteArray(elfFile.getEntryPoint());
		out.write(buffer);
		
		buffer = ConversionUtil.intToByteArray(DfuImageHeader.SIZE); // start of sections headers
		out.write(buffer);
		
		buffer = ConversionUtil.shortToByteArray((short) DfuImageHeader.SIZE);
		out.write(buffer);
		
		buffer = ConversionUtil.shortToByteArray((short) DfuImageSectionHeader.SIZE);
		out.write(buffer);
		
		buffer = ConversionUtil.shortToByteArray((short) elfFile.getProgramCount());
		out.write(buffer);
		
		writeCount += DfuImageHeader.SIZE;
		
		return writeCount;
	}
	
	private static int writeSections(FileOutputStream out, ElfFile elfFile, int writeCount) throws IOException
	{
		int offset, i, sectionHeadersOffset;
		
		sectionHeadersOffset = writeCount;
		
		for(ElfProgram program : elfFile.getPrograms())
		{
			writeCount = writeSectionHeader(out, program, elfFile.getEntryPoint(), writeCount);
		}
		
		i = 0;
		for(ElfProgram program : elfFile.getPrograms())
		{
			offset = ConversionUtil.align(writeCount, SECTION_DATA_BOUNDARY);
			updateSectionDataOffset(out, sectionHeadersOffset + (i*DfuImageSectionHeader.SIZE), offset);
			writeCount = writeSectionData(out, program, offset, writeCount);
			i++;
		}

		return writeCount;
	}
	
	private static int writeSectionHeader(FileOutputStream out, ElfProgram elfProgram, int entryPoint, int writeCount) throws IOException
	{
		byte buffer[];
		
		buffer = ConversionUtil.intToByteArray(0); // section data offset place holder
		out.write(buffer);
		
		buffer = ConversionUtil.intToByteArray(elfProgram.getVirtualAddress());
		out.write(buffer);
		
		buffer = ConversionUtil.intToByteArray(elfProgram.getPhysicalAddress());
		out.write(buffer);
		
		buffer = ConversionUtil.intToByteArray(elfProgram.getMemorySize());
		out.write(buffer);
		
		buffer = ConversionUtil.intToByteArray(0); // checksum place holder
		out.write(buffer);
		
		writeCount += DfuImageSectionHeader.SIZE;
		
		return writeCount;
	}
	
	private static int writeSectionData(FileOutputStream out, ElfProgram elfProgram, int offset, int writeCount) throws IOException
	{
		ByteBuffer buffer;
		byte b[];
		FileChannel fc = out.getChannel();
		
		fc.position(writeCount);
		
		// pad with zeros
		while(writeCount < offset)
		{
			out.write(0);
			writeCount++;
		}
		
		buffer = ByteBuffer.wrap(b = elfProgram.getProgramDataBuffer());
		fc.write(buffer, writeCount);

		return (writeCount + b.length);
	}
	
	private static void updateSectionDataOffset(FileOutputStream out, int fileOffset, int dataOffset) throws IOException
	{
		FileChannel fc = out.getChannel();
		ByteBuffer buffer;
		
		buffer = ByteBuffer.wrap(ConversionUtil.intToByteArray(dataOffset));
		fc.write(buffer, fileOffset);
	}
	

}




















