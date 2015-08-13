#define _POSIX_C_SOURCE 200908L

/* All of the libraries I don't feel like sorting through*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>


#define MAXLINE 1028

#define SERV_PORT 4936
#define SERV_PORT_STR "4936"
typedef struct sockaddr_in sockaddr_in; //being a bit lazy here, although it's really not needed



int main(){

    /* Stuff for compute */
    srand((unsigned int)time(NULL));
    time_t  s, e; //used for timing
    long    start   = 0;
    long    end     = 1; //used to hold the end variable (this will be passed eventually)
    long    sum     = 0; //holds perfect numbers
    long    temp; //just holds stuff
    long    ops; //operations (total)
    long    random; //holds rand value
    long    counter; //used for counting the ops in
    long    millops; //simply for formatting
    double  seconds;
    char   *perfnums; //just used for storing the nums as string
    int     pnums[10];      //this is used for

    /* Stuff for sockets */
    sockaddr_in serverAddr;
    socklen_t   addr_size;

    int     clientFd; //holds fd for the client
    char    JSONstr[MAXLINE]; // used for formating
    char    sendl  [MAXLINE]; // takes in data
    char    recvl  [MAXLINE];
    int     quit        = 0;
    int     try_count   = 0;



    do {
        /*---- Create the socket. The three arguments are: ----*/
        /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
        clientFd = socket(PF_INET, SOCK_STREAM, 0);

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
        if(connect(clientFd, (struct sockaddr *) &serverAddr, addr_size) == -1){
            fprintf(stderr, "Couldn't connect.\n");
            try_count++;
            if (try_count == 3) {
                fprintf(stderr, "Failed to connect three times, exiting now.");
                exit(EXIT_FAILURE);
            }
        }

        else
            try_count = 0;
        /* If it isn't */
        if (try_count == 0)
            break;

    } while (try_count < 3);


    while (quit != 1){

        read(clientFd, recvl, MAXLINE);

        memset(&recvl, '\0', MAXLINE);

        if(read(clientFd, recvl, MAXLINE) == 0){
            perror("Something broke...");
            exit(EXIT_FAILURE);
        }

        //JSONparse();
        //compute();
        s = clock();

        for (long i = start; i < end; i++) {
            for (long j = 1; j < i; j++) {
                if (i % j == 0) { //if modding it gives you a 0, diviser
                    sum += j;
                }
            }
            if (sum == i) {
                printf("%li, is a perfect number.\n", i);
            }
            sum = 0;
        }

        e = clock();
        seconds = ((double)s-(double)e)/(double)CLOCKS_PER_SEC;
        printf("Ops completed   : %lu\n"
               "Time Taken      : %.2lf\n"
               "Range checked   : %li - %li\n"
               "Million ops/sec : %li.\n",
               ops, seconds, start, end, (long)(ops/seconds + 0.5)/1000000);//DEBUG

        ops = (long)((ops/seconds) * 15);//setting up for next loop accounting for changes

        //JSONformat();
        snprintf(NULL, MAXLINE, <#const char *restrict, ...#>)
        snprintf(sendl, "{\"compute\":{ops:%lu,time:%lf,found:{%s}", ops, seconds, perfnums);
        write(clientFd, sendl, strlen(sendl) + 1);
        printf("Server sent: %s\n",recvl);
        
    }
    /*---- Read the message from the server into the buffer ----*/
    //recv(clientFd, buffer, 1024, 0);

    /*---- Print the received message ----*/
    //printf("Data received: %s", buffer);
    
    return 0;
}