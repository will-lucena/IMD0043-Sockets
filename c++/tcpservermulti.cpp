#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <iostream>
#include <cstdlib>
#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 100
using namespace std;
int main(int argc, char *argv[])
{
  int sd, rc, n, newsockfd;
  socklen_t cliLen;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];

  /* 1. CRIA O SOCKET */
  // socket(int domain, int type, int protocol)
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd < 0)
  {
    cout << argv[0] << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }


  // limpar estrutura de endereço
  bzero((char *) &servAddr, sizeof(servAddr));

  /* 2. FAZ A LIGACAO (BIND) DE TODOS OS ENDERECOS COM A PORTA */
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind(sd, (struct sockaddr *)&servAddr, sizeof(servAddr));
  if (rc < 0)
  {
    cout << argv[0] << ": nao foi possivel associar a porta"
         << LOCAL_SERVER_PORT << endl;
    exit(1);
  }
  cout << argv[0] << ": aguardando por dados na porta TCP("
       << LOCAL_SERVER_PORT << ")" << endl;

  listen(sd,5);

  cliLen = sizeof(cliAddr);

  newsockfd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
  if (newsockfd < 0){
    cout << argv[0] << ": ERRO no accept" << endl;
    exit(1);
  }
  
  cout << "Servidor: conectado de" << inet_ntoa(cliAddr.sin_addr) << "porta " << ntohs(cliAddr.sin_port) << endl;

  // This send() function sends the 13 bytes of the string to the new socket
  send(newsockfd, "Hello, world!\n", 13, 0);

  bzero(msg,MAX_MSG);

  n = read(newsockfd,msg,MAX_MSG-1);
     if (n < 0){
      cout << argv[0] << ": ERRO na leitura de socket" << endl;
      exit(1);
     }
      
     cout << "Here is the message:" << msg << endl;

     close(newsockfd);
     close(sd);
     return 0; 



  // /* 3. LOOP INFINITO PARA LEITURA (LISTEN) */
  // while (1)
  // {
  //   /* INICIA O BUFFER DE COMUNICACAO */
  //   memset(msg, 0x0, MAX_MSG);
  //   /* RECEBE MENSAGEM */
  //   cliLen = sizeof(cliAddr);
  //   n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *)&cliAddr, &cliLen);
  //   if (n < 0)
  //   {
  //     cout << argv[0] << ": nao foi possivel receber dados" << endl;
  //     continue;
  //   }
  //   /* IMPRIME A MENSAGEM RECEBIDA */
  //   cout << argv[0] << ": de " << inet_ntoa(cliAddr.sin_addr) << ":UDP(" << ntohs(cliAddr.sin_port) << ") : " << msg << endl;
  // } /* FIM DO LOOP INFINITO */
  // return 0;
}