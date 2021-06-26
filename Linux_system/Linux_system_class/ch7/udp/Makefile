all: client_exe server_exe

client_exe: client.c server.c
	gcc  -o client_exe  client.c

server_exe : server.c
	gcc  -o server_exe  server.c


clean:
	rm -vf *~
	rm -rf client_exe
	rm -rf server_exe
