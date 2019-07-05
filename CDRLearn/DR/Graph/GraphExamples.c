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
        scanf("%d %d %d", &i, &j, &weight);
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
    int indegree;/* 顶点的入度 */
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
        p->next = NULL;
        if (!G[vi-1].link) {
            G[vi-1].link = p;
        }else{
            q = G[vi-1].link;
            while (q->next != NULL) {
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
        while (el != NULL) {
            if (visited[el->adjvex] == 0) {
                next = el->adjvex;
                break;
            }
            el = el->next;
        }
    }
    return next;
}

static void Visit(VLink G[], int v){
    if (v >= 0) {
        printf("%d ", G[v].vertex);
    }
}

// 深度优先搜索递归算法
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

/* 深度优先搜索非递归算法
 1 ->2 ->3 ->5->6
 2 ->1 ->6 ->4
 3 ->8 ->2 ->10
 4 ->9
 5 ->6
 6 ->7
 7 ->8
 8 ->9
 9 ->10
 10 ->1
 */
void DFS2(VLink G[], int visited[], int v){
    int STACK[MaxVNum], top=-1, p;
    int el;
    STACK[++top] = v;
    while (top >= 0) {
        p = STACK[top];
        if (visited[p] == 0) {
            Visit(G, p);
            visited[p] = 1;
        }
        el = NEXTADJ(G, visited, p);
        if (el != -1) {
            if (visited[el] == 0) {
                STACK[++top] = el;
            }
        }else{
            --top;
        }
    }
}

// 广度优先遍历
void BFS(VLink G[], int visited[], int v){
    int QUEUE[MaxVNum];
    int front=-1,rear=-1,p;
    Visit(G, v);
    visited[v] = 1;
    QUEUE[++rear] = v;
    while (front != rear) {
        v = QUEUE[++front];
        p = FIRSTADJ(G, v);
        while (p != -1) {
            if (visited[p] == 0) {
                Visit(G, p);
                visited[p] = 1;
                QUEUE[++rear] = p;
            }
            p = NEXTADJ(G, visited, v);
        }
    }
    printf("\n");
}

void TRAVEL_DFS(VLink G[], int visited[], int n){
    int i;
    for (i=0; i<n; i++) {
        visited[i] = 0;
    }
    for (i=0; i<n; i++) {
        if (visited[i] == 0) {
            DFS2(G, visited, i);
        }
    }
    printf("\n");
}

void TRAVEL_BFS(VLink G[], int visited[], int n){
    int i;
    for (i=0; i<n; i++) {
        visited[i] = 0;
    }
    for (i=0; i<n; i++) {
        if (visited[i] == 0) {
            BFS(G, visited, i);
        }
    }
    printf("\n");
}

/*有向图结构
 输入：
 1 2 0
 1 3 0
 1 5 0
 1 6 0
 2 1 0
 2 6 0
 2 4 0
 3 8 0
 3 2 0
 3 10 0
 4 9 0
 5 6 0
 6 7 0
 7 8 0
 8 9 0
 9 10 0
 10 1 0
 // 邻接表表示：
 1 ->2 ->3 ->5->6
 2 ->1 ->6 ->4
 3 ->8 ->2 ->10
 4 ->9
 5 ->6
 6 ->7
 7 ->8
 8 ->9
 9 ->10
 10 ->1
 深度优先遍历：1 2 6 7 8 9 10 4 3 5
 广度优先遍历：1 2 3 5 6 4 8 10 7 9
 */
void DepthAndBreadthFirstSearch(){
    const int n=10;
    int visited[n];
    VLink G[n],*v;
    for (int i=0; i<n; i++) {
        visited[i]=0;
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    TRAVEL_DFS(G, visited, n);
    for (int i=0; i<n; i++) {
        visited[i] = 0;
    }
    TRAVEL_BFS(G, visited, n);
}

// 获取连通分量
void Component(VLink G[], int visited[], int n){
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            BFS(G, visited, i);
        }
    }
}

/*
 // 邻接表表示：
 1 ->2 ->3
 2 ->1 ->4
 3 ->8 ->2 ->10
 4 ->9
 5 ->6
 6 ->7
 7 ->8
 8 ->9
 9 ->10
 10 ->1
 深度优先遍历：1 2 4 9 10 3 8   5 6 7
 广度优先遍历：1 2 3 4 8 10 9   5 6 7
 */
