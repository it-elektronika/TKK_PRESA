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


modbus_t *ctx;
int i;
int nb;
int bb;
int rc;
int tc;
int connectiOn;
 
uint16_t regs[10];
char buff_reg[10][10];

char buff_inputs[28][2];


int conn;
int s;
int transId;
int posCounter;

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
char obufMT[21];
char ibufMT[21];

char obufDS[17];
char ibufDS[17];

char obufCl[17];
char ibufCl[17];

char obufOneB[58];
char ibufOneB[56];

char modifierBuff[20];
int modifier;


void initComm();
void initMain();

/*
void errorCheck();
*/
