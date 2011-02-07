

public class DfuResponse {
	private byte Status;
	private byte Command;
	private short VendorId;
	private short ProductId;
	private short DeviceId;
	private short FWVersion;
	private int HashSum;
	private int Length;

	private byte buffer[];

	private boolean bufferUpdated;

	public DfuResponse()
	{
		bufferUpdated = false;
		buffer = new byte[64];
	}

	public byte[] getBuffer()
	{
		bufferUpdated = false;
		return buffer;
	}

	private void updateBufferDataMembers()
	{
		this.Status = this.buffer[0];
		this.Command = this.buffer[1];
		this.VendorId = DfuUtilities.byteArrayToShort(this.buffer, 2);
		this.ProductId = DfuUtilities.byteArrayToShort(this.buffer, 4);
		this.DeviceId = DfuUtilities.byteArrayToShort(this.buffer, 6);
		this.FWVersion = DfuUtilities.byteArrayToShort(this.buffer, 8);
		this.HashSum = DfuUtilities.byteArrayToInt(this.buffer, 10);
		this.Length = DfuUtilities.byteArrayToInt(this.buffer, 14);

		bufferUpdated = true;
	}

	public int getStatus() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return Status;
	}

	public byte getCommand() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return Command;
	}

	public short getVendorId() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return VendorId;
	}

	public short getProductId() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return ProductId;
	}

	public short getDeviceId() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return DeviceId;
	}

	public short getFWVersion() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return FWVersion;
	}

	public int getHashSum() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return HashSum;
	}

	public int getLength() {
		if(!bufferUpdated)
		{
			updateBufferDataMembers();
		}
		return Length;
	}


}
