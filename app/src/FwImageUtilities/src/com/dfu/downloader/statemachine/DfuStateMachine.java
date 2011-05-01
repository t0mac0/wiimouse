package com.dfu.downloader.statemachine;

import javax.swing.SwingWorker;

import com.dfu.DfuImage;
import com.dfu.downloader.type.DfuCommandType;
import com.dfu.downloader.type.DfuStateType;
import com.msg.MessageGenerator;


public class DfuStateMachine extends SwingWorker<Void, Void>{

	private DfuStateTransitionTable transitionTable;
	private DfuImage fwImage;
	private MessageGenerator msg;
	private boolean ignoreVersion;


	public DfuStateMachine(MessageGenerator msg, DfuImage fwImage, boolean ignoreVersion) {
		transitionTable = new DfuStateTransitionTable();
		this.fwImage = fwImage;
		this.msg = msg;
		this.ignoreVersion = ignoreVersion;
	}

	@Override
	protected Void doInBackground() throws Exception {

		DfuCommandType currentCommand = DfuCommandType.QUERY_DEVICE;
		DfuCommonData commonData = new DfuCommonData(msg, fwImage, ignoreVersion);
		boolean updated = false;

		try {

			while(!isCancelled())
			{

				if( !transitionTable.getStateTransition(currentCommand) )
				{
					msg.addError(this, "Invalid state transition");
					break;
				}
				else if( !transitionTable.getTransitionAction().doAction(commonData) )
				{
					break;
				}
				else
				{
					currentCommand = commonData.getNextCommand();
					transitionTable.updateNextState();

					if( transitionTable.getCurrentState().equals(DfuStateType.COMPLETE_UPDATE))
					{
						msg.addInfo(this, "Successfully updated device firmware");
						updated = true;
						break;
					}

				}
			}

			if(!updated)
			{
				msg.addInfo(this, "Device has NOT  been updated");
			}

		} 
		catch(Exception e)
		{
			commonData.closeLink();
			throw e;
		}
		
		commonData.closeLink();
		
		return null;
	}





}
