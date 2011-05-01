package com;

import com.dfu.generator.DfuGenerator;

public class DfuGeneratorTest  {


	public static void main(String[] args) {
		
		@SuppressWarnings("unused")
		DfuGeneratorTest test = new DfuGeneratorTest();
	}
	
	public DfuGeneratorTest(){
		try {
			DfuGenerator.GenerateDfuImage(
					"C:\\Users\\Reed\\Programming\\wiiMouse_prj\\dan\\hid_mouse_virtual_com\\Debug\\hid_mouse_virtual_com.elf", 
					"dfuImages\\hid_mouse.img", 
					0xF46D, 
					0xF52B,
					0x0002,
					0x0002);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
