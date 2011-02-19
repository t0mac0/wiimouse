package com.dfu.downloader.statemachine.action.validate;

import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;

public class DfuActionEndSectionValidation implements DfuTransitionAction {

	public DfuActionEndSectionValidation() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.END_SECTION_VALIDATION);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;

		link = data.getSerialLink();

		data.addMessageInfo(this, "Ending section validation...");
		
		command.setSectionCount(data.getFwImage().getImageSectionsCount());

		if(link.sendCommand(command, response)){
			if(response.isSuccessful()){
				if(validateChecksum(data.getActiveImageSection().getCheckSum(), 
						response.getCheckSum()))
				{
					if(data.hasMoreImageSections()){
						data.setNextCommand(DfuCommandType.START_SECTION_VALIDATION);
					} 
					else
					{
						data.setNextCommand(DfuCommandType.END_VALIDATION);
					}
					result = true;
				}
				else
				{
					result = true; // TODO: temporary
					data.addMessageError(this, "Checksum did not validate");
				}
			}
			else
			{
				data.addMessageError(this, "Device failed: " + response.getErrorDescription());
			}
		}
		else
		{
			data.addMessageError(this, "Failed to send END_SECTION_VALIDATION command");
		}

		return result;
	}
	
	private boolean validateChecksum(int imageChecksum, int checksum){
		return true;
		//return (imageChecksum == checksum);

	}

}
