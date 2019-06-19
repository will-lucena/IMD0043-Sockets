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

int ative;

using namespace std;

void * listeningFunc(int* socket, char* clientProgram);

int main(int argc, char *argv[])
{
  int clientSocket, rc, cn, n;
  struct sockaddr_in remoteServAddr;
  struct hostent * h;
  socklen_t addr_size;
  string msgToSend;
  thread listening;


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
  remoteServAddr.sin_family = h->h_addrtype;
  memcpy((char *)&remoteServAddr.sin_addr.s_addr,
   h->h_addr_list[0], h->h_length);
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);


  memset(remoteServAddr.sin_zero, '\0', sizeof remoteServAddr.sin_zero);
  
  /* CONECTA O SOCKET COM O SERVIDOR USANDO O ENDEREÇO */
  addr_size = sizeof remoteServAddr;
  cn = connect(clientSocket, (struct sockaddr *)&remoteServAddr, addr_size);
  if(cn<0){
    cout << argv[0] << ": falha de conexão com a porta ou problema de ip" << endl;
    exit(1);
  }

  listening = thread(listeningFunc,&clientSocket,argv[0]); 


  string sair = "sair";
  ative = 1;

  //Loop de comunicação, enquanto o cliente não digitar sair
  while(1) {

   cout << argv[0] << ": Digite a mensagem: ";
   getline(cin,msgToSend);

     // Enviar mensagem para servidor
   n = write(clientSocket, msgToSend.c_str() , strlen(msgToSend.c_str()) + 1);

   if( n < 0)
   {
     cout << argv[0] << ": Falha no envio da mensagem." << endl;
     close(clientSocket);
     exit(1);
   }


   if (msgToSend == sair){
     cout << argv[0] << ": Cliente encerrando conexão." << endl;
     ative = 0;
     break;
   }

 }

 if(listening.joinable()){
  listening.join();
}

close(clientSocket);

return 0;
}

void * listeningFunc(int* socket, char* clientProgram){
  int clientSocket = *(socket);
  int n = 0;
  char msgReceived[MAX_MSG];

  string tonaescuta = "\n";
  tonaescuta += clientProgram;
  tonaescuta += ": To na escuta!";

  cout << tonaescuta << endl;

  while (ative ){

    n = read(clientSocket, msgReceived, MAX_MSG-1);

    if (n < 0)
    {
      cout << clientProgram << ": Recebimento falhou." << endl;
      close(clientSocket);
      exit(1);
    }else{

      cout << "\n" << msgReceived << endl;
    }

  }


}


