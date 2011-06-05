package com.dfu.downloader.statemachine.action.validate;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionEndValidation implements DfuTransitionAction {

	public DfuActionEndValidation() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.END_VALIDATION);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;

		link = data.getSerialLink();

		data.addMessageInfo(this, "Validation Complete.");

		command.setSectionCount(data.getFwImage().getImageSectionsCount());
		data.resetActiveImageSection();

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				data.setNextCommand(DfuCommandType.COMPLETE_UPDATE);
				result = true;
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send END_VALIDATION command");
		}

		return result;
	}

}
