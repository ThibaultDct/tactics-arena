Socket_Server: main.o Socket_Server.o Socket_Client.o ServFcnt.o
	gcc -o Socket_Server main.o Socket_Server.o Socket_Client.o ServFcnt.o lib/libws2_32.a
	@echo "Linking Completed !"

main.o: main.c Socket_Server.h
	gcc -o main.o -c main.c

Socket_Server.o: Socket_Server.c
	gcc -o Socket_Server.o -c Socket_Server.c

Socket_Client.o: Socket_Client.c
	gcc -o Socket_Client.o -c Socket_Client.c

ServFcnt.o: ServFcnt.c
	gcc -o ServFcnt.o -c ServFcnt.c
