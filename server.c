/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, portno, newsockfd;
     socklen_t clilen;
     char buffer[256];
	 
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
                error("ERROR on binding");
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
			error("ERROR on accept");
		//cli_addr.sin_addr
		printf("IP address is: %d\n", inet_ntoa(cli_addr.sin_addr));
	  while(1) {
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		if(strncmp(buffer,"q",1)==0) {
			close(newsockfd);
	 	break;
		}
		int pinakas[3][3]={{0,1,-1},
		{-1,0,1},
		{1,-1,0}};
		int cpu=rand()%3;
		int paixths;
		if(strncmp(buffer,"petra",5)==0) {
    	 	paixths=0;
		 } else if(strncmp(buffer,"psalidi",7)==0) {
    	 	paixths=1;
		 } else if(strncmp(buffer,"xarti",5)==0) {
    	 	paixths=2;
		 }
		char string[5];
		sprintf(string,"%d",cpu);
		n = write(newsockfd,string,strlen(string));
		if (n < 0) error("ERROR writing to socket");
						
			printf("Epaixe\n %s",buffer);
		   	switch(pinakas[cpu][paixths])
		   	{
			case 0:
				n = write(newsockfd,"\nIsopalia\n",strlen("\nIsopalia\n"));
					if (n < 0) error("ERROR writing to socket");
				break;
			case 1:
				 n = write(newsockfd,"\nExases\n",strlen("\nExases\n"));
					if (n < 0) error("ERROR writing to socket");
				break;
			case -1:
				n = write(newsockfd,"\nKerdises\n",strlen("\nKerdises\n"));
					if (n < 0) error("ERROR writing to socket");
				break;
		        }
		}
     close(newsockfd);
     close(sockfd);
     return 0; 
}
