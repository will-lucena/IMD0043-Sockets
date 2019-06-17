package Utils;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.net.Socket;
import java.util.Scanner;

public class Client {
  private Socket socket;
  private OutputStream ou;
  private Writer ouw;
  private BufferedWriter bfw;

  public Client(String target, String port) throws IOException {
    conectar(target, port);
  }

  public Client() throws IOException {
    conectar("localhost", "6066");
  }

  public void conectar(String ip, String port) throws IOException {

    socket = new Socket(ip, Integer.parseInt(port));
    ou = socket.getOutputStream();
    ouw = new OutputStreamWriter(ou);
    bfw = new BufferedWriter(ouw);
    bfw.flush();
  }

  public void enviarMensagem(String msg) throws IOException {

    if (msg.equals("Sair")) {
      bfw.write("Desconectado \r\n");
    } else {
      bfw.write(msg + "\r\n");
    }
    bfw.flush();
  }

  public void escutar() throws IOException {

    InputStream in = socket.getInputStream();
    Reader inr = new InputStreamReader(in);
    BufferedReader bfr = new BufferedReader(inr);
    String msg = "";

    while (!"Sair".equalsIgnoreCase(msg))

      if (bfr.ready()) {
        msg = bfr.readLine();
      }
  }

  public void sair() throws IOException {

    enviarMensagem("Sair");
    bfw.close();
    ouw.close();
    ou.close();
    socket.close();
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    try {
      Client client = new Client(args[0], args[1]);

      while (true) {
        String input = scanner.nextLine();
        client.enviarMensagem(input);
        client.escutar();
      }

    } catch (IOException e) {
      scanner.close();
      e.printStackTrace();
    } finally {
      scanner.close();
    }
  }
}