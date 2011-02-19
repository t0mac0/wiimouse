package com.dfu.downloader.statemachine.action.update;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionEndUpdate implements DfuTransitionAction {

	public DfuActionEndUpdate() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.END_UPDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;

		link = data.getSerialLink();

		data.addMessageInfo(this, "Ending device firmware update...");

		command.setSectionCount(data.getFwImage().getImageSectionsCount());

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				data.setNextCommand(DfuCommandType.BEGIN_VALIDATION);
				result = true;
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send END_UPDATE command");
		}

		return result;
	}
}
