package com;

import com.dfu.downloader.DfuDownloader;
import com.dfu.generator.DfuGenerator;
import com.msg.MessageEvent;
import com.msg.MessageListener;

public class DfuDownloaderTest implements MessageListener {


	public static void main(String[] args) {
		@SuppressWarnings("unused")
		DfuDownloaderTest test = new DfuDownloaderTest();

	}
	
	public DfuDownloaderTest() {
		
		try {
			DfuGenerator.GenerateDfuImage(
					"C:\\Users\\Reed\\Programming\\wiiMouse_prj\\dan\\hid_mouse_virtual_com\\Debug\\hid_mouse_virtual_com.elf", 
					"dfuImages\\hid_mouse.img", 
					0xF46D, 
					0x052B,
					0x0002,
					0x0002);
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		DfuDownloader downloader = new DfuDownloader();
		
		downloader.addMessageListener(this);
		try {
			downloader.downloadImage("dfuImages\\hid_mouse.img", true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void messageReceived(MessageEvent evnt) {
		System.out.printf("%s: %s\n", evnt.getSeverity().getDescription(), evnt.getMessage());
	}

}
