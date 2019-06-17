package Application;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
  public static void main(String[] args) throws UnknownHostException, IOException {

    if (args.length < 2) {
      throw new IOException("Unsuficient parameters");
    }

    Socket client = new Socket(args[0], Integer.parseInt(args[1]));
    System.out.println("Connected successful on " + args[0] + ":" + args[1]);

    Scanner scanner = new Scanner(System.in);
    PrintStream printStream = new PrintStream(client.getOutputStream());

    while (scanner.hasNextLine()) {
      printStream.println(scanner.nextLine());
      scanner.close();
    }
    closeConnection(printStream, scanner, client);
  }

  private static void closeConnection(PrintStream printStream, Scanner scanner, Socket client) throws IOException {
    printStream.close();
    client.close();
  }
}