//
//  BTreePractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/6/27.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "BTreePractice.h"
#include <stdlib.h>

#define MAX 100
typedef struct node{
    int data; /* 数据域 */
    struct node *lchild, *rchild; /* 分别指向左右子树的指针域 */
}BTNode, *BTREE;
#define SIZENODE sizeof(BTNode)

// 构建一个二叉排序树
static void InsertItem(BTREE *T, int item){
    BTREE t = malloc(SIZENODE);
    t->data = item;
    t->lchild = t->rchild = NULL;
    if (*T == NULL) {
        *T = t;
    }else{
        BTREE p = *T;
        while (1) {
            if (p->data > item) {
                if (p->lchild == NULL) {
                    p->lchild = t;
                    break;
                }else{
                    p = p->lchild;
                }
            }else{
                if (p->rchild == NULL) {
                    p->rchild = t;
                    break;
                }else{
                    p = p->rchild;
                }
            }
        }
    }
}
static BTREE BuildTree(int K[], int n){
    if (n <= 0) {
        return NULL;
    }
    BTREE T=NULL;
    for (int i=0; i<n; i++) {
        InsertItem(&T, K[i]);
    }
    return T;
}

static void Visit(BTREE T){
    printf("%d ", T->data);
}

// 前序遍历二叉树(非递归)
static void LayerOrder(BTREE T){
    BTREE STACK[MAX],p=T;
    int top=-1;
    while (p != NULL || top >= 0) {
        while (p != NULL) {
            Visit(p);
            STACK[++top] = p;
            p = p->lchild;
        }
        p = STACK[top--];
        p = p->rchild;
    }
    printf("\n");
}

static void Practice15(){
    
}


static int SortBTree(BTREE T){/* 适合层次遍历 */
    BTREE QUEUE[MAX],p;
    int front=-1,rear=0,b=1;
    if (!T) {
        return 0;
    }
    QUEUE[rear]=T;
    while (front != rear) {
        p = QUEUE[++front];
        if (p->lchild != NULL) {
            if (p->lchild->data >= p->data) {
                b = 0;
                break;
            }
            QUEUE[++rear] = p->lchild;
        }
        if (p->rchild != NULL) {
            if (p->rchild->data < p->data) {
                b = 0;
                break;
            }
            QUEUE[++rear] = p->rchild;
        }
    }
    return b;
}
// 判断是否是二叉排序树（非递归）
static void Practice16(){
    const int n=9;
    int A[n] = {4, 9, 5, 3, 8, 6, 2, 7, 2};
    BTREE T = BuildTree(A, n);
    T->lchild->lchild->data = 3;
    printf("前序遍历: \n");
    LayerOrder(T);
    int b = SortBTree(T);
    printf("是否是二叉排序树: %d \n", b);
}

// 适合后续遍历
static void PrintAncestor(BTREE T, int item){
    BTREE STACK1[MAX],p=T;
    int STACK2[MAX],flag=0,top=-1,find=0; /* 标记是否可与出栈 */
    while (p != NULL || top >= 0) {
        while (p != NULL) {
            STACK1[++top] = p;
            if (p->rchild == NULL) {
                STACK2[top] = 1;
            }else{
                STACK2[top] = 0;
            }
            p = p->lchild;
        }
        p = STACK1[top];
        flag = STACK2[top];
        if (flag) {
            if (p->data == item) {
                find = 1;
                break;
            }
            p = NULL;
            top--;
        }else{
            p = p->rchild;
            STACK2[top] = 1;
        }
        if (find) {
            break;
        }
    }
    if (top > 0) {
        for (int i=0; i<top; i++) {
            printf("%d ", STACK1[i]->data);
        }
    }else{
        printf("你丫的没祖先");
    }
    printf("\n");
}

/* 打印 item的祖先结点(非递归) */
static void Practice17(){
    const int n=9;
    int A[n] = {4, 9, 5, 1, 8, 6, 3, 7, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    printf("祖先结点: \n");
    PrintAncestor(T, 1);
}

int BTreePracticeMain(int argc, char *argv[]){
//    Practice17();
    Practice16();
    return 0;
}











