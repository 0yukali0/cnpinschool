CC := gcc
echo_client := echo-client-udp.c
echo_server := echo-server-udp.c
server := receiver.c
client := sender.c
rec := rec.c
send := send.c
all: 
	$(CC) -o echo_client $(echo_client)
	$(CC) -o echo_server $(echo_server)
	$(CC) -o server $(server)
	$(CC) -o client $(client)
	$(CC) -o rec $(rec)
	$(CC) -o send $(send)
clean:
	rm echo_client echo_server server client rec send