void ComponentTest(){
    int visited[MaxVNum]={0};
    const int n=10;
    VLink G[n],*v;
    for (int i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST(G, n, 14);
    Component(G, visited, n);
}

// 普里姆算法求最小生成树(最小代价生成树),，牛逼算法重在理解。注意：最小生成树无回路！！！🔥🔥🔥
void Prim(int GE[][MaxVNum], int n){
    
    int lowcost[n],teend[MaxVNum],i,j,k,mincost;
    lowcost[0]=0;
    teend[0]=0;
    for (i=1; i<n; i++) {
        lowcost[i] = GE[0][i];/* 权值数组赋初始值 */
        teend[i] = 0;/* 权值对应顶点 */
    }
    for (i=1; i<n; i++) {
        mincost = MaxValue;
        k=0;
        for (j=0; j<n; j++) {
            /* 只从没有走过的路径中筛选出最小权值路径( != 0) */
            if (lowcost[j] != 0 && lowcost[j] < mincost) {
                k=j;
                mincost = lowcost[j];
            }
        }
        printf("%d -> %d, ", teend[k], k);
        /* 置0代表已走过的顶点 */
        lowcost[k] = 0;
        for (j=0; j<n; j++) {
            /* 已经置为0的顶点此时不该再将该权值加入数组，因为最小生成树不允许回路 */
            if (lowcost[j] != 0 && GE[k][j] < lowcost[j]) {
                lowcost[j] = GE[k][j];
                teend[j] = k;
            }
        }
    }
}

void PrimTest(){
    const int n=6;
    int GE[n][MaxVNum],i,j;
    ADJMATRIX(GE, n, 10);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", GE[i][j]);
        }
        printf("\n");
    }
    Prim(GE, n);
}

int MinDist(int s[], int dist[], int n){
    int i,min=-1,minDist=MaxValue;
    for (i=0; i<n; i++) {
        if (s[i] == 0 && dist[i] < minDist) {
            minDist = dist[i];
            min = i;
        }
    }
    return min;
}

// 迪杰斯特拉算法求最短路径(牛逼算法，重在理解，理解路径构造的过程，怎么构造的) 🔥🔥🔥
void Shortest_Path_Dijkstra(int cost[][MaxVNum], int v, int n, int dist[], int path[][MaxVNum]){
    int i,w,u,count,pos[n],s[MaxVNum];
    for (i=0; i<n; i++) {
        s[i]=0;/* 标记数组置0,s 代表是否已经找到原点v到该顶点的最短路径，0/1 */
        dist[i]=cost[v][i]; /* dist 记录了原点 v 到各个顶点的路径长度，初始值为 cost 第 v 行数据 */
        path[i][0]=v; /* 记录原点到每个顶点的最短路径(eg:v->1->2...), 初始肯定都是从 v 开始 */
        pos[i]=0; /* 第 i 条最短路径此时个数(记录下一次应该在 path 的哪个位置插入路径) */
    }
    s[v]=1; /* 原点标记为 1 */
    count=1;
    while (count < n) {
        u = MinDist(s, dist, n);
        if (u == -1) { /* 代表所有顶点都已找到最短路径 */
            break;
        }
        s[u]=1; /* 代表找到一个最短路径置为1 */
        path[u][++pos[u]] = u; /* 将u设置到路径中去 */
        count++;
        // 根据 u 更新从 v 到所有未确定最短路径顶点的路径长度
        for (w=0; w<n; w++) { /* 查找u可以直接到达(路径1)的并且尚未确定最短路径的顶点 */
            if (cost[u][w] > 0 && cost[u][w] < MaxVNum && s[w] == 0) {
                // 找到了，并且通过 v->u->w 的长度小于 v 直接到 w 的距离，则更新 dist[w],并且path也更新为 v->u->w
                if (dist[u]+cost[u][w] < dist[w]) {
                    dist[w] = dist[u]+cost[u][w];
                    for (i=0; i<=pos[u]; i++) {
                        path[w][i] = path[u][i];
                    }
                    // 将 w 对应的标记为之调整到和 u 一样，因为路径一样。
                    pos[w]=pos[u];
                }
            }
        }

    }
    // 开始打印
    for (i=0; i<n; i++) {
        printf("原点 %d 到顶点 %d 的路径长度: %-2d, ", v, i, dist[i]);
        for (u=0; u<=pos[i]; u++) {
            printf("%d ", path[i][u]);
        }
        printf("\n");
    }
}

