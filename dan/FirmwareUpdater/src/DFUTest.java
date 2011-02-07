
public class DFUTest {

	private SerialComm comm;
	private DfuCommand command;
	private DfuResponse response;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		DFUTest test = new DFUTest();
	}

	public DFUTest()
	{
		comm = new SerialComm();
		command = new DfuCommand();
		response = new DfuResponse();

		int i;
		String port;

		for(i = 1; i < 10; i++)
		{
			port = "Com"+i;

			if( comm.OpenPort(port) )
			{
				System.out.printf(port + " opened\n");

				if(!QueryDevice(port)){

				}
				else if(!ValidateDeviceParameters(0xF46D, 0xF52B, 0xF000, 0x0001))
				{

				}
				else if(!InitializeDeviceUpdate(port))
				{

				}
				comm.ClosePort(port);
			}

		}

	}
	
	

	public boolean QueryDevice(String port)
	{
		boolean result = true;


		command.setCommand(0);


		if(!comm.Send(port, command.toByteArray()))
		{
			System.out.println("Failed to send query device command\n");
			result = false;
		}
		else if(!comm.Receive(port, response.getBuffer()))
		{
			System.out.println("Failed to receive query device result\n");
			result = false;
		}
		else if( response.getStatus() != 0 )
		{
			System.out.printf("Bad device status: %d\n", response.getStatus());
			result = false;
		}

		return result;
	}

	private boolean ValidateDeviceParameters(int Pid, int Vid, int Did, int FwVersion)
	{
		if( Pid == response.getProductId() &&
				Vid == response.getVendorId() &&
				Did == response.getDeviceId() &&
				FwVersion > response.getFWVersion())
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	private boolean InitializeDeviceUpdate(String port)
	{
		boolean result = true;

		command.setCommand(1);

		if(!comm.Send(port, command.toByteArray()))
		{
			System.out.println("Failed to send query device command\n");
			result = false;
		}
		else if(!comm.Receive(port, response.getBuffer()))
		{
			System.out.println("Failed to receive result\n");
			result = false;
		}
		else if( response.getStatus() != 0 )
		{
			System.out.printf("Bad device status: %d\n", response.getStatus());
			result = false;
		}

		return result;
	}
}

