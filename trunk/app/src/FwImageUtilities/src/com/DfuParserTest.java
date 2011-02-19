package com;

import com.dfu.DfuImage;
import com.dfu.parser.DfuParser;

public class DfuParserTest {


	public static void main(String[] args) {
		@SuppressWarnings("unused")
		DfuParserTest test = new DfuParserTest();
	}
	
	public DfuParserTest() {
		DfuImage image;
		
		try {
			image = DfuParser.parseDfuImage("dfuImages\\hid_mouse.img");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}


}
