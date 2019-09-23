//
//  PointPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/20.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "PointPractice.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define MaxNum 100000

static void CovertStr(char *s, char *t){
    char *sub,*first,*last,c;
    if ((sub = strstr(s, t)) == NULL) {
        printf("%s\n", s);
        return;
    }
    first = sub;
    last = sub+strlen(t)-1;
    while (first < last) {
        c = *first;
        *first = *last;
        *last = c;
        first++;
        last--;
    }
}

static void SubStrCovert(){
    char s[MaxNum],t[MaxNum];
    scanf("%s %s", s ,t);
    CovertStr(s, t);
    puts(s);
}

static int risingSort(const void *x1, const void *x2){
    return (*(double *)x1 > *(double *)x2) ? 1 : -1;
}

static int fallingSort(const void *x1, const void *x2){
    return (*(double *)x1 < *(double *)x2) ? 1 : -1;
}

static void qsortPractice(){
    const int n=10;
    int i;
    double A[n] = {0.9,0.7,0.8,0.1,0.1,0.3,0.2,0.5,0.4,1.0};
    qsort(A, n, sizeof(double), risingSort);
    for (i=0; i<n; i++) {
        printf("%.1lf ", A[i]);
    }
    putchar('\n');
    qsort(A, n, sizeof(double), fallingSort);
    for (i=0; i<n; i++) {
        printf("%.1lf ", A[i]);
    }
    putchar('\n');
}

static void PrintSortArr(int data[][3], int n){
    int i;
    for (i=0; i<n; i++) {
        printf("%d:%d ", data[i][2], data[i][0]);
    }
    putchar('\n');
}

static int riseSort(const void *x1, const void *x2){
    int xx1 = ((int *)x1)[0];
    int xx2 = ((int *)x2)[0];
    if (xx1 == xx2) {
        return 0;
    }
    return (xx1 > xx2) ? 1 : -1;
}

static int initiationSort(const void *x1, const void *x2){
    int xx1 = ((int *)x1)[1];
    int xx2 = ((int *)x2)[1];
    if (xx1 == xx2) {
        return 0;
    }
    return (xx1 > xx2) ? 1 : -1;
}

static void sortInputNumber(){
    const int n=7;
    int data[n][3],i,k=1;
    for (i=0; i<n; i++) {
        scanf("%d", data[i]);
        data[i][1] = i;
    }
    qsort(data, n, sizeof(data[0]), riseSort);
    data[0][2] = k++;
    for (i=1; i<n; i++) {
        if (data[i][0] == data[i-1][0]) {
            data[i][2] = k-1;
        }else{
            data[i][2] = k++;
        }
    }
    qsort(data, n, sizeof(data[0]), initiationSort);
    PrintSortArr(data, n);
}

static void init_primes(int primes[], int maxItem, int *n){
    // Create n of prime number
    int i,j,b,k=0;
    primes[k++] = 2;
    for (i=3; i<=maxItem; i+=2) {
        b = 1;
        for (j=0; primes[j]<=sqrt(i); j++) {
            if (i % primes[j] == 0) {
                b = 0;
                break;
            }
        }
        if (b) {
            primes[k++] = i;
        }
    }
    *n = k;
}

static int comp_int(const void *p1, const void *p2){
    return *(int *)p1-*(int *)p2;
}

static void searchPrimeTable(){
    int (*funcPoint)();
    funcPoint = comp_int;
    int primes[MaxNum],maxItem=100000,i,n,key=997;
    init_primes(primes, maxItem, &n);
    for (i=0; i<n; i++) {
        printf("prime: %d\n", primes[i]);
    }
    if (bsearch(&key, primes, n, sizeof(primes[0]), funcPoint) != NULL){
        printf("%d is a prime\n", key);
    }else{
        printf("%d is not a prime\n", key);
    }
}

typedef void (*Callback)(int max);
static void MaxValue(int a, int b, Callback callback){
    int c = a > b ? a : b;
    sleep(3);
    callback(c);
}

static void MaxCallback(int max){
    printf("Max value: %d \n", max);
}

void PointerPracticeMain(int argc, char **argv){
//    if (argc != 3) {
//        fprintf(stderr, "Usage: %s <arg1> <arg2> \n", argv[0]);
//    }
//    SubStrCovert();
//    qsortPractice();
//    sortInputNumber();
//    searchPrimeTable();
    printf("Begin \n");
    MaxValue(9, 8, MaxCallback);
}
