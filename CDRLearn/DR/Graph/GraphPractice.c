//
//  GraphPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/5.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "GraphPractice.h"
#include <stdlib.h>

typedef struct edge{
    int adjvex; /* 该边终止节点在顶点结点中的位置 */
    int weight; /* 该边的权值 */
    struct edge *next;
}ELink;

typedef struct ver{
    int vertex; /* 顶点的数据信息 */
    ELink *link; /* 指向第一条边所对应的边节点 */
}VLink;

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
 */
static void ADJLIST(VLink G[], int n, int e){
    int i,vi,vj,weight;
    ELink *p=NULL,*k=NULL;
    for (i=0; i<n; i++) {
        G[i].vertex = i;
        G[i].link = NULL;
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

static void DFS(VLink G[], int n, int visited[]){
    Visit(G, n);
    visited[n] = 1;
    ELink *p=G[n].link;
    while (p != NULL) {
        if (visited[p->adjvex] != 1) {
            DFS(G, p->adjvex, visited);
        }
        p = p->next;
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
}

// n个顶点的带权有向图邻接表存储，图中插入<u,v,weight>(假设u和v存在)
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
    DepthFirst(G, n, visited);
}

int GraphPracticeMain(int argc, char *argv[]){
    printf("Hello Graph practice \n");
    Practice7();
//    Practice7();
//    Practice7();
//    Practice7();
//    Practice7();
//    Practice7();
//    Practice7();
    
    return 0;
}
