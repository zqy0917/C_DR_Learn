//
//  BasicOperatOrderStack.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/6/21.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "BasicOperatOrderStack.h"
#include <stdlib.h>

#define M 1000

typedef struct Elem{
    int num;
}SElemType, *SElem;
#define SIZEELEM sizeof(SElemType)

SElemType STACK[M];
int top;

// 初始化顺序栈
void INITALS(int *top){
    *top = -1;
}

// 判空
int ISEMPTYS(int top){
    return top == -1;
}

// 判满
int FULLS(int top){
    return top == M-1;
}

int GETTOPS(SElemType STACK[], int top, SElem *item){
    if (ISEMPTYS(top)) {
        return 0;
    }else{
        *item = &STACK[top];
        return 1;
    }
}

int PUSH(SElemType STACK[], int *top, SElem item){
    if (FULLS(*top)) {
        return 0;/* 栈溢出a */
    }else{
        STACK[++(*top)] = *item;
        return 1;
    }
}

int POP(SElemType STACK[], int *top, SElem *item){
    if (ISEMPTYS(*top)) {
        return 0;
    }else{
        if (item) {
            *item = &STACK[*top];
        }
        (*top)--;
        return 1;
    }
}

SElem GETSELEM(int n){
    SElem it = malloc(SIZEELEM);
    it->num = n;
    return it;
}

void PRINTSTACK(SElemType STACK[], int top){
    printf("开始从栈顶遍历栈\n");
    int i;
    for (i=top; i>=0; i--) {
        printf("num: %d \n", STACK[i].num);
    }
}

void OrderStackMain(int argc, char *argv[]){
    printf("Hello Stack & Queue \n");
    INITALS(&top);
    int i;
    for (i=1; i<=10; i++) {
        SElem it = GETSELEM(i);
        PUSH(STACK, &top, it);
    }
    SElem itm;
    POP(STACK, &top, &itm);
    printf("pop 元素：%d \n", itm->num);
    GETTOPS(STACK, top, &itm);
    printf("栈顶 元素：%d \n", itm->num);
    PRINTSTACK(STACK, top);
}
