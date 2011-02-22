package com;

import java.util.Iterator;
import java.util.List;

public class FeepromEntry {

	String size;
	String flags;
	String data;
	String key;

	public FeepromEntry(String line, List<String>lines) {
		int l, r;

		l = line.indexOf("(")+1;
		r = line.indexOf(",",l);

		this.key = line.substring(l, r).trim();

		l = r+1;

		r = line.indexOf(",", l);
		this.data = line.substring(l, r).trim();

		l = r+1;

		r = line.indexOf(",", l);
		this.size = line.substring(l, r);

		l = r+1;

		r = line.lastIndexOf(")");

		this.flags = line.substring(l, r);

		updateData(lines);

	}

	public String getFlags(){
		return flags;
	}

	public String getSizeStr(){
		return size;
	}

	public String getData(){
		return this.data;
	}

	public String getKey()
	{return key;}

	public String getEntry()
	{
		String line;

		line = "{" + getSizeStr() + "*2, ";
		line += getKey() + ", ";
		line += "TRUE, ";
		line += getFlags() + ", ";
		line += "{NULL} }";

		return line;
	}

	private void updateData(List<String>lines)
	{
		String line;

		for(Iterator<String> it = lines.iterator(); it.hasNext();)
		{
			line = it.next();

			if(line.contains(data) && line.contains("#define"))
			{
				int l = line.indexOf(data)+ data.length();
				line =  line.substring(l);
				if(line.contains("//"))
					line = line.substring(0, line.indexOf("//"));
				
				if(!line.contains("\\")){
					data = line.replace("{", "").replace("}", "").trim();
				}
				else
				{
					data = "";
					do
					{
						data += line.replace("{", "").replace("}", "").replace("\\", "").trim();
						if(it.hasNext())
							line = it.next();
						else
							break;
					} 
					while(line.contains("\\"));
				}
			}
		}
	}
}
