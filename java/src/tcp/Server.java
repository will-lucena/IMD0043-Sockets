package tcp;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;

public class Server extends ServerSocket {

	public Server() throws IOException {
		super();
	}
	
	public Server(int port, int backlog, InetAddress address) throws IOException {
		super(port, backlog, address);
	}
	
	public Server(int port, int backlog) throws IOException{
		super(port, backlog);
	}
	
	public Server(int port) throws IOException{
		super(port);
	}
}
