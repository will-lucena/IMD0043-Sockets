package Application;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class Server {
  public static void main(String[] args) throws IOException {
    if (args.length < 1) {
      throw new IOException("invalid port");
    }

    ServerSocket server = new ServerSocket(Integer.parseInt(args[0]));
    System.out.println("Server running on port " + args[0]);

    Socket client = server.accept();
    System.out.println("new connection with " + client.getInetAddress().getHostAddress());

    LocalDateTime now = LocalDateTime.now();

    Scanner scanner = new Scanner(client.getInputStream());
    while (scanner.hasNextLine()) {
      String input = scanner.nextLine();
      if (verifyQuit(input)) {
        closeConnection(scanner, server, client);
      } else {
        System.out.println(createMessage(input, now));
      }
    }
  }

  private static void closeConnection(Scanner scanner, ServerSocket server, Socket client) throws IOException {
    scanner.close();
    server.close();
    client.close();
  }

  private static boolean verifyQuit(String content) {
    return content.contains("sair");
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