package com.dfu.downloader.statemachine.action.update;

import com.dfu.DfuImageSection;
import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuPacket;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionSectionUpdate implements DfuTransitionAction {


	public DfuActionSectionUpdate() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.SECTION_UPDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;
		DfuImageSection section;
		byte imageData[] = new byte[DfuPacket.PACKET_SIZE];
		int wordsRead = 0;
		int attempts = 0;
		boolean writeEnabled = false;

		link = data.getSerialLink();

		if((section = data.getActiveImageSection()) == null){
			data.addMessageError(this, "No more sections to update!");
			return false;
		}

		wordsRead = section.readImageData(imageData, DfuPacket.PACKET_SIZE);

		do {
			if(!writeEnabled)
			{
				command.setOffset(data.getTransferOffset());
				command.setLength(wordsRead);
				if(link.sendCommand(command, response))
				{
					if(response.isSuccessful())
					{
						writeEnabled = true;
					}
					else
					{
						data.addMessageError(this, "Device failed: " + response.getErrorDescription());
						break;
					}
				}
			}
			else
			{
				if(link.sendData(imageData, wordsRead, response))
				{
					if(response.isSuccessful())
					{
						data.setTransferOffset(wordsRead);
						if(section.dataBytesRemaining() > 0)
						{
							data.setNextCommand(DfuCommandType.SECTION_UPDATE);
						}
						else
						{
							data.setNextCommand(DfuCommandType.END_SECTION_UPDATE);
						}
						result = true;
						break;
					}
					else
					{
						data.addMessageError(this, "Device failed: " + response.getErrorDescription());
						break;
					}
				}
				else
				{
					writeEnabled = false;
					data.setTransferOffset(0);
				}
			}
		} while( attempts++ < 50);


		return result;
	}
	
}
