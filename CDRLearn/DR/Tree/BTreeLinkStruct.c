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

int SIMILAR(BTREE T1, BTREE T2){
    if (!T1 && !T2) {
        return 1;
    }
    if (T1 && T2 && SIMILAR(T1->lchild, T2->lchild) && SIMILAR(T1->rchild, T2->rchild)) {
        return 1;
    }
    return 0;
}

void BuildTree(BTREE *tree){
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') {
        *tree = NULL;
    }else{
        *tree = malloc(SIZENODE);
        (*tree)->data = ch-'a'+1;
        BuildTree(&((*tree)->lchild));
        BuildTree(&((*tree)->rchild));
    }
}

void DESTROYBT(BTREE *T){
    if ((*T)->lchild != NULL) {
        DESTROYBT(&(*T)->lchild);
    }
    if ((*T)->rchild != NULL) {
        DESTROYBT(&(*T)->rchild);
    }
    if (*T) {
        free(*T);
        *T = NULL;
    }
}

BTREE CopyBT(BTREE T1){
    BTREE T2=NULL;
    if (T1 != NULL) {
        T2 = malloc(SIZENODE);
        T2->data = T1->data;
        T2->lchild = CopyBT(T1->lchild);
        T2->rchild = CopyBT(T1->rchild);
    }
    return T2;
}

int EqualBT(BTREE T1, BTREE T2){
    if (!T1 && !T2) {
        return 1;
    }else if (T1 && T2 && T1->data == T2->data) {
        return EqualBT(T1->lchild, T2->lchild) && EqualBT(T1->rchild, T2->rchild);
    }
    return 0;
}

int DepthBT(BTREE T)
{
    BTREE STACK1[MAX],p=T;
    int STACK2[MAX] = {0};
    int maxDepth=0,top=-1,curDepth=0;
    while (p != NULL || top >= 0) {
        while (p != NULL) {
            STACK1[++top] = p;
            STACK2[top] = ++curDepth;
            p = p->lchild;
        }
        p = STACK1[top];
        curDepth = STACK2[top--];
        if (p->lchild == NULL && p->rchild == NULL && curDepth > maxDepth) {
            maxDepth = curDepth;
        }
        p = p->rchild;
    }
    return maxDepth;
}

int LayerBT(BTREE T, int item){
    BTREE STACK1[MAX],p=T;
    int STACK2[MAX];
    int top=-1,depth=0,flag=0;
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
                return top+1;
            }
            top--;
            p = NULL;
        }else{
            p = p->rchild;
            STACK2[top] = 1;
        }
    }
    return depth;
}

BTREE DeleteBT(BTREE T, int item){
    BTREE STACK[MAX],p=T,delNode=NULL,q=NULL;
    int top=-1;
    while ((p != NULL || top >= 0)) {
        while (p != NULL) {
            if (p->data == item) {
                if (q == NULL) {
                    DESTROYBT(&T);
                    return NULL;
                }else{
                    if (q->lchild == p) {
                        q->lchild = NULL;
                    }else{
                        q->rchild = NULL;
                    }
                    delNode = p;
                }
                break;
            }
            STACK[++top] = p;
            q = p;
            p = p->lchild;
        }
        if (delNode != NULL) {
            break;
        }
        p = STACK[top--];
        q = p;
        p = p->rchild;
    }
    if (delNode) {
        DESTROYBT(&delNode);
    }
    return T;
}

void ExchangeBT(BTREE T){
    BTREE QUEUE[MAX],p,tmp;
    int front=-1,rear=0;
    QUEUE[0] = T;
    while (front != rear) {
        p = QUEUE[++front];
        tmp = p->lchild;
        p->lchild = p->rchild;
        p->rchild = tmp;
        if (p->lchild != NULL) {
            QUEUE[++rear] = p->lchild;
        }
        if (p->rchild != NULL) {
            QUEUE[++rear] = p->rchild;
        }
    }
}

void InsertItem(BTREE *T, int item){
    BTREE p=NULL,r=NULL,t=NULL;
    t = malloc(SIZENODE);
    t->data = item;
    t->lchild = t->rchild = NULL;
    if (*T == NULL) {
        *T = t;
    }else{
        p = *T;
        while (p != NULL) {
            r = p;
            if (p->data > item) {
                p = p->lchild;
            }else{
                p = p->rchild;
            }
        }
        if (r->data > item) {
            r->lchild = t;
        }else{
            r->rchild = t;
        }
    }
}

void InsertRecursion(BTREE *T, int item){
    
    if (*T == NULL) {
        *T = malloc(SIZENODE);
        (*T)->data = item;
        (*T)->lchild = (*T)->rchild = NULL;
    }else{
        if ((*T)->data > item) {
            InsertItem(&((*T)->lchild), item);
        }else{
            InsertItem(&((*T)->rchild), item);
        }
    }
}

BTREE SortTree(int K[], int n){
    BTREE T=NULL;
    int i;
    if (n > 0) {
        for (i=0; i<n; i++) {
            InsertRecursion(&T, K[i]);
        }
    }
    return T;
}

// 非递归查找
BTREE SearchBST1(BTREE T, int item){
    BTREE p = T;
    if (T != NULL) {
        while (p != NULL && p->data != item) {
            if (p->data > item) {
                p = p->lchild;
            }else{
                p = p->rchild;
            }
        }
    }
    return p;
}

// 递归查找
BTREE SearchBSTRecursion(BTREE T, int item){
    if (T == NULL) {
        return NULL;
    }else if (T->data == item) {
        return T;
    }else{
        if (T->data > item) {
            return SearchBSTRecursion(T->lchild, item);
        }else{
            return SearchBSTRecursion(T->rchild, item);
        }
    }
}

void TreeBasicOperat(){
    BTREE T,T2;
    BuildTree(&T);
    T2 = CopyBT(T);
    int e;
    e = EqualBT(T, T2);
    printf("T1 和 T2 等价性：%d \n", e);
    LayerOrder(T);
    printf("\n");
    DESTROYBT(&T);
    LayerOrder(T);
    printf("\n");
    LayerOrder(T2);
    printf("\n");
    e = EqualBT(T, T2);
    printf("T1 和 T2 等价性：%d \n", e);
    e = DepthBT(T2);
    printf("T 深度：%d \n", e);
    e = LayerBT(T2, 6);
    printf("n 所在层次：%d \n", e);
    T2 = DeleteBT(T2, 1000);
    LayerOrder(T2);
    printf("\n");
    ExchangeBT(T2);
    LayerOrder(T2);
    printf("\n");
}

void SortBTreeOpeart(){
    const int n=8;
    int A[n] = {4, 2, 5, 2, 1, 6, 3, 7};
    /*
     4 2 1 2 3 5 6 7
     1 2 2 3 4 5 6 7
     1 3 2 2 7 6 5 4
     */
    BTREE T = SortTree(A, n);
    PreOrder(T);
    printf("\n");
    InOrder(T);
    printf("\n");
    PostOrder(T);
    printf("\n");
    int depth = DepthBT(T);
    printf("深度： %d \n", depth);
    BTREE ST = SearchBSTRecursion(T, 2);
    if (ST) {
        printf("查找到的值： %d \n", ST->data);
    }else{
        printf("没查找到 \n");
    }
}

int BTreeLinkMain(int argc, char *argv[])
{
//    CreateTreeWithInput();
//    Attribute();
//    Orders();
//    TreeBasicOperat();
    SortBTreeOpeart();
    return 0;
}
