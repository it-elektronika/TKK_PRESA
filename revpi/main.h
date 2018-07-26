int sockfd, newsockfd;
socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;

int n;
int program;
int PiControlHandle_g;

char sendBuff[256];
char recvBuff[256];
char outputWriteBuff[256];
