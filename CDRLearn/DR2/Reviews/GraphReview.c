//
//  GraphReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/11.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "GraphReview.h"
#include <stdlib.h>

#define MaxNum 1000

typedef struct Edge{
    int adjves;
    int weight;
    struct Edge *link;
}Edge, *PElink;

typedef struct Vertex{
    int data;
    int indegree;
    PElink link;
}Vertex, *PVlink;

static void AdjacencyList(PVlink vertexs[], int n, int e){
    int i,vi,vj,weight;
    PVlink pv;
    PElink pe,r;
    for (i=0; i<n; i++) {
        vertexs[i] = malloc(sizeof(Vertex));
        vertexs[i]->data=i+1;
        vertexs[i]->link = NULL;
        vertexs[i]->indegree = 0;
    }
    for (i=0; i<e; i++) {
        if (scanf("%d %d %d", &vi, &vj, &weight) != 3){
            printf("Invalid inout data\n");
            i--;
            continue;
        }
        r = malloc(sizeof(Edge));
        r->link = NULL;
        r->adjves = vj-1;
        pe = vertexs[vi-1]->link;
        if (pe == NULL) {
            vertexs[vi-1]->link = r;
        }else{
            while (pe->link != NULL){
                pe = pe->link;
            }
            pe->link = r;
        }
    }
}

static void FiguresTraverse(PVlink vertexs[], int n){
    PElink el;
    for (int i=0; i<n; i++) {
        printf("Pos: %d, data: %d ", i, vertexs[i]->data);
        el = vertexs[i]->link;
        while (el != NULL){
            printf("-> %d ", el->adjves);
            el = el->link;
        }
        putchar('\n');
    }
}

static void Visit(PVlink vertexs[], int v){
    if (v >= 0) {
        printf("%d ", vertexs[v]->data);
    }
}

static void DepthFirstSearchRecursive(PVlink vertexs[], int visited[], int v){
    Visit(vertexs, v);
    visited[v] = 1;
    PElink el = vertexs[v]->link;
    while(el != NULL){
        if (visited[el->adjves] == 0) {
            DepthFirstSearchRecursive(vertexs, visited, el->adjves);
        }
        el = el->link;
    }
}

static void DepthFirstSearchUnrecursive(PVlink vertexs[], int visited[], int v){
    int STACK[MaxNum], ver, top=-1;
    PElink el;
    STACK[++top] = v;
    while(top >= 0){
        ver = STACK[top];
        if (visited[ver] == 0) {
            Visit(vertexs, ver);
            visited[ver] = 1;
        }
        el = vertexs[ver]->link;
        for (el = vertexs[ver]->link; el && visited[el->adjves] == 1; el = el->link);
        if (el != NULL) {
            STACK[++top] = el->adjves;
        }else{
            top--;
        }
    }

}

static void BroadFirstSearchUnrecursive(PVlink vertexs[], int visited[], int v){
    int Queue[MaxNum], front=-1, rear=-1, k;
    PElink el;
    Visit(vertexs, v);
    visited[v] = 1;
    Queue[++rear] = v;
    while(front < rear){
        k = Queue[++front];
        el =vertexs[k]->link;
        while(el != NULL){
            if (visited[el->adjves] == 0) {
                Visit(vertexs, el->adjves);
                visited[el->adjves] = 1;
                Queue[++rear] = el->adjves;
            }
            el = el->link;
        }
    }

}

static void GraphSearch(PVlink vertexs[], int n, void (*SearchOperation)(PVlink vertexs[], int visited[], int v)){
    int visited[n], i;
    for (i=0; i<n; i++) {
        visited[i] = 0;
    }
    for (i=0; i<n; i++) {
        if (visited[i] == 0 && SearchOperation != NULL) {
            SearchOperation(vertexs, visited, i);
        }
    }
    putchar('\n');
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
static void CreateAdjacencyGraph(){
    const int n=10;
    const int e=17;
    PVlink vertexs[n];
    void (*SearchOperation)() = BroadFirstSearchUnrecursive;
    AdjacencyList(vertexs, n, e);
    FiguresTraverse(vertexs, n);
    GraphSearch(vertexs, n, *SearchOperation);
}

// Can you coding this algorithm？
static void Prim(){

}

void GraphReviewMain(int argc, char *argv[]){
    printf("GraphReviewMain \n");
    CreateAdjacencyGraph();
    
}




















