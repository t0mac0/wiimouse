

public class DfuCommand {
	private byte Command;
	private byte SubCommand;
	private int Offset;
	private int StartAddress;
	private int SectionsCount;
	private int Length;
	
	public byte[] toByteArray()
	{
		byte buffer[] = new byte[64];
		
		buffer[0] = this.Command;
		buffer[1] = this.SubCommand;
		DfuUtilities.intToByteArray(this.Offset, buffer, 2);
		DfuUtilities.intToByteArray(this.StartAddress, buffer, 6);
		DfuUtilities.intToByteArray(this.SectionsCount, buffer, 10);
		DfuUtilities.intToByteArray(this.Length, buffer, 14);
		
		return buffer;
	}
	
	
	public byte getCommand() {
		return Command;
	}
	public void setCommand(int command) {
		Command = (byte)command;
	}
	public byte getSubCommand() {
		return SubCommand;
	}
	public void setSubCommand(int subCommand) {
		SubCommand = (byte)subCommand;
	}
	public int getOffset() {
		return Offset;
	}
	public void setOffset(int offset) {
		Offset = offset;
	}
	public int getStartAddress() {
		return StartAddress;
	}
	public void setStartAddress(int startAddress) {
		StartAddress = startAddress;
	}
	public int getSectionsCount() {
		return SectionsCount;
	}
	public void setSectionsCount(int sectionsCount) {
		SectionsCount = sectionsCount;
	}
	public int getLength() {
		return Length;
	}
	public void setLength(int length) {
		Length = length;
	}
	
}
