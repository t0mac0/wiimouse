package com.util;

import java.nio.ByteBuffer;

public class ConversionUtil {

	public static int align(int unaligned, int boundary)
	{
		return boundary * ((unaligned + boundary - 1) / boundary);
	}
	public static byte[] intToByteArray(int integer) throws NumberFormatException
	{
		byte[] bytes = ByteBuffer.allocate(4).putInt(integer).array();

		return bytes;
	}
	
	public static byte[] shortToByteArray(short shrt) throws NumberFormatException
	{
		byte[] bytes = ByteBuffer.allocate(2).putShort(shrt).array();

		return bytes;
	}

	public static byte[] hexToByteArray(String integerString) throws NumberFormatException
	{
		int integer = Integer.parseInt(integerString,16);

		byte[] bytes = intToByteArray(integer);

		return bytes;
	}

	public static int byteArrayToInt(byte[] bytes) throws NumberFormatException
	{

		if(bytes.length < 4)
		{
			return 0;
		}

		return(bytes[0] << 24)
		+ ((bytes[1] & 0xFF) << 16)
		+ ((bytes[2] & 0xFF) << 8)
		+ (bytes[3] & 0xFF);


	}

	public static String byteArrayToHex(byte[] bytes) throws NumberFormatException
	{
		int val = 0;

		if(bytes.length < 4)
		{
			return "";
		}

		val = byteArrayToInt(bytes);

		return Integer.toHexString(val);
	}

	public static boolean byteToByteArray(byte[] array, int offset, int val)
	{
		if(offset > array.length - 1 )
			return false;
		array[offset+0] = (byte)val; 

		return true;
	}

	public static boolean shortToByteArray(byte[] array, int offset, int val)
	{
		if(offset > array.length - 2 )
			return false;

		byte[] bytes = intToByteArray(val);

		for(int i = 0; i < 2; i++){
			array[offset+i] = bytes[i];
		}

		return true;
	}

	public static boolean intToByteArray(byte[] array, int offset, int val)
	{
		if(offset > array.length - 4 )
			return false;

		byte[] bytes = intToByteArray(val);

		for(int i = 0; i < 4; i++){
			array[offset+i] = bytes[i];
		}

		return true;
	}

	public static boolean intToByteArrayBE(byte[] array, int offset, int val)
	{
		if(offset > array.length - 4 )
			return false;

		byte[] bytes = intToByteArray(val);

		for(int i = 0; i < 4; i++){
			array[offset+3-i] = bytes[i];
		}

		return true;
	}

	public static int byteArrayToByte(byte[] array, int offset){
		if( offset > array.length -1)
			return 0;

		return (int)array[offset];
	}

	public static int byteArrayToShortBE(byte[] bytes, int offset){
		if( offset > bytes.length -2)
			return 0;

		return ((bytes[offset+1] & 0xFF) << 8)
		+ (bytes[offset+0] & 0xFF);


	}

	public static int byteArrayToShort(byte[] bytes, int offset){
		if( offset > bytes.length -2)
			return 0;

		return ((bytes[offset+0] & 0xFF) << 8)
		+ (bytes[offset+1] & 0xFF);


	}

	public static int byteArrayToIntBE(byte[] bytes, int offset){
		if( offset > bytes.length -4)
			return 0;

		return (bytes[offset+3] << 24)
		+ ((bytes[offset+2] & 0xFF) << 16)
		+ ((bytes[offset+1] & 0xFF) << 8)
		+ (bytes[offset+0] & 0xFF);
	}
	
	public static int byteArrayToInt(byte[] bytes, int offset){
		if( offset > bytes.length -4)
			return 0;

		return (bytes[offset+0] << 24)
		+ ((bytes[offset+1] & 0xFF) << 16)
		+ ((bytes[offset+2] & 0xFF) << 8)
		+ (bytes[offset+3] & 0xFF);
	}
}
