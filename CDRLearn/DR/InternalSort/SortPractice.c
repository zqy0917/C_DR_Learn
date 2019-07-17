//
//  SortPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/16.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "SortPractice.h"
#include <stdlib.h>

#define MaxNum 100

static void PrintArray(int K[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%d ", K[i]);
    }
    printf("\n");
}

/* 荷兰国旗 */
static void Practice9(){
    
}

static void Index_Sort(int K[], int n){
    int i,j,tmp[n],a,count, C[n];
    for (i=0; i<n; i++) {
        a = K[i];
        count=0;
        for (j=0; j<n; j++) {
            if (K[j] < a) {
                count++;
            }
        }
        tmp[i] = count;
    }
    for(i=0; i<n; i++){
        C[tmp[i]] = K[i];
    }
    for (i=0; i<n; i++) {
        K[i] = C[i];
    }
}

static void Practice8(){
    const int n = 10;
    int K[n] = {6, 5, 3, 1, 10, 7, 8, 4, 2, 9};
    Index_Sort(K, n);
    PrintArray(K, n);
}

static void Sort_DoubleArray(int K[][MaxNum], int m, int n){
    int i,j,mins[m],minIndexs[m],min,C[m][MaxNum],temp1,temp2;
    for(i=0; i<m; i++){
        min = K[i][0];
        for(j=0; j<n; j++){
            if (K[i][j] < min) {
                min = K[i][j];
            }
        }
        mins[i] = min;
        minIndexs[i] = i;
    }
    for (i=1; i<m; i++) {
        temp1 = mins[i];
        temp2 = minIndexs[i];
        j = i-1;
        while (j > -1 && temp1 < mins[j]) {
            mins[j+1] = mins[j];
            minIndexs[j+1] = minIndexs[j];
            j--;
        }
        mins[j+1] = temp1;
        minIndexs[j+1] = temp2;
    }
    
    for (i=0; i<m; i++) {
        for(j=0; j<n; j++){
            C[i][j] = K[minIndexs[i]][j];
        }
    }
    for (i=0; i<m; i++) {
        for(j=0; j<n; j++){
            K[i][j] = C[i][j];
        }
    }
    for (i=0; i<m; i++) {
        for(j=0; j<n; j++){
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }
}

static void Practice7(){
    const int m = 5;
    const int n = 5;
    int K[m][MaxNum] = {
        {6, 5, 3, 1, 10},
        {7, 8, 6, 7, 9},
        {7, 8, 4, 6, 9},
        {7, 8, 3, 4, 9},
        {7, 8, 4, 2, 9}
    };
    Sort_DoubleArray(K, m, n);
}

/* 负数排在0前面，正数0后面 */
static void Sort_Sequence(int K[], int n){
    int i=0,negNum=0,posNum=0,C[n];
    for (i=0; i<n; i++) {
        if (K[i] < 0) {
            C[negNum++] = K[i];
        }else if (K[i] == 0) {
            
        }else if (K[i] > 0) {
            C[n-1-posNum++] = K[i];
        }
    }
    for (i=negNum; i<n-posNum; i++) {
        C[i] = 0;
    }
    for (i=0; i<n; i++) {
        K[i] = C[i];
    }
}

static void Practice6(){
    const int n = 10;
    int K[n] = {-1, 2, 0, 9, -9, 7, 0, 4, -2, 0};
    Sort_Sequence(K, n);
    PrintArray(K, n);
}

typedef struct node{
    int data;
    struct node *rlink;
    struct node *llink;
}Node, *LNode;

static LNode CREATEDLIST(int n){
    LNode r=NULL,p=NULL;
    for (int i=0; i<=n; i++)
    {
        LNode t = malloc(sizeof(Node));
        t->data = i+1;
        t->llink = NULL;
        t->rlink = NULL;
        if (p == NULL) {
            p = t;
        }else{
            r->rlink = t;
            t->llink = r;
        }
        r = t;
    }
    r->rlink = p;
    p->llink = r;
    return p;
}

static void PRINTDLIST(LNode list){
    printf("data.num: %d \n", list->data);
    LNode p = list->rlink;
    while (p->rlink != list) {
        printf("data.num: %d \n", p->data);
        p = p->rlink;
    }
}

// Only delete link
static void LinearListDelNode(LNode list, LNode link){
    LNode lastLink = link->llink;
    LNode nextLink = link->rlink;
    lastLink->rlink = nextLink;
    nextLink->llink = lastLink;
    link->llink = link->rlink = NULL;
}

static void LinearListInsertNode(LNode list, LNode lastNode, LNode node){
    LNode nextLink = lastNode->rlink;
    node->llink = lastNode;
    node->rlink = nextLink;
    lastNode->rlink = node;
    nextLink->llink = node;
}

// Insert sort linear list
// 2  2  1  5
static void LinearList_Sort(LNode list){
    if (list->rlink == list) {
        /* Linear list is NULL */
        return;
    }
    LNode i=list->rlink->rlink,j;
    while (i != list) {
        j = i->llink;
        LinearListDelNode(list, i);
        while (j != list) {
            if (j->data <= i->data) {// 未完待续🔥🔥🔥🔥🔥
                break;
            }
            j = j->llink;
        }
        // insert behind j
        LinearListInsertNode(list, j, i);
    }
    
}


static void Practice5(){
    LNode list = CREATEDLIST(10);
    list->rlink->rlink->data = 1;
    list->rlink->rlink->rlink->rlink->data = 3;
    list->rlink->rlink->rlink->rlink->rlink->rlink->rlink->data = 2;
    PRINTDLIST(list);
    printf("----------------- \n");
    LinearList_Sort(list);
    PRINTDLIST(list);
}
int SortPracticeMain(int argc, char *argv[]){
    printf("Hello Sort practice!!! \n");
//    Practice8();
//    Practice7();
//    Practice6();
    Practice5();
    
    return 0;
}
