#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

#define PORTNO 1500

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    int i;
    int count;
    char buffer[256];
    char buffer_request[256];
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.12");
    serv_addr.sin_port = htons(PORTNO);
    serv_addr.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
      error("ERROR opening socket");
    }
   
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {   
      error("ERROR connecting");
    }
     
    sprintf(buffer_request, "REQUEST%d\n", i);
     
    while(count < 1000)
    {
      printf("%s\n", buffer_request);
      bzero(buffer,256);
      n = write(sockfd,buffer,strlen(buffer_request));
      if (n < 0) 
      {
	error("ERROR writing to socket");
      }
      bzero(buffer,256);
      n = recv(sockfd, buffer, 3, 0);
       
      if (n < 0) 
      {
	error("ERROR reading from socket");
      }
      //printf(":%s\n", buffer);
      for(i=0; i < 3; i++)
      {
	printf("%d\n", buffer[i]);
      }
      count++;
      sleep(1);
    }
    close(sockfd);
    return 0;
}
