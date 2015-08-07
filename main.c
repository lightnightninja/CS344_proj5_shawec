//
//  main.c
//  a5
//
//  Created by Cierra Shawe on 8/5/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TEST_OPS 10000000



int main() {

    srand((unsigned int)time(NULL));
    long start = 0;
    long end = 1; //used to hold the end variable (this will be passed eventually)
    long sum = 0; //holds perfect numbers
    long t; //used for timing
    long temp; //just holds stuff
    long ops; //operations (total)
    long random; //holds rand value
    long counter; //used for counting the ops in
    double seconds;

    random = rand() % 2;
    t = clock();
    for (int i = 0; i < 10; i++) {
        random += rand() % 5;
    }
    t = clock() -t;


    t = clock();
    printf("t = %li\n", t);
    for (long i = TEST_OPS+random; i <= TEST_OPS+random; i++) {
        for (long j = 1; j < i; j++) {
            if (i % j == 0) { //if modding it gives you a 0, diviser
                temp += j;
            }
        }
        if (temp == i) {
            printf("%li, is a perfect number.\n", i);
        }
        sum = 0;
    }
    t = clock() - t;
    printf("t = %li\n", t);

    seconds = 1.0 /((double)t/(double)CLOCKS_PER_SEC);
    ops = 15 * seconds * (TEST_OPS+random);

    printf("Time taken for %i operations: %.4lf seconds\nIt would take %lu ops for 15 seconds of work.\n", TEST_OPS, (double)t/(double)CLOCKS_PER_SEC, ops);


    for (int i = 0; i < 5; i++) {


        counter = 0;
        random = rand() % TEST_OPS;
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

        printf("\n\nstart = %li\nend = %li\n", start, end);
        //start timing how long it takes
        t = clock();

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

        t = clock() - t;
        seconds = (double)t/(double)CLOCKS_PER_SEC;
        printf("Time taken for %lu operations: %lf\n", ops, seconds);
        printf("Numbers range checked: %li - %li, doing %.2li million operations per second.\n", start, end, (long)(ops/seconds + 0.5)/1000000);



        ops = (long)((ops/seconds) * 15);//setting up for next loop accounting for changes
    }

}