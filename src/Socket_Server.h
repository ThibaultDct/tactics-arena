#ifndef socket_server_h
#define socket_server_h

typedef struct Personnage{
  int id;
  char nom[128];
} t_personnage;


int startTCPSocketServ();
int startTCPSocketCli();
int sendStruct(int socket, t_personnage monperso);
int sendMSg(int socket);
const char * realStr();
void getLocalIP();
void startChat(int sock);
const char * setServIP();
// Personnage getStruct(int socket, Personnage monperso);

#endif
