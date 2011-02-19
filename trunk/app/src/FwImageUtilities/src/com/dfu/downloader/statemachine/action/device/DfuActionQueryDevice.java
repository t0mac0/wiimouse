package com.dfu.downloader.statemachine.action.device;

import com.dfu.DfuImage;
import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;
import com.dfu.downloader.type.DfuModeType;


public class DfuActionQueryDevice implements DfuTransitionAction{

	public DfuActionQueryDevice()  {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.QUERY_DEVICE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;
		int i = 0;

		if( !data.hasSerialLink()){
			data.setSerialLink(new DfuSerialLink());
		}
		link = data.getSerialLink();
		
		data.addMessageInfo(this, "Query device...");

		for(i = 1; i <= DfuSerialLink.MAX_COM_NUMBER; i++){
			if( link.openLink(i)){
				if(link.sendCommand(command, response)){
					if(!response.isSuccessful()){
						data.addMessageError(this, "Device failed: " + response.getErrorDescription());
						break;
					}
					if( validateDevice(response, data)){
						if(response.getMode().equals(DfuModeType.USER)){
							data.setNextCommand(DfuCommandType.INITIALIZE_UPDATE);
							data.setRequery(true);
						}
						else
						{
							data.setNextCommand(DfuCommandType.BEGIN_UPDATE);
							data.setRequery(false);
						}
						
						result = true;
						
						break;
					}
				}
				else {
					data.addMessageError(this, "Failed to send QUERY_DEVICE command");
					break;
				}
			}

			link.closeLink();
		}

		if(i > DfuSerialLink.MAX_COM_NUMBER){
			data.addMessageError(this, "No devices found that match Firmware Image parameters");
		}

		return result;
	}

	private boolean validateDevice(DfuResponse response, DfuCommonData data){
		boolean result = false;
		DfuImage header = data.getFwImage();

		if( (header.getProductId() == response.getProductId()) &&
				(header.getVendorId() == response.getVendorId()) &&
				(header.getDeviceId() == response.getDeviceId())){

			try{
				int ver = header.getVersion();
				if(ver > response.getFwVersion()){
					result = true;
					if(!data.isRequery())
					data.addMessageInfo(this, "Successfully query device and found it needs an update");
				}
				else
				{
					data.addMessageInfo(this, "Successfully query device and found it is already up-to-date");
				}
			} catch(NumberFormatException e){}

		}
		return result;
	}

}
