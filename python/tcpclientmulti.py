#!/usr/bin/env python3

# Importando a biblioteca de socket
import socket
import os
import sys

# O nome do host ou endereço IP do servidor
HOST = '127.0.0.1'  

# A porta usada pelo servidor
PORT = 1500        

# 1. SOCKET
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
# 2. CONNECT
server_address = (HOST, PORT)
print('Conectando ao servidor {} na porta {}'.format(*server_address))
sock.connect(server_address)

while True:

    # 3. SEND
    message = input("Digite mensagem a ser enviada: ")
    print('Enviando {!r}'.format(message))
    sock.sendall(message.encode())

    # 4. RECV
    data = sock.recv(1024).decode()
    print('Recebendo {!r}'.format(message) + ' de volta do {!r}'.format(server_address))

    if(message == 'sair'):
        break

# 5. CLOSE
print('Encerrando socket')
sock.close()