/*
	 Read input form command line
	 Send it to server
	 Wait for response
*/
import java.io.*;
import java.net.*;

public class EchoClient
{
	public static void main(String[] args)
	{
		try
		{
			Socket sock = new Socket("localhost", 6013);
			PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);

			InputStream in = sock.getInputStream();
			BufferedReader bin = new BufferedReader(new InputStreamReader(in));
			while(true)
			{
				String input = System.console().readLine();
				pout.println(input);

				String line = bin.readLine();
				if(line == null)
				{
					break;
				}
				System.out.println(line);

				/* close the socket connection */
			}
			sock.close();
		}
		catch(Exception e) {}
	}
}
