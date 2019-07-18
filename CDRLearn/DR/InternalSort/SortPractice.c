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

static LNode CREATEDLIST(int data[], int n){
    LNode r=NULL,p=NULL,head;
    head = malloc(sizeof(Node));
    head->data = n;
    head->llink = NULL;
    head->rlink = NULL;
    for (int i=0; i<n; i++)
    {
        LNode t = malloc(sizeof(Node));
        t->data = data[i];
        t->llink = NULL;
        t->rlink = NULL;
        if (p == NULL) {
            p = t;
            head->rlink = p;
            p->llink = head;
        }else{
            r->rlink = t;
            t->llink = r;
        }
        r = t;
    }
    r->rlink = head;
    head->llink = r;
    return head;
}

static void PRINTDLIST(LNode list){
    printf("data count: %d \n", list->data);
    LNode p = list->rlink;
    while (p != list) {
        printf("data.num: %d \n", p->data);
        p = p->rlink;
    }
}
static void Print_Single_List(LNode list){
    LNode p = list->rlink;
    printf("data count: %d \n", list->data);
    while (p != NULL) {
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
static void LinearList_Sort(LNode list){
    if (list->rlink == list) {
        /* Linear list is NULL */
        return;
    }
    LNode i=list->rlink->rlink,j,p;
    while (i != list) {
        p = i->rlink;
        j = i->llink;
        LinearListDelNode(list, i);
        while (j != list) {
            if (j->data <= i->data) {
                break;
            }
            j = j->llink;
        }
        LinearListInsertNode(list, j, i);
        i = p;
    }
    
}

static void Practice5(){
    const int n = 10;
    int A[n] = {2, 6, 3, 1, 7, 5, 9, 10, 4, 8};
    LNode list = CREATEDLIST(A,n);
    PRINTDLIST(list);
    printf("----------------- \n");
    LinearList_Sort(list);
    PRINTDLIST(list);
}

// Create a single Linear-list incloud head node, and the head node called "list".
static LNode Create_Single_List(int data[], int n){
    LNode list, r=NULL, p=NULL;
    list = malloc(sizeof(Node));
    list->data = n;
    list->rlink = NULL;
    list->llink = NULL;
    int i;
    for (i=0; i<n; i++) {
        p = malloc(sizeof(Node));
        p->rlink = NULL;
        p->llink = NULL;
        p->data = data[i];
        if (r == NULL) {
            list->rlink = p;
        }else{
            r->rlink = p;
        }
        r = p;
    }
    return list;
}

// Include head node Linear list Select-Sort,the head called "list". Memory outside of the linked list cannot be used, can not modify Linear list data.
// 5  2, 6, 3, 1, 7
static void Select_Sort_SingleList(LNode list){
    LNode p = list, r, min, k, s=NULL;
    while (p->rlink != NULL) {
        min = p->rlink;
        r = min->rlink;
        s = k = min;
        while (r != NULL) {
            if (r->data < min->data) {
                s = k;
                min = r;
            }
            k = r;
            r = r->rlink;
        }
        // Change p->rlink and minv
        if (min != p->rlink) {
            s->rlink = min->rlink;
            min->rlink = p->rlink;
            p->rlink = min;
        }
        p = min;
    }
}

static void Practice4(){
    const int n = 10;
    int A[n] = {2, 6, 3, 1, 7, 5, 9, 10, 4, 8};
    LNode list = Create_Single_List(A, n);
    Print_Single_List(list);
    printf("--------------------\n");
    Select_Sort_SingleList(list);
    Print_Single_List(list);
}

static void Adjust(int K[], int i, int n){
    int j = i*2, temp;
    temp = K[i];
    while (j <= n) {
        if (j<n && K[j] < K[j+1]) {
            j++;
        }
        if (temp >= K[j]) {
            break;
        }
        K[j/2] = K[j];
        j *= 2;
    }
    K[j/2] = temp;
}

static void Insert_Heap(int A[], int *n, int k){
    int i,temp,N = *n;;
    for (i=N/2; i>=1; i--) {
        Adjust(A, i, N);
    }
    for (i=1; i<=*n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    A[++N] = k;
    (*n) = N;
    for (i = N; i>1; i/=2) {
        if (A[i/2] < A[i]) {
            temp = A[i];
            A[i] = A[i/2];
            A[i/2] = temp;
        }else{
            break;
        }
    }
}

static void Practice3(){
    int n = 10,i;
    int K[] = {-1, 6, 5, 3, 1, 10, 7, 7, 4, 2, 8};
    Insert_Heap(K, &n, 11);
    for (i=1; i<=n; i++) {
        printf("%d ", K[i]);
    }
    printf("\n");
}

int SortPracticeMain(int argc, char *argv[]){
    printf("Hello Sort practice!!! \n");
//    Practice8();
//    Practice7();
//    Practice6();
//    Practice5();
//    Practice4();
    Practice3();
    return 0;
}
