//
//  FilePractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/10.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "FilePractice.h"
#include <stdlib.h>

#define HashMaxLen 100

typedef struct elem{
    int key;
}ElemType, *ElemLink;

typedef struct node{
    int key;
    struct node *link;
}HNode, *HNLink;

typedef ElemType Hashlist1[HashMaxLen];
typedef HNLink Hashlist2[HashMaxLen];

static int Practice1(Hashlist1 HT, int i, int n, int k){
    if (i >= n) {
        return -1;
    }
    if (HT[i].key == k) {
        return i;
    }
    return Practice1(HT, i+1, n, k);
}

// 淘汰算法查找
static int Practice2(Hashlist1 HT, int n, int k){
    int i,pos=-1;
    ElemType p;
    for (i=0; i<n; i++) {
        if (HT[i].key == k) {
            if (i > 0){
                p = HT[i-1];
                HT[i-1] = HT[i];
                HT[i] = p;
                pos = i-1;
            }else{
                pos = i;
            }
            break;
        }
    }
    return pos;
}

// 折半查找法插入元素,设从小到大 1，2，3，4，5.....
static int Practice3(Hashlist1 HT, int *n, int k){
    int i, low=0, high=*n-1, mid, pos=0;
    ElemLink p;
    if (HT[0].key >= k) {
        pos = 0;
    }else if (HT[*n-1].key <= k) {
        pos = *n;
    }else{
        while (low <= high) {
            mid = (low + high)/2;
            if (k >= HT[mid].key && k <= HT[mid+1].key) {
                pos = mid+1;
                break;
            }else if (HT[mid].key > k){
                high = mid-1;
            }else if (HT[mid+1].key < k){
                low = mid+1;
            }
        }
    }
    for (i=*n-1; i>=pos; i--) {
        HT[i+1] = HT[i];
    }
    p = malloc(sizeof(ElemType));
    p->key = k;
    HT[pos] = *p;
    (*n)++;
    return pos;
}

int FilePracticeMain(int argc, char *argv[]){
    int n=10;
    int i,pos=-1;
    Hashlist1 HT;
    ElemLink p;
    for (i=0; i<n; i++) {
        p = malloc(sizeof(ElemType));
        p->key = i+1;
        HT[i] = *p;
    }
    HT[0].key = 1;
    HT[1].key = 3;
    HT[2].key = 8;
    HT[3].key = 9;
    HT[4].key = 11;
    HT[5].key = 14;
    HT[6].key = 15;
    HT[7].key = 22;
    HT[8].key = 23;
    HT[9].key = 400;
//    pos = Practice1(HT, 0, n, 0);
//    pos = Practice2(HT, n, 0);
//    if (pos >= 0) {
//        printf("%d \n", HT[pos].key);
//    }else{
//        printf("没找到 \n");
//    }
    pos = Practice3(HT, &n, 13);
    printf("pos: %d \n", pos);
    for (i=0; i<n; i++) {
        printf("%d ", HT[i].key);
    }
    printf("\n");
    printf("%d\n", 'M'-'A'+1);
    printf("%d\n", 'T'-'A'+1);
    printf("%d\n", 'W'-'A'+1);
    printf("%d\n", 'T'-'A'+1);
    printf("%d\n", 'F'-'A'+1);
    printf("%d\n", 'S'-'A'+1);
    printf("%d\n", 'S'-'A'+1);
    return 0;
}
