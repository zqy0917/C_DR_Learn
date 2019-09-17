//
//  PositionOperate.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/21.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "PositionOperate.h"

#define MaxNum 100
static void swip(int A[], int i, int j){
    // 需注意 i 与 j 不可同
    A[i] = A[i] ^ A[j];
    A[j] = A[j] ^ A[i];
    A[i] = A[i] ^ A[j];
}

static void Quick_Sort(int A[], int n){
    int Queue1[MaxNum],Queue2[MaxNum],front=-1,rear=-1,i,j,s,t;
    Queue1[++rear] = 0;
    Queue2[rear] = n-1;
    while (rear > front) {
        s = Queue1[++front];
        t = Queue2[front];
        i = s+1;
        j = t;
        while (1) {
            while (i <= t && A[i] <= A[s]) {
                i++;
            }
            while (j >= s && A[j] > A[s]) {
                j--;
            }
            if (i < j) {
                swip(A, i, j);
            }else{
                break;
            }
        }
        if (s != j) {
            swip(A, s, j);
        }
        if (j-1 > s) {
            Queue1[++rear] = s;
            Queue2[rear] = j-1;
        }
        if (j+1 < t) {
            Queue1[++rear] = j+1;
            Queue2[rear] = t;
        }
    }
}

static void PrintArray(int A[], int n){
    int i;
    for (i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}


void print_bin(unsigned short n)
{
    int l = sizeof(n)*8;//总位数。
    int i;
    for(i = l-1;i>=0; i --){
        printf("%d", (n&(1<<i)) != 0);
    }
    printf("\n");
}

static void Examples(){
    const int n = 10;
    int A[n] = {4, 5, 1, 3, 7, 9, 2, 10, 6, 8};
    Quick_Sort(A, n);
    PrintArray(A, n);
    uint8_t aaa = 64;
    aaa <<= 1;
    print_bin(aaa);
    printf("aaa: %d \n", aaa);
}

static void Practice1(){
    unsigned short a,b,c=0;
    a = 217;
    print_bin(a);
    b = a >> 4;
    b &= ~(~c<<4);
    print_bin(b);
}

static void Practice2(){
    unsigned short a,b,n=3;
    a = 15787;
    print_bin(a);
    b = a<<(16-n);
    a >>= n;
    a |= b;
    print_bin(a);
}

int PosOperateExamplesMain(int argc, char *argv[]){
    printf("Hello Position Operate !!!\n");
    
//    Examples();
//    Practice1();
    Practice2();
    
    
    
    return 0;
}
