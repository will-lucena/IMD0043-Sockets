#!/usr/bin/env python3

# Importando a biblioteca de socket
import socket
import os
import sys

# Endereco de interface padrao de loopback (localhost)
HOST = '127.0.0.1'  

# Porta para escutar (portas nao privilegiadas sao > 1023)
PORT = 1500        

# 1. SOCKET
# socket.socket() cria um objeto de socket
# Parametros:familia de enderecos e o tipo de socket. AF_INET eh a familia de enderecos da 
# Internet para o IPv4, SOCK_STREAM eh o tipo de socket para TCP, o protocolo que sera usado 
# para transportar as mensagens mensagens na rede.
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2. BIND
# Associacao do socket a uma interface de rede e um numero de porta especificos
# Parametros: host (nome de host / endereco IP) e port (porta TCP)
server_address = (HOST, PORT)
print('Iniciando em {} na porta {}'.format(*server_address))
sock.bind(server_address)

# 3. LISTEN
# Habilita um servidor para aceitar conexoes. Isso o torna um socket de escuta.
# Aceita novas conexoes
sock.listen(2)
print ("Socket esta ouvindo a rede")  

# LOOP INFINITO PARA VARRER BLOQUEIOS DE CHAMADA
while True:

    # 4. ACEPT
    # Bloqueia e aguarda por uma conexao de entrada. Quando a conexao com o cliente eh
    # estabelecida, ele retorna um novo objeto de socket representando a conexao e uma 
    # tupla que contem o endereco do cliente.
    # Permite a comunicacao com o cliente
    print('Aguardando por uma conexao')
    connection, client_address = sock.accept()
    try:

        pid = os.fork()
        if pid == 0:
            sock.close()
            print('Conectado com ', client_address)

            # LOOP PARA RECEBER E RETRANSMITIR MENSAGENS
            while True:

                # 5. RECV
                data = connection.recv(1024).decode()
                print('##################################################################')
                print('Cliente {!r}'.format(client_address) + ' disse: {!r}'.format(data))
                if (data != 'sair' and data != ''):

                    # 6. SEND
                    print('Enviando {!r}'.format(data) + ' de volta para {!r}'.format(client_address))
                    connection.sendall(data.encode())
                    print('##################################################################')
                else:
                    print('Desconectando')
                    break
                    print (client_address, data)
            print ('Finalizando conexao do cliente', client_address)
            print('##################################################################')
            connection.close()
            sys.exit(0)
        else:
            connection.close()
            # LOOP PARA RECEBER E RETRANSMITIR MENSAGENS

# FIM DO LOOP INFINITO PARA VARRER BLOQUEIOS DE CHAMADA
    
    finally:
        # 7. CLOSE
        # Encerrando a conexao
        connection.close()