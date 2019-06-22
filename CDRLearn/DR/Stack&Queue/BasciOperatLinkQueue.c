//
//  BasciOperatLinkQueue.c
//  CDRLearn
//
//  Created by Zqy on 19/6/22.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "BasciOperatLinkQueue.h"
#include <stdlib.h>

typedef struct Elem{
    int num;
}QElemType, *QElem;
#define SIZEELEM sizeof(QElemType)

typedef struct node{
    QElem data;
    struct node *link;
}QNode, *QLink;
#define SIZEQNODE sizeof(QNode)

void INITIALQLINK(QLink *front, QLink *rear){
    *front = *rear = NULL;
}

int EMPTYQLINK(QLink front){
    return front == NULL;
}

int GETLINKQ(QLink front, QElem *item){
    if (EMPTYQLINK(front)) {
        *item = NULL;
        return 0;
    }else{
        *item = front->data;
        return 1;
    }
}

int ADDLINKQ(QLink *front, QLink *rear, QElem item){
    QLink node;
    if (!(node = malloc(SIZEQNODE))) {
        return 0;
    }else{
        node->data = item;
        node->link = NULL;
        if (*front == NULL) {
            *front = node;
        }else{
            (*rear)->link = node;
        }
        *rear = node;
        return 1;
    }
}

int DELLINKQ(QLink *front, QLink rear, QElem *item){
    if (EMPTYQLINK(*front)) {
        *item = NULL;
        return 0;
    }
    QLink p;
    p = *front;
    *item = (*front)->data;
    *front = (*front)->link;
    free(p);
    return 1;
}

void DESLINKQ(QLink *front, QLink *rear){
    while (*front) {
        *rear = (*front)->link;
        free(*front);
        *front = *rear;
    }
}

static QElem GETSELEM(int n){
    QElem it = malloc(SIZEELEM);
    it->num = n;
    return it;
}
static void PRINTQUEUE(QLink front){
    printf("从队头开始打印 \n");
    while (front != NULL) {
        printf("num: %d \n",front->data->num);
        front = front->link;
    }
}

void LinkQueueMain(int argc, char *argv[]){
    QLink front,rear;
    INITIALQLINK(&front, &rear);
    int i;
    for (i=1; i<=10; i++) {
        QElem it = GETSELEM(i);
        ADDLINKQ(&front, &rear, it);
    }
    QElem itm;
    DELLINKQ(&front, rear, &itm);
    printf("出队列元素：%d \n", itm->num);
    GETLINKQ(front, &itm);
    printf("队列首元素：%d \n", itm->num);
    PRINTQUEUE(front);
}






