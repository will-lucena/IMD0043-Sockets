package Application;

import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Server {

  private int port;
  private Map<Socket, PrintStream> clients;

  public Server(Integer port) {
    this.port = port;
    clients = new HashMap<Socket, PrintStream>();
  }

  public void run() throws IOException {
    ServerSocket server = new ServerSocket(this.port);
    System.out.println("Server running on port " + this.port);

    while (true) {
      Socket client = server.accept();
      System.out.println("New connection with " + client.getInetAddress().getHostAddress());

      PrintStream printStream = new PrintStream(client.getOutputStream());

      if (this.clients.containsKey(client)) {
        this.clients.replace(client, printStream);
      } else {
        this.clients.put(client, printStream);
      }

      ClientHandler handler = new ClientHandler(client, this);
      new Thread(handler).start();
    }
  }

  public void dispatchMessage(String msg, Socket senderClient) throws IOException {
    LocalDateTime now = LocalDateTime.now();
    for (Map.Entry<Socket, PrintStream> entry : this.clients.entrySet()) {
      if (entry.getKey() != senderClient) {
        entry.getValue().println(createMessage(msg, now));
      }
    }
  }

  public static void main(String[] args) throws IOException {
    if (args.length < 1) {
      throw new IOException("invalid port");
    }

    new Server(Integer.parseInt(args[0])).run();
  }

  public void closeConnection(Socket client) throws IOException {
    System.out.println(client.getInetAddress() + " disconnected from the server");
    client.close();
  }

  private static String createMessage(String message, LocalDateTime now) {
    StringBuilder sb = new StringBuilder();

    sb.append("Mensagem ");
    sb.append(message);
    sb.append(" recebida as ");
    sb.append(formatTime(now).replace(':', 'h'));

    return sb.toString();
  }

  private static String formatTime(LocalDateTime time) {
    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm");

    String formatDateTime = time.format(formatter);
    return formatDateTime;
  }
}