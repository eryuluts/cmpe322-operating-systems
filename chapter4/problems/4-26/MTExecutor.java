/*
	 Server socket listens at 6013 port.
	 Now, when a new connection occur I'm going to
	 create a new thread and handle request there.

	 wait_for_request loop
	 if request
	 create thread
	 client_socket -> thread

	 Concurrent Task: handle_request -> close_socket

	 This version uses executor interface.
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
			byte[] buffer = new byte[128];
			InputStream in = client.getInputStream();
			OutputStream out = client.getOutputStream();
			while(true)
			{
				int result = in.read(buffer);
				if(result == -1)
				{
					break;
				}

				out.write(buffer, 0, result);
			}

			/* close socket */
			client.close();
		}
		catch(Exception e) {}
	}
}

public class MTExecutor
{
	public static void main(String[] args)
	{
		try
		{
			ServerSocket sock = new ServerSocket(6013);
			ExecutorService service = Executors.newCachedThreadPool();
			/* now listen for connections */
			while (true)
			{
				Socket client = sock.accept();
				service.execute(new Request(client));
			}
		}
		catch(Exception e) {}
	}
}
