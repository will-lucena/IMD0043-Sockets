#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>   /* memset() */
#include <sys/time.h> /* select() */
#include <iostream>
#include <cstdlib>
#include <thread>


#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 256
#define MAX_CON 5


using namespace std;


int main(int argc, char *argv[])
{
  int clientSocket, rc, cn, n;
  struct sockaddr_in remoteServAddr;
  struct hostent * h;
  string msgToSend;
  char msgReceived[MAX_MSG];
  socklen_t addr_size;

  /* VERIFICA OS ARGUMENTOS PASSADOS POR LINHA DE COMANDO */
  if (argc < 2)
  {
    cout << "Uso : " << argv[0]
         << " <servidor> " << endl;
    exit(1);
  }

  /* 1. CRIA O SOCKET */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0)
  {
    cout << argv[0] << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }

  /* OBTEM O ENDERECO IP e PESQUISA O NOME NO DNS */
  h = gethostbyname(argv[1]);
  if (h == NULL) {
    cout << argv[0] <<  ": host desconhecido " << argv[1] << endl;
    exit(1);
  }
  cout << argv[0] << ": enviando dados para " << h->h_name
  << " (IP : " << inet_ntoa(*(struct in_addr *)h->h_addr_list[0])
  << ")" << endl;

  /* CONFIGURANDO ESTRUTURA REFERENTE AO HOST REMOTO (SERVIDOR) */
  //memset(remoteServAddr, '0' ,sizeof(remoteServAddr));
  remoteServAddr.sin_family = h->h_addrtype;
  memcpy((char *)&remoteServAddr.sin_addr.s_addr,
   h->h_addr_list[0], h->h_length);
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);


  memset(remoteServAddr.sin_zero, '\0', sizeof remoteServAddr.sin_zero);
  //Connect the socket to the server using the address
  addr_size = sizeof remoteServAddr;

  cn = connect(clientSocket, (struct sockaddr *)&remoteServAddr, addr_size);
  if(cn<0){
    cout << argv[0] << ": falha de conexão com a porta ou problema de ip" << endl;
    exit(1);
  }

  string sair = "sair";

  while(1) {

    cout << "Digite a mensagem:" << endl;
    getline(cin,msgToSend);

    //const std::string lower_str = boost::algorithm::to_lower_copy(msgToSend);

    if (msgToSend == sair){
      cout << "Encerrando conexão." << endl;
      close(clientSocket);
      break;
    }


    // msgToSend = "Hello, I am thread number " + to_string(nThread);
    n = write(clientSocket, msgToSend.c_str() , strlen(msgToSend.c_str()) + 1);

    if( n < 0)
    {
      cout << argv[0] << ": Falha no envio da mensagem." << endl;
      close(clientSocket);
      exit(1);
    }

    //Ler a mensagem do servidor
     memset(msgReceived, '0' ,sizeof(msgReceived));

    n = read(clientSocket, msgReceived, MAX_MSG-1);
    if (n < 0)
    {
      cout << argv[0] << ": Recebimento falhou." << endl;
      close(clientSocket);
      exit(1);
    }

    cout << argv[0] << ": Do servidor -> " << msgReceived << endl;

  }

  close(clientSocket);
  
  return 0;
}