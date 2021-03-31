CC := gcc
echo_client := echo-client-udp.c
echo_server := echo-server-udp.c
server := receiver.c
client := sender.c
echo_rec := echo_rec.c
echo_send := echo_send.c
rec := rec.c
send := send.c
all: 
	$(CC) -o echo_client $(echo_client)
	$(CC) -o echo_server $(echo_server)
	$(CC) -o server $(server)
	$(CC) -o client $(client)
	$(CC) -o rec $(rec)
	$(CC) -o send $(send)
	$(CC) -o echo_rec $(echo_rec)
	$(CC) -o echo_send $(echo_send)
clean:
	rm echo_client echo_server server client rec send