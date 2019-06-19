# Python program to implement client side of chat room. 
import socket 
import select 
import sys 
  
PORT = 1500

if len(sys.argv) != 2: 
    print "Uso: <script> <IP address>"
    exit() 


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

server.connect((str(sys.argv[1]), PORT)) 
  
while True: 
  
    sockets_list = [sys.stdin, server] 
  
    read_sockets,write_socket, error_socket = select.select(sockets_list,[],[]) 
  
    for socks in read_sockets: 
        if socks == server: 
            message = socks.recv(2048) 
            print message 
        else: 
            message = sys.stdin.readline() 
            server.send(message) 
            
server.close() 