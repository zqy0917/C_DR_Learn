//
//  StackQueuePractice.c
//  CDRLearn
//
//  Created by Zqy on 19/6/22.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "StackQueuePractice.h"

const int M = 1000000;

// 堆栈编写非递归算法，十进制转 r 进制（2<=r<=9）
static void CONVERT(int num, int r){
    int STACK[M], top=-1;
    while (num != 0) {
        STACK[++top] = num%r;
        num /= r;
    }
    while (top >= 0) {
        printf("%d", STACK[top--]);
    }
    printf("\n");
    
}

static void practice1(){
    int num = 10;
    CONVERT(num, 5);
}

int FUNCTION(int n){
    int STACK[M], top=-1, sum=1;
    while (n > 0) {
        STACK[++top] = n;
        n /= 2;
    }
    while (top >= 0) {
        sum *= STACK[top--];
    }
    return sum;
}

static void practice2(){
    int sum = FUNCTION(5);
    printf("函数值：%d \n", sum);
}

// Ackerman 函数（递归）
static int ACKRecursion(int m, int n){
    if (m == 0) {
        return n+1;
    }else if (m != 0 && n == 0) {
        return ACKRecursion(m-1, 1);
    }else if (m != 0 && n != 0) {
        return ACKRecursion(m-1, ACKRecursion(m, n-1));
    }
    return 0;
}

// Ackerman 函数（非递归）
static int ACKNORecursion(int m, int n){
    int STACK[M], top=-1;
    do {
        if (m == 0) {
            n++;
            if (top >= 0) {
                m = STACK[top];
            }
            top--;
        }else if (m != 0 && n == 0){
            m--;
            n = 1;
        }else if (m != 0 && n != 0){
            STACK[++top] = m-1;
            n--;
        }
    } while (top >= -1);
    return n;
}


static void practice3(){
    int m=2,n=30,res;
    res = ACKRecursion(m, n);
    printf("Ackerman 递归函数值：%d \n", res);
    res = ACKNORecursion(m, n);
    printf("Ackerman 非递归函数值：%d \n", res);
}

void SQPracticeMain(int argc, char *argv[]){
//    practice1();
//    practice2();
    practice3();
}














