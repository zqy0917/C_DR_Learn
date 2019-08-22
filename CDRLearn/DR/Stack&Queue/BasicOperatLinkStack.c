//
//  BasicOperatLinkStack.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/6/21.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "BasicOperatLinkStack.h"
#include <stdlib.h>

typedef struct Elem{
    int num;
    char c;
}SElemType, *SElem;
#define ELEMLEN sizeof(SElemType)

typedef struct node{
    SElem data;
    struct node *link;
}STNode, *STLink;
#define STLINKLEN sizeof(STNode)

static STLink top;

void INITIALSLINK(STLink *top){
    *top = NULL;
}

int EMPTYSLINK(STLink top){
    return top == NULL;
}

int GETTOPSLINK(STLink top, SElem *item){
    if(EMPTYSLINK(top)){
        return 0;
    }else{
        *item = top->data;
        return 1;
    }
}

int PUSHLINK(STLink *top, SElem item){
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

int POPLINK(STLink *top, SElem *item){
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

static SElem GETSELEM(int n){
    SElem it = malloc(ELEMLEN);
    it->num = n;
    return it;
}

static void PRINTSTACK(STLink top){
    printf("开始从栈顶遍历栈\n");
    while (top != NULL) {
        printf("num: %d \n", top->data->num);
        top = top->link;
    }
}

int CHECKCODE(char *fileName){
    STLink topStack;
    INITIALSLINK(&topStack);
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("打开文件失败 \n");
        return 0;
    }
    char ch;
    int b=1;
    while((ch = fgetc(fp))!=-1) {
        SElem it;
        if (ch == '(' || ch == '{') {
            if ((it = malloc(ELEMLEN)) == NULL){/*栈溢出*/
                b=0;break;
            }
            it->c = ch;
            PUSHLINK(&topStack, it);
        }else if (ch == ')' || ch == '}'){
            if (GETTOPSLINK(topStack, &it)){
                if ((ch == ')' && it->c == '(') || ((ch == '}' && it->c == '{'))) {
                    POPLINK(&topStack, NULL);
                }else{
                    b=0;break;
                }
            }else{
                b=0;break;
            }
        }
    }
    if (!EMPTYSLINK(topStack)) {
        b=0;
    }
    return b;
}

int CheckCode(char *fileName){
    STLink topStack;
    INITIALSLINK(&topStack);
    SElem it;
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("打开文件失败 \n");
        return 0;
    }
    char ch;
    while ((ch = fgetc(fp)) != -1) {
        if (ch == '(' || ch == '[' || ch == '{') {
            if ((it = malloc(sizeof(SElem))) == NULL) {
                printf("栈溢出 \n");
                return 0;
            }
            it->c = ch;
            PUSHLINK(&topStack, it);
        }else{
            if (ch == ')' || ch == ']' || ch == '}') {
                GETTOPSLINK(topStack, &it);
                if (EMPTYSLINK(topStack)) {
                    return 0;
                }else if (it->c == '(' && ch == ')') {
                    POPLINK(&topStack, NULL);
                }else if (it->c == '[' && ch == ']') {
                    POPLINK(&topStack, NULL);
                }else if (it->c == '{' && ch == '}') {
                    POPLINK(&topStack, NULL);
                }else{
                    return 0;
                }
            }
        }
    }
    if (!EMPTYSLINK(topStack)) {
        return 0;
    }
    return 1;
}


#define M 100
// 进制转换
void CONVERSION(int num){
    int STACK[M],top=-1;
    do {
        STACK[++top] = num % 8;
        num /= 8;
    } while (num != 0);
    while (top >= 0) {
        printf("%d", STACK[top--]);
    }
    printf("\n");
}

void CONVERSIONLINK(int num){
    STLink p,top=NULL;
    SElem it;
    do {
        p = malloc(STLINKLEN);
        it = GETSELEM(num % 8);
        p->data = it;
        p->link = top;
        top = p;
        num /= 8;
    } while (num != 0);
    while (top != NULL) {
        printf("%d", top->data->num);
        POPLINK(&top, NULL);
    }
    printf("\n");
}

// 递归转非递归
void RECCURRESIVE(int m, int n){
    int STACK[M],top=-1;
    do {
        if (m*n == 0) {
            n = m+n+1;
            if (top >= 0) {
                m = STACK[top];
            }
            top--;
        }else{
            STACK[++top] = m-1;
            n--;
        }
    } while (top >= -1);
    printf("结果：%d \n", n);
}

// 表达式计算 🔥🔥🔥
int EVAL(){
    return 0;
}

#define MaxN 100
#define MaxNM 10000

typedef struct move{
    int row;
    int col;
    int dir;
}MOVE, *MOVE_P;

