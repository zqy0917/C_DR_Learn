//
//  SortExamples.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/11.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "SortExamples.h"

// Insert sort function
void Insert_Sort(int K[], int n){
    int i,j,p;
    for (i=1; i<n; i++) {
        p = K[i];
        for (j=i-1; j>=0; j--) {
            if (K[j] <= p) {
                break;
            }else{
                K[j+1] = K[j];
            }
        }
        K[j+1] = p;
    }
}

// Binary insert sort, only reduce compare count !!!
void Bin_Insert_Sort(int K[], int n){
    int i,j,low,high,mid=0,p;
    for (i=1; i<n; i++) {
        p = K[i];
        low=0;
        high = i-1;
        while (low <= high) {
            mid = (low+high)/2;
            if (K[mid] > p) {
                high = mid-1;
            }else{
                low = mid+1;
            }
        }
        for (j=i-1; j >= low; j--) {
            K[j+1] = K[j];
        }
        K[low] = p;
    }
}

// Select sort
void Select_Sort(int K[], int n){
    int i,j,d,temp;
    for (i=0; i<n-1; i++) {
        d = i;
        for (j=i+1; j<n; j++){
            if (K[j] < K[d]) {
                d = j;
            }
        }
        if (d != i) {
            temp = K[d];
            K[d] = K[i];
            K[i] = temp;
        }
    }
}

void Bubble_Sort1(int K[], int n){
    int i,j,flag,temp;
    for (i=0; i<n-1; i++) {
        flag = 0;
        for (j=0; j<n-i-1; j++){
            if (K[j] > K[j+1]) {
                temp = K[j];
                K[j] = K[j+1];
                K[j+1] = temp;
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}

void Bubble_Sort2(int K[], int n){
    int i,j,flag=1;
    int temp;
    i = n-1;
    while (i > 0 && flag == 1) {
        flag = 0;
        for (j=0; j<i; j++) {
            if (K[j] > K[j+1]) {
                temp = K[j];
                K[j] = K[j+1];
                K[j+1] = temp;
                flag = 1;
            }
        }
        i--;
    }
}

static void PrintArray(int K[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%d ", K[i]);
    }
    printf("\n");
}

int SortPracticeMain(int argc, char *argv[]){
    printf("Hello internal srot \n");
    const int n = 10;
    int K[n] = {1, 6, 3, 5, 10, 7, 4, 8, 2, 9};
    // 1  3  5  6 10
//    Insert_Sort(K, n);
//    Bin_Insert_Sort(K, n);
//    Select_Sort(K, n);
//    Bubble_Sort2(K,n);
    Bubble_Sort1(K,n);
    PrintArray(K, n);
    return 0;
}




