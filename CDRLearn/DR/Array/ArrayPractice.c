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

static int ** CREATEMATRIX(int row, int col){
    int p=1,i,j,**A = calloc(sizeof(int *), row);
    for(i=0; i<row; i++){
        int *B = malloc(sizeof(int)*col);
        *(A+i) = B;
        for (j=0; j<col; j++) {
            A[i][j] = p++;
        }
    }
    return A;
}

static int ** CREATETHREECORNERMATRIX(int n){
    int p=1,i,j,**A = calloc(sizeof(int *), n);
    for(i=0; i<n; i++){
        int *B = malloc(sizeof(int)*n);
        *(A+i) = B;
        for (j=0; j<n; j++) {
            if (i == j || i == j+1 || i == j-1) {
                A[i][j] = p++;
            }else{
                A[i][j] = 0;
            }
        }
    }
    return A;
}

static void PRINTARRAY(int *a, int n){
    for (int i=0; i<n; i++) {
        printf("%d ", *(a+i));
    }
    printf("\n");
}

// 创建普通 n 阶矩阵
int **CREATEORDINARYARRAY(int n){
    int i,j,p=1;
    int **A = calloc(sizeof(int *), n);
    for (i=0; i<n; i++) {
        int *a = malloc(sizeof(int)*n);
        *(A+i) = a;
        for (j=0; j<n; j++) {
            A[i][j] = p++;
        }
    }
    return A;
}

int **CREATESYMMETRYMATRIX(int n){
    int p=1,i,j;
    int **B = (int **)malloc(sizeof(int *)*n);
    for (i=0; i<n; i++) {
        int *A = malloc(sizeof(int)*n);
        *(B+i) = A;
        for (j=0; j<=i; j++) {
            *(*(B+i)+j) = p;
            *(*(B+j)+i) = p;
            p++;
        }
    }
    return B;
}

// 对称矩阵转三元组
int **CONVERTTRIPLE(int **A, int n){
    int count = n*(n+1)/2;
    int **TA = calloc(sizeof(int *), count+1);
    int i,j,t=0;
    // 记录起始行数，列数，数据总个数
    int *ta = malloc(sizeof(int)*3);
    ta[0] = n;
    ta[1] = n;
    ta[2] = count;
    TA[t++] = ta;
    for (i=0; i<n; i++) {
        for(j=0; j<=i; j++){
            int *ta = malloc(sizeof(int)*3);
            *(ta+0) = i;
            *(ta+1) = j;
            *(ta+2) = A[i][j];
            TA[t++] = ta;
        }
    }
    return TA;
}

// 下三角矩阵
int ** CREATETOWARRAY(int n){
    int p=1,i,j;
    int **B = (int **)malloc(sizeof(int *)*n);
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
            printf("%-4d", *(A+j));
        }
        printf("\n");
    }
}

// 对称矩阵通过三元组还原
int ** ARRAYWITHTRIPLE(int **TA){
    int n,count,i,j;
    n = TA[0][0];
    count = TA[0][2];
    int **A = calloc(sizeof(int *), n);
    for (i=0; i<n; i++) {
        int *a = malloc(sizeof(int)*n);
        A[i] = a;
        for (j=0; j<=i; j++) {
            A[i][j] = A[j][i] = 0;
        }
    }
    for (i=1; i<=count; i++) {
        int *a = TA[i];
        int row = a[0];
        int col = a[1];
        int item = a[2];
        A[row][col] = A[col][row] = item;
    }
    return A;
}

void PRINTTRIPLE(int **TA){
    int row,col,count,i;
    row = TA[0][0];
    col = TA[0][1];
    count = TA[0][2];
    for (i=1; i<=count; i++) {
        int *A = TA[i];
        printf("数据：行：%d，列：%d，值：%d \n", A[0], A[1], A[2]);
    }
}

// 稀疏矩阵转三元组
void Practice1(){
    printf("Hello world \n");
}

void Practice2(){
    int n = 4;
    int **A = CREATETOWARRAY(n);
    PRINTTOWARRAY(A, n, n);
    printf("开始按列序存放 \n");
    int count=n*(n-1)/2;
    int *B = malloc(sizeof(int)*count);
    int *p = B;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int item = *(*(A+j)+i);
            if (i<j) {
                *p++ = item;
            }
        }
    }
    PRINTARRAY(B, count);
}

