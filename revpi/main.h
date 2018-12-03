#include <arpa/inet.h>
#define delay_time  100000
#define delay_time2 100000
#define THOUSAND 1000000L

int skipPick;
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
int n;
int s;
int program;
int transId;
int conn_AKD;
int doMeasurement;
//int doSetup;
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
void turnTable(int** turnTableStep, int** turnTableDone);
void turnTableFree(int** turnTableStep, int** turnTableDone);

int moveCylinder(int id, const char *input1, int input1_val, const char* input2, int input2_val, const char* output, int output_val, int nextStep);
void moveAkd(const char *akd);
void coreLoop(int* step, int* turnTableStep, int*  turnTableDone, int* moveGripperLowerStep, int* moveGripperLowerDone, int* moveGripperUpperStep, int* moveGripperUpperDone, int* movePressLowerStep, int* movePressLowerDone, int* movePressUpperStep, int* movePressUpperDone, int* movePressMiddleStep, int* movePressMiddleDone, int* pickCapStep, int* pickCapDone, int* conveyorOff, int* conveyorOn, int* countTurns, int* blockTableStep, int* blockTableDone, int* unblockTableStep, int* unblockTableDone);
void coreLoop2(int* step, int* turnTableStep, int*  turnTableDone, int* moveGripperLowerStep, int* moveGripperLowerDone, int* moveGripperUpperStep, int* moveGripperUpperDone, int* movePressLowerStep, int* movePressLowerDone, int* movePressUpperStep, int* movePressUpperDone, int* movePressMiddleStep, int* movePressMiddleDone, int* pickCapStep, int* pickCapDone, int* conveyorOff, int* conveyorOn, int* countTurns, int* blockTableStep, int* blockTableDone, int* unblockTableStep, int* unblockTableDone);


void moveGripperLower(int ** moveGripperLowerStep, int **moveGripperLowerDone);
void moveGripperUpper(int ** moveGripperUpperStep, int **moveGripperUpperDone);
void movePressLower(int ** movePressLowerStep, int **movePressLowerDone);
void movePressUpper(int ** movePressUpperStep, int **movePressUpperDone);
void movePressMiddle(int ** movePressMiddleStep, int **movePressMiddleDone);
void conveyorBelt(int ** conveyorOff, int ** conveyorOn);
void pickCap(int**step, int** pickCapStep, int** pickCapDone);
void blockTable(int **blockTableStep, int** blockTableDone);
void unblockTable(int **unblockTableStep, int** unblockTableDone);
void tableHome(int *step);
void measurement();
void setup();
void checkOutputs(int* step);
int checkCanSize(int nextStep);
void doorLock(int * doorLockOff, int * doorLockOn);

void clearTable(int* step, int* turnTableStep, int* turnTableDone, int* clearTableStep, int* clearTableDone, int* pickCapStep, int* pickCapDone, int* moveGripperLowerStep, int* moveGripperLowerDone, int* moveGripperUpperStep, int* moveGripperUpperDone, int* movePressLowerStep, int* movePressLowerDone, int* movePressMiddleStep, int* movePressMiddleDone, int* movePressUpperStep, int* movePressUpperDone, int* unblockTableStep, int* unbockTableDone, int* blockTableStep, int* blockTableDone, int* conveyorOff, int* conveyorOn);

void checkSafetyDoor();
void checkStopTotal();
void checkPower();
