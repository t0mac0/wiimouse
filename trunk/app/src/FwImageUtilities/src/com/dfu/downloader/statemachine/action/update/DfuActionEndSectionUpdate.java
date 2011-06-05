package com.dfu.downloader.statemachine.action.update;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionEndSectionUpdate implements DfuTransitionAction {

	public DfuActionEndSectionUpdate() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.END_SECTION_UPDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;

		link = data.getSerialLink();

		data.addMessageInfo(this, "Section update complete.");
		
		command.setSectionCount(data.getFwImage().getImageSectionsCount());

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				if(data.hasMoreImageSections()){
					data.setNextCommand(DfuCommandType.START_SECTION_UPDATE);
				} 
				else
				{
					data.setNextCommand(DfuCommandType.END_UPDATE);
				}
				result = true;
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send END_SECTION_UPDATE command");
		}

		return result;
	}

}
