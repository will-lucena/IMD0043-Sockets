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
#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 256
using namespace std;
int main(int argc, char *argv[])
{
  int sockfd, rc, i, cn, n;
  struct sockaddr_in cliAddr, remoteServAddr;
  struct hostent * h;
  char msgReceived[MAX_MSG];
  string msgToSent;


  /* VERIFICA OS ARGUMENTOS PASSADOS POR LINHA DE COMANDO */
  if (argc < 3)
  {
    cout << "Uso : " << argv[0]
    << " <servidor> <mensagem1> ... <mensagemN>" << endl;
    exit(1);
  }

  /* 1. CRIA O SOCKET */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    cout << argv[0] << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }

  /* OBTEM O ENDERECO IP e PESQUISA O NOME NO DNS */
  h = gethostbyname(argv[1]);
  if (h == NULL) {
    cout << argv[0] << ": host desconhecido " << argv[1] << endl;
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


  cn = connect(sockfd, (struct sockaddr *)&remoteServAddr, sizeof(remoteServAddr));
  if(cn<0){
    cout << argv[0] << ": falha de conexão com a porta ou problema de ip" << endl;
    exit(1);
  }

  //Cliente enviando mensagem até que digite sair
 // while (1) {

    for (i = 2; i < argc; i++)
    {

      if (!strcmp(argv[i], "sair")){
        cout << "Igual" << endl;
        close(sockfd);
        exit(0);
      }

      msgToSent += argv[i];
      msgToSent += " ";


    }

    n = write(sockfd, msgToSent.c_str(), strlen(msgToSent.c_str()) + 1);
      if (n < 0)
      {
        cout << argv[0] << ": erro na escrita para socket - " << msgToSent << endl;
        close(sockfd);
        exit(1);
      }

    memset(msgReceived, '0' ,sizeof(msgReceived));

    n = read(sockfd, msgReceived, MAX_MSG-1);
    if (n < 0)
    {
      cout << argv[0] << ": erro na leitura do socket" << endl;
      close(sockfd);
      exit(1);
    }

    cout << argv[0] << ": Mensagem do servidor -> " << msgReceived << endl;


 // }
  
  
  close(sockfd);
  
  return 0;
}