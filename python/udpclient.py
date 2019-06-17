# Importando a biblioteca de socket
import socket 

# O nome do host ou endereço IP do servidor
HOST = '127.0.0.1'  

# Definindo a porta a qual o cliente quer se conectar
# Nesse caso 12345 (server)
PORT = 12345 

# Importando a biblioteca de datetime
from datetime import datetime

# Utilizando o parametro datetime.now 
# para pegar a hora do SO
hora_atual = datetime.now()

# Utilizando o parametro strftime 
# para personalizar o formato da hora
view_hora = hora_atual.strftime('%H:%M')              
 
# 1. CRIACAO DO SOCKET

# Criando um objeto socket 
s = socket.socket()        

# 2. LIGACAO (BIND) DOS ENDERECOS COM A PORTA              
 
# Conectando-se ao servidor no computador local
s.connect((HOST, PORT))

# 3. ENVIANDO DADOS

# Enviando dados ao servidor
input_string = raw_input("Mensagem a ser enviada: ")
s.sendall('Mensagem ' + input_string + ' recebida as ' + view_hora)

# 4. RECEBENDO DADOS

# Recebendo dados do servidor
print s.recv(1024)

# 5. ENCERRANDO A CONEXAO

# Encerrando a conexao com o servidor
s.close()  