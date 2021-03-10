CC := gcc
addr := getHostaddr.c
name := getHostname.c
ip := getip.c
all: 
	$(CC) -o getHostaddr $(addr)
	$(CC) -o getHostname $(name)
	$(CC) -o getip $(ip)
getHostaddr: $(addr)
	$(CC) -o $@ $<
getHostname: $(name)
	$(CC) -o $@ $<
getip: $(ip)
	$(CC) -o $@ $<
clean:
	rm -rf getHostaddr getHostname getip
