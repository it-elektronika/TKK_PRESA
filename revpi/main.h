int sockfd, newsockfd;
socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;
struct sockaddr_in AKD_server;
char *ip_adrs;


fd_set fdsTCP;
fd_set fdsAKD;
struct timeval tv;
int step;

int s;
int n;
int program;
int transId;
int conn_AKD;

int PiControlHandle_g;

char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];


char readBuff[12];
char readBuff_recv[30];
char outputWriteBuff[256];
