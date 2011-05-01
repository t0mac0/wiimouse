package com.dfu.downloader;

import com.dfu.DfuImage;
import com.dfu.downloader.statemachine.DfuStateMachine;
import com.dfu.parser.DfuParser;
import com.msg.MessageGenerator;
import com.msg.MessageListener;


public class DfuDownloader {

	MessageGenerator msg;
	
	public DfuDownloader() {
		msg = new MessageGenerator();
	}
	
	public DfuDownloader(MessageListener listener) {
		msg = new MessageGenerator();
		
		addMessageListener(listener);
	}

	public void downloadImage(String imagePath, boolean ignoreVersion) throws Exception
	{
		DfuImage image;
		
		image = DfuParser.parseDfuImage(imagePath);

		new DfuStateMachine(msg, image, ignoreVersion).run();
	}
	
	public void addMessageListener(MessageListener listener)
	{
		msg.addMessageListener(listener);
	}
	
	public void removeMessageListener(MessageListener listener)
	{
		msg.removeMessageListener(listener);
	}
	

}














