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
    long end = 1;
    long sum = 0;
    long t;
    long temp;
    long ops;
    long random;
    long counter; //used for counting the ops in
    double seconds;


    t = clock();
    for (long i = TEST_OPS; i <= TEST_OPS; i++) {
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

    seconds = (double)t/(double)CLOCKS_PER_SEC;
    seconds = 1.0 / seconds;
    ops = 15 * seconds * TEST_OPS;

    printf("Time taken for %i operations: %lf\nIt would take %lu ops for 15 seconds of work.\n", TEST_OPS, (double)t/(double)CLOCKS_PER_SEC, ops);

    //random number used to reduce compiler optimization,
    random = rand() % TEST_OPS;
    start = random;
    end = start;
    temp = end;
    //get random up to the sameish number as ops, aka find out how much work to dish
    for (long i = random; ((i >> 1) + temp) < ops; i++, ++counter) {
        //this bit shift is supposed to check for rounding, always less
        temp += i;
    }
    ops = temp; //setting it so we have the correct number of ops we should be doing
    end += counter;

    printf("start = %li\nend = %li\n", start, end);
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
    printf("Numbers range checked: %li - %li, doing %li million operations per second.\n", start, end, (long)(ops/seconds + 0.5)/1000000);


//    for (long i = 1; i < ops; i++) {
//
//        temp = ops % i;
//        if (temp == 0) {
//            temp = 1;
//        }
//    }




}
