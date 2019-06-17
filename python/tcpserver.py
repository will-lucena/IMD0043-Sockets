#!/usr/bin/env python3

# Importando a biblioteca de socket
import socket

# Endereco de interface padrao de loopback (localhost)
HOST = '127.0.0.1'  

# Porta para escutar (portas nao privilegiadas sao > 1023)
PORT = 54321        

# 1. SOCKET
# socket.socket() cria um objeto de socket que suporta o tipo de gerenciador de contexto
# para uso em  uma with statement.
# Parametros:familia de enderecos e o tipo de socket. AF_INET eh a familia de enderecos da 
# Internet para o IPv4, SOCK_STREAM eh o tipo de socket para TCP, o protocolo que sera usado 
# para transportar as mensagens mensagens na rede.
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

    # 2. BIND
    # Associacao do socket a uma interface de rede e um numero de porta especificos
    # Parametros: host (nome de host / endereco IP) e port (porta TCP)
    s.bind((HOST, PORT))
    print ("Socket ligado a porta %s" %(PORT))

    # 3. LISTEN
    # Habilita um servidor para aceitar conexoes. Isso o torna um socket de escuta.
    # Aceita novas conexoes
    s.listen()
    print ("Socket esta ouvindo a rede")  

    # 4. ACEPT
    # Bloqueia e aguarda por uma conexao de entrada. Quando a conexao com o cliente eh
    # estabelecida, ele retorna um novo objeto de socket representando a conexao e uma 
    # tupla que contem o endereco do cliente.
    # Permite a comunicacao com o cliente
    conn, addr = s.accept()
    with conn:
        print('Servidor: estou conectado com ', addr)

        # LOOP INFINITO PARA VARRER BLOQUEIOS DE CHAMADA
        while True:

            # 5. RECV
            data = conn.recv(1024)
            
            if not data:
                break

            # 6. SEND
            print (data.decode())
            #conn.sendall(data)
        # LOOP INFINITO PARA VARRER BLOQUEIOS DE CHAMADA

    # 7. CLOSE
    conn.close()