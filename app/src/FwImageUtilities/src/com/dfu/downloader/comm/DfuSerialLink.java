package com.dfu.downloader.comm;

import com.dfu.downloader.transfer.DfuCommand;
import com.dfu.downloader.transfer.DfuResponse;



public class DfuSerialLink {
	public static final int MAX_COM_NUMBER = 15;

	private SerialNative com;
	private String port;
	private boolean connected;
	
	public DfuSerialLink() {
		com = new SerialNative();
		port = "";
		connected = false;
		
	}
	
	public boolean openLink(int comPortNumber){
		String port = "com"+comPortNumber;
		
		if(isOpened() && !closeLink()){

		}
		else if( com.OpenPort(port)){
			this.port = port;
			this.connected = true;
		}
		
		return connected;
	}
	
	public boolean closeLink()
	{
		com.ClosePort(port);
		connected = false;
		
		return true;
	}
	public boolean sendCommand(DfuCommand command)
	{
		boolean result = false;
		
		command.objectToPacket();
		
		if(isOpened() && com.Send(port, command.getPacketBuffer(), DfuCommand.COMMAND_SIZE))
		{
			result = true;
		}
		
		return result;
	}
	
	public boolean sendData(byte[] data, int size)
	{
		boolean result = false;
		
		
		if(isOpened() && com.Send(port, data, size))
		{
			result = true;
		}
		
		return result;
	}
	
	
	public boolean receiveResponse(DfuResponse response)
	{
		boolean result = false;
		
		if(isOpened() && com.Receive(port, response.getPacketBuffer(), DfuResponse.RESPONSE_SIZE))
		{
			response.packetToObject();
			result = true;
		}
		
		return result;
	}
	
	public boolean receiveData(byte[] data, int size)
	{
		boolean result = false;
		
		if(isOpened() && com.Receive(port, data, size))
		{
			result = true;
		}
		
		return result;
	}
	
	public boolean sendCommand(DfuCommand command, DfuResponse response){
		boolean result = false;
		
		if( sendCommand(command) &&
				receiveResponse(response)){
			result = true;
		}
		return result;
	}
	
	public boolean sendData(byte[] data, int size, DfuResponse response){
		boolean result = false;
		
		if( sendData(data, size) &&
				receiveResponse(response)){
			result = true;
		}
		return result;
	}
	
	public boolean receiveData(DfuCommand command, byte[] data, int size)
	{
		boolean result = false;
		
		if(isOpened() && sendCommand(command) && receiveData(data, size))
		{
			result = true;
		}
		
		return result;
	}
	
	public boolean isOpened(){
		return connected;
	}
	

}
