#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <iostream>
#include <cstdlib>
#include <ctime> /*hora */
#include <chrono>

#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 100

using namespace std;




int main(int argc, char *argv[])
{
  int sd, rc, n;
  socklen_t cliLen;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];


  /* 1. CRIA O SOCKET */
  sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sd < 0)
  {
    cout << argv[0] << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }
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
  cout << argv[0] << ": aguardando por dados na porta UDP("
       << LOCAL_SERVER_PORT << ")" << endl;
  /* 3. LOOP INFINITO PARA LEITURA (LISTEN) */
  while (1)
  {
    /* INICIA O BUFFER DE COMUNICACAO */
    memset(msg, 0x0, MAX_MSG);
    /* RECEBE MENSAGEM */
    cliLen = sizeof(cliAddr);
    n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *)&cliAddr, &cliLen);
    if (n < 0)
    {
      cout << argv[0] << ": nao foi possivel receber dados" << endl;
      continue;
    }
    /* IMPRIME A MENSAGEM RECEBIDA */

    //Hora
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt;
    tt = std::chrono::system_clock::to_time_t ( today );
    
    cout << argv[0] << ": de " << inet_ntoa(cliAddr.sin_addr) << ":UDP(" << ntohs(cliAddr.sin_port) <<
                       ") : Mensagem: " << msg << " - recebida em " <<  ctime(&tt) << "(hora local)" << endl;
  } /* FIM DO LOOP INFINITO */
  return 0;
}