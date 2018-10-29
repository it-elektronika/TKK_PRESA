#include <arpa/inet.h>
#define delay_time  100000
#define delay_time2 100000
#define THOUSAND 1000000L


int timer1;
struct timespec start1, stop1;
double elapsedTime1;
double target1;
 
int count_turns;
int cylCond;
int errorNum;
int sockfd, newsockfd;
socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;
struct sockaddr_in AKD_server;
char *ip_adrs;
int press;

int lastState;
int currentState;
int lastOutput;
int currentOutput;

fd_set fdsTCP;
fd_set fdsAKD;
struct timeval tv;
int step;
int pageNum;
int counter;
int s;
int n;
int program;
int transId;
int conn_AKD;

int inCycle;
int selectedCan;
int rise_detected;
int fall_detected;

int PiControlHandle_g;

signed char sendMessageBuff[256];
signed char receiveMessageBuff[256];

char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];


char readBuff[85];
char readBuff_recv[85];

char writePosTenBuff[58];
char writePosTenBuff_recv[57];
char writePosUpBuff[58];
char writePosUpBuff_recv[57];
char writePosDownBuff[58];
char writePosDownBuff_recv[57];



char outputWriteBuff[256];


char obufMT[21];
char ibufMT[21];

char obufMTN[21];
char ibufMTN[21];

char obufDMC[17];
char ibufDMC[17];
char obufDS[17];
char ibufDS[17];
char obufCl[17];
char ibufCl[17];

void timers();
void sendMessage();
void receiveMessage();

void sendModbus(int socket_fd, char *send_buff, int send_buff_size, char *receive_buff, int receive_buff_size, char *print_text);
void detectFall(const char *var);
void detectRise(const char *var);


int checkCylinder(const char* input1, int input1_val, const char* input2, int input2_val, int nextStep);
void preCheckCylinder(const char *input1, int input1_val, const char* input2, int input2_val, const char* output, int output_val);
void upPosPrep();
void downPosPrep();
