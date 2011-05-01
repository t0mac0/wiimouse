package com.dfu.downloader.statemachine;


import java.util.ListIterator;

import com.dfu.DfuImage;
import com.dfu.DfuImageSection;
import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.type.DfuCommandType;
import com.msg.MessageGenerator;


public class DfuCommonData {
	private DfuImage fwImage;
	private MessageGenerator msg;
	private DfuCommandType nextCommand;
	private DfuSerialLink serial;

	private boolean requery;
	private boolean hasSerialLink;
	private boolean ignoreVersion;
	private int transferAddress;
	private int transferOffset;

	private ListIterator<DfuImageSection> imageSectionIterator;
	private DfuImageSection actionImageSection;

	public DfuCommonData(MessageGenerator msg, DfuImage fwImage, boolean ignoreVersion){
		this.fwImage = fwImage;
		this.msg = msg;
		this.nextCommand = DfuCommandType.NULL;
		this.hasSerialLink = false;
		this.setRequery(false);
		this.transferAddress = 0;
		this.transferOffset = 0;
		this.ignoreVersion = ignoreVersion;
		
		imageSectionIterator = fwImage.getImageSections().listIterator();
		
	}


	public DfuImage getFwImage() {
		return fwImage;
	}


	public void setNextCommand(DfuCommandType nextCommand) {
		this.nextCommand = nextCommand;
	}


	public DfuCommandType getNextCommand() {
		return nextCommand;
	}


	public void setSerialLink(DfuSerialLink serial) {
		this.serial = serial;
		this.hasSerialLink = true;
	}


	public DfuSerialLink getSerialLink() {
		return serial;
	}

	public boolean hasSerialLink() {
		return hasSerialLink;
	}
	
	public void closeLink() {
		if(hasSerialLink)
			serial.closeLink();
	}

	public MessageGenerator getMsg() {
		return msg;
	}

	public void addMessageInfo(Object src, String msg){
		this.msg.addInfo(src, msg);
	}

	public void addMessageError(Object src, String msg){
		this.msg.addError(src, msg);
	}


	public void setRequery(boolean requery) {
		this.requery = requery;
	}


	public boolean isRequery() {
		return requery;
	}
	
	public void resetActiveImageSection(){
		while(this.imageSectionIterator.hasPrevious())
			this.actionImageSection = this.imageSectionIterator.previous();
		
	}

	public DfuImageSection getActiveImageSection(){
		return this.actionImageSection;
	}

	public boolean hasMoreImageSections(){
		return this.imageSectionIterator.hasNext();
	}
	
	public DfuImageSection nextActiveImageSection(){
		return this.actionImageSection = this.imageSectionIterator.next();
	}


	public void setTransferAddress(int transferAddress) {
		this.transferAddress = transferAddress;
	}


	public int getTransferAddress() {
		return transferAddress;
	}


	public void setTransferOffset(int transferOffset) {
		this.transferOffset = transferOffset;
	}


	public int getTransferOffset() {
		return transferOffset;
	}


	public void setIgnoreVersion(boolean ignoreVersion) {
		this.ignoreVersion = ignoreVersion;
	}


	public boolean isIgnoreVersion() {
		return ignoreVersion;
	}


}
