package Application;

import java.io.IOException;

import Utils.ServerSample;

public class Application {

	public static void main(String[] args) {
		int port = Integer.parseInt(args[0]);
		try {
			Thread t = new ServerSample(port);
			t.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
