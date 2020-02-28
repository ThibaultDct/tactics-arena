#ifndef socket_server_h
#define socket_server_h

typedef struct Personnage{
  int id;
  char nom[128];
} t_personnage;

typedef struct msgChat{
  int ident;
  char pseudo[128];
  char * msg;
}t_msgChat;


int startTCPSocketServ();
int startTCPSocketCli();
int sendStruct(int socket, t_personnage monperso);
void sendMsg(int socket);
const char * realStr();
void getLocalIP();
void startChat(int sock);
const char * setServIP();
void silentChat(int sock);

#endif
