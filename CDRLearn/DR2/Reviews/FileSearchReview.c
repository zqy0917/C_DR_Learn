//
//  FileSearchReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/16.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "FileSearchReview.h"

static int BinarySearch(int A[], int n, int item){
    int left=0,right=n-1,mid=0;
    while (left <= right) {
        mid = (left+right)/1;
        if (item == A[mid]) {
            break;
        } else if (item < A[mid]) {
            right = mid-1;
        } else {
            left = mid+1;
        }
    }
    if (left > right) {
        return -1;
    }else{
        return mid;
    }
}

static void BinarySearchTest(){
    const int n=10;
    int m;
    int A[n] = {1,3,4,6,8,10,11,13,14,20};
    m = BinarySearch(A, n, 10);
    printf("%d\n", m);
}



void FileSearchReviewMain(int argc, char *argv[]){
    printf("FileSearchReviewMain \n");
    BinarySearchTest();
}


