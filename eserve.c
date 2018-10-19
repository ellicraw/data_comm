#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

// incase of error
void error(const char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[]) 
{
    int sockfd, newsockfd, portno; // file descriptor, new file descriptor, port number
    char *buffer, *cformat, *export_file;
    unsigned int clilen; 
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    // make sure port number is provided
    if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     // error if opening socket
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr)); 
     portno = atoi(argv[1]); // get port number
     serv_addr.sin_family = AF_INET; 
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     
    // accept info from server 
    while(1) {
        clilen = sizeof(cli_addr);
        if (newsockfd == accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen) < 0) {}
    }

    
        printf("The file was received successfully\n");
	    printf("The new file created is sample_receive.txt\n");
 
     close(sockfd);
     return 0; 
}