CC := gcc
client := echo-client-udp.c
server := echo-server-udp.c
rec := receiver.c
send := sender.c
client := my-send.c
dayserver := my-rec.c
fakesev := echo_server02.c
fakecli := echo-client02.c
all: 
	$(CC) -o client $(client)
	$(CC) -o server $(server)
	$(CC) -o rec $(rec)
	$(CC) -o send $(send)
	$(CC) -o client $(client)
	$(CC) -o server $(dayserver)
	$(CC) -o fakesev $(fakesev)
	$(CC) -o fakecli $(fakecli)
clean:
	rm -rf client server rec send client server fakesev fakecli
