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

// 二叉树遍历求兄弟节点，层次遍历
BTREE GetBrother(BTREE T, int item){
    BTREE QUEUE[MAX],p=T;
    int front=-1,rear=0;
    if (T != NULL) {
        QUEUE[0] = T;
        while (front != rear) {
            if (p->lchild != NULL) {
                if (p->lchild->data == item) {
                    if (p->rchild != NULL) {
                        return p->rchild;
                    }else{
                        return NULL;
                    }
                }else{
                    QUEUE[++rear] = p->lchild;
                }
            }
            if (p->rchild != NULL) {
                if (p->rchild->data == item) {
                    if (p->lchild != NULL) {
                        return p->lchild;
                    }else{
                        return NULL;
                    }
                }else{
                    QUEUE[++rear] = p->rchild;
                }
            }
            p = QUEUE[++front];
        }
    }else{
        return NULL;
    }
    return NULL;
}

void Practice14(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    BTREE brother = GetBrother(T, 11);
    if (brother != NULL) {
        printf("兄弟节点：%d \n", brother->data);
    }else{
        printf("无兄弟节点 \n");
    }
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

void PrintAncestor2(BTREE T, int item){
    BTREE QUEUE[MAX];
    int front=-1, rear=-1;
    while (T != NULL) {
        if (T->data == item) {
            break;
        }
        QUEUE[++rear] = T;
        if (item < T->data) {
            T = T->lchild;
        }else {
            T = T->rchild;
        }
    }
    if (T == NULL) {
        printf("你丫的没祖先");
    }else{
        if (rear==front) {
            printf("你是根结点");
        }else{
            while (front < rear) {
                printf("%d ", QUEUE[++front]->data);
            }
        }
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
    PrintAncestor2(T, 4);
}

// 求 T 中 p 所指节点双亲节点，递归,适合层次遍历
BTREE GetParent(BTREE T, int item){
    BTREE p;
    if (T != NULL) {
        if (T->lchild != NULL && T->lchild->data == item) {
            return T;
        }
        if (T->rchild != NULL && T->rchild->data == item) {
            return T;
        }
        p = GetParent(T->lchild, item);
        if (p != NULL) {
            return p;
        }
        p = GetParent(T->rchild, item);
        if (p != NULL) {
            return p;
        }
    }
    return NULL;
}


BTREE GetParent2(BTREE T, int item){
    if ((T->lchild && T->lchild->data == item) || (T->rchild && T->rchild->data == item)) {
        return T;
    }
    BTREE p=NULL;
    if (T->lchild) {
        p = GetParent2(T->lchild, item);
        if (p) {
            return p;
        }
    }
    if (T->rchild) {
        p = GetParent2(T->rchild, item);
        if (p) {
            return p;
        }
    }
    return NULL;
}


static void Practice13(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    BTREE parent;
    parent = GetParent(T, 2);
    if (parent != NULL) {
        printf("Parent: %d \n", parent->data);
    }else{
        printf("你没爹 \n");
    }
}

// 打印所有左子树的根节点信息,前序遍历
static void PrintLeftParent(BTREE T){
    BTREE STACK[MAX],p=T;
    int top=-1;
    while (p != NULL || top >= 0) {
        while (p != NULL) {
            if (p -> lchild != NULL) {
                Visit(p);
            }
            STACK[++top] = p;
            p = p->lchild;
        }
        p = STACK[top--];
        p = p->rchild;
    }
}

static void Practice12(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    PrintLeftParent(T);
}

// 层次从右到左遍历
static void LayerOrder2(BTREE T){
    BTREE QUEUE[MAX],p;
    int front=-1,rear=-1;
    if (T == NULL) {
        return;
    }
    QUEUE[++rear] = T;
    p = T;
    do {
        p = QUEUE[++front];
        Visit(p);
        if (p->rchild != NULL) {
            QUEUE[++rear] = p->rchild;
        }
        if (p->lchild != NULL) {
            QUEUE[++rear] = p->lchild;
        }
    } while (rear != front);
    printf("\n");
}

static void Pracrtice11(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    printf("层次右->左遍历: \n");
    LayerOrder2(T);
}

// 递归算深度 🔥🔥🔥
int GetDepth(BTREE T){
    int m,n;
    if (!T) {
        return 0;
    }else{
        m = GetDepth(T->lchild);
        n = GetDepth(T->rchild);
        return (m>n?m:n) + 1;
    }
}

BTREE FindNode(BTREE T, int item){
    BTREE p;
    if (!T) {
        return NULL;
    }else{
        if (T->data == item) {
            return T;
        }else{
            p = FindNode(T->lchild, item);
            if (p) {
                return p;
            }
            p = FindNode(T->rchild, item);
            if (p) {
                return p;
            }
        }
    }
    return NULL;
}

// 后序遍历求深度
static int GetDepth2(BTREE T){
    BTREE STACK1[MAX], p=T;
    int STACK2[MAX], top=-1, flag, maxDepth=0;
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
            if (top+1 > maxDepth) {
                maxDepth = top+1;
            }
            p = NULL;
            top--;
        }else{
            STACK2[top] = 1;
            p = p->rchild;
        }
    }
    return maxDepth;
}

