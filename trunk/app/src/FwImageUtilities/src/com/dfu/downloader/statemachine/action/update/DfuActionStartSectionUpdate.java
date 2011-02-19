package com.dfu.downloader.statemachine.action.update;

import com.dfu.DfuImageSection;
import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionStartSectionUpdate implements DfuTransitionAction {

	public DfuActionStartSectionUpdate() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.START_SECTION_UPDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;
		DfuImageSection section;

		link = data.getSerialLink();

		if((section = data.nextActiveImageSection()) == null){
			data.addMessageError(this, "No more sections to update!");
			return false;
		}

		command.setStartAddress(section.getPhysicalAddress());
		command.setLength(section.getSize());
		section.resetDataPointer();

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				data.setNextCommand(DfuCommandType.SECTION_UPDATE);
				data.setTransferOffset(0);
				result = true;
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send START_SECTION_UPDATE command");
		}

		return result;
	}

}
