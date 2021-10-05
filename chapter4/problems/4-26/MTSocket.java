/*
	 Server socket listens at 6013 port.
	 Now, when a new connection occur I'm going to
	 create a new thread and handle request there.

	 wait_for_request loop
	 if request
	 create thread
	 client_socket -> thread

	 Concurrent Task:
thread: handle_request -> close_socket
 */
import java.net.*;
import java.io.*;
import java.util.concurrent.*;

class Request implements Runnable
{
	private Socket client;
	public Request(Socket client)
	{
		this.client = client;
	}

	/* The thread will execute in this method */
	public void run()
	{
		try
		{
			PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
			/* write the Date to the socket */
			pout.println(new java.util.Date().toString());
			/* close socket */
			client.close();
		}
		catch(Exception e) {}
	}
}

public class MTSocket
{
	public static void main(String[] args)
	{
		try
		{
			ServerSocket sock = new ServerSocket(6013);
			/* now listen for connections */
			while (true)
			{
				Socket client = sock.accept();
				Thread req = new Thread(new Request(client));
				req.start();
			}
		}
		catch(Exception e) {}
	}
}
