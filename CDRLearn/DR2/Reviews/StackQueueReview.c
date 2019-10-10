//
//  StackQueueReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/8.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "StackQueueReview.h"
#include <stdlib.h>
#include <ctype.h>

#define MaxNum 100

typedef struct SItem{
    int data;
    struct SItem *link;
}SItem, *PItem;

static int LinearStackPush(PItem *top, int data){
    PItem it = malloc(sizeof(SItem));
    if (it == NULL) {
        perror("Stack overflow\n");
        return 0;
    }
    it->data = data;
    it->link = NULL;
    if (*top != NULL) {
        it->link = *top;
    }
    *top = it;
    return 1;
}

static int LinearStackPop(PItem *top, PItem *item){
    if (*top == NULL) {
        printf("Empty Stack\n");
        return 0;
    }
    if (item) {
        *item = *top;
    }
    *top = (*top)->link;
    return 1;
}

static void LinearStackPractice(){
    int i,data;
    PItem top = NULL,item;
    for (i=1; i<=10; i++) {
        LinearStackPush(&top, i);
    }
    while((data = LinearStackPop(&top, &item)) != 0){
        printf("%d ", item->data);
    }
}

static void InitinalQueue(PItem *front, PItem *rear){
    *front = *rear = NULL;
}

static int EmptyQueue(PItem front){
    return front == NULL;
}

static int GetFront(PItem front, int *data){
    if (!EmptyQueue(front)) {
        *data = front->data;
        return 1;
    }
    *data = -1;
    return 0;
}

static int AddQueue(PItem *front, PItem *rear, int item){
    PItem p = malloc(sizeof(SItem));
    if (p == NULL) {
        printf("Memory overflow\n");
        return 0;
    }
    p->link = NULL;
    p->data = item;
    if (EmptyQueue(*front)) {
        *front = p;
    }else{
        (*rear)->link = p;
    }
    *rear = p;
    return 1;
}

static int DelQueue(PItem *front, PItem *rear){
    if (EmptyQueue(*front)) {
        return 1;
    }
    PItem r = *front;
    if (*rear == r) {
        *front = *rear = NULL;
    }else{
        *front = r->link;
    }
    free(r);
    return 1;
}

static void LinearQueuePractice(){
    int i,data;
    PItem front,rear;
    InitinalQueue(&front, &rear);
    for (i=1; i<=10; i++) {
        AddQueue(&front, &rear, i);
    }
    while (GetFront(front, &data) == 1){
        printf("Data: %d \n", data);
        DelQueue(&front, &rear);
    }
}

static int GetNumLength(int num){
    if (num == 0) {
        return 0;
    }
    return 1+GetNumLength(num/10);
}

static double Calculate(double a, double b, char operation){
    double res=0;
    if (operation == '+') {
        res = a + b;
    }else if(operation == '-'){
        res = a - b;
    }else if(operation == '*'){
        res = a * b;
    }else if(operation == '/'){
        res = a / b;
    }
    return res;
}

// A+(B-C/D)*E
// ABCD/-E*+
void SuffixExpressionCalculate(){
    char buf[BUFSIZ],*c;
    double STACK[MaxNum];
    int top=-1,tmp,count;
    fgets(buf, BUFSIZ, stdin);
    c = buf;
    while (*c != '\0' && *c != '\n'){
        if (*c == ' ') {
            c++;
            continue;
        }
        if (isdigit(*c)) {
            tmp = atoi(c);
            STACK[++top] = tmp;
            count = GetNumLength(tmp);
            c += count;
        }else{
            tmp = Calculate(STACK[top-1], STACK[top], *c);
            top -= 2;
            STACK[++top] = tmp;
            c++;
        }
    }
    printf("Result: %.4lf\n", STACK[top]);
}

void StackQueueReviewMain(int argc, char *argv[]){
    printf("Stack Queue review \n");
    // LinearStackPractice();
    // LinearQueuePractice();
    // SuffixExpressionCalculate();
    
}