MOVE_P GETPATH(int row, int col, int dir){
    MOVE_P m = malloc(sizeof(MOVE));
    m->row = row;
    m->col = col;
    m->dir = dir;
    return m;
}

static void CopyArray(int A[][MaxN], int B[][MaxN], int m, int n){
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            B[i][j] = A[i][j];
        }
    }
}

// 迷宫改进版
static void Maze(int B[][MaxN], int m, int n){
    int A[m][MaxN];
    CopyArray(B, A, m, n);
    int direction[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    MOVE_P STACK[MaxNM], curPos;
    int top = -1, row, col, *dir;
    STACK[++top] = GETPATH(1, 1, 0);
    A[1][1] = 2;
    while (top >= 0) {
        curPos = STACK[top];
        row = curPos->row;
        col = curPos->col;
        if (row == m-2 && col == n-2) {
            break;
        }
        dir = direction[curPos->dir];
        if (curPos->dir > 7) {
            free(curPos);
            top--;
            continue;
        }
        row += dir[0];
        col += dir[1];
        if (A[row][col] == 0) {
            A[row][col] = 2;
            STACK[++top] = GETPATH(row, col, 0);
        }else{
            curPos->dir += 1;
        }
    }
    // 打印堆栈路径
    if (top < 0) {
        printf("无路可走 \n");
    }else{
        for(int i=0; i<=top; i++){
            printf("第 %d 步, row: %d, col: %d \n", i+1, STACK[i]->row, STACK[i]->col);
        }
    }
}

void MAZE(int B[][MaxN], int m, int n){
    int A[m][MaxN];
    CopyArray(B, A, m, n);
    int direction[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    MOVE_P STACK[MaxNM], curPos;
    int top=0,curv=0,row,col; /* (1,1)处入口,进栈 */
    STACK[0] = GETPATH(1, 1, 0);
    A[1][1] = 2;/* 走过的地方置为2 */
    while (top >= 0) {
        curPos = STACK[top];
        row = curPos->row;
        col = curPos->col;
        while (curPos->dir < 8) {
            int *diret = direction[curPos->dir];
            int nRow = row+diret[0];
            int nCol = col+diret[1];
            curv = A[nRow][nCol];
            if (curv == 0) {
                /* 可以通行，入栈 */
                curPos = GETPATH(nRow, nCol, 0);
                STACK[++top] = curPos;
                A[nRow][nCol] = 2;
                break;
            }else if (curv == 1 || curv == 2) {
                /* 禁止通行，换方向 */
                A[nRow][nCol] = 2;
            }
            (curPos->dir)++;
        }
        if (curPos->dir == 8) {
            /* 没找到出路，回退 */
            MOVE_P p = STACK[top];
            (STACK[--top]->dir)++;
            free(p);
        }else if (curPos->row == m-2 && curPos->col == n-2){
            /* 找到出口 */
            break;
        }
    }
    // 打印堆栈路径
    if (top < 0) {
        printf("无路可走 \n");
    }else{
        for(int i=0; i<=top; i++){
            printf("第 %d 步, row: %d, col: %d \n", i+1, STACK[i]->row, STACK[i]->col);
        }
    }
}

void Conversion(int n){
    int STACK[MaxN], top = -1;
    int t;
    while (n > 0) {
        t = n % 8;
        n /= 8;
        STACK[++top] = t;
    }
    while (top >= 0) {
        t = STACK[top--];
        printf("%d", t);
    }
    printf("\n");
}


static int Reccurresive(int a, int b){
    int STACK[MaxN], top=-1, m=a, n=b;
    STACK[++top] = m;
    while (top >= 0) {
        if (m*n == 0) {
            n = m+n+1;
            if (top >= 0) {
                m = STACK[top];
            }
            top--;
        }else{
            STACK[++top] = m-1;
            n--;
        }
    }
    return n;
}


void LinkStackMain(int argc, char *argv[]){
//    INITIALSLINK(&top);
//    int i;
//    for (i=1; i<=10; i++) {
//        SElem it = GETSELEM(i);
//        PUSHLINK(&top, it);
//    }
//    SElem itm;
//    POPLINK(&top, &itm);
//    printf("pop 元素：%d \n", itm->num);
//    GETTOPSLINK(top, &itm);
//    printf("栈顶 元素：%d \n", itm->num);
//    PRINTSTACK(top);
//    int b = CheckCode("/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS/Day2.c");
//    if (b) {
//        printf("格式正确 \n");
//    }else{
//        printf("格式错误 \n");
//    }
//    printf("进制转换 \n");
//    Conversion(1024);
//    CONVERSIONLINK(1024);
//    RECCURRESIVE(2, 5);
//    int res = Reccurresive(2, 5);
//    printf("%d \n", res);
    const int n=8;
    int a[n][MaxN] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}};
    MAZE(a, n, n);
    printf("-------------------\n");
    Maze(a, n, n);
}
