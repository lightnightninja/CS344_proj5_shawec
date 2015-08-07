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

    long start = 0;
    long end;
    long sum = 0;
    long t;
    long temp;
    long ops;
    double seconds;


    printf("Please enter an integer: ");
    scanf("%li", &end);

    t = clock();
    for (long i = 1; i < TEST_OPS; i++) {

        temp = TEST_OPS % i;
        if (temp == 100) {
            temp = 1;
            printf("I'm in here for some reason\n");
        }
    }
    t = clock() - t;

    seconds = (double)t/(double)CLOCKS_PER_SEC;
    seconds = 1.0 / seconds;
    printf("Seconds = %lf\n", seconds);
    ops = 15 * seconds * TEST_OPS;

    printf("Time taken for %i operations: %lf\nIt would take %lu ops for 15 seconds of work.\n", TEST_OPS, (double)t/(double)CLOCKS_PER_SEC, ops);

    t = clock();
    for (long i = 1; i < ops; i++) {

        temp = ops % i;
        if (temp == 100) {
            temp = 1;
            printf("I'm in here for some reason\n");
        }
    }
    t = clock() - t;
    seconds = (double)t/(double)CLOCKS_PER_SEC;
    printf("Time taken for %lu operations: %lf\n", ops, seconds);

    for (long i = start; i < end; i++) {
        for (long j = 1; j < i; j++) {
            if (i % j == 0) {
                sum += j;
            }
        }
        if (sum == i) {
            printf("%li, is a perfect number.\n", i);
        }
        sum = 0;
    }
}
