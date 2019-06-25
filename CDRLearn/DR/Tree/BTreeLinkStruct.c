//
//  BTreeLinkStruct.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/6/25.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "BTreeLinkStruct.h"
#include <stdlib.h>
#include <math.h>

#define MAX 100
typedef struct node{
    int data; /* 数据域 */
    struct node *lchild, *rchild; /* 分别指向左右子树的指针域 */
}BTNode, *BTREE;
#define SIZENODE sizeof(BTNode)

// 广义表输入的形式建立二叉链表树, eg: A(B(D,E(G)),C(F(,H)))@
BTREE CreateTree(){
    int data = 1;
    BTREE STACK[MAX], p=NULL, t=NULL;
    char ch;
    int flag=0,top=-1; /* 0代表左子树，1代表右子树 */
    while (1) {
        scanf("%c", &ch);
        switch (ch) {
            case '@':
                return p;
            case '(':
                STACK[++top] = t;
                flag = 0;
                break;
            case ')':
                --top;
                break;
            case ',':
                flag = 1;
                break;
            default:
                t = malloc(SIZENODE);
                t->lchild = NULL;
                t->rchild = NULL;
                t->data = data++;
                if (p == NULL) {
                    p = t;
                }else{
                    // 从栈中取出并根据falg决定左右
                    BTREE parent = STACK[top];
                    if (!flag) { /* 左子树 */
                        parent->lchild = t;
                    }else{
                        parent->rchild = t;
                    }
                }
                break;
        }
    }
    return NULL;
}

BTREE CreateTreeWithArray(int BT[], int n){
    BTREE t,PTR[n],root = malloc(SIZENODE);
    root->data = BT[0];
    root->lchild = root->rchild = NULL;
    PTR[0] = root;
    int i,j;
    for (i=1; i<n; i++) {
        if (BT[i] != 0) {
            t = malloc(SIZENODE);
            t->data = BT[i];
            t->lchild = t->rchild = NULL;
            PTR[i] = t;
            j = (i-1)/2;
            if (i == j*2+1) {
                PTR[j]->lchild = t;
            }else{
                PTR[j]->rchild = t;
            }
        }
    }
    return root;
}

// 递归求叶子结点数目
int GetLeafNodeRecursion(BTREE root){
    if (root == NULL) {
        return 0;
    }
    if (root->rchild == NULL && root->lchild == NULL) {
        return 1;
    }
    return GetLeafNodeRecursion(root->rchild) + GetLeafNodeRecursion(root->lchild);
}

static int max(int a, int b){
    return a>b?a:b;
}

int GetMaxDepth(BTREE T){
    if (T == NULL) {
        return 0;
    }
    return max(GetMaxDepth(T->lchild),GetMaxDepth(T->rchild))+1;
}

// 广义表方式输入二叉树
void CreateTreeWithInput(){
    BTREE tree = CreateTree();
    printf("前序遍历递归：\n");
    void PreOrder(BTREE T);
    PreOrder(tree);
    printf("\n");
}

// 二叉树一些属性（深度，叶子数）
void Attribute(){
    BTREE tree;
    const int n=15;
    int BT[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    tree = CreateTreeWithArray(BT, n);
    int leafCount = GetLeafNodeRecursion(tree);
    printf("叶子结点个数: %d \n", leafCount);
    int depth = GetMaxDepth(tree);
    printf("深度: %d \n", depth);
}

void Visit(BTREE T){
    printf("%d ", T->data);
}

// 递归算法对二叉树前序遍历
void PreOrder(BTREE T){
    if (T != NULL) {
        Visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

// 非递归算法对二叉树前序遍历
void PreOrder2(BTREE T){
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
}

// 递归算法对二叉树中序遍历
void InOrder(BTREE T){
    if (T != NULL) {
        InOrder(T->lchild);
        Visit(T);
        InOrder(T->rchild);
    }
}

// 非递归算法对二叉树中序遍历
void InOrder2(BTREE T){
    BTREE STACK[MAX], p=T;
    int top=-1;
    while (p != NULL || top >= 0) {
        while (p !=NULL ) {
            STACK[++top] = p;
            p = p->lchild;
        }
        p = STACK[top--];
        Visit(p);
        p = p->rchild;
    }
}

// 递归算法对二叉树后序遍历
void PostOrder(BTREE T){
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        Visit(T);
    }
}

// 非递归算法对二叉树后序遍历
void PostOrder2(BTREE T){
    BTREE STACK1[MAX],p=T;
    int STACK2[MAX],top=-1,flag;
    while (p != NULL || top >= 0) {
        while (p != NULL) {
            ++top;
            STACK1[top] = p;
            if (p->rchild != NULL) {
                STACK2[top] = 0;
            }else{
                STACK2[top] = 1;
            }
            p = p->lchild;
        }
        p = STACK1[top];
        flag = STACK2[top];
        if (flag) {
            // 可以直接访问
            Visit(p);
            top--;
            p = NULL;
        }else{
            // 遍历右结点, 此时p还没退栈，再次回来时已经遍历完右结点所以可以访问，此时flag置1
            p = p->rchild;
            STACK2[top] = 1;
        }
    }
}

// 层次遍历
void LayerOrder(BTREE T){
    BTREE QUEUE[MAX],p=T;
    int front,rear;
    if (T != NULL){
        QUEUE[0] = T;
        front = -1;
        rear = 0;
        while (front < rear) {
            p = QUEUE[++front];
            Visit(p);
            if (p->lchild != NULL){
                QUEUE[++rear] = p->lchild;
            }
            if (p->rchild != NULL) {
                QUEUE[++rear] = p->rchild;
            }
        }
    }
}

// 二叉树遍历
void Orders(){
    BTREE tree;
    const int n=16;
    int BT[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    tree = CreateTreeWithArray(BT, n);
    printf("前序遍历递归：\n");
    PreOrder(tree);/* 1 2 4 5 3 6 7 */
    printf("\n中序遍历递归：\n");
    InOrder(tree);/* 4 2 5 1 6 3 7 */
    printf("\n后序遍历递归：\n");
    PostOrder(tree);/* 4 5 2 6 7 3 1 */
    printf("\n\n***************************\n\n");
    printf("前序遍历非递归：\n");
    PreOrder2(tree);/* 1 2 4 5 3 6 7 */
    printf("\n中序遍历非递归：\n");
    InOrder2(tree);/* 4 2 5 1 6 3 7 */
    printf("\n后序遍历非递归：\n");
    PostOrder2(tree);/* 4 5 2 6 7 3 1 */
    printf("\n\n***************************\n\n");
    printf("层次遍历：\n");
    LayerOrder(tree);
    printf("\n");
}



int BTreeLinkMain(int argc, char *argv[])
{
//    CreateTreeWithInput();
//    Attribute();
    Orders();
    return 0;
}
