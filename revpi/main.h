#include <arpa/inet.h>
#define delay_time  100000
#define delay_time2 100000
#define THOUSAND 1000000L

int timer1;
struct timespec start1, stop1;
double elapsedTime1;
double target1;
 
int safetyDoorLastState;
int safetyDoorCurrentState;

int stopTotalLastState;
int stopTotalCurrentState;
int pressing;

int powerLastState;
int powerCurrentState;
int tableClear;

int w;
int releaseCapDone;
int alarmReset;
int turnTableStep;
int turnTableDone;
int movePressZeroPosStep;
int movePressZeroPosDone;
int moveGripperLowerStep;
int moveGripperLowerDone;
int moveGripperUpperStep;
int moveGripperUpperDone;
int movePressLowerStep;
int movePressLowerDone;
int movePressUpperStep;
int movePressUpperDone;
int movePressMiddleStep;
int movePressMiddleDone;
int pickCapStep;
int pickCapDone;
int blockTableStep;
int blockTableDone;
int unblockTableStep;
int unblockTableDone;
int clearTableStep;
int clearTableDone;
int conveyorOff;
int conveyorOn;
int doorLockOff;
int doorLockOn;



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
int n;
int s;
int program;
int transId;
int conn_AKD;
int doMeasurement;
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
char ibufMT[50];

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
void turnTable();
void turnTableFree();

int moveCylinder(int id, const char *input1, int input1_val, const char* input2, int input2_val, const char* output, int output_val, int nextStep);
void moveAkd(const char *akd);
void coreLoop();
void coreLoop2();


void moveGripperLower();
void moveGripperUpper();
void movePressLower();
void movePressUpper();
void movePressMiddle();
void conveyorBelt();
void pickCap();
void blockTable();
void unblockTable();
void tableHome();
void tableHomeFree();
void measurement();
void setup();
void checkOutputs();
int checkCanSize(int nextStep);
void doorLock();
void clearTable();
void resetSafetyDoor();
void resetStopTotal();
void resetPower();
void noPress();
void checkStartStop();
void moveUpper();
void moveMaxUpper();
void checkInCycle();
void initVars();
void prepareSteps();
void checkTableClear();
void releaseCap(int nextStep);
