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

## Compilando (no caminho: c++/):

		g++ -std=c++11 udpserver.cpp -o udpsrv
		g++ -std=c++11 udpclient.cpp -o udpcli 

## Rodando (no caminho: c++/):

Abra um terminal e ative o servidor:

		./udpsrv

Abra outro terminal e execute o cliente:

		./udpcli localhost testando à envia a mensagem “testando” ao servidor local
		./udpcli 127.0.0.1 teste1 teste2 à envia as mensagens “teste1” e “teste2” ao servidor local
		./udpcli 10.7.23.15 teste3 à envia a mensagem “teste3” ao servidor remoto 10.7.23.15 (supondo que o servidor esteja a executar neste host)


# PYTHON

## Material de Apoio

Multithreading em Python : https://www.tutorialspoint.com/python/python_multithreading.htm

Sockets em Python : https://www.tutorialspoint.com/python/python_networking.htm


## Compilando e Rodando UDP (no caminho: python/udp/):

Abra um terminal e ative o servidor:

		python server.py

Abra outro terminal e execute o cliente:

		python client.py

## Compilando e Rodando TCP (no caminho: python/tcp/):

Abra um terminal e ative o servidor:

		python3 server.py

Abra outro terminal e execute o cliente:

		python3 client.py


# JAVA

## Material de Apoio

Multithreading em Java : https://www.tutorialspoint.com/java/java_multithreading.htm

Sockets em Java : https://www.tutorialspoint.com/java/java_networking.htm


# RESULTADOS ESPERADOS

1. [X] Altere o código cliente/servidor UDP apresentado de modo que o servidor responda com
a mensagem “Mensagem XXX recebida às 99h99 (hora local)”. Considere que o cliente enviará a
mensagem XXX e esperará pela resposta do servidor. Ao receber a resposta, deverá imprimir na
tela.

2. [ ] Tomando como base o código implementado no item anterior, implemente um
cliente/servidor para o mesmo fim que utilize socket TCP.

3. [ ] Tomando como base o código implementado no item anterior, altere o código para
permitir que o cliente possa enviar N mensagens pelo terminal (até que digite “sair”). Permita
ainda que o servidor atenda múltiplos clientes, a exemplo de um servidor web, como discutido
na aula anterior.

4. [ ] Tomando como base o código implementado no itens anteriores,
implemente os mesmos exercícios utilizando as linguagens python e java!
	• Documente o seu código
	• Seu código deve apresentar as mesmas funcionalidades da versão C++
	• Ao final, apresente um relatório indicando as dificuldades, vantagens e desvantagens da programação em socket para cada linguagem
	• Indique qual a sua linguagem de preferência para futuras implementações utilizando sockets


Programa desenvolvido por _Bianca Santiago_ (*bianca.santiago72@gmail.com*), _Clarissa Soares_ (*clahzita@gmail.com*), _William Lucena_ (*will.lucen4@gmail.com*), 2019.1

