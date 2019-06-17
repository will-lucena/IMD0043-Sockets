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
PORT = 54321        

# 1. SOCKET
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    
    # 2. CONNECT
    s.connect((HOST, PORT))

    # 3. SEND
    input_string = input("Mensagem a ser enviada: ")
    s.send(str.encode('Mensagem ' + input_string + ' recebida as ' + view_hora))
    
    # 4. RECV
    data = s.recv(1024)

    # 5. CLOSE
    s.close()