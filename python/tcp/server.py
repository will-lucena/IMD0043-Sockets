#!/usr/bin/env python3

import socket

# Endereço de interface padrão de loopback (localhost)
HOST = '127.0.0.1'  

# Porta para escutar (portas não privilegiadas são > 1023)
PORT = 54321        

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    pass  # Use o objeto socket sem chamar s.close ().
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Conectado em', addr)
        while True:
            data = conn.recv(1024)

                        
            #a=""
            #for i in range(0,len(data)):
            #    a=a+data[i]
            
            if not data:
                break

            #conn.sendall(a)
            print (data)
            conn.sendall(data)