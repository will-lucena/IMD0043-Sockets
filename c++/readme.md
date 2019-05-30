# Compilando:
* g++ udpserver.cpp -o udpsrv.exec
* g++ udpclient.cpp -o udpcli.exec

#Rodando:
* Abra um terminal e ative o servidor:
* #./udpsrv
* Abra outro terminal e execute o cliente:
* #./udpcli localhost testando à envia a mensagem “testando” ao servidor local
* #./udpcli 127.0.0.1 teste1 teste2 à envia as mensagens “teste1” e “teste2” ao servidor
local
* #./udpcli 10.7.23.15 teste3 à envia a mensagem “teste3” ao servidor remoto
10.7.23.15 (supondo que o servidor esteja a executar neste host)