void ShortPathTest(){
    const int n=7;
    int GE[n][MaxVNum],i,j;
    ADJMATRIX(GE, n, 25);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", GE[i][j]);
        }
        printf("\n");
    }
    int v=0, dist[n], path[n][MaxVNum];
    Shortest_Path_Dijkstra(GE, v, n, dist, path);
}

// 依次输入带权有向图 n 个顶点和 e 个表示边的顶点偶对，写一算法建立邻接表结构(附带顶点入度字段)
void ADJLIST_TOPO(VLink G[], int n, int e){
    int k,vi,vj,weight;
    ELink *p,*q;
    for (k=0; k<n; k++) {
        G[k].vertex = k;
        G[k].link = NULL; /* 建立 n 个顶点结点 */
    }
    for (k=0; k<e; k++) {
        scanf("%d %d %d", &vi, &vj, &weight); /* 输入一个顶点偶对与权值 */
        p = (ELink *)malloc(sizeof(ELink));
        p->adjvex = vj;
        p->weight = weight;
        p->next = NULL;
        G[vj].indegree++;
        if (!G[vi].link) {
            G[vi].link = p;
        }else{
            q = G[vi].link;
            while (q->next != NULL) {
                q = q->next;
            }
            q->next = p;
        }
    }
}

// 拓扑排序算法
void TOPO_Sort(VLink G[], int n, int V[], int *Vn){
    ELink *p=NULL;
    int STACK[MaxVNum],top=-1,i,j,k;
    for (i=0; i<n; i++) {
        if (G[i].indegree == 0) {
            STACK[++top] = i;
        }
    }
    i=0;
    while (top >= 0) {
        j = STACK[top--];
        V[i++] = G[j].vertex;
        p = G[j].link;
        while (p != NULL) {
            k = p->adjvex;
            G[k].indegree--;
            if (G[k].indegree == 0) {
                STACK[++top] = k;
            }
            p = p->next;
        }
    }
    *Vn = i;
}

int TOPO_Judge(VLink G[], int V[], int n){
    int i,j,k,b=1,exist[n];
    ELink *p=NULL;
    for (i=0; i<n; i++) {
        k=-1;
        for (j=0; j<n; j++) {
            if (G[j].vertex == V[i]) {
                if (exist[j] != 1) {
                    k = j;
                    exist[k]=1;
                }
                break;
            }
        }
        if (k >= 0 && G[k].indegree == 0) {
            p = G[k].link;
            while (p != NULL) {
                j = p->adjvex;
                G[j].indegree--;
                p = p->next;
            }
        }else{
            b=0;
            break;
        }
    }
    return b;
}

void TOPO_SortTest(){
    int visited[MaxVNum]={0};
    const int n=7;
    VLink G[n],*v;
    for (int i=0; i<n; i++) {
        v = malloc(sizeof(VLink));
        G[i] = *v;
    }
    ADJLIST_TOPO(G, n, 8);
    Component(G, visited, n);
    int indegrees[n];
    for (int i=0; i<n; i++) {
        indegrees[i] = G[i].indegree;
        printf("%d ", G[i].indegree);
    }
    printf("\n");
    int V[n]={-1}, Vn=0, b;
    TOPO_Sort(G, n, V, &Vn);
    if (Vn == n) {
        for (int i=0; i<n; i++) {
            printf("%d ", V[i]);
        }
        printf("\n");
    }else{
        printf("网中存在回路！！！ \n");
    }
    for (int i=0; i<n; i++) {
        G[i].indegree = indegrees[i];
    }
    b = TOPO_Judge(G, V, n);
    printf("是否拓扑序列: %d \n", b);
}

int GraphExampleMain(int argc, char *argv[]){
    printf("Hello Graph %d\n", MaxValue);
//    DepthAndBreadthFirstSearch();
//    ComponentTest();
//    PrimTest();
//    ShortPathTest();
    TOPO_SortTest();
    
    return 0;
}
