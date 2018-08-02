#include <modbus.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#define AKD_frame_posSmall 30
#define AKD_frame_posSmall2 50
#define AKD_frame_posMedium 100
#define AKD_frame_posBig 167.2
#define lastStep 9
#define PORTNO 1500
#define BILLION 1000000000L;
modbus_t *ctx;

int sockfd;
struct sockaddr_in serv_addr;
struct sockaddr_in server;
char *ip_adrs;
fd_set fds;
fd_set fdsTCP;

struct timeval tv;

int connectiOn;
char connStat[2][2];
int n; 
int conn_presa;
int conn_hmi;
int s;

int moveTask;
int transId;
int posCounter;

char buff_reg[10][10];
char regs[10];
char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];

char inputs[28][20];
char outputs[28][20];

char buff_inputs[28][20];
char buff_outputs[28][20];

int scrollArr[28];
char stepCounter[10];
char stepCond[10][3][50];
char stepName[10][50];
int step;
int posMan;
int posUp;
int posDown;

char smallBuff[20];
char small2Buff[20];


char mediumBuff[20];
char bigBuff[20];
char posManBuff[20]; 
char posUpBuff[30]; 
char posDownBuff[30]; 



int firstPosSmall;
int firstPosSmall2;
int firstPosMedium;
int firstPosBig;

int secondPosSmall;
int secondPosSmall2;
int secondPosMedium;
int secondPosBig;

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
char tmBuff[20];
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
void sendRequest(int reqId, int outputId, int id);
void receiveResponse();
void timer(float measure);

void initCommTCP();
void initCommAKDPress();
void initMain();
