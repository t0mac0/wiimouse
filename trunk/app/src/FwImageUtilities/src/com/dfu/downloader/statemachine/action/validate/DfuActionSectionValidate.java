package com.dfu.downloader.statemachine.action.validate;

import com.dfu.DfuImageSection;
import com.dfu.downloader.comm.DfuSerialLink;
import com.dfu.downloader.statemachine.DfuCommonData;
import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuPacket;
import com.dfu.downloader.transfer.DfuResponse;
import com.dfu.downloader.type.DfuCommandType;


public class DfuActionSectionValidate implements DfuTransitionAction {

	public DfuActionSectionValidate() {}

	public boolean doAction(DfuCommonData data) {
		DfuCommand command = new DfuCommand(DfuCommandType.SECTION_VALIDATE);
		DfuResponse response = new DfuResponse();
		DfuSerialLink link;
		boolean result = false;
	    DfuImageSection section;
		byte imageData[] = new byte[DfuPacket.PACKET_SIZE];
		byte deviceData[] = new byte[DfuPacket.PACKET_SIZE];
		int wordsRead = 0;
		int attempts = 0;
		boolean readEnabled = false;

		link = data.getSerialLink();

		if((section = data.getActiveImageSection()) == null){
			data.addMessageError(this, "No more sections to validate!");
			return false;
		}

		wordsRead = section.readImageData(imageData, DfuPacket.MAX_PACKET_SIZE);

		do {
			if(!readEnabled)
			{
				command.setOffset(data.getTransferOffset());
				command.setLength(wordsRead);
				if(link.sendCommand(command, response))
				{
					if(response.isSuccessful())
					{
						readEnabled = true;
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
				if(link.receiveData(command, deviceData, wordsRead))
				{
					if(!validateReceivedDataChunk(imageData, deviceData, wordsRead, data.getTransferOffset()))
					{
						data.addMessageError(this, "Device image data did not validate");
						break;
					}
					data.setTransferOffset(wordsRead);
					if(section.dataBytesRemaining() > 0)
					{
						data.setNextCommand(DfuCommandType.SECTION_VALIDATE);
					}
					else
					{
						data.setNextCommand(DfuCommandType.END_SECTION_VALIDATION);
					}
					result = true;
					break;

				}
				else
				{
					readEnabled = false;
					data.setTransferOffset(0);
				}
			}
		} while( attempts++ < 15);


		return result;
	}

	private boolean validateReceivedDataChunk(byte[] imageData, byte[] deviceData, int size, int offset){
		boolean valid = true;

		for(int i = 0; i < size; i++){
			if(imageData[i] != deviceData[i]){
				valid = false;
				System.out.printf("didn't validate at %X\n", offset+i);
				System.out.printf("%X != %X\n", imageData[i], deviceData[i]);
				//break;
			}
		}
		return valid;
	}

}
