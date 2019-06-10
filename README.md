# IMD0043-Sockets

C++

Multithreading em C++ https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm

Sockets em C++ : 

https://www.tutorialspoint.com/unix_sockets/

https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

https://www.freebsd.org/doc/en_US.ISO8859-1/books/developers-handbook/sockets-essential-functions.html

Compilando:
* g++ udpserver.cpp -o udpsrv
* g++ udpclient.cpp -o udpcli

Rodando:

• Abra um terminal e ative o servidor:
* #./udpsrv

• Abra outro terminal e execute o cliente:
* #./udpcli localhost testando à envia a mensagem “testando” ao servidor local
* #./udpcli 127.0.0.1 teste1 teste2 à envia as mensagens “teste1” e “teste2” ao servidor
local
* #./udpcli 10.7.23.15 teste3 à envia a mensagem “teste3” ao servidor remoto
10.7.23.15 (supondo que o servidor esteja a executar neste host)


PYTHON

Multithreading em Python : https://www.tutorialspoint.com/python/python_multithreading.htm

Sockets em Python : https://www.tutorialspoint.com/python/python_networking.htm

JAVA

Multithreading em Java : https://www.tutorialspoint.com/java/java_multithreading.htm

Sockets em Java : https://www.tutorialspoint.com/java/java_networking.htm
