#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Socket_Server.h"
#define PORT 50135
#define MAX_BUFF_SIZE 80
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
#elif __UNIX__ || defined __APPLE__ || defined  __linux__
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



char monStr[80];




void getLocalIP(){
  char monIP[81];
  char s[81];
  int dPoint = 0;
  FILE *fic;
  fic=fopen("test.txt", "r" );
   if( fic == NULL ){
      printf( "The file was not opened\n" );
    }
   else
   {
      /*
      * Get ip from the file named fic
      */
      fgets(s,sizeof(s),fic);   // C4996
      int cpt = 0;
      for(int i = 0; s[i]; i++){
        if((int)s[i - 2] == 58){
          dPoint = 1;
        }
        if( (((int)s[i] >= 46) && ((int)s[i] <= 57)) && (dPoint == 1) ){
          monIP[cpt] = s[i];
          cpt++;
        }
      }
      printf("L'ip du serveur est : %s", monIP);
    }
}


int sendStruct(int socket, t_personnage monperso){
  int sockSendError;

  sockSendError = send(socket, (void *)&monperso, sizeof(monperso), 0);
  if(sockSendError == SOCKET_ERROR){
    printf("Impossible d'envoyer la structure... \n");
  }
  else{
    printf("Structure envoyée ! ");
  }
  printf("Press key to continue...");
  getchar();
  return 0;
}

const char * realStr(){

  printf("Saisir votre message : ");
  scanf(" %[^\n]", monStr);

  printf("\n votre message : %s \n", monStr);

return monStr;
}

int sendMSg(int socket){
  int sockCli;
  const char * buffer = malloc(sizeof(char) * 128);
  buffer = realStr();

  printf(" Message sendMSg : %s \n", buffer);
  sockCli = send(socket, buffer, sizeof(buffer), 0);
  if(sockCli != SOCKET_ERROR){
  printf("Message envoyé avec succes ! \n");
  }
  else{
    printf("Send MSG error ... \n");
  }
  return 0;
}

void startChat(int sock){
  const char * buffer = malloc(sizeof(char) * 128);
  char bufferRecv[128];
  time_t seconds;
  time(&seconds);
  int choix = 0;

  do {
    if(recv(sock, bufferRecv, sizeof(bufferRecv),0) != SOCKET_ERROR){
      printf(" recu : %s \n", bufferRecv);
      time(&seconds);
    }
    printf("Envoyer un message (1) ");
    scanf("%d", &choix);
    if(choix == 1){
      if(recv(sock, bufferRecv, sizeof(bufferRecv),0) != SOCKET_ERROR){
        printf(" recu : %s \n", bufferRecv);
        time(&seconds);
      }
      sendMSg(sock);
    }

    printf("Attente : ");
    printf("%ld \n", (time(NULL) - seconds));
    sleep(1);
  } while((time(NULL) -seconds)  != (1 *60));
}
