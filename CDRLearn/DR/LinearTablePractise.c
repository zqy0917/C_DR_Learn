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
            d->data->num = -100;
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

void parctice29(){
    
}





