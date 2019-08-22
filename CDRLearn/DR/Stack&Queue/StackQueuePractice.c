//
//  StackQueuePractice.c
//  CDRLearn
//
//  Created by Zqy on 19/6/22.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "StackQueuePractice.h"
#include <stdlib.h>

const int M = 1000000;

typedef struct Elem{
    int n;
    int org;
    int help;
    int tar;
    int via;
}SElemType, *SElem;
#define ELEMLEN sizeof(SElemType)

typedef struct node{
    SElem data;
    struct node *link;
}STNode, *STLink;
#define STLINKLEN sizeof(STNode)

typedef struct QElem{
    int num;
}QElemType, *QElem;
#define SIZEELEM sizeof(QElemType)

typedef struct qnode{
    QElem data;
    struct qnode *link;
}QNode, *QLink;
#define SIZEQNODE sizeof(QNode)

typedef struct stnode{
    int data;
    struct stnode *link;
}SNode, *SLink;
#define SIZESNODE sizeof(SNode)

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

// 链接对栈十进制num转r进制
static void JinzhiTransform(int num, int r){
    SLink top=NULL, k=NULL;
    while (num > 0) {
        k = malloc(STLINKLEN);
        k->data = num % r;
        k->link = NULL;
        k->link = top;
        top = k;
        num /= r;
    }
    while (top != NULL) {
        printf("%d", top->data);
        k = top;
        top = top->link;
        free(k);
    }
    printf("\n");
}

static void practice1(){
    int num = 19950823;
    JinzhiTransform(num, 8);
}

int Function2(int n){
    int STACK[M], top=-1, res=1;
    STACK[++top] = n;
    while (top >= 0) {
        if (n/2 != 0) {
            STACK[++top] = n/2;
            n /= 2;
        }else{
            res *= STACK[top--];
        }
    }
    return res;
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
    int sum = Function2(59);
    printf("函数值：%d \n", sum);
}

static int ACKRecursion2(int m, int n){
    int STACK[M], top=-1;
    STACK[++top] = m;
    while (top >= 0) {
        if (m == 0) {
            n += 1;
            m = STACK[top--];
        }else{
            if (n == 0) {
                m--;
                n = 1;
            }else{
                STACK[++top] = m-1;
                n--;
            }
        }
    }
    return n;
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
    res = ACKRecursion2(m, n);
    printf("Ackerman 非递归函数值：%d \n", res);
}

int Gcd2(int m, int n){
    int tmp;
    while (1) {
        if (m < 0) {
            tmp = m;
            m = n;
            n = tmp;
        }else{
            if (n == 0) {
                n = m;
                break;
            }else{
                tmp = m % n;
                m = n;
                n = tmp;
            }
        }
    }
    return n;
}

// 非递归编写m，n最大公约数
int GCD(int m, int n){
    int t;
    do {
        if (m<n) {
            t = n;
            n = m;
            m = t;
        }else if (n == 0) {
            break;
        }else{
            t = n;
            n = m%n;
            m = t;
        }
    } while (n != 0);
    return m;
}

static void practice4(){
    printf("Hello 6.23 \n");
    int t = GCD(72,64);
    printf("公约数：%d \n", t);
    
}

int ChectBacket(char *s){
    int STACK[M], top=-1;
    while (*s != '@') {
        if (*s == '(') {
            STACK[++top] = '(';
        }else if (*s == ')') {
            if (top < 0) {
                return 0;
            }else{
                top--;
            }
        }
        s++;
    }
    return top == -1;
}

static void practice5(){
    char *e = "(1+2*3+(4)-6-5*9+10)@";
    int b = ChectBacket(e);
    printf("合法性：%d \n", b);
}

// 汉诺塔(递归)
int aaa = 0;
void MOVE(int n, int org, int tar){
    ++aaa;
    char c=org+'A',t=tar+'A';
    printf("将第 %d 个盘子从：%c, 挪到：%c \n", n, c, t);
}

static void INITIALSLINK(STLink *top){
    *top = NULL;
}

static int EMPTYSLINK(STLink top){
    return top == NULL;
}

static int GETTOPSLINK(STLink top, SElem *item){
    if(EMPTYSLINK(top)){
        return 0;
    }else{
        *item = top->data;
        return 1;
    }
}

