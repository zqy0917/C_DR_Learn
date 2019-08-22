//
//  BasciOperatOrderQueue.c
//  CDRLearn
//
//  Created by Zqy on 19/6/22.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "BasciOperatOrderQueue.h"
#include <stdlib.h>

#define M 100
typedef struct Elem{
    int num;
}QElemType, *QElem;
#define SIZEELEM sizeof(QElemType)

void INITQUEUE(QElemType QUEUE[], int *front, int *rear){
    *front = *rear = -1;
}

int EMPTYQ(int front, int rear){
    return front == rear;
}

int GETQ(QElemType QUEUE[], int front, int rear, QElem *item){
    if (EMPTYQ(front, rear)){
        return 0;
    }else{
        *item = &QUEUE[front+1];
        return 1;
    }
}

int ADDQ(QElemType QUEUE[], int *rear, QElem item){
    if (*rear == M-1) {
        return 0;
    }else{
        QUEUE[++(*rear)] = *item;
        return 1;
    }
}

// 改造成循环队列

void InitCQUEUE(QElemType QUEUE[], int *front, int *rear){
    *front = *rear = 0;
}

int ADDCQ(QElemType QUEUE[], int front, int *rear, QElem item, int QueueLen){
    int r = *rear;
    if ((r+1)%QueueLen == front) {
        printf("队列下溢 \n");
        return 0;
    }else{
        r = (r+1) % QueueLen;
        QUEUE[r] = *item;
        *rear = r;
        return 1;
    }
}

int DELCQ(QElemType QUEUE[], int *front, int rear, QElem *item, int QueueLen){
    if (*front == rear) {
        printf("队列上溢 \n");
        *item = NULL;
        return 0;
    }else{
        *front = ((*front)+1) % QueueLen;
        if (item) {
            *item = &QUEUE[*front];
        }
        return 1;
    }
}

int DELQ(QElemType QUEUE[], int *front, int rear, QElem *item){
    if (EMPTYQ(*front, rear)) {
        *item = NULL;
        return 0;
    }else{
        *item = &QUEUE[++(*front)];
        return 1;
    }
}

static QElem GETSELEM(int n){
    QElem it = malloc(SIZEELEM);
    it->num = n;
    return it;
}
static void PRINTQUEUE(QElemType QUEUE[], int front, int rear){
    printf("从队头开始打印 \n");
    for (int i=front+1; i<=rear; i++) {
        printf("num: %d \n", QUEUE[i].num);
    }
}

static void PRINTCQUEUE(QElemType QUEUE[], int front, int rear, int queueLen){
    printf("从队头开始打印 \n");
    for (int i=front+1; i!=rear+1; i++) {
        printf("num: %d \n", QUEUE[i].num);
        if (i == queueLen-1) {
            i = -1;
        }
    }
}

void OrderQueueMain(int argc, char *argv[]){
//    QElemType QUEUE[M];
//    int front,rear;
//    INITQUEUE(QUEUE, &front, &rear);
//    int i;
//    for (i=1; i<=10; i++) {
//        QElem it = GETSELEM(i);
//        ADDQ(QUEUE, &rear, it);
//    }
//    QElem itm;
//    DELQ(QUEUE, &front, rear, &itm);
//    printf("出队列：%d \n", itm->num);
//    GETQ(QUEUE, front, rear, &itm);
//    printf("对头元素：%d \n", itm->num);
//    PRINTQUEUE(QUEUE, front, rear);
    const int queueLen = 10;
    QElemType QUEUE[queueLen];
    int front,rear;
    InitCQUEUE(QUEUE, &front, &rear);
    int i;
    for (i=1; i<=queueLen-1; i++) {
        QElem it = GETSELEM(i);
        ADDCQ(QUEUE, front, &rear, it, queueLen);
    }
    DELCQ(QUEUE, &front, rear, NULL, queueLen);
    DELCQ(QUEUE, &front, rear, NULL, queueLen);
    QElem it = GETSELEM(-100);
    ADDCQ(QUEUE, front, &rear, it, queueLen);
    ADDCQ(QUEUE, front, &rear, it, queueLen);
    ADDCQ(QUEUE, front, &rear, it, queueLen);
    DELCQ(QUEUE, &front, rear, NULL, queueLen);
    ADDCQ(QUEUE, front, &rear, it, queueLen);
//    ADDCQ(QUEUE, front, &rear, it, queueLen);
    PRINTCQUEUE(QUEUE, front, rear, queueLen);
}






