//
//  CycleLinearTable.h
//  CDRLearn
//
//  Created by Zqy on 19/6/16.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#ifndef CycleLinearTable_h
#define CycleLinearTable_h

#include <stdio.h>
#include <stdlib.h>

static int n = 0;

typedef struct
{
    int num;
    char data[10];
}EType, *ElemType;

typedef struct node
{
    ElemType data;
    struct node *link;
}LNode, *LinkList;


typedef struct dnode{
    ElemType data;
    struct dnode *llink,*rlink;
}DNode, *DLinkList;

typedef struct dlrunode{
    ElemType data;
    struct dlrunode *llink,*rlink;
    int freq;
}DLRUNode, *DLRULinkList;

#define LNodeSize sizeof(LNode)
#define DNodeSize sizeof(DNode)
#define DLRUNodeSize sizeof(DLRUNode)

void READ(ElemType *a);

void PRINTDLIST(DLinkList list);

void DRDay3(int argc, char *argv[]);

#endif /* CycleLinearTable_h */
