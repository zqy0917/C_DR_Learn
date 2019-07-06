//
//  GraphPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/5.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "GraphPractice.h"
#include <stdlib.h>

#define MaxVNum 100

typedef struct edge{
    int adjvex; /* 该边终止节点在顶点结点中的位置 */
    int weight; /* 该边的权值 */
    struct edge *next;
}ELink;

typedef struct ver{
    int outNum; /* 出度 */
    int inNum; /* 入度 */
    int vertex; /* 顶点的数据信息 */
    ELink *link; /* 指向第一条边所对应的边节点 */
}VLink;

static void ADJLIST(VLink G[], int n, int e){
    int i,vi,vj,weight;
    ELink *p=NULL,*k=NULL;
    for (i=0; i<n; i++) {
        G[i].vertex = i;
        G[i].link = NULL;
        G[i].inNum = 0;
        G[i].outNum = 0;
    }
    for (i=0; i<e; i++) {
        scanf("%d %d %d", &vi, &vj, &weight);
        k = malloc(sizeof(ELink));
        k->next = NULL;
        k->adjvex = vj;
        k->weight = weight;
        p = G[vi].link;
        if (p == NULL) {
            G[vi].link = k;
        }else{
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = k;
        }
    }
}

static void Visit(VLink G[], int v){
    if (v >= 0) {
        printf("%d ", G[v].vertex);
    }
}

static void DFS(VLink G[], int i, int visited[]){
    Visit(G, i);
    visited[i] = 1;
    ELink *p=G[i].link;
    while (p != NULL) {
        if (visited[p->adjvex] != 1) {
            DFS(G, p->adjvex, visited);
        }
        p = p->next;
    }
}

static void DFS2(VLink G[], int i, int visited[]){
    int STACK[MaxVNum],top=-1,k,b;
    STACK[++top] = i;
    ELink *p;
    while (top >= 0) {
        k = STACK[top];
        if (visited[k] == 0) {
            Visit(G, k);
            visited[k]=1;
        }
        p = G[k].link;
        b=0;
        while (p != NULL) {
            if (visited[p->adjvex] == 0) {
                b=1;
                STACK[++top] = p->adjvex;
                break;
            }
            p = p->next;
        }
        if (!b) {
            top--;
        }
    }
}

static void BFS(VLink G[], int n, int visited[]){
    int QUEUE[MaxVNum],front=-1,rear=-1,p;
    ELink *el;
    QUEUE[++rear] = n;
    while (rear != front) {
        p = QUEUE[++front];
        if (visited[p] == 0) {
            Visit(G, p);
            visited[p]=1;
        }
        el = G[p].link;
        while (el != NULL) {
            if (visited[el->adjvex] == 0) {
                Visit(G, el->adjvex);
                visited[el->adjvex]=1;
                QUEUE[++rear] = el->adjvex;
            }
            el = el->next;
        }
    }
}

static void DepthFirst(VLink G[], int n, int visited[]){
    int i;
    for (i=0; i<n; i++) {
        visited[i]=0;
    }
    for (i=0; i<n; i++) {
        if (visited[i] == 0) {
            DFS(G, i, visited);
        }
    }
    printf("\n");
}

static void BreadthFirst(VLink G[], int n, int visited[]){
    int i;
    for (i=0; i<n; i++) {
        visited[i]=0;
    }
    for (i=0; i<n; i++) {
        if (visited[i] == 0) {
            BFS(G, i, visited);
        }
    }
    printf("\n");
}

// n个顶点的带权有向图邻接表存储，图中插入<u,v,weight>(假设u和v存在)
// 注意：<u,v> u，v仅代表顶点的值(vertex)，并不代表顶点在数组中的位置
// 数组只是邻接表存储法的产生品，原本的图没有数组这个概念，只有{<ui, uj>....}
static void Insert(VLink G[], int n, int u, int v, int weight){
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
        return;
    }
    int i,uPos=0,vPos=0;
    for (i=0; i<n; i++) {
        if (G[i].vertex == u) {
            uPos = i;
        }else if (G[i].vertex == v) {
            vPos = i;
        }
    }
    ELink *el,*p,*r=NULL;
    el = G[uPos].link;
    if (el == NULL) {
        p = malloc(sizeof(ELink));
        p->next = NULL;
        p->adjvex = vPos;
        p->weight = weight;
        G[uPos].link = p;
    }else{
        while (el->next != NULL) {
            if (el->adjvex == vPos) {
                el->weight = weight;
                break;
            }
            if (vPos < el->adjvex) {
                p = malloc(sizeof(ELink));
                p->next = el;
                p->adjvex = vPos;
                p->weight = weight;
                if (r == NULL) {
                    G[uPos].link = p;
                }else{
                    r->next = p;
                }
            }
            r = el;
            el = el->next;
        }
        
    }
}
void Delete(VLink G[], int n, int u, int v);
/*有向图结构
 输入：
 0 1 0
 0 2 0
 1 0 0
 1 3 0
 2 7 0
 2 1 0
 2 9 0
 3 8 0
 4 5 0
 5 6 0
 6 7 0
 7 8 0
 8 9 0
 9 0 0
 // 邻接表表示：
 0 ->1 ->2
 1 ->0 ->3
 2 ->7 ->1 ->9
 3 ->8
 4 ->5
 5 ->6
 6 ->7
 7 ->8
 8 ->9
 9 ->0
 深度优先遍历：0 1 3 8 9 2 7  4 5 6
 广度优先遍历：0 1 2 3 7 9 8  4 5 6
 广度优先遍历：0 1 2 3 5 7 9 8 6  4
 */
