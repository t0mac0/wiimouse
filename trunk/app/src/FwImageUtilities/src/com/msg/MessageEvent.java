package com.msg;

import java.util.EventObject;


public class MessageEvent extends EventObject {

	private static final long serialVersionUID = 1L;
	

	public enum Severity {
		INFO ("Info"),
		ERROR ("Error"),
		DEBUG ("Debug");
		
		private String description;
		
		private Severity(String desc)
		{
			this.description = desc;
		}
		
		public String getDescription(){
			return this.description;
		}
	}
	
	private String message;
	private Severity severity;
	
	public MessageEvent(Object source, Severity severity, String message) {
		super(source);

		this.message = message;
		this.severity = severity;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public Severity getSeverity() {
		return severity;
	}

	public void setSeverity(Severity severity) {
		this.severity = severity;
	}
	
	

}