static void Pracrtice10(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    BTREE d;
    d = FindNode(T, 5);
    if (d) {
        printf("Depth: %d \n", GetDepth2(d));
    }else{
        printf("没找到 \n");
    }
    d = FindNode(T, 2);
    if (d) {
        printf("Depth: %d \n", GetDepth2(d));
    }else{
        printf("没找到 \n");
    }
    d = FindNode(T, 4);
    if (d) {
        printf("Depth: %d \n", GetDepth2(d));
    }else{
        printf("没找到 \n");
    }
}

// 递归算层次(非递归采用后序遍历),我的版
static int Layer(BTREE T, int item){
    if (!T) {
        return 0;
    }else{
        if (T->data == item) {
            return 1;
        }
        int n=0;
        n = Layer(T->lchild, item);
        if (n) {
            return 1+n;
        }
        n = Layer(T->rchild, item);
        if (n) {
            return 1+n;
        }
        return 0;
    }
}

// 标准答案版
static int Layer2(BTREE T, int item, int d){
    if(!T){
        return 0;
    }else{
        int n=0;
        if (T->data == item) {
            return d;
        }else{
            if ((n=Layer2(T->lchild, item, d+1)) > 0) {
                return n;
            }else{
                return Layer2(T->rchild, item, d+1);
            }
        }
    }
}

int maxValue(int value1, int value2){
    return value1 > value2 ? value1 : value2;
}

int Layer3(BTREE T, int item){
    int layer=0;
    if (T->data == item) {
        return 1;
    }else{
        if (T->lchild) {
            layer = Layer3(T->lchild, item);
            if (layer) {
                return layer+1;
            }
        }
        if (T->rchild) {
            layer = Layer3(T->rchild, item);
            if (layer) {
                return layer+1;
            }
        }
        return 0;
    }
}

static void Pracrtice9(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    printf("前序遍历: \n");
    LayerOrder(T);
    int layer;
    layer = Layer3(T, 4);
    printf("层次：%d \n", layer);
    layer = Layer2(T, 110, 1);
    printf("层次：%d \n", layer);
    layer = Layer(T, 4);
    printf("层次：%d \n", layer);
    
}

// 计算最大深度和最小深度
static int CountMaxMinDepth(BTREE T){
    int maxDepth=0,minDepth=MAX;
    BTREE STACK1[MAX],p=T;
    int STACK2[MAX],flag=0,top=-1;
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
            if (p->lchild == NULL && p->rchild == NULL) {
                if (top+1 > maxDepth) {
                    maxDepth = top+1;
                }
                if (top+1 < minDepth) {
                    minDepth = top+1;
                }
            }
            p = NULL;
            --top;
        }else{
            STACK2[top] = 1;
            p = p->rchild;
        }
    }
    return maxDepth-minDepth <= 1;
}

static int JudgePerfectBTree(BTREE T){
    BTREE QUEUE[MAX],p;
    int front=-1,rear=0,flag=0,b=1;/* flag 0代表左右非空，1代表右空，2代表左空, 3代表全空 */
    QUEUE[0] = T;
    while (front != rear) {
        p = QUEUE[++front];
        if (p->lchild == NULL) {
            if (p->rchild != NULL) {
                b = 0;
                break;
            }else{
                flag = 3;
            }
        }else{
            QUEUE[++rear] = p->lchild;
            if (p->rchild != NULL){
                if (flag != 0) {
                    b = 0;
                    break;
                }
                QUEUE[++rear] = p->rchild;
                flag = 0;
            }else{
                if (flag != 0) {
                    b = 0;
                    break;
                }
                flag = 1;
            }
        }
    }
    return b;
}

static int JudgePerfectBTree2(BTREE T){
    BTREE QUEUE[MAX], p=T;
    int front=-1, rear=-1, flag=0, b=1;
    QUEUE[++rear] = p;
    while (front < rear) {
        p = QUEUE[++front];
        if (!p->lchild && p->rchild) {
            b = 0;
            break;
        }
        if ((p->lchild && !p->rchild) || (!p->lchild && !p->rchild)) {
            flag = 1;
        }
        if (p->lchild && p->rchild && flag) {
            b = 0;
            break;
        }
        if (p->lchild) {
            QUEUE[++rear] = p->lchild;
        }
        if (p->rchild) {
            QUEUE[++rear] = p->rchild;
        }
    }
    return b;
}

