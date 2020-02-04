#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Socket_Server.h"
#define PORT 50135
/*
* If program run on Windows
*/
#if defined _WIN64 || defined (WIN32) || defined _WIN32
  #include <winsock2.h>
  /*
  * Needed  non-existent type with winsock2
  */
  typedef int socklen_t;
/*
* Else if program run on Linux
*/
#elif __unix__ || defined __APPLE__
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  /*
  * Avoid differences to close a socket
  * between socket.h and winsock2.h
  * Adding missing definitions with socket.h
  */
  #define closesocket(param) close(param)
  #define INVALID_SOCKET -1
  #define SOCKET_ERROR -1
  /*
  * Adding missing types with socket.h
  */
  typedef int SOCKET;
  typedef struct sockaddr_in SOCKADDR_IN;
  typedef struct sockaddr SOCKADDR;

#endif


int startTCPSocketServ(){
  #if defined _WIN64 || defined (WIN32) || defined _WIN32
    /*
    * Change the cmd codepage
    */
    system("chcp 65001");
    system("netsh advfirewall firewall add rule name=\"Tactics\" protocol=TCP dir=in localport=50135 action=allow");
    system("netsh advfirewall firewall add rule name=\"Tactics\" protocol=TCP dir=out localport=50135 action=allow");
    system("ipconfig | findstr /r \"IPv4.*192\" > test.txt");
    system("cls");
    WSADATA WSAData;
    /*
    * Creating var to manage errors
    */
    int windWSAError;
    /*
    * WSAStratup Initialising winsock2 library
    * return 0 if there is no problems
    */
    windWSAError = WSAStartup(MAKEWORD(2,2), &WSAData);
  #elif defined __LINUX__ || defined __APPLE__
    system("ifconfig | grep \"inet 192.*\" | sed \"s/netmask.*//g\" | sed \"s/inet//g\" > test.txt");
    int windWSAError= 0;
  #endif

  int choixCli = 2;
  char buffer[128];

  t_personnage monpersoServ;
  monpersoServ.id = 1;
  sprintf(monpersoServ.nom,"Hello world");



  printf("\nLancement de la créatoin du serveur...\n");
  /*
  * Setting up the socket for all systems
  */
  SOCKADDR_IN sockServIn = { 0 };
  int sock;
  int socketConnected;
  int sockError;
  SOCKADDR_IN sockConnectedAddr;
  socklen_t sizeofSocketConnected;

  if(!windWSAError){
    printf("\nLa socket numéro %d en mode TCP/IP est valide  !\n", (int)&sock);
    /*
    * Initialising struct
    * Can change s_addr with given ip inet_addr("192.168.0.0") or INADDR_ANY
    * ptdr
    */
    sockServIn.sin_addr.s_addr=htonl(INADDR_ANY) ;
    sockServIn.sin_family = AF_INET;
    sockServIn.sin_port = htons (PORT);
    /*
    * Creating socket :
    * param 1 : Use TCP/IP
    * param 2 : Use with TCP
    * param 3 : Protocole parameter (useless) -> 0
    */
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET){
      /*
      *bind info to the socket
      */
      sockError = bind(sock, (SOCKADDR*)&sockServIn, sizeof(sockServIn));
      /*
      * Check if the socket is correct
      */
      if(sockError != SOCKET_ERROR){
        printf("\nDémarrage du serveur... \n");
        /*
        * Starting to connect
        * (max number of connection 5)
        */
        sockError = listen(sock,5);
        if(sockError != SOCKET_ERROR){
          printf("\nEn attente de la connexion d'un client...\n");
          getLocalIP();
          sizeofSocketConnected = sizeof(sockConnectedAddr);
          socketConnected = accept(sock, (struct  sockaddr  *)&sockConnectedAddr, &sizeofSocketConnected);
          if(socketConnected != SOCKET_ERROR){
            printf("\nConnexion établie avec le client !\n");
            printf("\nChargement de la partie... \n");
            printf("Début de la communication : \n");



            printf("L'id du perso est : %d \n", monpersoServ.id);
            printf("Le nom du perso est : %s \n", monpersoServ.nom);

            printf("(1) SI struct envoyée : ");
            scanf("%d",&choixCli);
            if(choixCli == 1 ){
              if(recv(socketConnected,(void *)&monpersoServ, sizeof(monpersoServ), 0) != SOCKET_ERROR){
                printf("Votre perso a été modifié ! \n");
                printf("l'id du perso est maintenant : %d \n", monpersoServ.id);
                printf("Le nom du perso est maintenant : %s \n", monpersoServ.nom);
              }
            }

            printf("Fin de la communication \n");
            /* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
            // printf("Press anny key to close socket... ");
            sleep(120);
          }
            shutdown(socketConnected, 2);
          closesocket(sock);
          system("netsh advfirewall firewall delete rule name=\"Tactics\"");
      }
      else{
        printf("\nUn problème est survenu lors de la connexion du client :( \n");
      }
    }
    else{
      printf("\nUn problème est survenue lors de la liaison avec le clien :( \n");
    }
  }
  else{
    printf("\nUn problème est survenue lors de la création de la socket :( \n");
  }
}
else{
  printf("Un problème est survenue avec Windows :( \n");
}
getchar();
return 0;
}
