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
#define MaxValue 100000

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
        r->adjves = vj;
        (vertexs[vj]->indegree)++;
        pe = vertexs[vi]->link;
        if (pe == NULL) {
            vertexs[vi]->link = r;
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
 // link table show：
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
 Depth first：1 2 6 7 8 9 10 4 3 5
 Broad first：1 2 3 5 6 4 8 10 7 9
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


static void CreateUndirectionADJMatrix(int A[][MaxNum], int n, int e){
    int i, j, s, t, w;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            A[i][j] = MaxValue;
        }
    }
    for (i=0; i<e; i++) {
        scanf("%d %d %d", &s, &t, &w);
        A[s][t] = w;
        A[t][s] = w;
    }
}

// Prim Algorithm get minimum spanning tree.
// Can you coding this algorithm alone?
// Yes, I am willing to try.
// Finally I beat it!!!👊👊👊
static void Prim(int GE[][MaxNum], int n){
    int added[n], minTarget[n], i, j, count=0, minPath=MaxValue, minPos=0;
    for (i=0; i<n; i++) {
        added[i] = 0;
        minTarget[i] = 0;
    } 
    added[0] = 1;
    count++;
    while(count < n){
        minPath=MaxValue;
        for (i=1; i<n; i++) {
            if (added[i] == 0 && GE[i][minTarget[i]] < minPath) {
                minPos = i;
                minPath = GE[i][minTarget[i]];
            }
        }
        printf("Path: %d->%d\t", minPos+1, minTarget[minPos]+1);
        count++;
        added[minPos] = 1;
        for (j=1; j<n; j++) {
            if (added[j] == 0 && GE[j][minPos] < GE[j][minTarget[j]]) {
                minTarget[j] = minPos;
            }
        }
    }
}

// Dijskel Algorithm get shortest path.
// Can you coding this algorithm alone?
// Yes, I am willing to try.
// Finally I beat it!!!👊👊👊
static void Dijskel(int GE[][MaxNum], int n, int v){
    int confirms[n], minPaths[n][n], pathsPos[n], minPathCosts[n], i, j, count=0, minPos, minCost;
    for (i=0; i<n; i++) {
        minPaths[i][0] = v;
        pathsPos[i] = 1;
        minPathCosts[i] = GE[i][v];
        confirms[i] = 0;
    }
    confirms[v] = 1;
    count++;
    while(count < n){
        minPos = 0;
        minCost = MaxValue;
        for (i=0; i<n; i++) {
            if (confirms[i] == 0 && minPathCosts[i] < minCost) {
                minPos = i;
                minCost = minPathCosts[i];
            }
        }
        confirms[minPos] = 1;
        count++;
        for (i=0; i<n; i++) {
            if (confirms[i] == 0 && minPathCosts[i] > minCost+GE[i][minPos]) {
                for (j=0; j<pathsPos[minPos]; j++) {
                    minPaths[i][j] = minPaths[minPos][j];
                }
                minPaths[i][j] = minPos;
                minPathCosts[i] = minCost+GE[i][minPos];
                pathsPos[i] = pathsPos[minPos]+1;
            }
        }
    }
    for (i=0; i<n; i++) {
        for (j=0; j<pathsPos[i]; j++) {
            printf("%d -> ", minPaths[i][j]+1);
        }
        if (i == v) {
            printf("\n");
        }else{
            printf("%d\n", i+1);
        }
    }
}

static void PrimTest(){
    const int n=6, e=20;
    int GE[n][MaxNum],i,j;
    CreateUndirectionADJMatrix(GE, n, e);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", GE[i][j]);
        }
        printf("\n");
    }
    Prim(GE, n);
    putchar('\n');
}

static void DijskelTest(){
    const int n=7, e=25;
    int GE[n][MaxNum],i,j;
    CreateUndirectionADJMatrix(GE, n, e);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", GE[i][j]);
        }
        printf("\n");
    }
    Dijskel(GE, n, 3);
}


static void GetTopoSort(PVlink vertexs[], int n, int e, int topoList[]){
    int STACK[MaxNum],i,j,top=-1,k;
    PElink p;
    for (i=0; i<n; i++) {
        if (vertexs[i]->indegree == 0) {
            STACK[++top] = i;
        } 
    }
    i=0;
    while(top >= 0){
        j = STACK[top--];
        topoList[i++] = vertexs[j]->data;
        p = vertexs[j]->link;
        while(p != NULL){
            k = p->adjves;
            (vertexs[k]->indegree)--;
            if (vertexs[k]->indegree <= 0) {
                STACK[++top] = k;
            }
            p = p->link;
        }
    }
    if (i < n) {
        printf("网中存在回路\n");
    }else{
        for (j=0; j<i; j++) {
            printf("%d ", topoList[j]);
        }
        putchar('\n');
    }
}

static int JudgeTopoList(PVlink vertexs[], int topoList[], int n, int e){
    return -1;
}

static void TopoSortTest(){
    const int n=7, e=8;
    int topoList[n], indigrees[n], i, b;
    PVlink vertexs[n];
    AdjacencyList(vertexs, n, e);
    for (i=0; i<n; i++) {
        indigrees[i] = vertexs[i]->indegree;
    }
    GetTopoSort(vertexs, n, e, topoList);
    for (i=0; i<n; i++) {
        vertexs[i]->indegree = indigrees[i];
    }
    
}  


void GraphReviewMain(int argc, char *argv[]){
    printf("GraphReviewMain \n");
    //CreateAdjacencyGraph();
    //PrimTest();
    //DijskelTest();
    TopoSortTest();
}




















