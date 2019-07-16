//
//  SortExamples.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/11.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "SortExamples.h"

#define MaxNum 100

static int compareCount=0;
static int swipCount=0;

static void swip(int K[], int i, int j){
    int temp = K[i];
    K[i] = K[j];
    K[j] = temp;
}

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
            compareCount++;
            if (K[j] < K[d]) {
                d = j;
            }
        }
        if (d != i) {
            temp = K[d];
            K[d] = K[i];
            K[i] = temp;
            swipCount++;
        }
    }
}

// Bubble sort
void Bubble_Sort1(int K[], int n){
    int i,j,flag,temp;
    for (i=0; i<n-1; i++) {
        flag = 0;
        for (j=0; j<n-i-1; j++){
            compareCount++;
            if (K[j] > K[j+1]) {
                temp = K[j];
                K[j] = K[j+1];
                K[j+1] = temp;
                flag = 1;
                swipCount++;
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
            compareCount++;
            if (K[j] > K[j+1]) {
                temp = K[j];
                K[j] = K[j+1];
                K[j+1] = temp;
                flag = 1;
                swipCount++;
            }
        }
        i--;
    }
}

// Shell sort, follow progress
// 1, 6, 3, 5, 10, 7, 4, 8, 2, 9

// gap = 5
// 1, 4  3  2, 9,  7  6  8  5  10
// 1, 4  3  2, 9,  7  6  8  5  10

// gap = 2
// 1  2  3  4  6  7  5  8  9  10
// 1  2  3  4  5  7  6  8  9  10
// 1  2  3  4  5  7  6  8  9  10

// gap = 1
// 1  2  3  4  5  6  7  8  9  10
// 1  2  3  4  5  6  7  8  9  10
static void Shell_Sort(int K[], int n){
    int i,j,gap=n,flag=0;
    int temp;
    while (gap > 1) {
        gap /= 2;
        do {
            flag = 0;
            for(i=0; i<=n-gap-1; i++){
                j = i+gap;
                compareCount++;
                if (K[i] > K[j]) {
                    temp = K[i];
                    K[i] = K[j];
                    K[j] = temp;
                    flag = 1;
                    swipCount++;
                }
            }
            
        } while (flag != 0);
    }
    
}

// Quick sort, follow progress, My algorithm
// 5, 6, 3, 1, 10, 7, 4, 8, 2, 9
static void Quick_Sort(int K[], int low, int high){
    int i=low,p=low+1,q=high,temp;
    if (low >= high) {
        return;
    }
    while (p <= q) {
        if (K[p] > K[i] && K[q] <= K[i]) {
            temp = K[p];
            K[p] = K[q];
            K[q] = temp;
            swipCount++;
        }
        if (K[p] <= K[i]) {
            p++;
        }
        if (K[q] > K[i]) {
            q--;
        }
        compareCount+=3;
    }
    temp = K[i];
    K[i] = K[q];
    K[q] = temp;
    swipCount++;
    Quick_Sort(K, low, q-1);
    Quick_Sort(K, q+1, high);
}

// Quick sort, follow progress, teach algorithm original.
// 6, 5, 3, 1, 10, 7, 4, 8, 2, 9
static void Quick_Sort2(int K[], int s, int t){
    int i,j;
    if (s < t) {
        while (1) {
            i = s;
            j = t+1;
            do {
                i++;
                compareCount++;
            } while (!(K[s] <= K[i] || i == t));
            do {
                j--;
                compareCount++;
            } while (!(K[s] >= K[j] || j == s));
            compareCount -= 2;
            if (i < j) {
                swip(K, i, j);
                swipCount++;
            }else{
                break;
            }
        }
        swip(K, s, j);
        swipCount++;
        Quick_Sort2(K, s, j-1);
        Quick_Sort2(K, j+1, t);
    }
}

// Quick sort, follow progress, the teach algorithm which I changed.
// 6, 5, 3, 1, 10, 7, 4, 8, 2, 9
static void Quick_Sort3(int K[], int s, int t){
    int i,j;
    if (s < t) {
        while (1) {
            i = s+1;
            j = t;
            while (K[i] <= K[s]) {
                compareCount++;
                i++;
            }
            while (K[j] > K[s]) {
                compareCount++;
                j--;
            }
            if (i < j) {
                swip(K, i, j);
                swipCount++;
            }else{
                break;
            }
        }
        swip(K, s, j);
        swipCount++;
        Quick_Sort3(K, s, j-1);
        Quick_Sort3(K, j+1, t);
    }
}

// Quick sort, follow progress, unrecursive .
// 6, 5, 3, 1, 10, 7, 4, 8, 2, 9
static void Quick_Sort4(int K[], int s, int t){
    int STACK1[MaxNum],STACK2[MaxNum],top=-1;
    int i,j;
    STACK1[++top] = s;
    STACK2[top] = t;
    while (top >= 0) {
        s = STACK1[top];
        t = STACK2[top--];
        i = s+1;
        j = t;
        while (1) {
            while (K[i] <= K[s]) {
                compareCount++;
                i++;
            }
            while (K[j] > K[s]) {
                compareCount++;
                j--;
            }
            if (i < j) {
                swip(K, i, j);
                swipCount++;
            }else{
                break;
            }
        }
        swip(K, s, j);
        swipCount++;
        if (s < j-1) {
            STACK1[++top] = s;
            STACK2[top] = j-1;
        }
        if (j+1 < t) {
            STACK1[++top] = j+1;
            STACK2[top] = t;
        }
    }
}

static void Adjust(int K[], int i, int n){
    int j=i*2;
    int temp = K[i];
    while (j <= n) {
        if (j<n && K[j] < K[j+1]) {
            j++;
        }
        if (temp >= K[j]) {
            break;
        }
        K[j/2] = K[j];
        j *= 2;
    }
    K[j/2] = temp;
}

// Heap sort
static void Heap_Sort(int K[], int n){
    int i;
    for (i=n/2; i>=1; i--) {
        Adjust(K, i, n);
    }
    for (i=n; i>=1; i--) {
        swip(K, i, 1);
        Adjust(K, 1, i-1);
    }
}

static void PrintArray(int K[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%d ", K[i]);
    }
    printf("\n");
}

int SortExamplesMain(int argc, char *argv[]){
    printf("Hello internal srot \n");
//    const int n = 10;
    const int n = 11;
//    int K[n] = {6, 5, 3, 1, 10, 7, 8, 4, 2, 9};
//    int K[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    int K[n] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int K[n] = {0, 6, 5, 3, 1, 10, 7, 8, 4, 2, 9};
    // 1  3  5  6 10
//    Insert_Sort(K, n);
//    Bin_Insert_Sort(K, n);
//    Select_Sort(K, n);
//    Bubble_Sort2(K,n);
//    Bubble_Sort1(K,n);
//    Shell_Sort(K,n);
//    Quick_Sort(K, 0, n-1);
//    Quick_Sort2(K, 0, n-1);
//    Quick_Sort3(K, 0, n-1);
//    Quick_Sort4(K, 0, n-1);
    Heap_Sort(K, n-1);
    PrintArray(K, n);
    printf("compare: %d \n", compareCount);
    printf("swip: %d \n", swipCount);
    return 0;
}




