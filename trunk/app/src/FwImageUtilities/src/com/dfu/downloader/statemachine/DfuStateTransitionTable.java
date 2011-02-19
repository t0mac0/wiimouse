package com.dfu.downloader.statemachine;

import java.util.ArrayList;
import java.util.List;

import com.dfu.downloader.statemachine.action.DfuTransitionAction;
import com.dfu.downloader.statemachine.action.device.DfuActionCompleteDeviceUpdate;
import com.dfu.downloader.statemachine.action.device.DfuActionInitializeDevice;
import com.dfu.downloader.statemachine.action.device.DfuActionQueryDevice;
import com.dfu.downloader.statemachine.action.update.DfuActionBeginUpdate;
import com.dfu.downloader.statemachine.action.update.DfuActionEndSectionUpdate;
import com.dfu.downloader.statemachine.action.update.DfuActionEndUpdate;
import com.dfu.downloader.statemachine.action.update.DfuActionSectionUpdate;
import com.dfu.downloader.statemachine.action.update.DfuActionStartSectionUpdate;
import com.dfu.downloader.statemachine.action.validate.DfuActionBeginValidation;
import com.dfu.downloader.statemachine.action.validate.DfuActionEndSectionValidation;
import com.dfu.downloader.statemachine.action.validate.DfuActionSectionValidate;
import com.dfu.downloader.statemachine.action.validate.DfuActionStartSectionValidation;
import com.dfu.downloader.type.DfuCommandType;
import com.dfu.downloader.type.DfuStateType;



public class DfuStateTransitionTable {

	@SuppressWarnings("serial")
	private List<DfuState> transitionTable  = new ArrayList<DfuState>() {{
		//					Command								Current State						Next State                   			Action
		add(new DfuState(DfuCommandType.QUERY_DEVICE, 			DfuStateType.NULL, 					DfuStateType.QUERY, 				new DfuActionQueryDevice()));
		add(new DfuState(DfuCommandType.INITIALIZE_UPDATE, 		DfuStateType.QUERY, 				DfuStateType.INITIALIZE, 			new DfuActionInitializeDevice()));
		add(new DfuState(DfuCommandType.QUERY_DEVICE, 			DfuStateType.INITIALIZE,			DfuStateType.QUERY, 				new DfuActionQueryDevice()));
		
		add(new DfuState(DfuCommandType.BEGIN_UPDATE, 			DfuStateType.QUERY,					DfuStateType.BEGIN_UPDATE, 			new DfuActionBeginUpdate()));
		add(new DfuState(DfuCommandType.START_SECTION_UPDATE,	DfuStateType.BEGIN_UPDATE,			DfuStateType.START_SECTION_UPDATE, 	new DfuActionStartSectionUpdate()));
		add(new DfuState(DfuCommandType.SECTION_UPDATE, 		DfuStateType.START_SECTION_UPDATE,	DfuStateType.SECTION_UPDATE, 		new DfuActionSectionUpdate()));
		add(new DfuState(DfuCommandType.SECTION_UPDATE, 		DfuStateType.SECTION_UPDATE,		DfuStateType.SECTION_UPDATE, 		new DfuActionSectionUpdate()));
		add(new DfuState(DfuCommandType.END_SECTION_UPDATE, 	DfuStateType.SECTION_UPDATE,		DfuStateType.END_SECTION_UPDATE, 	new DfuActionEndSectionUpdate()));
		add(new DfuState(DfuCommandType.START_SECTION_UPDATE, 	DfuStateType.END_SECTION_UPDATE,	DfuStateType.START_SECTION_UPDATE, 	new DfuActionStartSectionUpdate()));
		add(new DfuState(DfuCommandType.END_UPDATE, 			DfuStateType.END_SECTION_UPDATE,	DfuStateType.END_UPDATE, 			new DfuActionEndUpdate()));
		
		add(new DfuState(DfuCommandType.BEGIN_VALIDATION, 		DfuStateType.END_UPDATE,			DfuStateType.BEGIN_VALIDATION, 		new DfuActionBeginValidation()));
		add(new DfuState(DfuCommandType.START_SECTION_VALIDATION,DfuStateType.BEGIN_VALIDATION,		DfuStateType.START_SECTION_VALIDATION, new DfuActionStartSectionValidation()));
		add(new DfuState(DfuCommandType.SECTION_VALIDATE,		DfuStateType.START_SECTION_VALIDATION,DfuStateType.VALIDATE_SECTION, 	new DfuActionSectionValidate()));
		add(new DfuState(DfuCommandType.SECTION_VALIDATE,		DfuStateType.VALIDATE_SECTION,		DfuStateType.VALIDATE_SECTION, 		new DfuActionSectionValidate()));
		add(new DfuState(DfuCommandType.END_SECTION_VALIDATION,	DfuStateType.VALIDATE_SECTION,		DfuStateType.END_SECTION_VALIDATION,new DfuActionEndSectionValidation()));
		add(new DfuState(DfuCommandType.START_SECTION_VALIDATION,DfuStateType.END_SECTION_VALIDATION,DfuStateType.START_SECTION_VALIDATION,new DfuActionStartSectionValidation()));
		add(new DfuState(DfuCommandType.END_VALIDATION,			DfuStateType.END_SECTION_VALIDATION,DfuStateType.COMPLETE_UPDATE,		new DfuActionCompleteDeviceUpdate()));
	}};
	

	private DfuStateType currentState;
	private DfuStateType pendingState;
	private DfuTransitionAction transitionAction;
	
	public DfuStateTransitionTable(){
		currentState = DfuStateType.NULL;
		pendingState = DfuStateType.NULL;
		transitionAction = null;
	}
	
	public boolean getStateTransition(DfuCommandType command)
	{
		boolean validTransition = false;
		
		pendingState = DfuStateType.NULL;
		
		for(DfuState state : transitionTable){
			if(state.getCommand().equals(command) &&
					state.getCurrentState().equals(currentState) )
			{
				this.pendingState = state.getNextState();
				this.transitionAction = state.getAction();
				validTransition = true;
				break;
			}
		}
		
		return validTransition;
	}
	
	public void updateNextState(){
		this.currentState = this.pendingState;
	}

	public DfuStateType getCurrentState() {
		return currentState;
	}

	public void setCurrentState(DfuStateType currentState) {
		this.currentState = currentState;
	}

	public DfuTransitionAction getTransitionAction() {
		return transitionAction;
	}
	
	
}
