//
//  LinearTablePractise.c
//  CDRLearn
//
//  Created by Zqy on 19/6/16.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "LinearTablePractise.h"


static DLinkList CREATEDLIST(const int n){
    DLinkList list=NULL,r=NULL;
    ElemType it;
    int i;
    for (i=0; i<=n; i++){
        READ(&it);
        it->num = i;
        DLinkList d = malloc(DNodeSize);
        d->data = it;
        d->llink = NULL;
        d->rlink = NULL;
        if (i == 0) {
            d->data->num = -1;
            list = d;
        }else{
            r->rlink = d;
            d->llink = r;
        }
        r = d;
    }
    r->rlink = list;
    list->llink = r;
    return list;
}

void CHANGEDLIST(DLinkList list){
    DLinkList p = list->rlink;
    int i=1;
    while (p != list) {
        if (i % 2 == 0) {
            p->data->num = -i;
        }
        i++;
        p = p->rlink;
    }
}

/*将带头的双向循环链表中所有 >0 的元素放到 <0 的前面*/
int parctice30(){
    DLinkList head = CREATEDLIST(10);
    CHANGEDLIST(head);
    PRINTDLIST(head);
    
    DLinkList p = head->rlink;
    if (p->rlink == p) {
        printf("空链表 \n");
        return -1;
    }
    while (p != head) {
        if (p->data->num > 0) {
            DLinkList tmp = p->rlink;
            p->llink->rlink = p->rlink;
            p->rlink->llink = p->llink;
            p->rlink = head->rlink;
            p->llink = head;
            head->rlink = p;
            p->rlink->llink = p;
            p = tmp;
        }else{
            p = p->rlink;
        }
    }
    
    printf("排序后 \n");
    PRINTDLIST(head);
    
    return 1;
}

void parctice29(int n){
    DLinkList list=NULL, r=NULL;
    ElemType it=NULL;
    int i;
    int j;
    for (i=0; i<=n; i++) {
        READ(&it);
        DLinkList t = malloc(DNodeSize);
        t->data = it;
        t->llink = NULL;
        t->rlink = NULL;
        if (i == 0) {
            // -1 代表链表头
            it->num = -1;
            list = t;
        }else{
            scanf("%d", &j);
            it->num = j;
            r->rlink = t;
            t->llink = r;
        }
        r = t;
    }
    r->rlink = list;
    list->llink = r;
    while (r != list) {
        printf("%d ", r->data->num);
        r = r->llink;
    }
    printf("\n");
}

int practice28(){
    DLinkList list=NULL, r=NULL, p=NULL;
    ElemType it=NULL;
    int j;
    while (scanf("%d", &j)){
        if (j == -1) {
            break;
        }
        READ(&it);
        DLinkList t = malloc(DNodeSize);
        t->data = it;
        t->llink = NULL;
        t->rlink = NULL;
        it->num = j;
        if (list == NULL) {
            list = t;
        }else{
            r->rlink = t;
            t->llink = r;
        }
        r = t;
    }
    if (list == NULL) {
        printf("链表为空 \n");
        return 0;
    }
    r->rlink = list;
    list->llink = r;
    p = r;
    r=list;
    int symmetry = 1;
    while (1) {
        if (p->data->num != r->data->num) {
            symmetry = 0;
            break;
        }
        if (r->rlink == p || r->rlink == p->llink) {
            break;
        }
        r = r->rlink;
        p = p->llink;
    }
    printf("对称：%d \n", symmetry);
    return symmetry;
}

void practice27(int delNum){
    DLinkList list,head = CREATEDLIST(10);
    head->llink->data->num = 4;
    head->llink->llink->data->num = 4;
    head->rlink->rlink->data->num = 4;
    head->rlink->data->num = 4;
    list = head->rlink;
    while (list != head) {
        if (list->data->num == delNum){
            DLinkList tmp = list->rlink;
            list->llink->rlink = list->rlink;
            list->rlink->llink = list->llink;
            free(list);
            list = tmp;
        }else{
            list = list->rlink;
        }
    }
    PRINTDLIST(head);
}

