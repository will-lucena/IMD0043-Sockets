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
#include <thread>
#include <mutex>
#include <vector>
#include <string>

#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 256
#define MAX_CON 5

using namespace std;

char msg[MAX_MSG];
string buffer;
mutex m;

void * socketThread(int* nSocket, char* server, short unsigned int porta);

int main(int argc, char *argv[])
{
  int sockfd, newsockfd;
  int rc, lt, n, i;
  socklen_t cliLen;
  struct sockaddr_in cliAddr, servAddr;
  thread mythreads[MAX_CON];



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
    cout << argv[0] << ": nao foi possivel associar a porta " << LOCAL_SERVER_PORT << endl;
    exit(1);
  }
  cout << argv[0] << ": aguardando por dados na porta TCP(" << LOCAL_SERVER_PORT << ")" << endl;

/* 3. OUVINDO CONEXÕES*/ 
  lt = listen(sockfd , MAX_CON);
  if (lt < 0)
  {
    cout << argv[0] << ": erro no listen"
    << LOCAL_SERVER_PORT << endl;
    exit(1);
  }
  cout << argv[0] << ": ouvindo até " << MAX_CON << " clientes" << endl;


  i=0;
  while(1){
    cliLen = sizeof(cliAddr);

/* 4. ACCEPT*/
    newsockfd = accept(sockfd, (struct sockaddr *) &cliAddr, &cliLen);
    if (newsockfd < 0)
    {
      cout << argv[0] << ": erro no accept"
      << LOCAL_SERVER_PORT << endl;
      exit(1);
    }
    cout << argv[0] << ": estou conectado com " << inet_ntoa(cliAddr.sin_addr) << " na porta "
    << ntohs(cliAddr.sin_port) << endl;

    mythreads[i] = thread(socketThread,&newsockfd,argv[0], ntohs(cliAddr.sin_port)); 

    
    if( i >= MAX_CON)
    {
      i = 0;
      while(i < MAX_CON)
      {
        if(mythreads[i].joinable()){
          mythreads[i++].join();
        }
      }
      i = 0;
    }

    
  }
  close(sockfd);
  return 0;
}


void * socketThread(int* nSocket, char* server, short unsigned int porta)
{
  int newSocket = *(nSocket);
 // int newSocket = *((int *)arg);
  int n;
  while(1){
/* 5. RECEBENDO MENSAGEM DO CLIENTE*/
    m.lock();

    memset(&msg, '0', sizeof(msg));

    n = read(newSocket,msg,MAX_MSG-1);
    if (n < 0)
    {
      cout << server << ": erro na leitura do socket " << LOCAL_SERVER_PORT << endl;
      close(newSocket);
      exit(1);
    } 

//Hora
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt;
    tt = std::chrono::system_clock::to_time_t ( today );

    cout << server << ": Mensagem de TCP(" << porta << "): " << msg << "\nRecebida em (hora local): " <<  ctime(&tt) << endl;

    
/* 6. ENVIANDO MENSAGEM DO CLIENTE*/
    string msgStr = msg;
    buffer = "Mensagem " + msgStr;
    buffer += " recebida em ";
    buffer += ctime(&tt);
    buffer += " (hora local)";

    m.unlock();

    sleep(1);

    n = write(newSocket, buffer.c_str() , strlen(buffer.c_str()) + 1);

    if( n < 0)
    {
      cout << server << ": Falha no envio da mensagem." << endl;
      close(newSocket);
      exit(1);
    }

  }
  cout << "Saindo de socketThread \n" << endl;
  close(newSocket);

}
