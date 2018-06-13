#include <modbus.h>  


modbus_t *ctx;
int i;
int nb;
int bb;
int rc;
int tc;
int connectiOn;
 
uint16_t regs[10];

uint16_t regsSmall[10];
uint16_t regsMedium[10];
uint16_t regsLarge[10];


void initComm();
void initMain();


/*
void errorCheck();
*/