static int PUSHLINK(STLink *top, SElem item){
    STLink p;
    if (!(p=malloc(STLINKLEN))) {
        return 0;
    }else{
        p->data = item;
        p->link = *top;
        *top = p;
        return 1;
    }
}

static int POPLINK(STLink *top, SElem *item){
    STLink p;
    if (EMPTYSLINK(*top)) {
        return 0;
    }else{
        p = *top;
        if (item != NULL) {
            *item = p->data;
        }
        *top = (*top)->link;
        free(p);
        return 1;
    }
}

static SElem GETSELEM(int n, int org, int help, int tar, int via){
    SElem it = malloc(ELEMLEN);
    it->n = n;
    it->org = org;
    it->help = help;
    it->tar = tar;
    it->via = via;
    return it;
}

static void Hanoi(int n, int org, int help, int tar){
    if (n == 1) {
        MOVE(1, org, tar);
    }else{
        Hanoi(n-1, org, tar, help);
        MOVE(n, org, tar);
        Hanoi(n-1, help, org, tar);
    }
}

// 汉诺塔 非递归 🔥🔥🔥
static void Hanoi2(int n, int org, int help, int tar){
    
    STLink top;
    INITIALSLINK(&top);
    SElem it, item;
    it = GETSELEM(n, org, help, tar, 0);
    PUSHLINK(&top, it);
    int a=1;
    
    while (!EMPTYSLINK(top)) {
        GETTOPSLINK(top, &it);
        if (a == 1) {
            POPLINK(&top, NULL);
            a = 0;
        }
        if (it->n == 1 || it->via == 1) {
            MOVE(it->n, it->org, it->tar);
            POPLINK(&top, NULL);
        }else{
            item = GETSELEM(it->n-1, it->help, it->org, it->tar, 0);
            PUSHLINK(&top, item);
            
            item = GETSELEM(it->n, it->org, it->help, it->tar, 1);
            PUSHLINK(&top, item);
            
            item = GETSELEM(it->n-1, it->org, it->tar, it->help, 0);
            PUSHLINK(&top, item);
  
        }
    }
}


static void practice6(){
    Hanoi2(3, 0, 1, 2);
    printf("一共走了 %d 步\n", aaa);
}

static void INITQUEUE(QLink *rear){
    *rear = NULL;
}

static int ADDQ(QLink *rear, QElem it){
    QLink h,t;
    if (!(t = malloc(SIZEQNODE))) {
        return 0;
    }
    t->data = it;
    h = (*rear)->link;
    t->link = h;
    (*rear)->link = t;
    *rear = t;
    return 1;
}

static int DELQ(QLink *rear, QElem *it){
    if ((*rear)->link == *rear) {
        *it = NULL;
        return 0;
    }
    QLink h,p;
    h = (*rear)->link;
    p = h->link;
    *it = p->data;
    h->link = p->link;
    if (p == *rear) {
        *rear = h;
    }
    free(p);
    return 1;
}

static QElem GETQELEM(int n){
    QElem it = malloc(SIZEELEM);
    it->num = n;
    return it;
}

void PRINTQUEUE(QLink rear){
    if (rear->link == rear) {
        printf("空队列 \n");
        return;
    }
    printf("对头开始打印 \n");
    QLink h = rear->link->link;
    while (h != rear->link ) {
        printf("NUM：%d \n", h->data->num);
        h = h->link;
    }
}

void practice7(){
    QLink rear;
    INITQUEUE(&rear);
    QElem it;
    it = GETQELEM(-1);
    QLink head = malloc(SIZEQNODE);
    head->data = it;
    head->link = head;
    rear = head;
    for (int i=1; i<=10; i++) {
        it = GETQELEM(i);
        printf("%d 入队列 \n", it->num);
        ADDQ(&rear, it);
    }
    for (int i=1; i<=9; i++) {
        DELQ(&rear, &it);
        printf("%d 出队列 \n", it->num);
    }
    PRINTQUEUE(rear);
}

void SQPracticeMain(int argc, char *argv[]){
//    practice1();
//    practice2();
//    practice3();
//    practice4();
//    practice5();
//    practice6();
    practice7();
    
}














