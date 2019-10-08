//
//  ArrayReview.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/10/8.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "ArrayReview.h"

// less time resume 1 2 3 4 5   5 1 2 3 4    4 5 1 2 3   3 4 5 1 2
static void ArrayItemCycleMove(int A[], int n, int k){
    int t = k%n,i,j;
    int temp;
    i = n-t,j=n-1;
    while(i < j){
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        i++;
        j--;
    }
    i = 0,j = n-t-1;
    while(i < j){
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        i++;
        j--;
    }
    i = 0,j = n-1;
    while(i < j){
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        i++;
        j--;
    }
}

static void MovePractice(){
    const int n=10;
    int A[n] = {1,2,3,4,5,6,7,8,9,10},i;
    ArrayItemCycleMove(A, n, 13);
    for (i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
    putchar('\n');
}

static void MoveZero(int A[], int n){
    int i,k=0;
    for (i=n-1; i>=0; i--) {
        if (A[i] == 0) {
            k++;
        }else{
            if (k > 0) {
                A[i+k] = A[i];
                A[i] = 0;
            }
        }
    }
}

static void MoveZeroPractice(){
    const int n=10;
    int A[n] = {0,2,3,0,0,6,7,8,0,0},i;
    MoveZero(A, n);
    for (i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
    putchar('\n');
}

void ArrayReviewMain(int argc, char *argv[]){
    printf("Array review\n");
    // MovePractice();
    MoveZeroPractice();
}