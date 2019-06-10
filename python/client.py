import socket 
from datetime import datetime

hora_atual = datetime.now()
view_hora = hora_atual.strftime('%H:%M')              
 
s = socket.socket()         
 
port = 12345               
 
s.connect(('127.0.0.1', port))

input_string = raw_input("Enter data you want to send->")
s.sendall('Mensagem ' + input_string + ' recebida as ' + view_hora)

print s.recv(1024)

s.close()  