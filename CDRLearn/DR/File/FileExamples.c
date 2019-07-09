//
//  FileExamples.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/9.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "FileExamples.h"

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
        
    }
    return 0;
}

int FileExampleMain(int argc, char *argv[]){
    printf("Hello file!!! 2019-07-09 \n");
//    FindNum();
    
    return 0;
}
