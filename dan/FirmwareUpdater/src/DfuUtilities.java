
public class DfuUtilities {

	static boolean intToByteArray(int integer, byte[] array, int offset)
	{
		if(array.length < offset+4)
		{
			return false;
		}

		array[offset+3] = (byte)(integer >> 24);
		array[offset+2] = (byte)(integer >> 16);
		array[offset+1] = (byte)(integer >> 8);
		array[offset+0] = (byte)(integer >> 0);
		return true;
	}

	static int byteArrayToInt( byte[] array, int offset)
	{
		int val = 0;

		if(array.length < offset+4)
		{
			return 0;
		}

		val =  (int) (((int)array[offset+3]) << 24);
		val |= (int) (((int)array[offset+2]) << 16);
		val |= (int) (((int)array[offset+1]) << 8);
		val |= (int) (((int)array[offset+0]) << 0);

		return val;
	}
	
	static short byteArrayToShort( byte[] array, int offset)
	{
		short val;

		if(array.length < offset+2)
		{
			return 0;
		}

		val =  (short) (((short)array[offset+1]) << 8);
		val |= (short) (((short)array[offset+0]) << 0);
		
		return val;
	}
}
