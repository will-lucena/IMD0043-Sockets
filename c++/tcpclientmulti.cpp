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
//#include <boost/algorithm/string.hpp>    


#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 256
#define MAX_CON 5


using namespace std;


void * clientThread(int nThread, char*server, char* host)
{

  cout << "In the thread" << endl;

  int clientSocket, rc, i, cn, n;
  struct sockaddr_in remoteServAddr;
  struct hostent * h;
  string msgToSend;
  char msgReceived[MAX_MSG];
  socklen_t addr_size;

  /* 1. CRIA O SOCKET */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0)
  {
    cout << server << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }

  /* OBTEM O ENDERECO IP e PESQUISA O NOME NO DNS */
  h = gethostbyname(host);
  if (h == NULL) {
    cout << server <<  ": host desconhecido " << host << endl;
    exit(1);
  }
  cout << server << ": enviando dados para " << h->h_name
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
    cout << server << ": falha de conexão com a porta ou problema de ip" << endl;
    exit(1);
  }

  string sair = "sair";

  while(1) {

    // cout << "Digite a mensagem:" << endl;
    // getline(msgToSend);

    // const std::string lower_str = boost::algorithm::to_lower_copy(msgToSend);

    // if (lower_str == sair){
    //   cout << "Encerrando conexão." << endl;
    //   close(sockfd);
    //   return 0;
    // }


    msgToSend = "Hello, I am thread number " + to_string(nThread);
    
    
    if( send(clientSocket , msgToSend.c_str() , strlen(msgToSend.c_str()) , 0) < 0)
    {
      cout << server << ": Falha no envio da mensagem." << endl;
      close(clientSocket);
      exit(1);
    }

    //Ler a mensagem do servidor
    if(recv(clientSocket, msgReceived, MAX_MSG, 0) < 0)
    {
      cout << server << ": Recebimento falhou." << endl;
      close(clientSocket);
      exit(1);
    }

    cout << server << ": Mensagem recebida -> " << msgReceived << endl;

  }

  close(clientSocket);
}


int main(int argc, char *argv[])
{
  int i = 0;
  thread mythreads[MAX_CON];

  while(i< MAX_CON)
  {

    mythreads[i] = thread(clientThread, i, argv[0], argv[1]);
    i++;
  }

  sleep(20);

  i = 0;
  while(i< MAX_CON)
  {
    if(mythreads[i].joinable()){
      mythreads[i++].join();
    }
  }
  
  return 0;
}