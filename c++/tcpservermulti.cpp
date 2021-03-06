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
#define MAX_CON 50

using namespace std;

char msg[MAX_MSG];
string buffer;
mutex m;
vector<int> todosClientesConectados;

void * socketThread(int* nSocket, char* server, short unsigned int portaClient, char * IPClient);

int main(int argc, char *argv[])
{
  int sockfd, newsockfd;
  int rc, lt, n, i, conexoes;
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


  conexoes=0;
  
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

    /*Guardar os clientes para enviar mensagem */
    todosClientesConectados.push_back(newsockfd);

    cout << argv[0] << ": estou conectado com " << inet_ntoa(cliAddr.sin_addr) << " na porta "
    << ntohs(cliAddr.sin_port) << endl;

    mythreads[conexoes++] = thread(socketThread,&newsockfd,argv[0], ntohs(cliAddr.sin_port), inet_ntoa(cliAddr.sin_addr)); 


    if( conexoes >= MAX_CON)
    {
      conexoes = 0;
      while(i < MAX_CON)
      {
        if(mythreads[conexoes].joinable()){
          mythreads[conexoes++].join();
        }
      }
      i = 0;
    }


  }

  for(i=0; i < conexoes; i++){
    if(mythreads[i].joinable()){
      mythreads[i].join();
    }
  }


  close(sockfd);
  return 0;
}


void * socketThread(int* nSocket, char* server, short unsigned int portaClient, char * IPClient)
{
  int newSocket = *(nSocket);
 // int newSocket = *((int *)arg);
  int n;
  while(1){
/* 5. RECEBENDO MENSAGEM DO CLIENTE*/   
    n = read(newSocket,msg,MAX_MSG-1);
    if (n < 0)
    {
      cout << server << ": erro na leitura do socket " << endl;
      break;
    } 

    m.lock(); // inicio bloqueio
    string msgStr = msg;
    string portaStr = to_string(portaClient);
    string ipStr = IPClient;

    // Informações sobre hora
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt;
    tt = std::chrono::system_clock::to_time_t ( today );

    if (msgStr == "sair") { 
      buffer = ipStr;
      buffer += " TCP(";
      buffer += portaStr;
      buffer += ") desconectou em (hora local) - ";
      buffer += ctime(&tt);

      cout << server << ": " << ipStr << " TCP(" << portaStr << ") desconectou em (hora local) - " << ctime(&tt);

    }else{

      buffer = "Mensagem de " + ipStr;
      buffer += " TCP(";
      buffer += portaStr;
      buffer += "): ";
      buffer += msgStr;
      buffer += "\nRecebida em (hora local): ";
      buffer += ctime(&tt);

      cout << "> Mensagem de "<< ipStr << "TCP(" << portaStr << "): " << msgStr << "\n> Recebida em (hora local): " <<  ctime(&tt);
    }
    
    m.unlock(); // fim  bloqueio

    n = 0;
    sleep(1);
    vector<int>::iterator clientePos;
  /* 7. ENVIANDO MENSAGEM PARA O CLIENTES CONECTADOS*/
    for (vector<int>::iterator sk = todosClientesConectados.begin();
                    sk != todosClientesConectados.end(); sk++) {
      
      if(*sk != newSocket){

         n = write(*sk, buffer.c_str() , strlen(buffer.c_str()) + 1);

        if( n < 0)
        {
          cout << server << ": Falha no envio da mensagem." << endl;
          break;
        }   

      }else{
        //guarda posição do cliente caso precise apagar da lista
        clientePos = sk;
          
      }
    }
   

    if (msgStr == "sair") { 
      //caso o cliente esteja desconectando tem que tirar da lista de clientes
      todosClientesConectados.erase(clientePos);
      //depois de enviar mensagens, sair.
      break; 
    }

  }
  
  close(newSocket);

}
