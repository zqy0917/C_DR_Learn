//
//  ArrayPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/6/19.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "ArrayPractice.h"
#include <stdlib.h>

static int *CREATEARRAY(int n){
    int *a = calloc(sizeof(int), n);
    for (int i=1; i<=n; i++) {
        a[i-1] = i;
    }
    return a;
}

static void PRINTARRAY(int *a, int n){
    for (int i=0; i<n; i++) {
        printf("%d ", *(a+i));
    }
    printf("\n");
}

int ** CREATETOWARRAY(int n){
    int p=1,i,j;
    int **B = (int **)malloc(sizeof(int)*n);
    for (i=0; i<n; i++) {
        int *A = (int *)calloc(sizeof(int), n);
        for (j=0; j<n; j++) {
            if (i>=j) {
                A[j] = p;
                p++;
            }else{
               A[j] = 0;
            }
        }
        *(B+i) = A;
    }
    return B;
}

void PRINTTOWARRAY(int **a, int row,int col){
    for (int i=0; i<row; i++) {
        int *A = *(a+i);
        for (int j=0; j<col; j++) {
            printf("%d ", *(A+j));
        }
        printf("\n");
    }
}

// 稀疏矩阵转三元组
void Practice1(){
    printf("Hello world \n");
}

void Practice2(){
    printf("Hello world \n");
    int n = 5;
    int **A = CREATETOWARRAY(n);
    PRINTTOWARRAY(A, n, n);
    printf("开始按列序存放 \n");
    
}

void ArrayPractice(int argc, char *argv[]){
    Practice2();
}
