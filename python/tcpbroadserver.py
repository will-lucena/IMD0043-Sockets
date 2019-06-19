#!/usr/bin/env python3

# Importando a biblioteca de datetime
from datetime import datetime

# Utilizando o parametro datetime.now para pegar a hora do SO
hora_atual = datetime.now()


# Importando a biblioteca de socket
import socket
import select 
import sys 
from thread import *

PORT = 1500

if len(sys.argv) != 2: 
    print "Correct usage: <script> <IP address>"
    exit() 

# 1. SOCKET
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 

# 2. BIND
server.bind((str(sys.argv[1]), PORT))

# 3. LISTEN
server.listen(100) 

list_of_clients = []

def clientthread(conn, addr): 
  
    # sends a message to the client whose user object is conn 
    # 4. ACCEPT
    conn.send("Conectado ao servidor!") 
  
    while True: 
            try: 
                message = conn.recv(2048) 
                if message: 
 
                    message_to_send = "<" + addr[0] + str(datetime.now())  + "> " + message 

                    print message_to_send
                    broadcast(message_to_send, conn) 
  
                else: 
                    remove(conn) 
  
            except: 
                continue


def broadcast(message, connection): 
    for clients in list_of_clients: 
        if clients!=connection: 
            try: 
                clients.send(message) 
            except: 
                clients.close() 
                remove(clients) 

def remove(connection): 
    if connection in list_of_clients: 
        list_of_clients.remove(connection)


while True: 
  
	#4. ACCEPT
    conn, addr = server.accept() 
  
    #Adiciona cliente a lista
    list_of_clients.append(conn) 
  
    print "<" + addr[0] + " - " str(datetime.now()) + "> conectado"
  
    start_new_thread(clientthread,(conn,addr))     
  
conn.close() 
server.close() 