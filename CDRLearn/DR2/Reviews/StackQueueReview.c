//
//  StackQueueReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/8.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "StackQueueReview.h"
#include <stdlib.h>

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

void StackQueueReviewMain(int argc, char *argv[]){
    printf("Stack Queue review \n");
    LinearStackPractice();
}
