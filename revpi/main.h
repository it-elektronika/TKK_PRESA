int sockfd, newsockfd;
socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;

fd_set fdsTCP;
struct timeval tv;


int n;
int program;
int PiControlHandle_g;

char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];


char outputWriteBuff[256];
