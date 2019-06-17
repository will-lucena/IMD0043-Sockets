package Utils;

//File Name GreetingServer.java
import java.net.*;
import java.time.LocalTime;
import java.io.*;

public class ServerSample extends Thread {
	private ServerSocket serverSocket;

	public ServerSample(int port) throws IOException {
		serverSocket = new ServerSocket(port);
		serverSocket.setSoTimeout(10000);
	}

	public void run() {
		LocalTime current;
		while (true) {
			try {
				current = LocalTime.now();
				System.out.println("Waiting for client on port " + serverSocket.getLocalPort() + "...");
				Socket server = serverSocket.accept();

				System.out.println("Just connected to " + server.getRemoteSocketAddress());
				DataInputStream in = new DataInputStream(server.getInputStream());
				System.out.println(in.readUTF());
				System.out.println("Mensagem `" + in.readUTF() + "` recebida as " + current.toString());
				DataOutputStream out = new DataOutputStream(server.getOutputStream());
				
				out.writeUTF("Mensagem `" + in.readUTF() + "` recebida as " + current.toString());
				server.close();
			} catch (SocketTimeoutException s) {
				System.out.println("Socket timed out!");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
