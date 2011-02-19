package com.msg;

import javax.swing.event.EventListenerList;

public class MessageGenerator {

	protected EventListenerList listenerList;
	
	public MessageGenerator() {
		listenerList = new EventListenerList();
	}

	public void addMessageListener(MessageListener listener)
	{
		listenerList.add(MessageListener.class, listener);
	}
	
	public void removeMessageListener(MessageListener listener)
	{
		listenerList.remove(MessageListener.class, listener);
	}
	
	public void sendMessage(MessageEvent evnt)
	{
		Object[] listeners = listenerList.getListenerList();
		
		for(int i = 0; i < listeners.length; i+=2)
		{
			if(listeners[i] == MessageListener.class)
			{
				((MessageListener)listeners[i+1]).messageReceived(evnt);
			}
		}
	}
	
	public void addError(Object src, String err)
	{
		sendMessage(new MessageEvent(src, MessageEvent.Severity.INFO, err));
	}
	
	public void addInfo(Object src, String msg)
	{
		sendMessage(new MessageEvent(src, MessageEvent.Severity.INFO, msg));
	}
}
