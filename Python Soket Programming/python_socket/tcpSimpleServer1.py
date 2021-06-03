from socket import \
	socket, AF_INET, SOCK_STREAM
s = socket(AF_INET, SOCK_STREAM)
s.bind(('127.0.0.1', 9999))
s.listen(5) # max queued connections
while 1:
    sock, addr = s.accept()
    data = sock.recv(1024)
    print 'Received: ' + data 
    sock.send(data)
sock.close()
