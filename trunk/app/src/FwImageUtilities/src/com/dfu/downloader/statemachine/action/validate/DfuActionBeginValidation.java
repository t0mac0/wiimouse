package com.dfu.downloader.statemachine.action.validate;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionBeginValidation implements DfuTransitionAction {

	public DfuActionBeginValidation() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.BEGIN_VALIDATION);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;

		link = data.getSerialLink();

		data.addMessageInfo(this, "Beginning validation...");

		command.setSectionCount(data.getFwImage().getImageSectionsCount());
		data.resetActiveImageSection();

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				data.setNextCommand(DfuCommandType.START_SECTION_VALIDATION);
				result = true;
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send BEGIN_VALIDATION command");
		}

		return result;
	}

}
