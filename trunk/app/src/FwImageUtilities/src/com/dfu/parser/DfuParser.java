package com.dfu.parser;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import com.dfu.DfuImage;
import com.dfu.DfuImageSection;
import com.dfu.header.DfuImageHeader;
import com.dfu.header.DfuImageSectionHeader;


public class DfuParser {

	public static DfuImage parseDfuImage(String path) throws Exception
	{
		DfuImage dfuImage;
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

		dfuImage = parseDfuImage(buffer);

		return dfuImage;
	}

	private static void bufferFile(byte[] buffer, File file) throws IOException
	{
		InputStream reader = new FileInputStream(file);
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
	
	private static DfuImage parseDfuImage(byte[] buffer) throws Exception
	{
		DfuImage dfuImage;
		DfuImageHeader header;
		List<DfuImageSection> imageSections;
		
		header = new DfuImageHeader(buffer);
		imageSections = parseImageSections(header, buffer);
		
		
		dfuImage = new DfuImage(header, imageSections);
		
		return dfuImage;
	}
	
	private static List<DfuImageSection> parseImageSections(DfuImageHeader imageHeader, byte buffer[])
	{
		List<DfuImageSection> sections = new ArrayList<DfuImageSection>();
		List<Byte> sectionData;
		DfuImageSectionHeader header;
		int offset;
		
		offset = imageHeader.getSectionHeaderOffset();
		
		for(int i = 0; i < imageHeader.getSectionHeaderCount(); i++)
		{
			header = new DfuImageSectionHeader(buffer, offset);
			offset += imageHeader.getSectionHeaderSize();
			
			sectionData = parseImageSectionData(buffer, header);
			
			sections.add(new DfuImageSection(header, sectionData));
		}
		
		
		return sections;
	}

	private static List<Byte> parseImageSectionData(byte[] buffer, DfuImageSectionHeader header)
	{
		List<Byte> sectionData;
		int offset;
		
		sectionData = new ArrayList<Byte>();
		offset = header.getFileOffset();
		
		for(int i = 0; i < header.getSize(); i++)
		{
			sectionData.add(buffer[offset+i]);
		}
		
		return sectionData;
	}


}
