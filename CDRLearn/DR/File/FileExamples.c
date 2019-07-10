//
//  FileExamples.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/9.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "FileExamples.h"
#include <stdlib.h>

// 顺序查找
int Seq_Search(int key[], int n, int k){
    int i;
    for (i=0; i<n; i++) {
        if (key[i] == k) {
            return i;
        }
    }
    return 0;
}

// 二分查找
int Bin_Search(int key[], int n, int k){
    int low=0,mid,high=n-1;
    while (low <= high) {
        mid = (low + high)/2;
        if (key[mid] == k) {
            return mid;
        }else if (k > key[mid]) {
            low = mid+1;
        }else{
            high = mid-1;
        }
    }
    return -1;
}

// 二分递归
int Recur_Bin_Search(int key[], int low, int high, int k){
    int mid = (low + high)/2;
    if (low > high) {
        return -1;
    }
    if (key[mid] == k) {
        return mid;
    }else if (k > key[mid]){
        return Recur_Bin_Search(key, low+1, high, k);
    }else if (k < key[mid]){
        return Recur_Bin_Search(key, low, high-1, k);
    }
    return -1;
}

void FindNum(){
    int key[] = {2, 5, 8, 11, 15, 16, 22, 24, 27, 35, 50};
    int n = sizeof(key)/sizeof(int),pos;
//    pos = Bin_Search(key, n, 11);
//    pos = Bin_Search(key, n, 35);
    pos = Recur_Bin_Search(key, 0, n-1, 5);
    if (pos >= 0) {
        printf("%d \n", key[pos]);
    }else{
        printf("没找到 \n");
    }
    
}

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

int Hash(int k){
    return k%3;
}

int HashInsert(Hashlist1 HT, int M, int k){
    /* M 表示表的实际长度 */
    int i,D;
    i = Hash(k);
    D=i;
    // Tomorrow continue
    while (HT[D].key != 0 && HT[D].key != k) {
        D = Hash(D+1);
        if (D == i) {
            /* 散列表已满 */
            return -1;
        }
    }
    if (HT[D].key != k) {
        HT[D].key = k;
    }
    return 0;
}

// 冲突法采用开放定址法 (2) d = 1方，-1方，2方，-2方.......,称为二次探测在散列
int HashSearch(Hashlist1 HT, int M, int k){
    int i,di,D;
    i = Hash(k);
    D = i;
    di = 1;
    while (HT[D].key !=0 && HT[D].key != k) {
        D = Hash(i+di*di);
        di++;
        if (D == i) {
            /* 没找到 */
            return -1;
        }
    }
    if (HT[D].key == k) {
        return D;
    }
    return -1;
}

// 采用桶式冲突法删除数据(链地址法)
int HashDelete(Hashlist2 HT, int k){
    int i;
    i = Hash(k);
    HNLink p = HT[i],r=NULL;
    while (p != NULL) {
        if (p->key == k) {
            if (r == NULL) {
                HT[i] = p->link;
            }else{
                r->link = p->link;
            }
            free(p);
            return i;
        }
        r = p;
        p = p->link;
    }
    return -1;
}

int FileExampleMain(int argc, char *argv[]){
    printf("Hello file!!! 2019-07-09 \n");
//    FindNum();
    
    return 0;
}
