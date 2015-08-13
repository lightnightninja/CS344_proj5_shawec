#define _POSIX_C_SOURCE 200908L

#include <sys/types.h>  // basic system data types
#include <sys/socket.h> // basic socket definitions
#include <sys/time.h>   // timeval{} for select()
#include <sys/un.h>
#include <time.h>       // timespec{} for pselect()
#include <netinet/in.h> // sockaddr_in{} and other Internet defns
#include <arpa/inet.h>  // inet(3) functions
#include <errno.h>
#include <fcntl.h>      // for nonblocking
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   // for S_xxx file mode constants
#include <sys/uio.h>    // for iovec{} and readv/writev
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 1028

#define SERV_PORT 4936
#define SERV_PORT_STR "4936"

/****************** CLIENT CODE ****************/

int main(){
    int clientSocket;
    char buffer[BUFFSIZE];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(SERV_PORT);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) == -1)
        fprintf(stderr, "Couldn't connect.\n");

    while(fgets(sendline, MAXLINE, stdin) != NULL){

        memset(&recvline, '\0', MAXLINE);

        write(clientSocket, sendline, strlen(sendline) + 1);

        if(read(clientSocket, recvline, MAXLINE) == 0){
            perror("Something broke");
            exit(-1);
        }
        
        printf("Server sent: %s\n",recvline);
        
    }
    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, buffer, 1024, 0);

    /*---- Print the received message ----*/
    printf("Data received: %s",buffer);   
    
    return 0;
}