static void Practice8(){
    const int n=7;
    int A[n] = {8, 6, 11, 7, 3, 10, 11};
    BTREE T = BuildTree(A, n);
    LayerOrder(T);
    int b;
    b = JudgePerfectBTree(T);
    printf("Prefect: %d \n", b);
    b = JudgePerfectBTree2(T);
    printf("Prefect: %d \n", b);
}

// 前序中序恢复树 🔥🔥🔥  🔥🔥🔥
BTREE RecoverBTree(int Preod[], int Inod[], int n){
    
    return NULL;
}
static void Practice7(){}

// 打印所有祖先结点（非递归后续遍历）
static void PrintAllParent(BTREE T, int item){
    BTREE STACK1[MAX],p=T;
    int STACK2[MAX],flag=0,top=-1;
    if (!T) {
        return;
    }
    while (p != NULL || top >= 0) {
        while (p != NULL) {
            STACK1[++top] = p;
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
            if (p->data == item) {
                if (top > 0) {
                    for (flag=0; flag<top; flag++) {
                        printf("%d ", STACK1[flag]->data);
                    }
                    printf("\n");
                }else{
                    printf("你丫的没祖先\n");
                }
                return;
            }
            top--;
            p = NULL;
        }else{
            p = p->rchild;
            STACK2[top] = 1;
        }
    }
}


static void PrintAncestors(BTREE T, int item){
    BTREE STACK1[MAX], p=T;
    int STACK2[MAX], top=-1, flag;
    while (p || top >= 0) {
        while (p) {
            STACK1[++top] = p;
            if (p->rchild) {
                STACK2[top] = 0;
            }else{
                STACK2[top] = 1;
            }
            p = p->lchild;
        }
        flag = STACK2[top];
        p = STACK1[top];
        if (flag) {
            top--;
            if (p->data == item) {
                break;
            }
            p = NULL;
        }else{
            STACK2[top] = 1;
            p = p->rchild;
        }
    }
    if (top >= 0) {
        for (flag=0; flag<=top; flag++) {
            printf("%d ", STACK1[flag]->data);
        }
        printf("\n");
    }else{
        printf("你丫的没祖先\n");
    }
}

static void Practice6(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    LayerOrder(T);
    PrintAllParent(T, 12);
    PrintAncestors(T, 12);
    
}

typedef struct tNode{
    BTREE date;
    struct tNode *link;
}TNode, *LNode;
#define SIZETNode sizeof(TNode)

static void Push(LNode *top, BTREE t){
    LNode node = malloc(SIZENODE);
    node->date = t;
    if (*top == NULL) {
        node->link = NULL;
        *top = node;
    }else{
        node->link = *top;
        *top = node;
    }
}

static void Pop(LNode *top){
    *top = (*top)->link;
}

// 统计度为1数量
static int OneCount(BTREE  T){
    if (!T) {
        return 0;
    }
    int n=0;
    BTREE p=T;
    LNode top=NULL;
    while (p != NULL || top != NULL) {
        while (p != NULL) {
            Push(&top, p);
            if ((p->lchild == NULL && p->rchild != NULL) || (p->lchild != NULL && p->rchild == NULL)) {
                n++;
                printf("%d ", p->data);
            }
            p = p->lchild;
        }
        p = top->date;
        p = p->rchild;
        Pop(&top);
    }
    return n;
}

static int OneCount2(BTREE T){
    if (!T) {
        return 0;
    }
    int sum = 0;
    LNode top=NULL;
    BTREE p = T;
    Push(&top, p);
    while (top) {
        while (p) {
            if ((p->lchild && !p->rchild) || (!p->lchild && p->rchild)) {
                sum++;
                printf("%d ", p->data);
            }
            Push(&top, p);
            p = p->lchild;
        }
        p = top->date;
        p = p->rchild;
        Pop(&top);
    }
    return sum;
}

static void Practice5(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    LayerOrder(T);
    int m;
    m = OneCount(T);
    printf("度为1个数 %d \n", m);
    m = OneCount2(T);
    printf("度为1个数 %d \n", m);
}

static void Destory2(BTREE *T){
    if (*T == NULL) {
        return;
    }
    Destory2(&(*T)->lchild);
    Destory2(&(*T)->rchild);
    free(*T);
    *T = NULL;
}


static void Destory(BTREE *T){
    if (*T) {
        if ((*T)->lchild != NULL) {
            Destory(&((*T)->lchild));
        }
        if ((*T)->rchild != NULL) {
            Destory(&((*T)->rchild));
        }
        free(*T);
        *T = NULL;
    }
}

