package com.dfu.downloader.comm;

import java.net.URL;
import java.util.HashMap;

import com.sun.jna.Library;
import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Platform;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;

public class SerialNative {

	static class SerialCommSettings extends Structure {
		public int Baud;
		public byte ByteSize;
		public byte Parity;
		public byte StopBits;
		public int AbortOnError;
		public int InputBufferSize;
		public int OutputBufferSize;
		public int ReadIntervalTimeout;
		public int ReadTotalTimeoutConstant;
		public int ReadTotalTimeoutMultiplier;
		public int WriteTotalTimeoutConstant;
		public int WriteTotalTimeoutMulitplier;
	}

	private static HashMap<String, Pointer> SerialComPortHandles;
	private static SerialCommJNA SerialCommLink;

	public interface SerialCommJNA extends Library {
		public Pointer serial_comm_open(String port, boolean use_default_settings );

		public boolean serial_comm_set_settings(Pointer handle, SerialCommSettings settings);

		public int serial_comm_send(Pointer handle, Pointer buffer, int size);

		public int serial_comm_receive(Pointer handle, Pointer buffer, int size);

		public boolean serial_comm_close(Pointer handle);
		
		SerialCommJNA INSTANCE = (SerialCommJNA) Native.loadLibrary( "serial_comm64", SerialCommJNA.class);
	}
	
	public SerialNative() {
		setLibraryPath();
		SerialComPortHandles = new HashMap<String, Pointer>();

		SerialCommLink = SerialCommJNA.INSTANCE;
	}

	public boolean OpenPort(String Port)
	{
		boolean result = false;
		Pointer handle;

		handle = new Memory(8);

		handle = SerialCommLink.serial_comm_open(Port,  true);
		
		if(handle != null)
		{
			result = true;
			SerialComPortHandles.put(Port, handle);
		}
		
		return result;

	}

	public boolean Send(String Port, byte Data[], int size)
	{
		boolean result = false;
		Pointer handle = null;
		Pointer buffer;

		handle = SerialComPortHandles.get(Port);

		if( handle == null )
			return false;
		else if( Data.length < size)
			return false;

		buffer = new Memory(size);

		buffer.write(0, Data, 0,size);

		if( SerialCommLink.serial_comm_send(handle, buffer, size) > 0)
		{
			result = true;
		}

		return result;
	}

	public boolean Receive(String Port, byte Data[], int size)
	{
		boolean result = false;
		Pointer handle = null;
		Pointer buffer;

		handle = SerialComPortHandles.get(Port);

		if( handle == null )
			return false;
		else if( Data.length < size)
			return false;

		buffer = new Memory(size);

		if( SerialCommLink.serial_comm_receive(handle, buffer, size) > 0)
		{
			result = true;
			buffer.read(0, Data, 0, size);
		}

		return result;
	}

	public boolean ClosePort(String Port)
	{
		boolean result = false;
		Pointer handle = null;

		handle = SerialComPortHandles.get(Port);

		if( (handle != null) && SerialCommLink.serial_comm_close(handle) )
		{
			result = true;
			SerialComPortHandles.remove(Port);
		}

		return result;

	}
	
	private void setLibraryPath()
	{
		if( Platform.isWindows() )
		{
			String path;
			URL library = this.getClass().getResource("/serial_comm64.dll");
			
			path = library.getPath().replaceFirst("/","");
			
			path = path.substring(0, path.lastIndexOf("/"));
			System.out.println(path);
			System.setProperty("jna.library.path", path);
		}
	}

}
