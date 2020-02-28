#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Socket_Server.h"
#define PORT 443
#define MAX_BUFF_SIZE 128
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
     #if defined _WIN64 || defined (WIN32) || defined _WIN32
      fgets(s,sizeof(s),fic);
    #elif __UNIX__ || defined __APPLE__ || defined  __linux__
      fscanf(fic,"%s",s);   // C4996
    #endif
      int cpt = 0;
      dPoint = 1;
      for(int i = 0; s[i]; i++){
        
        #if defined _WIN64 || defined (WIN32) || defined _WIN32
          dPoint = 0;
          if((int)s[i - 2] == 58){
            dPoint = 1;
          }
        #endif
        if(((int)s[i] >= 46) && ((int)s[i] <= 57)){
          monIP[cpt] = s[i];
          cpt++;
        }
      }
      printf("L'ip du serveur est : %s", monIP);
    }
}

const char * setServIP(){
  char * servIP = malloc(sizeof(char) * MAX_BUFF_SIZE);
  printf("Saisir l'addresse IP du serveur : ");
  scanf(" %s", servIP);

  printf("\n%s\n", servIP);
  return servIP;
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

void sendMsg(int socket){
  int sockCli;
  char  * buffer;
  buffer = malloc(sizeof(char) * MAX_BUFF_SIZE);
  
  printf("Saisir votre message : ");
  scanf(" %[^\n]", buffer);

  printf("\n votre message : %s \n", buffer);
  
  
  printf("Buffer size sendMSG: %lu (%lu)", strlen(buffer), sizeof(buffer));

  printf(" Message sendMSg : %s \n", buffer);
  sockCli = send(socket, buffer, sizeof(buffer), 0);
  if(sockCli != SOCKET_ERROR){
    printf("Message envoyé avec succes ! \n");
    free(buffer);
  }
  else{
    printf("Send MSG error ... \n");
    
  }
  free(buffer);
}

void startChat(int sock){
  int choix = 0;
  time_t seconds;
  time(&seconds);
  do {
    printf("\nEnvoyer un message (1) ");
    scanf("%d", &choix);
    if(choix == 1){
      sendMsg(sock);
    }
    printf("Attente : ");
    printf("%ld \n", (time(NULL) - seconds));
    sleep(1);
  } while((time(NULL) -seconds)  != (1 *60));
}

void silentChat(int sock){
  
  t_msgChat msgSilentChat;
  msgSilentChat.ident=0;
  sprintf(msgSilentChat.pseudo,"Null");
  msgSilentChat.msg = NULL;
  msgSilentChat.msg = malloc(10);
  sprintf(msgSilentChat.msg,"Bonjour");
  
  printf("\nsize of msgSlilentCHat.msg : %lu (%lu) \n", strlen(msgSilentChat.msg), sizeof(msgSilentChat.msg));

  time_t seconds;
  time(&seconds);
  
  
  // if(recv(socketConnected,(void *)&msgSilentChat, sizeof(msgSilentChat), 0) != SOCKET_ERROR){
  //   printf("Vous avez un nouveau message ! \n");
  //   printf("[%s] : %s",msgSilentChat.pseudo, msgSilentChat.msg);
  //   }
  
  
  // while(1 && ((time(NULL) - seconds)  != (1 *60))){
  //   if(recv(sock, bufferRecv, sizeof(bufferRecv),0) != SOCKET_ERROR){
  //     printf("recu : %s \n", bufferRecv);
  //     printf("size of bufferRecv startChat: %lu (%lu)", strlen(bufferRecv), sizeof(bufferRecv));
  //     time(&seconds);
  //     sleep(1);
  //   }
    // printf("Attente : ");
    // printf("%ld \n", (time(NULL) - seconds));
    // sleep(1);
    
  // }
}
