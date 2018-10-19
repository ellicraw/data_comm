#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>

void error(const char *errorMessage)
{
    perror(errorMessage);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, write_byte, portno;
    long size;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char *buffer, *cformat, *export_file;
    FILE *fileptr;

    if (argc != 5) {
        fprintf(stderr, "ERROR, There are too little or too many arguments");
    }

    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    // get port number and establish socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
        error("ERRORm, opening socket\n");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    // make a connection to the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR, connecting");
  
        bzero(buffer,512);
        
    //get file path  
    const char* file_path = argv[3]; 

    // get format of file
    uint8_t format = atoi(argv[4]);
    if (format < 0 || format > 3) {
        fprintf(stderr,"ERROR, the format is out of range\n");
        exit(1);
    }

    // send file format
    cformat = malloc(sizeof(char));
    strcpy(cformat, argv[4]);
    write(sockfd, cformat, sizeof(cformat));

    // send size of file
    size = ftell(fileptr);
    write(sockfd, &size, sizeof(size));

    // open file 
    fileptr = fopen(file_path,"r");
    
    //check if file is NULL
    if (fileptr != NULL) {
        fprintf(stderr,"ERROR, the file is incorrect\n");
    }

    //send file name
    export_file = malloc(100 * sizeof(char));
    strcpy(export_file, argv[5]);
    write(sockfd, export_file, sizeof(export_file));
    
    // send the file
    buffer = malloc(size * sizeof(char));
    fread(buffer, size, 1, fileptr); // read file into the buffer
    void *data = buffer;
    while (size > 0) {
        write_byte = write(sockfd, data, size);
        size -= write_byte;
        data += write_byte;
    }

	printf("The file was sent successfully\n");
    
    close(sockfd);
    return 0;
}