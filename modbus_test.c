#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

int x;
int s;
int transid;

void main()
{
  
  char *ip_adrs;
  struct sockaddr_in server;

  fd_set fds;
  struct timeval tv;

  char obuf_ed[17];
  char ibuf_ed[17];

  char obuf[58];
  char ibuf[56];
  ip_adrs = "192.168.0.13";
  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  server.sin_family = AF_INET;
  server.sin_port = htons(502);
  server.sin_addr.s_addr = inet_addr(ip_adrs);

  
  x = connect(s, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
  printf("X=%d\n",x);

  if(x < 0)
  {
    printf("Connection unsuccessfull\n");
  }
  else
  {
  /*  
    int * intloc9 = (int*)(&obuf[13]);
    int * intloc10 = (int*)(&obuf[17]);
    int * intloc11 = (int*)(&obuf[21]);
    int * intloc12 = (int*)(&obuf[25]);
    int * intloc13 = (int*)(&obuf[29]);
    int * intloc14 = (int*)(&obuf[33]);
    int * intloc15 = (int*)(&obuf[37]);
    int * intloc16 = (int*)(&obuf[41]);
    int * intloc17 = (int*)(&obuf[45]);
    int * intloc18 = (int*)(&obuf[49]);
    */
    memset(obuf, 0, 58);
   
    int * intloc1 = (int*)(&obuf[0]);
    int * intloc2 = (int*)(&obuf[2]);
    int * intloc3 = (int*)(&obuf[4]);
    int * intloc4 = (int*)(&obuf[6]);
    int * intloc5 = (int*)(&obuf[7]);
    int * intloc6 = (int*)(&obuf[8]);
    int * intloc7 = (int*)(&obuf[10]);
    int * intloc8 = (int*)(&obuf[12]);

    int * intloc9 = (int*)(&obuf[16]);
    int * intloc10 = (int*)(&obuf[17]);    
    int * intloc11 = (int*)(&obuf[21]);
    int * intloc12 = (int*)(&obuf[28]);
    int * intloc13 = (int*)(&obuf[29]);
    int * intloc14 = (int*)(&obuf[33]);
    int * intloc15 = (int*)(&obuf[40]);
    int * intloc16 = (int*)(&obuf[44]);
    int * intloc17 = (int*)(&obuf[48]);
    int * intloc18 = (int*)(&obuf[52]);

    * intloc1 = htons(1);   
    * intloc2 = htons(0);
    * intloc3 = htons(47);
    * intloc4 = 1;
    * intloc5 = 16;
    * intloc6 = htons(8192);
    * intloc7 = htons(20);
    * intloc8 = 40;
    * intloc9 = 0;             /*mtnum*/    
    * intloc10 = htonl(1000);  /*pos - (desired value must be multiplied by 10000) */
    * intloc11 = htonl(1000);  /*vel -  (desired value must be multiplied by 10000) */
    * intloc12 = 16;           /*cntl*/
    * intloc13 = htonl(1000);  /*acc - (desired value must be multiplied by 10000) */  
    * intloc14 = htonl(1000);  /*dec - (desired value must be multiplied by 10000) */  
    * intloc15 = 1;            /*next*/
    * intloc16 = 0;            /*delay*/
    * intloc17 = 1;            /*mtset*/
    * intloc18 = 1;            /*drvsav*/

    FD_ZERO(&fds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    
    x = select(32, NULL, &fds, NULL, &tv);
    x = send(s, obuf, 53, 0);
    printf("Message Sent!\n");
    FD_SET(s, &fds);
    x = select(32, &fds, NULL, NULL, &tv);
    x = recv(s, ibuf, 50 , 0);
    
    /*
    int * intloc1_ed = (int*)(&obuf_ed[0]);
    int * intloc2_ed = (int*)(&obuf_ed[2]);
    int * intloc3_ed = (int*)(&obuf_ed[4]);
    int * intloc4_ed = (int*)(&obuf_ed[6]);
    int * intloc5_ed = (int*)(&obuf_ed[7]);
    int * intloc6_ed = (int*)(&obuf_ed[8]);
    int * intloc7_ed = (int*)(&obuf_ed[10]);
    int * intloc8_ed = (int*)(&obuf_ed[12]);
    int * intloc9_ed = (int*)(&obuf_ed[13]);
            
    * intloc1_ed = htons(0);  
    * intloc2_ed = htons(0);
    * intloc3_ed = htons(11);
    * intloc4_ed = 1;
    * intloc5_ed = 16;
    * intloc6_ed = htons(254);
    * intloc7_ed = htons(2);
    * intloc8_ed = 4;
    * intloc9_ed = htonl(1);
            
    FD_ZERO(&fds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
            
    x = select(32, NULL, &fds, NULL, &tv);
    x = send(s, obuf_ed, 17, 0);
    printf("OBUF: %s", obuf_ed);           
    FD_SET(s, &fds);
    x = select(32, &fds, NULL, NULL, &tv);
    x = recv(s, ibuf_ed, 50 , 0);
    transid++;        
            
    printf("Drive Enabled\n" );
   */

    close(s);
    printf("Connection  successfull\n");
  }
}
