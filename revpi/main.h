int sockfd, newsockfd;
socklen_t clilen;
char sendBuff[256];
char recvBuff[256];

struct sockaddr_in serv_addr, cli_addr;
int n;
int program;
char regs[10];
int PiControlHandle_g;

