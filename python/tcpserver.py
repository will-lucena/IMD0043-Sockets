#!/usr/bin/env python3

# Importando a biblioteca de socket
import socket

# Endereco de interface padrao de loopback (localhost)
HOST = '127.0.0.1'  

# Porta para escutar (portas nao privilegiadas sao > 1023)
PORT = 54321        

# 1. CRIACAO DO SOCKET
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    #pass  # Use o objeto socket sem chamar s.close ().
    s.bind((HOST, PORT))
    print ("Socket ligado a porta %s" %(PORT))
    s.listen()
    print ("Socket esta ouvindo a rede")  
    conn, addr = s.accept()
    with conn:
        print('Servidor: estou conectado com ', addr)
        while True:
            data = conn.recv(1024)
            
            if not data:
                break

            print (data.decode())
            #conn.sendall(data)
    conn.close()