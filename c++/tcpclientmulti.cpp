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
#include <stdlib.h>
#include <stdio.h>


#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 100
using namespace std;
int main(int argc, char *argv[])
{
  int sd, rc, i, n;
  struct sockaddr_in cliAddr, remoteServAddr;
  struct hostent *h;
  char msg[MAX_MSG];
  
  // /* VERIFICA OS ARGUMENTOS PASSADOS POR LINHA DE COMANDO */
  // if (argc < 3)
  // {
  //   cout << "Uso : " << argv[0]
  //        << " <servidor> <mensagem1> ... <mensagemN>" << endl;
  //   exit(1);
  // }

  /* OBTEM O ENDERECO IP e PESQUISA O NOME NO DNS */
  h = gethostbyname(argv[1]);

  if (h == NULL)
  {
    cout << argv[0] << ": host desconhecido " << argv[1] << endl;
    exit(1);
  }
  cout << argv[0] << ": enviando dados para " << h->h_name
       << " (IP : " << inet_ntoa(*(struct in_addr *)h->h_addr_list[0])
       << endl;

  // limpar estrutura de endereço
  bzero((char *) &remoteServAddr, sizeof(remoteServAddr));

  /* CONFIGURANDO ESTRUTURA REFERENTE AO HOST REMOTO (SERVIDOR) */
  remoteServAddr.sin_family = h->h_addrtype;
  memcpy((char *)&remoteServAddr.sin_addr.s_addr,
         h->h_addr_list[0], h->h_length);
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

  /* 1. CRIA O SOCKET */
  sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sd < 0)
  {
    cout << argv[0] << ": nao foi possivel abrir o socket" << endl;
    exit(1);
  }

  //Conectar
  if (connect(sd, (struct sockaddr *) &remoteServAddr, sizeof(remoteServAddr)) < 0) {
    cout << "Erro de conexão" << endl;
    exit(1);
  }

  while (true) {
    string command;    // Now it's a string!
    cout << "Digite a mensagem" << endl;
    cin >> command;

    if (command == "sair") {
      break;
    }

    bzero(msg,MAX_MSG);
    fgets(msg,MAX_MSG-1,stdin);
    n = write(sd, msg, strlen(msg));
    if (n < 0){
      cout << "Erro escrevendo para socket" << endl;
      exit(1);
    }
         
    bzero(msg,MAX_MSG);

    n = read(sd, msg, MAX_MSG-1);

    if (n < 0){
      cout << "Erro lendo do socket" << endl;
      exit(1);
    }

    cout << msg << "\n" << endl;
    close(sd);


  }
    
    return 0;

  // /* 2. FAZ A LIGACAO (BIND) DE TODOS OS ENDERECOS COM A PORTA */
  // cliAddr.sin_family = AF_INET;
  // cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  // cliAddr.sin_port = htons(0);
  // rc = bind(sd, (struct sockaddr *)&cliAddr, sizeof(cliAddr));
  // if (rc < 0)
  // {
  //   cout << argv[0] << ": nao foi possivel ligar a porta" << endl;
  //   exit(1);
  // }
  /* 3. ENVIA DADOS */
  // for (i = 2; i < argc; i++)
  // {
  //   rc = sendto(sd, argv[i], strlen(argv[i]) + 1, 0, (struct sockaddr *)&remoteServAddr, sizeof(remoteServAddr));
  //   if (rc < 0)
  //   {
  //     cout << argv[0] << ": nao foi possivel enviar dados " << argv[i - 1] << endl;
  //     close(sd);
  //     exit(1);
  //   }
  // }
  // return 1;
}