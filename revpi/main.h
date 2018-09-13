#define delay_time 500000
#define delay_time2 250000

int sockfd, newsockfd;
socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;
struct sockaddr_in AKD_server;
char *ip_adrs;
int press;

fd_set fdsTCP;
fd_set fdsAKD;
struct timeval tv;
int step;

int s;
int n;
int program;
int transId;
int conn_AKD;

int selectedCan;

int PiControlHandle_g;

char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];


char readBuff[12];
char readBuff_recv[30];

char writePosTenBuff[58];
char writePosTenBuff_recv[56];

char outputWriteBuff[256];


char obufMT[21];
char ibufMT[21];

char obufMTN[21];
char ibufMTN[21];


char obufDS[17];
char ibufDS[17];
char obufCl[17];
char ibufCl[17];


void sendModbus(int socket, int socket_fd, char *send_buff, int send_buff_size, char *receive_buff, int receive_buff_size, char *print_text);
