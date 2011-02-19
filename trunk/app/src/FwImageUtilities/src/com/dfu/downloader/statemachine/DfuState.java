package com.dfu.downloader.statemachine;

import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.type.DfuCommandType;
import com.dfu.downloader.type.DfuStateType;


public class DfuState {

	private DfuCommandType command;
	private DfuStateType currentState;
	private DfuStateType nextState;
	private DfuTransitionAction action;
	
	public DfuState(DfuCommandType command, 
					DfuStateType currentState, 
					DfuStateType nextState,
					DfuTransitionAction action)
	{
		this.command = command;
		this.currentState = currentState;
		this.nextState = nextState;
		this.action = action;
	}


	public DfuCommandType getCommand() {
		return command;
	}

	public DfuStateType getCurrentState() {
		return currentState;
	}

	public DfuStateType getNextState() {
		return nextState;
	}

	public DfuTransitionAction getAction() {
		return action;
	}
	
	
}
