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

#define LNodeSize sizeof(LNode)

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

int INSERTLINK4(LinkList list, int i, ElemType item){
    LinkList p,q=list;
    int j=1;
    while (j<i && q != NULL) {
        q = q->link;
        j++;
    }
    if (j != i || q == NULL) {
        printf("链表中不存在第 i 个链节点! \n");
        return -1;
    }
    p = malloc(sizeof(LNode));
    p->data = item;
    p->link = q->link;
    q->link = p;
    return 1;
}

void INSERTLINK5(LinkList *list, ElemType item){
    LinkList p,q,r=NULL;
    p = malloc(LNodeSize);
    p->data = item;
    if (*list == NULL || item->num <= (*list)->data->num) {
        p->link = *list;
        *list = p;
    }else{
        q = *list;
        while (q != NULL && item->num >= q->data->num) {
            r = q;
            q = q->link;
        }
        if (r != NULL) {
            p->link = r->link;
            r->link = p;
        }
    }
}

// r: 前驱节点
// q: 要删除节点
void DELETELINK1(LinkList *list, LinkList r, LinkList q){
    if (q == *list) {
        *list = q->link;
    }else{
        r->link = q->link;
    }
    free(q);
}

void DELETELINK2(LinkList *list, LinkList q){
    if (*list == q) {
        *list = q->link;
        free(q);
    }else{
        LinkList p = *list;
        while (p->link != q && p->link != NULL) {
            p = p->link;
        }
        if (p->link != NULL) {
            p->link = q->link;
            free(q);
        }
    }
}

void DELETELIST(LinkList *list)
{
    LinkList q = *list;
    while (q != NULL) {
        *list = q->link;
        free(q);
        q = *list;
    }
}

void DELETEITEM(LinkList *list, ElemType item){
    LinkList q=*list,p=(*list)->link;
    while (p != NULL) {
        if (p->data->num == item->num) {
            q->link = p->link;
            free(p);
            p = q->link;
        }else{
            q = p;
            p = p->link;
        }
    }
    if ((*list)->data->num == item->num) {
        q = *list;
        *list = (*list)->link;
        free(q);
    }
}

void INVERT(LinkList *list){
    LinkList q=NULL,r,p=*list;
    while (p != NULL) {
        r = p;
        p = p->link;
        r->link = q;
        q = r;
    }
    *list = q;
}

void CONNECT(LinkList lista, LinkList listb){
    LinkList p = lista;
    while (p->link != NULL) {
        p = p->link;
    }
    p->link = listb;
}

LinkList MERGELIST(LinkList lista, LinkList listb){
    LinkList listc,p=lista,q=listb,r;
    if (lista->data->num <= listb->data->num) {
        listc = lista;
        p = p->link;
    }else{
        listc = listb;
        q = q->link;
    }
    r = listc;
    while (p != NULL && q != NULL) {
        if (p->data->num <= q->data->num) {
            r->link = p;
            r = p;
            p = p->link;
        }else{
            r->link = q;
            r = q;
            q = q->link;
        }
    }
    r->link = p?p:q;
    return listc;
}

LinkList COPY(LinkList list)
{
    LinkList listb;
    if (list == NULL) {
        return NULL;
    }else{
        listb = malloc(LNodeSize);
        listb->data = list->data;
        listb->link = COPY(list->link);
    }
    return listb;
}

LinkList LINKSORT(ElemType A[], int n){
    LinkList list = NULL;
    int i;
    for (i=0; i<n; i++) {
        INSERTLINK5(&list, A[i]);
    }
    return list;
}

void REMOVE(LinkList *list){
    if (*list == NULL) {
        printf("数据异常 \n");
        return;
    }
    LinkList q=NULL,r=*list,s=*list,p=*list;
    p = p->link;
    while (p != NULL) {
        if (p->data->num >= r->data->num) {
            q = s;
            r = p;
        }
        s = p;
        p = p->link;
    }
    if (s != r) {
        if (r == *list) {
            *list = (*list)->link;
        }else{
            q->link = r->link;
        }
        s->link = r;
        r->link = NULL;
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
    PRINTDATA(head);
    printf("长度：%d \n", LENGHT(head));
    printf("后续操作 \n");
    ElemType it = malloc(sizeof(ElemType));
    
//    // 找数据
//    it->num = 6;
//    LinkList find = FIND(head, it);
//    printf("找到的数据：%d \n", find->data->num);
    
//    // 头插入
//    READ(&it);
//    INSERTLINK1(&head, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
//    
//    // 尾插入
//    READ(&it);
//    INSERTLINK2(&head, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
//    
//    // 指定节点插入
//    READ(&it);
//    INSERTLINK3(&head, head->link->link, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
    
//    // 指定位置后面插入
//    READ(&it);
//    INSERTLINK4(head, 4, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
    
//    // 按值有序插入
//    READ(&it);
//    it->num = 7;
//    INSERTLINK5(&head, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));

//    // 按节点删除
//    DELETELINK2(&head, head->link->link->link);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));

      // 销毁链表
//    DELETELIST(&head);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));

//      // 按值删除
//    READ(&it);
//    it->num = 7;
//    DELETEITEM(&head, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));

//    // 反转
//    INVERT(&head);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
    
//    // 合并
//    int j = 8;
//    n = 6;
//    LinkList head2 = CREATE(j);
//    PRINTDATA(head2);
//    printf("长度：%d \n", LENGHT(head2));
//    printf("合并后 \n");
//    LinkList c = MERGELIST(head, head2);
//    PRINTDATA(c);
//    printf("长度：%d \n", LENGHT(c));
    
//    // copy
//    LinkList d = COPY(head);
//    PRINTDATA(d);
//    printf("长度：%d \n", LENGHT(d));

//    // 排序
//    ElemType it1 = malloc(sizeof(ElemType));
//    it1->num = 4;
//    ElemType it2 = malloc(sizeof(ElemType));
//    it2->num = 9;
//    ElemType it3 = malloc(sizeof(ElemType));
//    it3->num = 2;
//    ElemType it4 = malloc(sizeof(ElemType));
//    it4->num = 4;
//    ElemType it5 = malloc(sizeof(ElemType));
//    it5->num = 1;
//    ElemType it6 = malloc(sizeof(ElemType));
//    it6->num = 7;
//    ElemType it7 = malloc(sizeof(ElemType));
//    it7->num = 0;
//    ElemType it8 = malloc(sizeof(ElemType));
//    it8->num = 2;
//    ElemType A[8] = {it1, it2, it3, it4, it5, it6, it7, it8};
//    LinkList S = LINKSORT(A, 8);
//    PRINTDATA(S);
//    printf("长度：%d \n", LENGHT(S));
//
//    // 指定位置后面插入
//    READ(&it);
//    INSERTLINK4(head, 4, it);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
//    REMOVE(&head);
//    PRINTDATA(head);
//    printf("长度：%d \n", LENGHT(head));
    

    
}
