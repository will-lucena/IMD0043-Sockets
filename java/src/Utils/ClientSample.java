package Utils;

//File Name GreetingClient.java
import java.net.*;
import java.util.Scanner;
import java.io.*;

public class ClientSample {

	public static void main(String[] args) {
		String serverName = args[0];
		String message = "Hello from ";
		if (args[2].length() > 0) {
			message = args[2];
		}
		int port = Integer.parseInt(args[1]);
		try {
			System.out.println("Connecting to " + serverName + " on port " + port);
			Socket client = new Socket(serverName, port);

			System.out.println("Just connected to " + client.getRemoteSocketAddress());
			OutputStream outToServer = client.getOutputStream();
			DataOutputStream out = new DataOutputStream(outToServer);
			Scanner scanner = new Scanner(System.in);
			out.writeUTF(message);
			InputStream inFromServer = client.getInputStream();
			DataInputStream in = new DataInputStream(inFromServer);
			System.out.println("Server says " + in.readUTF());

			while (true) {
				out.writeUTF(scanner.nextLine());
				inFromServer = client.getInputStream();
				in = new DataInputStream(inFromServer);
				System.out.println("Server says " + in.readUTF());
				if (in.readUTF().contains("sair")) {
					break;
				}
			}
			client.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
