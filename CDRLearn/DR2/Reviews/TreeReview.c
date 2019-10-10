//
//  TreeReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/8.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "TreeReview.h"
#include <stdlib.h>

#define MaxNum 1000
typedef struct TNode{
    int data;
    struct TNode *llink;
    struct TNode *rlink;
}TNode, *BTree;

static BTree CreateOrderTree(int A[], int n){
    int i,front,rear;
    BTree Queue[n],T,r,p;
    front = rear = -1;
    i = 0;
    T = malloc(sizeof(TNode));
    T->llink = T->rlink = NULL;
    T->data = A[i++];
    Queue[++rear] = T;
    while (i < n) {
        r = malloc(sizeof(TNode));
        r->llink = r->rlink = NULL;
        r->data = A[i++];
        p = Queue[front+1];
        if (p->llink == NULL) {
            p->llink = r;
        }else{
            p->rlink = r;
            front++;
        }
        Queue[++rear] = r;
    }
    return T;
} 

// Layer traverse
static void LayerTraverse(BTree T){
    BTree Queue[MaxNum],r;
    int front=-1,rear=-1;
    Queue[++rear] = T;
    while(front < rear){
        r = Queue[++front];
        printf("%d ", r->data);
        if (r->llink) {
            Queue[++rear] = r->llink;
        }
        if (r->rlink) {
            Queue[++rear] = r->rlink;
        }
    }
    putchar('\n');
}

/*
     1
   2   3
 4  5 6  7
8  
1 2 4 8 5 3 6 7
*/
static void FormerTraverseRecursive(BTree T){
    if (!T) {
        return;
    }
    printf("%d ", T->data);
    FormerTraverseRecursive(T->llink);
    FormerTraverseRecursive(T->rlink);
}

static void FormerTraverseUnrecursive(BTree T){
    BTree STACK[MaxNum],p;
    int top=-1;
    p = T;
    while(top >= 0 || p != NULL){
        while (p != NULL){
            printf("%d ", p->data);
            STACK[++top] = p;
            p = p->llink;
        }
        p = STACK[top--];
        p = p->rlink;
    }
    putchar('\n');
}

/*
     1
   2   3
 4  5 6  7
8  
8 4 2 5 1 6 3 7
*/
static void MiddleTraverseRecursive(BTree T){
    if (!T) {
        return;
    }
    MiddleTraverseRecursive(T->llink);
    printf("%d ", T->data);
    MiddleTraverseRecursive(T->rlink);
}

static void MiddleTraverseUnrecursive(BTree T){
    BTree STACK[MaxNum],p;
    int top = -1;
    p = T;
    while (top >= 0 || p != NULL){
        while (p != NULL) {
            STACK[++top] = p;
            p = p->llink;
        }
        p = STACK[top--];
        printf("%d ", p->data);
        p = p->rlink;
    }
    putchar('\n');
}

/*
     1
   2   3
 4  5 6  7
8  
8 4 5 2 6 7 3 1
*/
static void BehindTraverseRecursive(BTree T){
    if (!T) {
        return;
    }
    BehindTraverseRecursive(T->llink);
    BehindTraverseRecursive(T->rlink);
    printf("%d ", T->data);
}

static void BehindTraverseUnrecursive(BTree T){
    BTree STACK1[MaxNum], p;
    int STACK2[MaxNum], top=-1, flag;
    p = T;
    while (top >= 0 || p != NULL) {
        while (p != NULL) {
            STACK1[++top] = p;
            if (p->rlink != NULL) {
                STACK2[top] = 0;
            }else{
                STACK2[top] = 1;
            }
            p = p->llink;
        }
        p = STACK1[top];
        flag = STACK2[top];
        if (flag) {
            printf("%d ", p->data);
            top--;
            p = NULL;
        }else{
            p = p->rlink;
            STACK2[top] = 1;
        }
    }
    putchar('\n');
}

static void CreateTree(){
    const int n=8;
    int A[n] = {1, 2, 3, 4, 5, 6, 7,8};
    BTree T = CreateOrderTree(A, n);
    LayerTraverse(T);
    FormerTraverseRecursive(T);
    putchar('\n');
    FormerTraverseUnrecursive(T);
    MiddleTraverseRecursive(T);
    putchar('\n');
    MiddleTraverseUnrecursive(T);
    BehindTraverseRecursive(T);
    putchar('\n');
    BehindTraverseUnrecursive(T);
}

static void InsertSortTreeItemUnrecursive(BTree T, BTree item){  
    BTree r=NULL;;
    while (T != NULL){
        r = T;
        if (item->data > T->data) {
            T = T->rlink;
        }else if(item->data < T->data) {
            T =T->llink;
        }else{
            r = NULL;
            break;
        }
    }
    if (r != NULL) {
        if (item->data >= r->data) {
            r->rlink = item;
        }else{
            r->llink = item;
        }
    }
}

static BTree CreateSqrtTree(int A[], int n){
    if (n <= 0) {
        return NULL;
    }
    BTree T,p;
    int i=0;
    T = malloc(sizeof(TNode));
    T->llink = T->rlink = NULL;
    T->data = A[i++];
    while (i < n){
        p = malloc(sizeof(TNode));
        p->llink = p->rlink = NULL;
        p->data = A[i++];
        InsertSortTreeItemUnrecursive(T, p);
    }
    return T;
}

static void CreateSortTree(){
    const int n=8;
    int A[n] = {1, 2, 3, 4, 5, 6, 7,8};
    BTree T = CreateSqrtTree(A, n);
    // LayerTraverse(T);
    BehindTraverseRecursive(T);
    putchar('\n');
}

void TreeReviewMain(int argc, char *argv[]){
    printf("TreeReviewMain \n");
    // CreateTree();
    CreateSortTree();
}
