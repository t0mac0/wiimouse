package com.dfu.downloader.statemachine.action.device;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionInitializeDevice implements DfuTransitionAction {

	public DfuActionInitializeDevice() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.INITIALIZE_UPDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;
		
		link = data.getSerialLink();
		
		data.addMessageInfo(this, "Initializing device for update...");
		
		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				data.addMessageInfo(this, "Waiting 10s while device enters device update mode...");
				data.setNextCommand(DfuCommandType.QUERY_DEVICE);
				try {
					Thread.sleep(10000);
					result = true;
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send INITIALIZE_UPDATE command");
		}
		
		return result;
	}

}