void Practice3(){
    int n = 4;
    int **A = CREATESYMMETRYMATRIX(n);
    PRINTTOWARRAY(A, n, n);
    printf("三元组存储 \n");
    int **B = CONVERTTRIPLE(A, n);
    PRINTTRIPLE(B);
    printf("三元组还原 \n");
    int **C = ARRAYWITHTRIPLE(B);
    PRINTTOWARRAY(C, n, n);
}

void MOVEONE(int *A, int n){
    if (n <= 1) {
        return;
    }
    int t = *(A+n-1);
    for (int i=n-2; i>=0; i--) {
        *(A+i+1) = *(A+i);
    }
    *A = t;
}

// item 循环向右移k位，使用一个数组元素的附加空间
void Practice4(){
    int n = 10;
    int *A = CREATEARRAY(n);
    PRINTARRAY(A, n);
    int k=3;
    for (int i=0; i<k; i++) {
        MOVEONE(A, n);
    }
    PRINTARRAY(A, n);
}

// 时间复杂度：O(n),循环右移 k 位置，采用尽可能少的空间 🔥🔥🔥
void Practice5(){
    int k = 5;
    int n = 10;
    int *A = CREATEARRAY(n);
    PRINTARRAY(A, n);
    for (int i=0; i<n; i++) {
//        int tmp = A[i+k];
    }
}

// n 阶 3 对角矩阵压缩存储
int * THREECORNERCOMPRESS(int **A, int n){
    int i,j,*t,*B = calloc(sizeof(int), 3*n-2);
    t = B;
    for(i=0; i<n; i++){
        for (j=0; j<n; j++) {
            if (i == j || i == j+1 || i == j-1) {
                *t++ = A[i][j];
            }
        }
    }
    return B;
}

// 根据三对角矩阵压缩存储还原数据
static int FINDITEM(int *B, int i, int j){
    return B[2*i+j-3];
}

void Practice6(){
    int n = 4;
    int **A = CREATETHREECORNERMATRIX(n);
    PRINTTOWARRAY(A, n, n);
    printf("压缩存储 \n");
    int *B = THREECORNERCOMPRESS(A, n);
    PRINTARRAY(B, 3*n-2);
    int i=2,j=3;
    printf("寻找 %d 行，%d 列数据：%d \n", i, j, FINDITEM(B, i, j));
    
}

int CALCULATEMultiply(int **A, int n){
    int i,num=1;
    for (i=0; i<n; i++) {
        int *a = A[i];
        num *= a[i]*a[n-i-1];
    }
    return num;
}

void Practice7(){
    int n = 2;
    int **A = CREATEORDINARYARRAY(n);
    PRINTTOWARRAY(A, n, n);
    int num = CALCULATEMultiply(A, n);
    printf("对角线乘积：%d \n", num);
}

int OUTSKIRTSSUM(int **A, int n){
    int i,j,sum=0;
    for (i=0; i<n; i++) {
        int *a = A[i];
        if (i == 0 || i == n-1) {
            for (j=0; j<n; j++) {
                sum += a[j];
            }
        }else{
            sum += a[0]+a[n-1];
        }
    }
    return sum;
}

void Practice8(){
    int n = 3;
    int **A = CREATEORDINARYARRAY(n);
    PRINTTOWARRAY(A, n, n);
    int num = OUTSKIRTSSUM(A, n);
    printf("外围一圈和：%d \n", num);
}

// 旋转数组第 tier 层,🔥🔥🔥(做得很慢)
void REVERSENTIER(int **A, int n, int tier){
    int i;
    for (int j=0; j<n-1-tier*2; j++) {
        int tmp = A[tier][tier];
        for (i=tier; i<=n-tier-2; i++) {
            A[i][tier] = A[i+1][tier];
        }
        for (i=tier+1; i<=n-tier; i++) {
            A[n-tier-1][i-1] = A[n-tier-1][i];
        }
        for (i=n-1-tier; i>=tier+1; i--) {
            A[i][n-1-tier] = A[i-1][n-1-tier];
        }
        for (i=n-1-tier; i>=tier+2; i--) {
            A[tier][i] = A[tier][i-1];
        }
        A[tier][tier+1] = tmp;
    }
}

