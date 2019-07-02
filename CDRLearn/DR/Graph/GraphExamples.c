//
//  GraphExamples.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/1.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "GraphExamples.h"
#include <math.h>
#include <stdlib.h>

#define MaxValue __INT_MAX__
#define MaxVNum 100

// 输入带权无向图（无向图邻接矩阵是对称矩阵）
void ADJMATRIX(int A[][MaxVNum], int n, int e){
    int i,j,k,weight;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            A[i][j] = MaxValue; /* 邻接矩阵赋初始值 */
        }
    }
    for (k=0; k<e; k++) {
        scanf("i=%d,j=%d,weight=%d", &i, &j, &weight);
        A[i][j] = weight;
        A[j][i] = weight;
    }
}

typedef struct edge{
    int adjvex; /* 该边终止节点在顶点结点中的位置 */
    int weight; /* 该边的权值 */
    struct edge *next;
}ELink;

typedef struct ver{
    int vertex; /* 顶点的数据信息 */
    ELink *link; /* 指向第一条边所对应的边节点 */
}VLink;

// 依次输入带权有向图 n 个顶点和 e 个表示边的顶点偶对，写一算法建立邻接表结构
void ADJLIST(VLink G[], int n, int e){
    int k,vi,vj,weight;
    ELink *p,*q;
    for (k=0; k<n; k++) {
        G[k].vertex = k+1;
        G[k].link = NULL; /* 建立 n 个顶点结点 */
    }
    for (k=0; k<e; k++) {
        scanf("%d %d %d", &vi, &vj, &weight); /* 输入一个顶点偶对与权值 */
        p = (ELink *)malloc(sizeof(ELink));
        p->adjvex = vj-1;
        p->weight = weight;
        if (!G[vi-1].link) {
            G[vi-1].link = p;
        }else{
            q = G[vi-1].link;
            while (q->next) {
                q = q->next;
            }
            q->next = p;
        }
    }
}

// 删除值为 item 的顶点 
void DELVER(VLink G[], int *n, int item){
    int i,k=-1;
    ELink *p,*r,*q;
    for (i=0; i<*n; i++) {
        if (G[i].vertex == item) {
            k = i;
            break;
        }
    }
    if (k == -1) {
        return;
    }
    // 找到item所在位置
    p = G[k].link;
    for (i=k+1; i<*n; i++) {
        G[i-1] = G[i];
    }
    (*n)--;
    while (p != NULL) {
        r = p;
        p = p->next;
        free(r);
    }
    for (i=0; i<*n; i++) {
        p = G[i].link;
        r = NULL;
        while (p != NULL) {
            if (p->adjvex == k) {
                if (r == NULL) {
                    G[i].link = NULL;
                }else{
                    q = p;
                    r->next = p->next;
                    p = p->next;
                    free(q);
                }
            }else{
                if (p->adjvex > k) {
                    (p->adjvex)--;
                }
                r = p;
                p = p->next;
            }
            
        }
    }
}

int FIRSTADJ(VLink G[] ,int v){
    if (v >= 0 && G[v].link != NULL) {
        return G[v].link->adjvex;
    }
    return -1;
}

int NEXTADJ(VLink G[], int visited[], int v){
    int next=-1;
    if (v >= 0) {
        VLink vl = G[v];
        ELink *el = vl.link;
        while (el != NULL && visited[el->adjvex] == 0) {
            next = el->adjvex;
            break;
        }
    }
    return next;
}

static void Visit(VLink G[], int v){
    if (v >= 0) {
        printf("%d ", G[v].vertex);
    }
}

void DFS(VLink G[], int visited[], int v){
    int w;
    Visit(G, v);
    visited[v] = 1;
    w = FIRSTADJ(G, v);
    while (w != -1) {
        if (visited[w] == 0) {
            DFS(G, visited, w);
        }
        w = NEXTADJ(G, visited, v);
    }
}

void TRAVEL_DFS(VLink G[], int visited[], int n){
    int i;
    for (i=0; i<n; i++) {
        visited[i] = 0;
    }
    DFS(G, visited, 5);
    printf("\n");
}

int GraphExampleMain(int argc, char *argv[]){
    printf("Hello Graph %d\n", MaxValue);
    const int n=10;
    int visited[n];
    VLink G[n],*v;
    for (int i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, n);
    TRAVEL_DFS(G, visited, n);
    
    return 0;
}