static void Practice4(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T = BuildTree(A, n);
    LayerOrder(T);
    Destory2(&T);
    LayerOrder(T);
}

// 递归判断是否为等价
static int Equally(BTREE T1, BTREE T2){
    if (T1 == NULL && T2 == NULL) {
        return 1;
    }
    if (T1 != NULL && T2 != NULL) {
        if (T1->data == T2->data) {
            return Equally(T1->lchild, T2->lchild) && Equally(T1->rchild, T2->rchild);
        }else{
            return 0;
        }
    }
    return 0;
}




static int Equally2(BTREE T1, BTREE T2){
    if (T1 && T2 && (T1->data != T2->data)) {
        return 0;
    }
    if (!(T1 && T2)) {
        return 0;
    }
    return Equally(T1->lchild, T2->lchild) && Equally(T1->rchild, T2->rchild);
}


static void Practice3(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    int B[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T1 = BuildTree(A, n);
    BTREE T2 = BuildTree(B, n);
    LayerOrder(T1);
    LayerOrder(T2);
    int b;
    b = Equally(T1, T2);
    printf("是否等价：%d \n", b);
    b = Equally2(T1, T2);
    printf("是否等价：%d \n", b);
}

static int Similar2(BTREE T1, BTREE T2){
    if (T1 == NULL && T2 == NULL) {
        return 1;
    }
    if (T1 && T2) {
        return Similar2(T1->lchild, T2->lchild) && Similar2(T1->rchild, T2->rchild);
    }
    return 0;
}

// 判断是否相似
static int Similar(BTREE T1, BTREE T2){
    if (T1 == NULL && T2 == NULL) {
        return 1;
    }
    if (T1 != NULL && T2 != NULL) {
        return Similar(T1->lchild, T2->lchild) && Similar(T1->rchild, T2->rchild);
    }
    return 0;
}

static void Practice2(){
    const int n=9;
    int A[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    int B[n] = {4, 11, 5, 3, 9, 6, 2, 10, 2};
    BTREE T1 = BuildTree(A, n);
    BTREE T2 = BuildTree(B, n);
    LayerOrder(T1);
    LayerOrder(T2);
    int b;
    b = Similar(T1, T2);
    printf("是否相似：%d \n", b);
    b = Similar2(T1, T2);
    printf("是否相似：%d \n", b);
}

// 莫名其妙的崩溃？？ 🔥🔥🔥
static BTREE BuildOrderTree(int A[], int n){
    int i,front=-1,rear=0,t,QUEUE2[MAX],flag;
    BTREE QUEUE1[MAX],p=NULL,tmp,k;
    for (i=0; i<n; i++) {
        t = A[i];
        if (t != 0) {
            tmp = malloc(sizeof(SIZENODE));
            tmp->data = t;
            tmp->lchild = NULL;
            tmp->rchild = NULL;
        }else{
            tmp = NULL;
        }
        if (p == NULL) {
            if (t != 0) {
                p = tmp;
                QUEUE1[rear] = p;
                QUEUE2[rear] = 0;
            }else{
                return NULL;
            }
        }else{
            k = QUEUE1[front+1];
            flag = QUEUE2[front+1];
            if (flag == 0) {
                QUEUE2[front+1] = 1;
                if (tmp != NULL) {
                    k->lchild = tmp;
                    QUEUE1[++rear] = tmp;
                    QUEUE2[rear] = 0;
                }
            }else if (flag == 1) {
                if (tmp != NULL) {
                    k->rchild = tmp;
                    QUEUE1[++rear] = tmp;
                    QUEUE2[rear] = 0;
                }
                front++;
            }
        }
    }
    
    return p;
}

// 递归算法对二叉树中序遍历
static void InOrder(BTREE T){
    if (T != NULL) {
        InOrder(T->lchild);
        Visit(T);
        InOrder(T->rchild);
    }
}

// 根据顺序二叉树，前序遍历 🔥🔥🔥
static void Practice1(){
    const int n=7;
    int A[n] = {1, 2, 3, 0, 0, 4, 5};
    BTREE T = BuildOrderTree(A, n);
    InOrder(T);
}

int BTreePracticeMain(int argc, char *argv[]){
//    Practice17();
//    Practice16();
//    Practice14();
//    Practice13();
//    Practice12();
//    Pracrtice11();
//    Pracrtice10();
//    Pracrtice9();
//    Practice8();
//    Practice7();
//    Practice6();
//    Practice5();
//    Practice4();
//    Practice3();
    Practice2();
//    Practice1();
    
    return 0;
}