void PRINTDLRULIST(DLRULinkList list){
    DLRULinkList t = list;
    while (t != NULL) {
        printf("data.num: %d, freq: %d \n", t->data->num, t->freq);
        t = t->rlink;
    }
}

void INSERTSORT(DLRULinkList *list, DLRULinkList node) {
    node->llink = NULL;
    node->rlink = NULL;
    if (*list == NULL) {
        *list = node;
    }else if (node->freq >= (*list)->freq) {
        node->rlink = *list;
        (*list)->llink = node;
        *list = node;
    }else{
        DLRULinkList r = (*list)->rlink;
        while (r != NULL) {
            if (node->freq >= r->freq) {
                node->rlink = r;
                node->llink = r->llink;
                r->llink->rlink = node;
                r->llink = node;
                break;
            }else{
                r = r->rlink;
            }
        }
    }
}

// freq 加 1，并且保持链表按照 freq 递减排列，类似于 LRU 淘汰算法
void LOCATE(DLRULinkList *list, int x){
    DLRULinkList p = *list;
    DLRULinkList lruHead=NULL,r=NULL;
    while (p != NULL) {
        DLRULinkList tmp = p->rlink;
        if (p->data->num == x) {
            (p->freq) += 1;
            // 将p从原链表中先删除,后续在按序添加
            if (p->llink == NULL) {
                *list = p->rlink;
            }else if (p->rlink == NULL) {
                p->llink->rlink = NULL;
            }else{
                p->llink->rlink = p->rlink;
                p->rlink->llink = p->llink;
            }
            p->llink = NULL;
            p->rlink = NULL;
            if (lruHead == NULL) {
                lruHead = p;
            }else{
                r->rlink = p;
                p->llink = r;
            }
            r = p;
        }
        p = tmp;
    }
    
    // 表明至少存在一个需要排序的链节点, 按序插入回链表
    while (lruHead != NULL) {
        DLRULinkList next = lruHead->rlink;
        INSERTSORT(list, lruHead);
        lruHead = next;
    }
}
void practice26(){
    const int n=10;
    int i;
    ElemType it;
    DLRULinkList list=NULL,r=NULL;
    for (i=1; i<=n; i++) {
        READ(&it);
        it->num = i;
        DLRULinkList t = malloc(DLRUNodeSize);
        t->llink = NULL;
        t->rlink = NULL;
        t->data = it;
        t->freq = 0;
        if (list == NULL) {
            list = t;
        }else{
            r->rlink = t;
            t->llink= r;
        }
        r = t;
    }
    list->rlink->data->num = 4;
    list->rlink->rlink->data->num = 4;
    PRINTDLRULIST(list);
    printf("-------开始操作-------- \n");
    LOCATE(&list, 1);
    LOCATE(&list, 1);
    LOCATE(&list, 5);
    LOCATE(&list, 5);
    LOCATE(&list, 5);
    LOCATE(&list, 6);
    LOCATE(&list, 6);
    LOCATE(&list, 6);
    LOCATE(&list, 6);
    LOCATE(&list, 5);
    LOCATE(&list, 8);
    LOCATE(&list, 8);
    LOCATE(&list, 9);
    PRINTDLRULIST(list);
    
}

// 线性链表应用，略
void practice25(){}

