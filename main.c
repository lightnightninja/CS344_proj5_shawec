//
//  main.c
//  a5
//
//  Created by Cierra Shawe on 8/5/15.
//  Copyright (c) 2015 Cierra Shawe. All rights reserved.
//

#include <stdio.h>
#include <time.h>

int main() {

    long start = 0;
    long end;
    long sum = 0;
    printf("Please enter an integer: ");
    scanf("%li", &end);

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
