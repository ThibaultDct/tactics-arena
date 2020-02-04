#include <stdio.h>
#include <stdlib.h>
#include "Socket_Server.h"
#define PORT 50135


int main(int argc, char const *argv[]) {

  #if defined (WIN32)
    /*
    * Change the cmd codepage on Windows
    */
    system("chcp 65001");
    system("cls");
    #elif __unix__ || defined __APPLE_
    system("clear");
    #endif

  int choix = 0;
  printf("Bienvenue dans le serveur :) \n");


  printf("Lancer le serveur (1) \n");
  printf("Lancer le client (2) \n");
  printf("\nFaites votre choix : \n");
  scanf("%d", &choix);

  switch (choix) {
    case 1:startTCPSocketServ();break;
    case 2:startTCPSocketCli();break;
  }

  printf("\nPres any key to continue... \n");
  getchar();
  return EXIT_SUCCESS;
}
