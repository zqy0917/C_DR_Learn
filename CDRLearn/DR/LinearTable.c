//
//  LinearTable.c
//  StudyDay1
//
//  Created by Zqy on 19/6/15.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "LinearTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int n = 1;

typedef struct
{
    int num;
    char data[10];
}EType, *ElemType;

void READ(ElemType *a){
    *a = malloc(sizeof(EType));
    (*a)->num = n++;
    char *d = "data";
    strcpy((*a)->data, d);
}

void INITITEM(EType A[], int n){
    for (int i=1; i<=n; i++) {
        ElemType item = malloc(sizeof(EType));
        item->num = i;
        char *data = "data";
        strcpy(item->data, data);
        A[i-1] = *item;
    }
}

void INITITEM2(EType A[], int n){
    for (int i=1; i<=n; i++) {
        ElemType item = malloc(sizeof(EType));
        item->num = i;
        char *data = "data";
        strcpy(item->data, data);
        A[i-1] = *item;
    }
}

void PRINTITEMS(EType A[], int n){
    int i;
    for (i=0; i<n; i++) {
        EType item = A[i];
        printf("第 %d 个元素, data: %s \n", item.num, item.data);
    }
}

void DELETEITEM2(EType A[], int *n, EType item)
{
    int i, k=-1;
    for (i=0; i<*n; i++) {
        EType it = A[i];
        if (it.num == item.num) {
            k++;
        }else{
            A[i-k-1] = it;
        }
    }
    *n = *n-k-1;
}

void INSERTITEM(EType A[], int *n, int i, EType item)
{
    int j;
    if (i<1 || i>*n+1) {
        printf("数据异常 \n");
        return;
    }
    for (j=*n-1; j>=i-1; j--) {
        A[j+1] = A[j];
    }
    A[i-1] = item;
    ++(*n);
}

void INSERTITEMSORT(EType A[], int *n, EType item)
{
    if (item.num >= A[*n-1].num) {
        A[*n++] = item;
    }else{
        int i=0;
        while (item.num >= A[i].num)
        {
            i++;
        }
        INSERTITEM(A, n, i+1, item);
    }
}

void purge(int A[], int *n)
{
    int i, k=0;
    if (*n<=1) {
        return;
    }
    for (i=1; i<*n; i++){
        if (A[k] != A[i]) {
            A[++k] = A[i];
        }
    }
    *n = k+1;
}

void PRINT(int A[], int n){
    int i;
    for (i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

typedef struct node
{
    ElemType data;
    struct node *link;
    
}LNode, *LinkList;

LinkList CREATE(int n){
    LinkList p,r=NULL,list = NULL;
    ElemType a = NULL;
    int i;
    for (i=1; i<=n; i++) {
        READ(&a);
        p = malloc(sizeof(LNode));
        p->data = a;
        p->link = NULL;
        if (list == NULL) {
            list = p;
        }else{
            r->link = p;
        }
        r = p;
    }
    return list;
}

int PRINTDATA(LinkList list){
    LinkList p = list;
    while (p != NULL)
    {
        printf("data.num: %d \n", p->data->num);
        p = p->link;
    }
    return n;
}

int LENGHT(LinkList list){
    LinkList p = list;
    int n=0;
    while (p != NULL)
    {
        n++;
        p = p->link;
    }
    return n;
}

int LENGHT2(LinkList list){
    if (list == NULL) {
        return 0;
    }else{
        return 1 + LENGHT2(list->link);
    }
}

int ISEMPTY(LinkList list){
    return list == NULL;
}

static LinkList FIND(LinkList list, ElemType item){
    LinkList p = list;
    while (p->data->num != item->num)
    {
        p = p->link;
    }
    return p;
}

void INSERTLINK1(LinkList *list, ElemType item){
    LinkList p = malloc(sizeof(LNode));
    p->link = *list;
    p->data = item;
    *list = p;
}

void INSERTLINK2(LinkList *list, ElemType item){
    LinkList p,r;
    p = malloc(sizeof(LNode));
    p->link = NULL;
    p->data = item;
    r = *list;
    while (r->link != NULL)
    {
        r = r->link;
    }
    r->link = p;
}

void INSERTLINK3(LinkList *list, LinkList q, ElemType item){
    LinkList p = malloc(sizeof(LNode));
    p->data = item;
    p->link = NULL;
    if (ISEMPTY(*list)) {
        *list = p;
    }else{
        p->link = q->link;
        q->link = p;
    }
}

void DRDay2()
{
    // printf("DR-LinearTable, come on \n");
    // int n = 10;
    // ElemType A[n+1];
    // INITITEM(A, n);
    // PRINTITEMS(A, n);
    // printf("删除后：\n");
    // ElemType item = A[n/2];
    // // should delete item 6
    // DELETEITEM2(A, &n, item);
    // PRINTITEMS(A, n);
    // ElemType *it = malloc(sizeof(ElemType));
    // it->num = 6;
    // INSERTITEMSORT(A, &n, *it);
    // printf("insert后：\n");
    // PRINTITEMS(A, n);
    
    // INSERTITEMSORT(
    
    // int n=10;
    // int A[10] = {1, 1, 2, 3, 4, 4, 5, 5, 9, 9};
    // purge(A, &n);
    // PRINT(A, n);
    
    int m = 10;
    LinkList head = CREATE(m);
    printf("长度：%d \n", LENGHT(head));
    ElemType it = malloc(sizeof(ElemType));
    it->num = 6;
    LinkList find = FIND(head, it);
    printf("找到的数据：%d \n", find->data->num);
    
    // 头插入
    READ(&it);
    INSERTLINK1(&head, it);
    PRINTDATA(head);
    printf("长度：%d \n", LENGHT(head));
    
    // 尾插入
    READ(&it);
    INSERTLINK2(&head, it);
    PRINTDATA(head);
    printf("长度：%d \n", LENGHT(head));
    
    // 指定节点插入
    READ(&it);
    INSERTLINK3(&head, head->link->link, it);
    PRINTDATA(head);
    printf("长度：%d \n", LENGHT(head));
    
}
