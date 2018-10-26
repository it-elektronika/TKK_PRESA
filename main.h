#include <modbus.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#define lastStep 15
#define ioPins 42
#define PORTNO 1500
#define BILLION 1000000L




int sockfd;
struct sockaddr_in serv_addr;  /* REVPI */
struct sockaddr_in server;     /* AKD_PRESA */

char *ip_adrs;
fd_set fds;
fd_set fdsTCP;
int inCycle;

enum page_stage_t {ENTER, ENABLE, EXIT};  
enum page_stage_t page_stage;
  
struct timeval tv;
int clearError;
int selectedCan;
int errorNum;
int connectiOn;
int n; 
int conn_presa;
int conn_hmi;
int s;

int moveTask;
int transId;
int posCounter;

char sendMessageBuff[256];
char receiveMessageBuff[256];

char sendReadBuff[256];
char recvReadBuff[256];

char sendWriteBuff[256];
char recvWriteBuff[256];

char inputs[ioPins][40];
char outputs[ioPins][40];

char buff_inputs[ioPins][20];
char buff_outputs[ioPins][20];

char buff_inputs_val[ioPins][40];
char buff_outputs_val[ioPins][40];

int scrollArr[84];
char stepCounter[lastStep+2];
char stepCond[lastStep+2][3][50];
char stepName[lastStep+2][50];
int step;
int posMan;
int posUp;
int posDown;

int press;
char pressBuff[20];

char AKD_smallBuff[20];
char AKD_small2Buff[20];
char AKD_mediumBuff[20];
char AKD_bigBuff[20];

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

int AKD_frame_posSmall;
int AKD_frame_posSmall2;
int AKD_frame_posMedium;
int AKD_frame_posBig;

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

void sendRequest(int reqId, int id, int outputState);
void receiveResponse();
void timer(float measure);

void sendMessage();
void receiveMessage();

void initCommTCP();
void initCommAKDPress();
void initMain();
void sendModbus(int socket_fd, char *send_buff, int send_buff_size, char *receive_buff, int receive_buff_size, char *print_text);
void checkError();
