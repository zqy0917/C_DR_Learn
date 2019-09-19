//
//  FuncExample.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/18.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "FuncExample.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
#define PI 3.1415926535897
#define MAXNum 1000
#define NumOf(x) (sizeof(x)/sizeof(x[0]))

double sin(double x);
static double TrangleArea(double a, double b, double ang_c){
    double s;
    s = a*b*sin(ang_c/180.0*PI)/2.0;
    return s;
}

static void move(int n, int from, int to){
    printf("%d from %c, to %c \n", n, 'A'+from, 'A'+to);
}

static void Hanoi(int n, int from, int via, int to){
    if (n == 1) {
        move(n, from, to);
        return;
    }
    Hanoi(n-1, from, to, via);
    move(n, from, to);
    Hanoi(n-1, via, from, to);
}

static void printNum(int n){
    if (n == 0) {
        return;
    }
    if (n % 10 != 0) {
        printf("%d", n%10);
    }
    printNum(n/10);
}

static int covertDigist(int n){
    int i,sum=0;
    while (n > 0) {
        if (n%10 != 0) {
            sum *= 10;
            sum += n%10;
        }
        n /= 10;
    }
    return sum;
}

// 斐波纳西级数
static int jump(int n){
    if (n == 1) {
        return 1;
    }else if (n == 2) {
        return 2;
    }else if (n == 3) {
        return 4;
    }
    return jump(n-1)+jump(n-2)+jump(n-3);
}

static void printPrimes(int n){
    int primes[300]={2},i,j,b,m=1;
    for (i=3; i<n; i+=2) {
        b=1;
        for (j=0; primes[j] <= sqrt(i); j++) {
            if (i % primes[j] == 0) {
                b = 0;
                break;
            }
        }
        if (b) {
            primes[m++] = i;
            printf("%d ", i);
        }
    }
}

static void calculateLocal(){
    int i,char_pos[MAXNum]={0};
    char c;
    for (i=1; (c = getchar()) != EOF; i++) {
        if (islower(c)) {
            if (char_pos[c-'a'] > 0) {
                printf("%c %d:%d \n", c, char_pos[c-'a'], i);
                return;
            }else{
                char_pos[c-'a'] = i;
            }
        }
    }
    printf("0\n");
}

static int isPrime(int n){
    int i,b=1;
    for (i=2; i<=sqrt(n); i++) {
        if (n%i == 0) {
            b=0;
            break;
        }
    }
    return b;
}

static int queue_add(int QUEUE[MAXNum], int head, int *rear, int item){
    int end = (*rear+1)%MAXNum;
    if (end == head) {
        printf("Queue up fill \n");
        return 0;
    }
    QUEUE[end] = item;
    *rear = end;
    return 1;
}

static int queue_del(int QUEUE[MAXNum], int *head, int rear){
    int front = *head;
    if (front == rear) {
        printf("Queue down fill \n");
        return 0;
    }else{
        front = (front+1) % MAXNum;
        return 1;
    }
}

static void bigPrime(int n){
    int j,m,QUEUE[MAXNum]={2,3,5,7},head=0,tail=3,rear=0;
    int digits[] = {1,3,7,9};
    while (--n > 0) {
        for (rear=tail; head<=rear; head++) {
            m = QUEUE[head]*10;
            for (j=0; j<NumOf(digits); j++) {
                if (isPrime(m+digits[j])) {
                    QUEUE[++tail] = m+digits[j];
                }
            }
        }
    }
    for (j=rear+1; j<=tail; j++) {
        printf("%d \n", QUEUE[j]);
    }
}

static void bigPrime2(int n){
    int hd=0,tail=4,QUEUE[MAXNum]={2,3,5,7};
    int digits[] = {1,3,7,9};
    int i,m,len,end=0;
    for (len=1; len<n; len++) {
        for (end=tail; hd<end; hd++) {
            m = QUEUE[hd]*10;
            for (i=0; i<NumOf(digits); i++) {
                if (isPrime(m+digits[i])) {
                    QUEUE[tail++] = m+digits[i];
                }
            }
        }
    }
    for (i=end; i<tail; i++) {
        printf("%d \n", QUEUE[i]);
    }
}

void FuncExampleMain(int argc, char *argv[]){
//    int i,x;
//    for (i=1; i<argc; i++) {
//        printf("%s ", argv[i]);
//    }
//    double s = TrangleArea(1, 2, 60.0);
//    printf("area: %lf \n", s);
//    while (scanf("%d", &x) != EOF) {
//        printf("%d", x);
//    }
//    int n=3;
//    Hanoi(n, 0, 1, 2);
//    printNum(1900);
//    putchar('\n');
//    int m=300,n=2300;
//    m = covertDigist(m);
//    n = covertDigist(n);
//    printf("%d \n", m*n);
//    int n=10;
//    n = jump(n);
//    printf("%d \n", n);
//    printPrimes(100);
//    calculateLocal();
//    bigPrime(8);
//    char *aaa = "ASDFGHJ";
//    char c = 'S';
//    char *ss = strchr(aaa, c);
//    printf("%s \n", ss);
    
}
