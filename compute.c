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


char* concat(char *s1, char *s2)
{
    char *result = (char *)malloc(strlen(s1)+strlen(s2)+1);//+1 for NULL
    strncpy(result, s1, strlen(s1));
    strcat(result, s2);
    return result;
}

int* compute(int start, int end, int nums[10]){

	return 1;
	
}

int main(){

    /* Stuff for compute */
    srand((unsigned int)time(NULL));
    time_t  s, e;				//used for timing
    long    start   = 0;
    long    end     = 1;		//used to hold the end variable (this will be passed eventually)
    long    sum     = 0;		//holds perfect numbers
    long    temp;				//just holds stuff
    long    ops;				//operations (total)
    long    random;				//holds rand value
    long    counter;			//used for counting the ops in
    long    millops;			//simply for formatting
    double  seconds;
    int     len;
    int     numsFound;			//holds the numbers found for pos in array
    int     pnums[10];          //this is used for
    char   *perfnums;           //just used for storing the nums as string
    char   *perfTemp;           //used to free the old string

    /* Stuff for sockets */
    sockaddr_in serverAddr;
    socklen_t   addr_size;

    int     clientFd;           //holds fd for the client
    char   *JSONstr;            // used for formating
    char    sendl[MAXLINE];     // takes in data
    char    recvl[MAXLINE];
    int     quit       = 0;
    int     try_count  = 0;


    /*Create the socket.*/
    do {
        /* Uses: IP, Stream socket, and TCP to open socketFd*/
        clientFd = socket(PF_INET, SOCK_STREAM, 0);

        /* Configure settings of the server address struct */

        serverAddr.sin_family = AF_INET; /* Address family = Internet */
        serverAddr.sin_port = htons(SERV_PORT); /* Set port number */
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* Set IP address to localhost */
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); /* Set all bits of the padding field to 0 */

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

	ops = 1250000000; //this is just a start number to give it something to do at first 
    while (quit != 1){

		/*******************DEBUG*****************/
		counter = 0;
		random = rand() % 100000000;
		start = random;
		end = start;
		temp = end;

		//get random up to the sameish number as ops, aka find out how much work to dish
		for (long i = random; ((i >> 1) + temp) < ops; i++, ++counter) {
			//this bit shift is supposed to check for rounding, always less
			temp += i;
		}
		ops = temp;
		end += counter;

		//get random up to the sameish number as ops, aka find out how much work to dish
		for (long i = random; ((i >> 1) + temp) < ops; i++, ++counter) {
			//this bit shift is supposed to check for rounding, always less
			temp += i;
		}
		ops = temp;
		end += counter;

		/******************************************/

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
        millops = (long)(ops/seconds + 0.5)/1000000;
        printf("Ops completed   : %lu\n"
               "Time Taken      : %.2lf\n"
               "Range checked   : %li - %li\n"
               "Million ops/sec : %li.\n",
               ops, seconds, start, end, millops);//DEBUG

        ops = (long)((ops/seconds) * 15);//setting up for next loop accounting for changes

        //JSONformat();
        //for (int i = 0; i < 10; i++) {}

        len = snprintf(NULL, MAXLINE, "{\"compute\":{ops:%lu,time:%lf,found:{%s}", ops, seconds, perfnums);
        snprintf(sendl, len, "{\"compute\":{ops:%lu,time:%lf,found:{%s}", ops, seconds, perfnums);
        write(clientFd, sendl, strlen(sendl) + 1);
        printf("Server sent: %s\n",recvl);
        
    }
    /*---- Read the message from the server into the buffer ----*/
    //recv(clientFd, buffer, 1024, 0);

    /*---- Print the received message ----*/
    //printf("Data received: %s", buffer);
    
    return 0;
}