static void Practice7(){
    static int n=10;
    int i;
    VLink G[n], *v;
    for (i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    int visited[n];
    BreadthFirst(G, n, visited);
    Insert(G, n, 2, 5, 0);
    BreadthFirst(G, n, visited);
    Delete(G, n, 2, 5);
    BreadthFirst(G, n, visited);
}

// 删除图中一条边 <u,v>,假设 u，v存在
void Delete(VLink G[], int n, int u, int v){
    int i,uPos=0,vPos=0;
    ELink *r=NULL,*p=NULL;
    for(i=0; i<n; i++){
        if (G[i].vertex == u) {
            uPos = i;
        }
        if (G[i].vertex == v) {
            vPos = i;
        }
    }
    p = G[uPos].link;
    if (p->adjvex == v) {
        G[uPos].link = p->next;
        free(p);
    }else{
        while (p != NULL) {
            if (p->adjvex == v) {
                r->next = p->next;
                free(p);
                break;
            }
            r = p;
            p = p->next;
        }
    }
}

void GetOutInNum(VLink G[], int n){
    int i;
    ELink *p=NULL;
    for (i=0; i<n; i++) {
        p = G[i].link;
        while (p != NULL) {
            G[i].outNum++;
            G[p->adjvex].inNum++;
            p = p->next;
        }
    }
}

static void Practice5(){
    static int n=10;
    int i;
    VLink G[n], *v;
    for (i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    int visited[n];
    BreadthFirst(G, n, visited);
    GetOutInNum(G, n);
    for (i=0; i<n; i++) {
        printf("顶点 %d 的度：%d \n", i, G[i].inNum+G[i].outNum);
    }
}

void GetOutInNum2(int A[][MaxVNum], int e, int B[], int n){
    int i;
    for (i=0; i<n; i++) {
        B[i]=0;
    }
    for (i=0; i<e; i++) {
        B[A[i][0]]++;
        B[A[i][1]]++;
    }
}

static void Practice4(){
    const int e=6,n=6;
    int A[e][MaxVNum] = {
        {0, 1, 0},
        {1, 2, 0},
        {2, 3, 0},
        {3, 4, 0},
        {4, 5, 0},
        {5, 0, 0},
    },B[n];
    GetOutInNum2(A, e, B, n);
    for (int i=0; i<n; i++) {
        printf("%d ", B[i]);
    }
}

static void Convert(VLink G[], int n, int B[][MaxVNum]){
    int i,j;
    ELink *p=NULL;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            B[i][j] = -1;
        }
    }
    for (i=0; i<n; i++) {
        p = G[i].link;
        while (p != NULL) {
            B[i][p->adjvex] = p->weight;
            p = p->next;
        }
    }
}

static void Practice3(){
    static int n=10;
    int i,j;
    VLink G[n], *v;
    for (i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    int visited[n];
    BreadthFirst(G, n, visited);
    int B[n][MaxVNum];
    Convert(G, n, B);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
}

static void Convert2(int A[][MaxVNum], VLink G[], int n){
    int i,j;
    VLink *vl;
    ELink *p,*r=NULL;
    for (i=0; i<n; i++) {
        vl = malloc(sizeof(VLink));
        vl->inNum = 0;
        vl->outNum = 0;
        vl->link = NULL;
        vl->vertex = i;
        G[i] = *vl;
        for (j=0; j<n; j++) {
            if (A[i][j] != -1) {
                p = malloc(sizeof(ELink));
                p->next = NULL;
                p->adjvex = j;
                p->weight = A[i][j];
                if (G[i].link == NULL) {
                    G[i].link = p;
                }else{
                    r->next = p;
                }
                r = p;
            }
        }
    }
}

static void Practice2(){
    static int n=10;
    int i,j;
    VLink G[n], *v, E[n];
    for (i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    int visited[n];
    BreadthFirst(G, n, visited);
    int B[n][MaxVNum];
    Convert(G, n, B);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    Convert2(B, E, n);
    BreadthFirst(E, n, visited);
}

//
static void Practice1(){
    static int n=10;
    int i,j;
    VLink G[n], *v, E[n];
    for (i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    int visited[n];
    BreadthFirst(G, n, visited);
}

int GraphPracticeMain(int argc, char *argv[]){
    printf("Hello Graph practice \n");
//    Practice7();
//    Practice5();
//    Practice4();
//    Practice3();
//    Practice2();
    Practice1();
    
    return 0;
}
