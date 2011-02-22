package com;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.io.FileUtils;

public class FeepromPrepreprocessor {

	private static final String ADD_ENTRY = "FEEPROM_ADD_ENTRY";
	private static final String ENTRY_DATA = "#define _$FEEPROM_ENTRY_DATA$_";
	private static final String ENTRIES = "#define _$FEEPROM_ENTRIES$_";
	private static final String ENTRY_COUNT = "#define _$FEEPROM_ENTRY_COUNT$_";
	private static final String USE_GENERATOR = "#ifdef USE_FEEPROM_ENTRY_GENERATOR";

	@SuppressWarnings("unused")
	public static void main(String[] args) {
		try {
			System.out.println("Pre-preprocessing Flash Eeprom files...");
			FeepromPrepreprocessor proc = new FeepromPrepreprocessor(args[0], args[1]);
			System.out.println("Finished preproccessing Flash Eeprom files.");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public FeepromPrepreprocessor(String projectPath, String outFileName) throws IOException {

		List<FeepromEntry> entries = getEntries(projectPath);
		populateOutfile(projectPath + "\\" + outFileName, entries);

		System.out.printf("Pre-processed %d entries and wrote to: %s\n", entries.size(), outFileName);
	}

	private List<FeepromEntry> getEntries(String projectPath) throws IOException
	{
		List<FeepromEntry> entries = new ArrayList<FeepromEntry>();
		String[] extensions = {"c", "h"};

		Collection<File> files = FileUtils.listFiles(new File(projectPath), extensions, true);

		for(Iterator<File> it = files.iterator(); it.hasNext();)
		{
			getFileEntries(it.next(), entries);
		}
		return entries;
	}

	private void getFileEntries(File file, List<FeepromEntry> entries) throws IOException
	{
		BufferedReader reader = new BufferedReader(new FileReader(file));
		String line;
		FeepromEntry entry;
		List<String>lines = new ArrayList<String>();
		boolean entryFound = false;

		while( (line = reader.readLine()) != null)
		{
			lines.add(line);
			if(line.contains(ADD_ENTRY) && !line.contains("#define"))
			{
				entryFound = true;

			}
		}
		reader.close();

		if(entryFound)
		{
			for( String l : lines)
			{
				if(l.contains(ADD_ENTRY))
				{
					entry = new FeepromEntry(l, lines);
					entries.add(entry);
				}
			}
		}


	}

	private void populateOutfile(String path, List<FeepromEntry> entries) throws IOException
	{
		BufferedReader reader;
		BufferedWriter writer;
		String line;
		List<String> lines = new ArrayList<String>();
		boolean writeFile = true;

		reader = new BufferedReader(new FileReader(path));
		while( (line = reader.readLine()) != null)
		{
			if(line.contains(USE_GENERATOR))
			{
				lines.add(USE_GENERATOR);
				writeEntriesCount(lines, entries.size());
				writeEntries(lines, entries);
				writeEntryData(lines, entries);
				writeFile = false;
			}
			else if(line.contains("#else"))
			{
				writeFile = true;
			}

			if(writeFile)
				lines.add(line);
		}
		reader.close();



		writer = new BufferedWriter(new FileWriter(path));

		for(String l : lines)
		{
			writer.write(l + "\n");
		}
		writer.close();
	}

	private void writeEntryData(List<String> lines, List<FeepromEntry> entries)
	{
		String line;

		line = ENTRY_DATA  + " {\\\n";

		for(FeepromEntry entry : entries)
		{
			line += "\t\t" + entry.getData() + ",\\\n";
		}
		line += "}";
		lines.add(line);

	}

	private void writeEntries(List<String> lines, List<FeepromEntry> entries)
	{
		String line;

		line = ENTRIES + " { \\\n";

		for(FeepromEntry entry : entries)
		{
			line += "\t\t" + entry.getEntry() + ",\\\n";
		}
		line += "}";
		lines.add(line);
	}



	private void writeEntriesCount(List<String> lines, int count)
	{
		lines.add(ENTRY_COUNT + " " + count + "\n");
	}

}
