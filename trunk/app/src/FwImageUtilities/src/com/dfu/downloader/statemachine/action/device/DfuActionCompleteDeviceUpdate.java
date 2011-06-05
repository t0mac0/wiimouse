package com.dfu.downloader.statemachine.action.device;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionCompleteDeviceUpdate implements DfuTransitionAction {

	public DfuActionCompleteDeviceUpdate() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.COMPLETE_UPDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;

		link = data.getSerialLink();

		data.addMessageInfo(this, "Completing firmware update.");

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				result = true;
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send COMPLETE_UPDATE command");
		}

		return result;
	}
}
