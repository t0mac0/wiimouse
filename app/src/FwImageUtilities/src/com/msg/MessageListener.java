package com.msg;

import java.util.EventListener;

public interface MessageListener extends EventListener {

	public void messageReceived(MessageEvent evnt);

}
