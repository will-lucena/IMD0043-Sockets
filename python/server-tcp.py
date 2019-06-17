import socket
import sys
PORTA = 10000



# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', PORTA)
print('starting up on {} port {}'.format(*server_address))
sock.bind(server_address)

# Listen for incoming connections
sock.listen(2)

while True:
    # Wait for a connection
    print('waiting for a connection')
    connection, client_address = sock.accept()
    try:
        print('connection from', client_address)

        # Receive the data in small chunks and retransmit it
        while True:
            data = connection.recv(16).decode()
            print('received {!r}'.format(data))
            if (data != 'sair' and data != ''):
                print('sending data back to the client')
                connection.sendall(data.encode())
            else:
            	print('desconnecting')
            	break

    finally:
        # Clean up the connection
        connection.close()