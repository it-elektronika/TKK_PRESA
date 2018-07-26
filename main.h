#include <modbus.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#define AKD_frame_posSmall 50
#define AKD_frame_posMedium 100
#define AKD_frame_posBig 150
#define lastStep 9
#define PORTNO 1500
modbus_t *ctx;

int sockfd;
struct sockaddr_in serv_addr;
 
int nb;
int bb;
int rc;
int tc;
int connectiOn;
int n; 

uint16_t regs[10];
char buff_reg[10][10];

char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];


char inputs[28][20];
char outputs[28][20];

char buff_inputs[28][10];
char buff_outputs[28][10];

int scrollArr[28];
char stepCounter[10];
char stepCond[10][3][50];
char stepName[10][50];
int step;
int posMan;
char smallBuff[20];
char mediumBuff[20];
char bigBuff[20];

char posManBuff[20]; 

int moveTask;
int conn;
int s;
int transId;
int posCounter;

int firstPosSmall;
int firstPosMedium;
int firstPosBig;

int secondPosSmall;
int secondPosMedium;
int secondPosBig;

char *ip_adrs;
struct sockaddr_in server;

fd_set fds;
struct timeval tv;

int year;
int month;
int day;
int hour;
int minute;

char yearBuff[20];
char monthBuff[20];
char dayBuff[20];
char hourBuff[20];
char minuteBuff[20];

char setTBuff[100];
char tmBuff[10];

char obufNT[21];
char ibufNT[21];

char obufClFirst[17];
char ibufClFirst[17];

char obufOneA[58];
char ibufOneA[56];

char obufMT[21];
char ibufMT[21];
char obufMTN[21];
char ibufMTN[21];


char obufDS[17];
char ibufDS[17];

char obufCl[17];
char ibufCl[17];

char obufOneB[58];
char ibufOneB[56];

char obufEd[17];
char ibufEd[17];

char modifierBuff[20];
int modifier;


void readLine(int fd, char data[], size_t maxlen);
void sendRequest(int reqId, int outputId);
void receiveResponse();

void initCommTCP();
void initCommAKDPress();
void initMain();