static LinkList CreateList(int n){
    
    LinkList p = NULL,r = NULL;
    ElemType it = NULL;
    int i;
    for (i=1; i<=n; i++) {
        READ(&it);
        it->num = i;
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
    return p;
}

LinkList CreateACycleListHead(int n){
    
    LinkList p = NULL,r = NULL;
    ElemType it = NULL;
    int i;
    for (i=0; i<=n; i++) {
        READ(&it);
        it->num = i;
        LinkList t = malloc(LNodeSize);
        t->data = it;
        t->link = NULL;
        if (p == NULL) {
            // 头节点存表长
            p = t;
            p->data->num = n;
        }else{
            r->link = t;
        }
        r = t;
    }
    if (r != NULL) {
        r->link = p;
    }
    return p;
}

static LinkList CreateACycleList(int n){
    
    LinkList p = NULL,r = NULL;
    ElemType it = NULL;
    int i;
    for (i=1; i<=n; i++) {
        READ(&it);
        it->num = i;
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
    if (r != NULL) {
        r->link = p;
    }
    return p;
}

LinkList CreateACycleListRear(int n){
    
    LinkList p = NULL,r = NULL;
    ElemType it = NULL;
    int i;
    for (i=1; i<=n; i++) {
        READ(&it);
        it->num = i;
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
    if (r != NULL) {
        r->link = p;
    }
    return r;
}

void PROINTREARLIST(LinkList rear){
    if (rear == NULL) {
        printf("空链表 \n");
        return;
    }
    LinkList r,head = rear->link;
    printf("data.num: %d \n", head->data->num);
    r = head->link;
    while (r != head) {
        printf("data.num: %d \n", r->data->num);
        r = r->link;
    }
}

static void PROINTCYCLELIST(LinkList list){
    printf("链表长度: %d \n", list->data->num);
    LinkList r;
    r = list->link;
    while ((r != list) && r != NULL) {
        printf("data.num: %d \n", r->data->num);
        r = r->link;
    }
}

static void PRINTCYCLEUNHEADLIST(LinkList list){
    if (list == NULL) {
        printf("Empty linear list \n");
        return;
    }
    printf("data.num: %d \n", list->data->num);
    LinkList p = list->link;
    while (p != list) {
        printf("data.num: %d \n", p->data->num);
        p = p->link;
    }
}


static void PROINTLIST(LinkList list){
    LinkList r=list;
    while (r != NULL) {
        printf("data.num: %d \n", r->data->num);
        r = r->link;
    }
}

void practice24() {
    LinkList rear = CreateACycleListRear(8);
    PROINTREARLIST(rear);
    printf("--------连接后-------- \n");
    if (!rear) {
        printf("空链表 \n");
        return;
    }
    LinkList head = rear->link;
    LinkList r=NULL,p=head,rearConnect=rear;
    while (p != rear) {
        LinkList t = malloc(LNodeSize);
        t->data = p->data;
        if (r == NULL) {
            t->link = head;
            rearConnect = t;
        }else{
            t->link = r;
        }
        rear->link = t;
        r = t;
        p = p->link;
    }
    PROINTREARLIST(rearConnect);
}

// 逆转链表方向
void practice23(){
    LinkList q=NULL,r,rear,list = CreateACycleListHead(10);
    PROINTCYCLELIST(list);
    rear = list->link;
    while (rear->link != list) {
        rear = rear->link;
    }
    r = list->link;
    while (r != rear) {
        LinkList tmp = r->link;
        list->link = r->link;
        rear->link = r;
        if (q == NULL) {
            r->link = list;
        }else{
            r->link = q;
        }
        q = r;
        r = tmp;
    }
    printf("反转后 \n");
    PROINTCYCLELIST(list);
}

void CUTLIST(LinkList *head1, LinkList *head2, LinkList list){
    ElemType it;
    LinkList h1,n,h2,m,p=list;
    READ(&it);
    it->num = 0;
    h1 = malloc(LNodeSize);
    h1->data = it;
    h1->link = NULL;
    READ(&it);
    it->num = 0;
    h2 = malloc(LNodeSize);
    h2->data = it;
    h2->link = NULL;
    n = h1;
    m = h2;
    int i=0,j=0,q=0;
    while (p != NULL) {
        LinkList next = p->link;
        if (i % 2 == 0) {
            n->link = p;
            n = p;
            j++;
        }else{
            m->link = p;
            m = p;
            q++;
        }
        p->link = NULL;
        p = next;
        i++;
    }
    h1->data->num = j;
    h2->data->num = q;
    if (n != NULL) {
        n->link = h1;
    }
    if (m != NULL) {
        m->link = h2;
    }
    *head1 = h1;
    *head2 = h2;
}

void practice22() {
    LinkList list = CreateList(9);
    PROINTLIST(list);
    printf("开始分离 \n");
    LinkList head1=NULL, head2=NULL;
    CUTLIST(&head1, &head2, list);
    printf("head1 表长度：%d \n", head1->data->num);
    PROINTCYCLELIST(head1);
    printf("head2 表长度：%d \n", head2->data->num);
    PROINTCYCLELIST(head2);
}

void DELETEPLAST(LinkList p){
    LinkList q=p->link,n=p;
    
    while (q->link != p) {
        n = q;
        q = q->link;
    }
    n->link = q->link;
    free(q);
    q = NULL;
}

void practice21(){
    LinkList list = CreateACycleList(2);
    PRINTCYCLEUNHEADLIST(list);
    LinkList p = list->link->link;
    printf("p: %d \n", p->data->num);
    DELETEPLAST(p);
    PRINTCYCLEUNHEADLIST(p);
}

void practice20(){
    int k=5;
    LinkList list = CreateACycleList(k);
    int i;
    while (1) {
        scanf("%d", &i);
        if (i == -1) {
            break;
        }
        list->data->num = i;
        list = list->link;
    }
    PRINTCYCLEUNHEADLIST(list);
}

// 删除多余使链表数据域值不同
void prcatice19(){
    LinkList list = CreateList(10);
    list->link->data->num = 1;
    list->link->link->link->data->num = 6;
    PROINTLIST(list);
    LinkList p=list->link,q=list,r;
    q->link = NULL;
    int exist;
    while (p != NULL) {
        r = q;
        exist = 0;
        while (1) {
            if (r->data->num == p->data->num) {
                exist = 1;
                break;
            }
            if (r->link == NULL) {
                break;
            }
            r = r->link;
        }
        LinkList tmp = p->link;
        if (exist) {
            free(p);
        }else{
            r->link = p;
            p->link = NULL;
        }
        p = tmp;
    }
    printf("排重后：\n");
    PROINTLIST(list);
}

static LinkList MERGELIST(LinkList x, LinkList y){
    LinkList p1=x->link,p2=y,list=x,r;
    list->link = NULL;
    r = list;
    int i=1;
    while (p1 != NULL && p2 != NULL) {
        LinkList tmp;
        if (i % 2 == 0) {
            tmp = p1->link;
            r->link = p1;
            p1->link = NULL;
            r = p1;
            p1 = tmp;
        }else{
            tmp = p2->link;
            r->link = p2;
            p2->link = NULL;
            r = p2;
            p2 = tmp;
        }
        i++;
    }
    if (p1 != NULL) {
        r->link = p1;
    }else if (p2 != NULL) {
        r->link = p2;
    }
    return list;
}
void prcatice18(){
    LinkList list = CreateList(5);
    list->data->num = 100;
    list->link->data->num = 200;
    list->link->link->data->num = 300;
    list->link->link->link->data->num = 400;
    list->link->link->link->link->data->num = 500;
    LinkList list2 = CreateList(10);
    LinkList mergeL = MERGELIST(list, list2);
    PROINTLIST(mergeL);
}

LinkList FINDK(LinkList list, int k){
    int i=1;
    LinkList p=list,r=NULL;
    while (p != NULL) {
        if (r != NULL){
            r = r->link;
        }
        if (i == k) {
            r = list;
        }
        i++;
        p = p->link;
    }
    return r;
}

void prcatice17(){
    LinkList list = CreateList(5);
    PROINTLIST(list);
    printf("\n");
    LinkList r = FINDK(list, 2);
    if (r == NULL) {
        printf("没找到 \n");
    }else{
        printf("%d \n", r->data->num);
    }
}

void MOVEMINITEM(LinkList *list){
    LinkList p=(*list)->link,r=*list,m=NULL,k=NULL;
    int min = (*list)->data->num;
    while (p != NULL) {
        if (p->data->num < min) {
            k = m;
            r = p;
        }
        m = p;
        p = p->link;
    }
    if (r != *list) {
        k->link = r->link;
        r->link = *list;
        *list = r;
    }
}
void prcatice16(){
    LinkList list = CreateList(10);
    list->link->link->link->link->data->num = -100;
    list->link->link->link->data->num = -100;
    PROINTLIST(list);
    printf("移动后 \n");
    MOVEMINITEM(&list);
    PROINTLIST(list);
}

void CHAGEP(LinkList *list, LinkList p){
    LinkList t=NULL,f=*list;
    if (p == f) {
        t = p->link;
        p->link = p->link->link;
        t->link = p;
        *list = t;
    }else{
        while (f != NULL) {
            if (f == p) {
                break;
            }
            t = f;
            f = f->link;
        }
        if (t != NULL && f != NULL) {
            LinkList tmp = f->link->link;
            t->link = f->link;
            f->link->link = f;
            f->link = tmp;
        }
    }
}
void prcatice15(){
    LinkList list = CreateList(5);
    PROINTLIST(list);
    LinkList p = list;
    printf("移动 %d 后 \n", p->data->num);
    CHAGEP(&list, p);
    PROINTLIST(list);
}

void prcatice14(){
    LinkList list = CreateList(10);
    list->link->data->num = 3;
    PROINTLIST(list);
    LinkList p=list, r=NULL;
    int b=1;
    while (p != NULL) {
        if (r != NULL && r->data->num > p->data->num) {
            b = 0;
            break;
        }
        r = p;
        p = p->link;
    }
    if (b) {
        printf("按顺序排列 \n");
    }else{
        printf("非按顺序排列 \n");
    }
}

void DELETEMAX(LinkList *list){
    LinkList p=(*list)->link, r=*list, m=NULL, max=*list;
    
    while (p != NULL) {
        if (p->data->num > max->data->num) {
            m = r;
            max = p;
        }
        r = p;
        p = p->link;
    }
    if (max == *list) {
        *list = (*list)->link;
    }else{
        m->link = max->link;
    }
    free(max);
}

void prcatice13(){
    LinkList list = CreateList(10);
    list->data->num = 30;
    PROINTLIST(list);
    DELETEMAX(&list);
    printf("删除最大后 \n");
    PROINTLIST(list);
}

// 删除 [i,i+k-1]
void DELETECUSTOM(LinkList *list, int i, int k){
    int j=1;
    LinkList p = *list,r=NULL;
    while (p != NULL) {
        if (j == i-1) {
            r = p;
            p = p->link;
        }else if (j >= i && j < i+k) {
            if (r == NULL) {
                *list = (*list)->link;
                free(p);
                p = *list;
            }else{
                r->link = p->link;
                free(p);
                p = r->link;
            }
        }else if (j >= i+k){
            break;
        }else{
            p = p->link;
        }
        j++;
    }
}

void prcatice12(){
    LinkList list = CreateList(10);
    PROINTLIST(list);
    DELETECUSTOM(&list, 5, 3);
    printf("删除后 \n");
    PROINTLIST(list);
}

void DELETEI(LinkList *list, int i){
    LinkList p=*list, r=NULL;
    int j=1;
    while (p != NULL) {
        if (j == i) {
            break;
        }
        j++;
        r = p;
        p = p->link;
    }
    if (p == NULL) {
        return;
    }
    if (r == NULL) {
        *list = (*list)->link;
    }else{
        r->link = p->link;
    }
    free(p);
}

void prcatice11(){
    LinkList list = CreateList(5);
    PROINTLIST(list);
    DELETEI(&list, 5);
    printf("删除后 \n");
    PROINTLIST(list);
}

void CHAGEITEM(LinkList list, int d, int item){
    LinkList p = list;
    while (p != NULL) {
        if (p->data->num == d) {
            p->data->num = item;
        }
        p = p->link;
    }
}

void prcatice10(){
    LinkList list = CreateList(5);
    list->link->data->num = 5;
    list->link->link->data->num = 5;
    PROINTLIST(list);
    CHAGEITEM(list, 5, 100);
    printf("修改后 \n");
    PROINTLIST(list);
}

int *CREATEARRAY(int n){
    int *a = calloc(sizeof(int), n);
    for (int i=1; i<=n; i++) {
        a[i-1] = i;
    }
    return a;
}

void PRINTARRAY(int *a, int n){
    for (int i=0; i<n; i++) {
        printf("%d ", *(a+i));
    }
    printf("\n");
}

void MEAGEARRAY(int (*a)[], int n, int (*b)[], int m, int i){
    if (i <= 0 || i > n+1) {
        printf("擦数异常 \n");
        return;
    }
    int j;// m = 2, i=2
    for (j=n-1; j>i-2; j--) {
        (*a)[j+m] = (*a)[j];
        (*a)[j] = 0;
    }
    for (j=0; j<m; j++) {
        (*a)[j+i-1] = (*b)[j];
    }
}

void prcatice9(){
    int n = 6;
    int m = 5;
    int a[20] = {1,6,7,8,9,10};
    int b[5] = {2,3,4,5,6};
    MEAGEARRAY(&a, n, &b, m,2);
    PRINTARRAY(a, 11);
}

void prcatice8(){
    int a[20];
    int i=0;
    int n=10;
    while (i < n) {
        scanf("%d", &a[i]);
        i++;
    }
    PRINTARRAY(a, n);
}

void DELETEAITEM(int *a, int n, int i){
    for (int j=i; j<n; j++) {
        a[j] = a[j+1];
    }
}

void DELETERANGE(int *a, int n, int x, int y)
{
    for (int i=0; i<n; i++) {
        int it = *(a+i);
        if (it > x && it < y) {
            DELETEAITEM(a, n, i);
            i--;
            n--;
        }
    }
}

void prcatice7(){
    int n=10;
    int *a = CREATEARRAY(n);
    PRINTARRAY(a, 10);
    DELETERANGE(a, n, 0, 9);
    PRINTARRAY(a, 10);
}

// 删除序号为奇数的元素,require: O(n)
void DELETEODD(int *a, int n){
    // 1,2,3,4,5,6,7,8,9,10
    //   |   |   |   |   |
    // 1,2,3
    int k=0;
    for (int i=0; i<n; i++) {
        *(a+i) = *(a+i+k);
        k++;
    }
}

void prcatice6(){
    int n=12;
    int *a = CREATEARRAY(n);
    PRINTARRAY(a, n);
    printf("删除后 \n");
    DELETEODD(a, n);
    int i;
    if (n % 2 == 0) {
        i = n/2;
    }else{
        i = n/2+1;
    }
    PRINTARRAY(a, i);
}

void DELETEODDITEM(int *a, int *n){
    for (int i=0; i<*n; i++) {
        if (*(a+i) % 2 == 1) {
            DELETEAITEM(a, *n, i);
            (*n)--;
        }
    }
}

void prcatice5(){
    int n=10;
    int *a = CREATEARRAY(n);
    PRINTARRAY(a, n);
    printf("删除后 \n");
    DELETEODDITEM(a, &n);
    PRINTARRAY(a, n);
}

// 逆转线性表
void OVERTURN(int *a, int n){
    int *p = a+n-1;
    while (a < p) {
        int t = *a;
        *a = *p;
        *p = t;
        a++;
        p--;
    }
}

int FINDITEM(int *a, int n, int item){
    if (n <= 0) {
        return -1;
    }else if (*a == item) {
        return 0;
    }else{
        int q = FINDITEM(a+1, n-1, item);
        return q >= 0 ? q+1 : -1;
    }
}

void prcatice4(){
    int n=9;
    int *a = CREATEARRAY(n);
    PRINTARRAY(a, n);
    printf("逆转后 \n");
    OVERTURN(a, n);
    PRINTARRAY(a, n);
}

void prcatice3(){
    int n=9;
    int *a = CREATEARRAY(n);
    PRINTARRAY(a, n);
    int p = FINDITEM(a, n, 6);
    printf("位置：%d \n", p);
}

void MAXMIN(int *a, int n){
    int max = *a,min = *a;
    for (int i=0; i<n; i++) {
        if (*(a+i) > max) {
            max = *(a+i);
        }else if (*(a+i) < min) {
            min = *(a+i);
        }
    }
    printf("最大值：%d, 最小值：%d \n", max, min);
}

void prcatice2(){
    int n=10;
    int *a = CREATEARRAY(n);
    PRINTARRAY(a, n);
    MAXMIN(a, n);
}

int MINITEM(int *a, int n){
    int min = *a,j=0;
    for (int i=0; i<n; i++) {
        if (*(a+i) < min) {
            min = *(a+i);
            j = i;
        }
    }
    printf("最小值：%d, 所在位置：%d \n", min, j);
    return j;
}

void prcatice1(){
    int n=10;
    int *a = CREATEARRAY(n);
    *(a+5) = -100;
    PRINTARRAY(a, n);
    MINITEM(a, n);
}


































