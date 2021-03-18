CC := gcc
client := echo-client-udp.c
server := echo-server-udp.c
rec := receiver.c
send := sender.c
all: 
	$(CC) -o client $(client)
	$(CC) -o server $(server)
	$(CC) -o rec $(rec)
	$(CC) -o send $(send)
clean:
	rm -rf client server rec send
