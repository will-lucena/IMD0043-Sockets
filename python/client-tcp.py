import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10000)
print('connecting to {} port {}'.format(*server_address))
sock.connect(server_address)

while True:
    # try:

    # Send data
    message = input("Digite mensagem a ser enviada: ")
    #message = b'This is the message.  It will be repeated.'
    print('sending {!r}'.format(message))
    sock.sendall(message.encode())

    # # Look for the response
    # amount_received = 0
    # amount_expected = len(message)

    #while amount_received < amount_expected:
    data = sock.recv(16).decode()
    #    amount_received += len(data)
    print('received {!r}'.format(data))

    if(message == 'sair'):
        break

print('closing socket')
sock.close()