package com.dfu.downloader.statemachine.action;

import com.dfu.downloader.statemachine.DfuCommonData;

public interface DfuTransitionAction {

	boolean doAction(DfuCommonData data);
}
