# Importando a biblioteca de socket
import socket 

# 1. CRIACAO DO SOCKET 

# Criando um objeto socket
s = socket.socket()                 
print "socket criado com sucesso"   
 
# Reservando uma porta no computador local
# nesse caso, a porta eh 12345
port = 12345      

# 2. LIGACAO (BIND) DOS ENDERECOS COM A PORTA

# Campo IP vazio
# Servidor ouvindo pedidos providos de 
# outros computadores na rede
s.bind(('', port))        
print "socket ligado a %s" %(port)

# Colocando o socket em modo escuta
s.listen(5)     
print "socket esta ouvindo a rede"      

# 3. RECEBENDO DADOS

# LOOP INFINITO PARA LEITURA (LISTEN)
while True:
 
   # Esteblecendo conexao com o cliente.
   c, addr = s.accept()     
   print 'Tenho conexao com ', addr

   # Pegando dados do cliente
   data=c.recv(1024)

   if not data:
     break

   # 4. ENVIANDO DADOS PARA O CLIENTE
   
   # Imprimindo a mensagem recebida do cliente
   print data

   # 5. ENCERRANDO A CONEXAO
 
   # Encerrando a conexao com o cliente
   c.close()

# FIM DO LOOP INFINITO