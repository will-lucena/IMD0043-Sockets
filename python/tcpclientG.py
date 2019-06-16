#!/usr/bin/env python3

# Importando a biblioteca de datetime
from datetime import datetime

# Utilizando o parametro datetime.now 
# para pegar a hora do SO
hora_atual = datetime.now()

# Utilizando o parametro strftime 
# para personalizar o formato da hora
view_hora = hora_atual.strftime('%H:%M')

import socket

HOST = '127.0.0.1'  # O nome do host ou endereço IP do servidor
PORT = 54321        # A porta usada pelo servidor

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    #s.sendall('Hello, world')

    input_string = input("Insira os dados que deseja enviar: -> ")
    #s.sendall(b'Mensagem ' + input_string + ' recebida as ' + view_hora)
    s.sendall(b'SeiLa')
    
    data = s.recv(1024)

print('Received', repr(data))