void REVERSE(int **A, int n){
    for (int i=0; i<n/2; i++) {
        REVERSENTIER(A, n, i);
    }
}

// 空间复杂度为 O(1),将整个数组旋转 90 度
void Practice9(){
    int n = 7;
    int **A = CREATEORDINARYARRAY(n);
    PRINTTOWARRAY(A, n, n);
    printf("旋转后 \n");
    REVERSE(A, n);
    PRINTTOWARRAY(A, n, n);
}

// 螺旋方阵,n=5
int ** SPIRALMATRIX(int n){
    int **A = calloc(sizeof(int *), n);
    int i,j,p=1;
    for (i=0; i<n; i++) {
        int *a = malloc(sizeof(int)*n);
        *(A+i) = a;
    }
    for (i=0; i<n/2; i++) {
        for(j=i; j<n-i; j++){
            A[i][j] = p++;
        }
        for (j=i+1; j<n-i; j++) {
            A[j][n-i-1] = p++;
        }
        for (j=n-2-i; j>=i; j--) {
            A[n-i-1][j] = p++;
        }
        for (j=n-2-i; j>=i+1; j--) {
            A[j][i] = p++;
        }
    }
    if (n%2 == 1) {
        A[n/2][n/2] = p;
    }
    return A;
}

void Practice10(){
    int n=5;
    int **A = SPIRALMATRIX(n);
    PRINTTOWARRAY(A, n, n);
}

// 鞍点: i 行最小，j行最大
void ANDIAN(int **A, int row, int col){
    int i,j,t;
    for (i=0; i<row; i++) {
        int min=A[i][0];
        for (j=0; j<col; j++) {
            if (A[i][j] < min) {
                min = A[i][j];
            }
        }
        for (j=0; j<col; j++) {
            if (A[i][j] == min) {
                int max = min;
                for (t=0; t<row; t++) {
                    if (A[t][j] > max) {
                        max = A[t][j];
                        break;
                    }
                }
                if (max == min) {
                    printf("鞍点 row: %d, col: %d, item: %d \n", i, j, min);
                }
            }
        }
    }
}

void Practice11(){
    int row=3;
    int col=4;
    int **A = CREATEMATRIX(row, col);
    A[2][1] = 9;
    PRINTTOWARRAY(A, row, col);
    ANDIAN(A, row, col);
}

// 数组A，时间复杂度O(n),使得左边为奇数，右边偶数🔥🔥🔥🔥 复杂度未完成
void ADJUSTARRAY(int *A, int n){
    int i,k=0,*B=malloc(sizeof(int)*n);
    for (i=0; i<n; i++){
        if (A[i] % 2 == 0) {/* 偶数 */
            B[k] = A[i];
            k++;
        }else{/* 奇数 */
            A[i-k] = A[i];
        }
    }
    for (i=n-k; i<n; i++){
        A[i] = B[i-n+k];
    }
}

void Practice12(){
    const int n=11;
    int A[n] = {1, 2, 3, 5, 7, 6, 4, 9, 9, 2, 1};
    PRINTARRAY(A, n);
    ADJUSTARRAY(A, n);
    printf("排序后 \n");
    PRINTARRAY(A, n);
}

// A[0,...,n-1], 将所有 0 元素依次移到数组前端
void MOVEZERO(int *A, int n){
    int i,k=n-1;
    for (i=n-1; i>=0; i--) {
        if (A[i] != 0) {
            A[k--] = A[i];
            if (i != k+1) {
                A[i]=0;
            }
        }
    }
}

void Practice13(){
    const int n=5;
    int A[n] = {0, 2, 3, 5, 9};
    PRINTARRAY(A, n);
    MOVEZERO(A, n);
    printf("排序后 \n");
    PRINTARRAY(A, n);
}

void ArrayPractice(int argc, char *argv[]){
//    Practice2();
//    Practice3();
//    Practice4();
//    Practice5();
//    Practice6();
//    Practice7();
//    Practice8();
//    Practice9();
//    Practice10();
//    Practice11();
//    Practice12();
    Practice13();
}
