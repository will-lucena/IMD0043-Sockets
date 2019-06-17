# IMD0043-Sockets

# SOBRE O PROJETO

# C++

## Material de Apoio

Multithreading em C++ : 

https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm

Sockets em C++ : 

https://www.tutorialspoint.com/unix_sockets/

https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

https://www.freebsd.org/doc/en_US.ISO8859-1/books/developers-handbook/sockets-essential-functions.html

https://dzone.com/articles/parallel-tcpip-socket-server-with-multi-threading

## Compilando e Rodando UDP (no caminho: c++/):
Abra um terminal e compile:

		g++ -std=c++11 udpserver.cpp -o udpsrv
		g++ -std=c++11 udpclient.cpp -o udpcli 
		
Ative o servidor:

		./udpsrv

Abra outro terminal e execute o cliente (./udpcli <servidor> <mensagem 1> <mensagemN>):
		
		./udpcli localhost testandp envio de mensagem “testando” ao servidor local
		./udpcli 127.0.0.1 teste1 teste2 à envia as mensagens “teste1” e “teste2” ao servidor local
		./udpcli 10.7.23.15 teste3 à envia a mensagem “teste3” ao servidor remoto 10.7.23.15
		(supondo que o servidor esteja a executar neste host)

## Compilando e Rodando TCP (no caminho: c++/):
Abra um terminal e compile:

		g++ -std=c++11 tcpserver.cpp -o tcpsrv
		g++ -std=c++11 tcpclient.cpp -o tcpcli 
		
Ative o servidor:

		./tcpsrv

Abra outro terminal e execute o cliente (./tcpcli <servidor> <mensagem 1> <mensagemN>):
		
		./tcpcli localhost testando envio de mensagem

## Compilando e Rodando TCP Multithreading (no caminho: c++/):
Abra um terminal e compile:

		g++ -std=c++11 -pthread -lpthread tcpservermulti.cpp -o tcpsrvmult
		g++ -std=c++11 tcpclientmulti.cpp -o tcpclimult 
		
Abra um terminal e ative o servidor:

		./tcpsrvmult

Abra outro terminal e execute o cliente (./tcpclimult <servidor>):

		./tcpclimult localhost
		
Quando solicitado, digite a mensagem e aguarde a resposta do servidor, quando quiser encerrar a conexão com servidor, digite "sair".


# PYTHON

## Material de Apoio

Multithreading em Python : 

https://www.tutorialspoint.com/python/python_multithreading.htm

Sockets em Python : 

https://www.tutorialspoint.com/python/python_networking.htm

https://github.com/shauryauppal/Socket-Programming-Python

https://realpython.com/python-sockets/#tcp-sockets

https://wiki.python.org.br/SocketBasico

https://pymotw.com/3/socket/tcp.html


## Compilando e Rodando UDP (no caminho: python/):

Abra um terminal e ative o servidor:

		python udpserver.py

Abra outro terminal e execute o cliente:

		python udpclient.py

## Compilando e Rodando TCP (no caminho: python/):

Abra um terminal e ative o servidor:

		python3 tcpserver.py

Abra outro terminal e execute o cliente:

		python3 tcpclient.py

## Compilando e Rodando TCP Multithreading (no caminho: python/):

Abra um terminal e ative o servidor:

		python3 tcpservermulti.py

Abra outro terminal e execute o cliente:

		python3 tcpclientmulti.py


# JAVA

## Material de Apoio

* Multithreading em Java : 

https://www.tutorialspoint.com/java/java_multithreading.htm

https://www.caelum.com.br/apostila-java-orientacao-objetos/apendice-sockets/#soluo-do-sistema-de-chat

* Sockets em Java : 

https://www.tutorialspoint.com/java/java_networking.htm

https://www.geeksforgeeks.org/iterate-map-java/

## Compilando (no caminho java/src/Application)

1. javac Server.java Client.java MessageHandler.java ClientHandler.java

## Executando

1. Abra um terminal e execute java Application.Server *porta*
2. Abra outro terminal e execute java Application.Client localhost *mesma porta do server*
3. Abra outro terminal e execute java Application.Client localhost *mesma porta do server*

## Notas

Ao inicializar o servidor, o cliente A e o cliente B e enviar uma mensagem pelo cliente A ela so sera exibida no cliente B,
o mesmo para o caso inverso.

Para desconectar um cliente basta digitar "sair"


# RESULTADOS ESPERADOS

1. [X] Altere o código cliente/servidor UDP apresentado de modo que o servidor responda com
a mensagem “Mensagem XXX recebida às 99h99 (hora local)”. Considere que o cliente enviará a
mensagem XXX e esperará pela resposta do servidor. Ao receber a resposta, deverá imprimir na
tela.

2. [X] Tomando como base o código implementado no item anterior, implemente um
cliente/servidor para o mesmo fim que utilize socket TCP.

3. [X] Tomando como base o código implementado no item anterior, altere o código para
permitir que o cliente possa enviar N mensagens pelo terminal (até que digite “sair”). Permita
ainda que o servidor atenda múltiplos clientes, a exemplo de um servidor web, como discutido
na aula anterior.

4. [X] Tomando como base o código implementado no itens anteriores,
implemente os mesmos exercícios utilizando as linguagens python e java!
	* Documente o seu código
	* Seu código deve apresentar as mesmas funcionalidades da versão C++
	* Ao final, apresente um relatório indicando as dificuldades, vantagens e desvantagens da programação em socket para cada linguagem
	* Indique qual a sua linguagem de preferência para futuras implementações utilizando sockets


Programa desenvolvido por _Bianca Santiago_ (*bianca.santiago72@gmail.com*), _Clarissa Soares_ (*clahzita@gmail.com*), _William Lucena_ (*will.lucen4@gmail.com*), 2019.1

