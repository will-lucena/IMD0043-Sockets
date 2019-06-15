#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime> /*hora */
#include <chrono>

#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 256

using namespace std;




int main(int argc, char *argv[])
{
  int sockfd, newsockfd;
  int rc, n;
  socklen_t cliLen;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];
  char buffer[MAX_MSG];


  /* 1. CRIA O SOCKET */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    cout << argv[0] << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }


  /* 2. FAZ A LIGACAO (BIND) DE TODOS OS ENDERECOS COM A PORTA */
  memset(&servAddr, '0', sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
  if (rc < 0)
  {
    cout << argv[0] << ": nao foi possivel associar a porta"
         << LOCAL_SERVER_PORT << endl;
    exit(1);
  }

  /* 3. OUVINDO CONEXÕES*/
  cout << argv[0] << ": aguardando por dados na porta TCP("
       << LOCAL_SERVER_PORT << ")" << endl;
  listen(sockfd , 20);
 
  cliLen = sizeof(cliAddr);

  /* 4. ACCEPT*/
  newsockfd = accept(sockfd, (struct sockaddr *) &cliAddr, &cliLen);
  if (newsockfd < 0)
  {
    cout << argv[0] << ": erro no accept"
         << LOCAL_SERVER_PORT << endl;
    exit(1);
  }
  cout << argv[0] << "servidor: estou conectado com " << inet_ntoa(cliAddr.sin_addr) << " na porta "
       << ntohs(cliAddr.sin_port) << endl;


  /* 5. RECEBENDO MENSAGEM DO CLIENTE*/
  memset(&msg, '0', sizeof(msg));
  n = read(newsockfd,msg,MAX_MSG-1);
  if (n < 0)
  {
    cout << argv[0] << ": erro na leitura do de socket"
         << LOCAL_SERVER_PORT << endl;
    exit(1);
  } 

  //Hora
  std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
  time_t tt;
  tt = std::chrono::system_clock::to_time_t ( today );

  cout << argv[0] << ": Mensagem de " << inet_ntoa(cliAddr.sin_addr) << ":TCP(" << ntohs(cliAddr.sin_port) <<
                       ") ->  " << msg << " - recebida em " <<  ctime(&tt) << " (hora local)" << endl;

  /* 6. ENVIANDO MENSAGEM DO CLIENTE*/
  memset(&buffer, '0', sizeof(buffer));
  sprintf (buffer, "Mensagem %s recebida em  %.24s\r (hora local)", msg, ctime(&tt));

  send(newsockfd, buffer, sizeof(buffer), 0);


  close(newsockfd);
  close(sockfd);

  return 0;
}