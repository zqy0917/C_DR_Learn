//
//  LinearListReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/8.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "LinearListReview.h"
#include <stdlib.h>

#define MaxNum 100

typedef struct LData{
    int data;
    struct LData *llink;
    struct LData *rlink;
}LData, *PLink;

static PLink CreateSingleList(int data[], int n){
    PLink list=NULL,r=NULL,p;
    int i;
    for (i=0; i<n; i++) {
        p = malloc(sizeof(LData));
        p->llink = p->rlink = NULL;
        p->data = data[i];
        if (r == NULL) {
            list = p;
        }else{
            r->rlink = p;
        }
        r = p;
    }
    return list;
}

static PLink SearchLink(PLink list, int k){
    if (list == NULL) {
        return NULL;
    }
    if (list->data == k) {
        return list;
    }
    return SearchLink(list->rlink, k);
}

static void PrintSingleList(PLink list){
    while(list != NULL){
        fprintf(stdout, "%d\n", list->data);
        list = list->rlink;
    }
}

static PLink CreateSingleCycleList(int data[], int n){
    PLink list=NULL,r=NULL,p;
    int i;
    for (i=0; i<n; i++) {
        p = malloc(sizeof(LData));
        p->llink = p->rlink = NULL;
        p->data = data[i];
        if (r == NULL) {
            list = p;
        }else{
            r->rlink = p;
        }
        r = p;
    }
    r->rlink = list;
    return list;
}

static void PrintSingleCycleList(PLink list){
    PLink r = list;
    if (r != NULL) {
        fprintf(stdout, "%d\n", r->data);
        r = r->rlink;
    }
    while(r != list){
        fprintf(stdout, "%d\n", r->data);
        r = r->rlink;
    }
}

static PLink CreateDoubleCycleList(int data[], int n){
    PLink list=NULL,r=NULL,p;
    int i;
    for (i=0; i<n; i++) {
        p = malloc(sizeof(LData));
        p->llink = p->rlink = NULL;
        p->data = data[i];
        if (r == NULL) {
            list = p;
        }else{
            r->rlink = p;
            p->llink = r;
        }
        r = p;
    }
    r->rlink = list;
    list->llink = r;
    return list;
}

static void PrintDoubleCycleList(PLink list){
    PLink r = list;
    if (r != NULL) {
        fprintf(stdout, "%d\n", r->data);
        r = r->rlink;
    }
    while(r != list){
        fprintf(stdout, "%d\n", r->data);
        r = r->rlink;
    }
}

static void SingleListPractice(){
    const int n=10;
    int data[n] = {8, 3, 5, 9, 1, 2, 4, 6, 7, 10};
    PLink list = CreateSingleList(data, n);
    PrintSingleList(list);
    PLink t = SearchLink(list, 12);
    if (t != NULL) {
        printf("Search result:%d\n", t->data);
    }else{
        printf("Not found\n");
    }
}

static void SingleCycleListPractice(){
    const int n=10;
    int data[n] = {8, 3, 5, 9, 1, 2, 4, 6, 7, 10};
    PLink list = CreateSingleCycleList(data, n);
    PrintSingleCycleList(list);
}

static void DoubleCycleListPractice(){
    const int n=10;
    int data[n] = {8, 3, 5, 9, 1, 2, 4, 6, 7, 10};
    PLink list = CreateDoubleCycleList(data, n);
    PrintDoubleCycleList(list);
}

void LinearListReviewMain(int argc, char *argv[]){
    printf("Linear list review \n");
   
    // SingleListPractice();
    // SingleCycleListPractice();
    // DoubleCycleListPractice();
    
}




