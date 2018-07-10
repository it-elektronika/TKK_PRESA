#include <modbus.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

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


int x;
int s;
int transId;
int posCounter;

char *ip_adrs;
struct sockaddr_in server;

fd_set fds;
struct timeval tv;

char obufDM[17];
char ibufDM[17];


char obufMT[21];
char ibufMT[21];

char obufDS[17];
char ibufDS[17];

char obufCl[17];
char ibufCl[17];

char obufOneA[58];
char ibufOneA[56];

char obufOneB[58];
char ibufOneB[56];

char obufTwoA[58];
char ibufTwoA[56];

char obufTwoB[58];
char ibufTwoB[56];

char obufThreeA[58];
char ibufThreeA[56];

char obufThreeB[58];
char ibufThreeB[56];


char modifierBuff[20];
int modifier;


void initComm();
void initMain();

/*
void errorCheck();
*/
