//
//  CycleLinearTable.c
//  CDRLearn
//
//  Created by Zqy on 19/6/16.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "CycleLinearTable.h"
#include "LinearTablePractise.h"
#include <string.h>

void READ(ElemType *a){
    *a = malloc(sizeof(EType));
    (*a)->num = n++;
    const char *d = "data";
    strcpy((*a)->data, d);
}

LinkList CreateACycleList(int n){

    LinkList p = NULL,r = NULL;
    ElemType it = NULL;
    int i;
    for (i=0; i<n; i++) {
        READ(&it);
        LinkList t = malloc(LNodeSize);
        t->data = it;
        t->link = NULL;
        if (p == NULL) {
            p = t;
        }else{
            r->link = t;
        }
        r = t;
    }
    r->link = p;
    return p;
}

void PRINTCYCLELIST(LinkList list){
    LinkList p = list;
    printf("data.num: %d \n", p->data->num);
    p = p->link;
    while (p != list) {
        printf("data.num: %d \n", p->data->num);
        p = p->link;
    }
}

void JOSEPHUS(int n, int m, int k){
    LinkList p = CreateACycleList(n);
    LinkList r=NULL,q = p;
    int i;
    for (i=0; i<k; i++) {
        r = q;
        q = q->link;
    }
    while (q->link != q) {
        for (i=1; i<m; i++) {
            r = q;
            q = q->link;
        }
        r->link = q->link;
        printf("data.num: %d \n", q->data->num);
        free(q);
        q = r->link;
    }
    printf("最后： %d \n", q->data->num);
    
}

DLinkList CREATEDLIST(int n){
    DLinkList r=NULL,p=NULL;
    ElemType it = NULL;
    for (int i=0; i<=n; i++)
    {
        DLinkList t = malloc(DNodeSize);
        READ(&it);
        t->data = it;
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

void PRINTDLIST(DLinkList list){
    DLinkList p = list->rlink;
    while (p != list) {
        printf("data.num: %d \n", p->data->num);
        p = p->rlink;
    }
}

int INSERTD(DLinkList list, ElemType x, ElemType item){
    DLinkList p=list->rlink,q;
    
    while (p != list && p->data->num != x->num) {
        p = p->rlink;
    }
    if (p == list) {
        printf("参数错误 \n");
        return -1;
    }
    q = malloc(DNodeSize);
    q->data = item;
    q->rlink = p->rlink;
    p->rlink->llink = q;
    p->rlink = q;
    q->llink = p;
    return 1;
}

int DELETED(DLinkList list, ElemType it){
    DLinkList q = list->rlink;
    while (q != list && q->data->num != it->num) {
        q = q->rlink;
    }
    if (q == list) {
        printf("数据异常 \n");
        return -1;
    }
    q->llink->rlink = q->rlink;
    q->rlink->llink = q->llink;
    free(q);
    return 1;
}

/*
 打印文本最后n行
 */

#define DEFLINES 10
#define MAXLINE 81

typedef struct Tail{
    char data[MAXLINE];
    struct Tail *link;
}NTail, *TailList;
#define  SIZENTAIL sizeof(NTail)

void PRINTFILE(int argc, char *argv[]){
    argc--;
    argv = argv+1;
    char curline[MAXLINE], *fileName;
    int n = DEFLINES, i=0;
    TailList list, r, tmp;
    FILE *fp;
    if (argc == 3 && argv[1][0] == '-') {
        n = atoi(argv[1]+1);
        fileName = argv[2];
    }
    
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("打开文件失败 \n");
        exit(-1);
    }
    
    list = malloc(SIZENTAIL);
    list->data[0] = '\0';
    r = list;
    for (i=1; i<n; i++) {
        tmp = malloc(SIZENTAIL);
        tmp->data[0] = '\0';
        r->link = tmp;
        r = tmp;
    }
    r->link = list;
    r = list;
    
    while (fgets(curline, MAXLINE, fp) != NULL) {
        strcpy(r->data, curline);
        r = r->link;
    }
    
    for (i=0; i<n; i++) {
        printf("%s", r->data);
        r = r->link;
    }
    fclose(fp);
}


void DRDay3(int argc, char *argv[]){
    
//    LinkList p = CreateACycleList(10);
//    PRINTCYCLELIST(p);
//    JOSEPHUS(10, 3, 0);
//    DLinkList dlist = CREATEDLIST(10);
//    PRINTDLIST(dlist);
//    ElemType it = malloc(sizeof(ElemType));
//    it->num = 1;
//    ElemType insertIt = malloc(sizeof(ElemType));
//    insertIt->num = 19;
//    printf("插入后 \n");
//    INSERTD(dlist, it, insertIt);
//    PRINTDLIST(dlist);
//    
//    printf("删除后 \n");
//    DELETED(dlist, insertIt);
//    PRINTDLIST(dlist);
//    PRINTFILE(argc, argv);
//    parctice30();
//    parctice29(10);
//    practice28();
//    practice27(4);
//    practice24();
//    practice23();
//    practice22();
//    practice21();
//    practice20();
//    prcatice19();
//    prcatice18();
//    prcatice17();
//    prcatice16();
//    prcatice15();
//    prcatice14();
//    prcatice13();
//    prcatice12();
//    prcatice10();
//    prcatice9();
//    prcatice8();
//    prcatice7();
//    prcatice6();
//    prcatice5();
    prcatice4();
}








