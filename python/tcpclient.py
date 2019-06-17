#!/usr/bin/env python3

# Importando a biblioteca de datetime
from datetime import datetime

# Utilizando o parametro datetime.now 
# para pegar a hora do SO
hora_atual = datetime.now()

# Utilizando o parametro strftime 
# para personalizar o formato da hora
view_hora = hora_atual.strftime('%H:%M')

# Importando a biblioteca de socket
import socket

# O nome do host ou endereço IP do servidor
HOST = '127.0.0.1'  

# A porta usada pelo servidor
PORT = 1500        

# 1. SOCKET
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
# 2. CONNECT
server_address = (HOST, PORT)
print('Conectando em {} na porta {}'.format(*server_address))
sock.connect(server_address)

while True:

    # 3. SEND
    message = input("Digite mensagem a ser enviada: ")
    print('Enviando {!r}'.format(message)  + ' as {!r}'.format(view_hora))
    sock.sendall(message.encode())

    # 4. RECV
    data = sock.recv(1024).decode()
    print('Recebendo dados de volta do servidor')

    if(message == 'sair'):
        break

# 5. CLOSE
print('Encerrando socket')
sock.close()