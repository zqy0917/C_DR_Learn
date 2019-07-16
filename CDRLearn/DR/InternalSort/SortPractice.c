//
//  SortPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/7/16.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "SortPractice.h"

#define MaxNum 100

static void PrintArray(int K[], int n){
    int i;
    for (i=0; i<n; i++){
        printf("%d ", K[i]);
    }
    printf("\n");
}

/* 荷兰国旗 */
static void Practice9(){
    
}

static void Index_Sort(int K[], int n){
    int i,j,tmp[n],a,count, C[n];
    for (i=0; i<n; i++) {
        a = K[i];
        count=0;
        for (j=0; j<n; j++) {
            if (K[j] < a) {
                count++;
            }
        }
        tmp[i] = count;
    }
    for(i=0; i<n; i++){
        C[tmp[i]] = K[i];
    }
    for (i=0; i<n; i++) {
        K[i] = C[i];
    }
}

static void Practice8(){
    const int n = 10;
    int K[n] = {6, 5, 3, 1, 10, 7, 8, 4, 2, 9};
    Index_Sort(K, n);
    PrintArray(K, n);
}

static void Sort_DoubleArray(int K[][MaxNum], int m, int n){
    int i,j,mins[m],minIndexs[m],min,C[m][MaxNum],temp1,temp2;
    for(i=0; i<m; i++){
        min = K[i][0];
        for(j=0; j<n; j++){
            if (K[i][j] < min) {
                min = K[i][j];
            }
        }
        mins[i] = min;
        minIndexs[i] = i;
    }
    for (i=1; i<m; i++) {
        temp1 = mins[i];
        temp2 = minIndexs[i];
        j = i-1;
        while (j > -1 && temp1 < mins[j]) {
            mins[j+1] = mins[j];
            minIndexs[j+1] = minIndexs[j];
            j--;
        }
        mins[j+1] = temp1;
        minIndexs[j+1] = temp2;
    }
    
    for (i=0; i<m; i++) {
        for(j=0; j<n; j++){
            C[i][j] = K[minIndexs[i]][j];
        }
    }
    for (i=0; i<m; i++) {
        for(j=0; j<n; j++){
            K[i][j] = C[i][j];
        }
    }
    for (i=0; i<m; i++) {
        for(j=0; j<n; j++){
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }
}

static void Practice7(){
    const int m = 5;
    const int n = 5;
    int K[m][MaxNum] = {
        {6, 5, 3, 1, 10},
        {7, 8, 6, 7, 9},
        {7, 8, 4, 6, 9},
        {7, 8, 3, 4, 9},
        {7, 8, 4, 2, 9}
    };
    Sort_DoubleArray(K, m, n);
}

int SortPracticeMain(int argc, char *argv[]){
    printf("Hello Sort practice!!! \n");
//    Practice8();
    Practice7();
    
    
    return 0;
}
