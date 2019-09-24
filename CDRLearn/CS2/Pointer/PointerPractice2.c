//
//  PointerPractice2.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/23.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "PointerPractice2.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MaxNum 1000

static void intPointer(){
    const int n=4;
    int A[n][10] = {
        {1,2,3,4,5,6,7,8,9,10},
        {11,22,33,44,55,66,77,88,99,100},
        {111,222,333,444,555,666,777,888,999,1000},
        {1111,2222,3333,4444,5555,6666,7777,8888,9999,10000},
    };
    int (*p)[10] = A;
    for (int i=0; i<n; i++) {
        for (int j=0; j<10; j++) {
            printf("%-5d ", *(*(p+i)+j));
        }
        putchar('\n');
    }
}

static void strChange(){
    const int n=5;
    char strs[n][MaxNum],*targetStr = "_xy_",*p;
    int i;
    for (i=0; i<n; i++) {
        scanf("%s", strs[i]);
        p = strs[i];
        while (*p != '\0') {
            if (*p == '_') {
                printf("_ab_");
                p += strlen(targetStr);
                continue;
            }else{
                putchar(*p);
            }
            p++;
        }
    }
}

static char * GetValue(char *str, double *d){
    if (sscanf(str, "%lf", d) != 1) {
        return NULL;
    }
    while (*str != '\0' && !isspace(*str)) {
        str++;
    }
    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

static void Practice14(){
    const int N=5;
    int i,n;
    double d,sum;
    char buf[BUFSIZ], *p;
    for (i=1; i<=N && (p=fgets(buf, BUFSIZ, stdin)) != NULL; i++) {
        sum = 0;
        for (n=0; (p = GetValue(p, &d)) != NULL; n++) {
            sum += d;
        }
        if (n > 0) {
            printf("%d:%d %.2lf \n", i, n, sum/n);
        }
    }
}

static double CountDoubleSum(int argc, char *argv[]){
    int i;
    double sum=0,d;
    for (i=1; i<argc; i++) {
        if (sscanf(argv[i], "%lf", &d) == 1){
            sum += d;
        }
    }
    return sum;
}

static void matrix_add(int (*m1)[5], int (*m2)[5], int (*s)[5]){
    int i,j;
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            *(*(s+i)+j) = *(*(m1+i)+j) + *(*(m2+i)+j);
        }
    }
}

static void Practice20(){
    const int n = 5;
    int i,j;
    int matrix1[n][n] = {
        {1,1,1,1,1},
        {2,2,2,2,2},
        {3,3,3,3,3},
        {4,4,4,4,4},
        {5,5,5,5,5}
    };
    int matrix2[n][n] = {
        {5,5,5,5,5},
        {4,4,4,4,4},
        {3,3,3,3,3},
        {2,2,2,2,2},
        {1,1,1,1,1}
    };
    int s[n][n];
    matrix_add(matrix1, matrix2, s);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ", s[i][j]);
        }
        putchar('\n');
    }
}

static void swip_d(double *d1, double *d2){
    double temp = *d1;
    *d1 = *d2;
    *d2 = temp;
}

static int com_str(const void *str1, const void *str2){
    char *str11 = (char *)str1;
    char *str22 = (char *)str2;
    unsigned long n1,n2;
    n1 = strlen(str11);
    n2 = strlen(str22);
    if (n1 > n2) {
        return 1;
    } else if (n1 < n2) {
        return -1;
    } else {
        return strcmp(str11, str22);
    }
}

#define MaxRow 5
#define MaxCol 2000
static void Practice22(){
    char strs[MaxRow][MaxCol],*p;
    int i=0,j;
    while (i<MaxRow && ((p=fgets(strs[i], MaxCol, stdin)) != NULL)){
        while (*p != '\n') {
            p++;
        }
        *p = '\0';
        i++;
    };
    qsort(strs, MaxRow, sizeof(strs[0]), com_str);
    for (j=0; j<i; j++) {
        printf("%s \n", strs[j]);
    }
}

static int int_sort(const void *x1, const void *x2){
    return *(int *)x1 - *(int *)x2;
}

#define MaxIntegers 6
static void Practice23(){
    int nums[MaxIntegers]={0},i,j;
    for (i=0; i<MaxIntegers&&fscanf(stdin, "%d", &nums[i]); i++);
    qsort(nums, MaxIntegers, sizeof(nums[0]), int_sort);
    for (j=i-i/2; j<i; j++) {
        printf("%d ", nums[j]);
    }
    putchar('\n');
}

// Cycle string abcd 4
static int isCycleStr(char *str){
    char *left,*right;
    left = str;
    right = str+strlen(str)-1;
    while (left < right) {
        if (*left != *right) {
            break;
        }
        left++;
        right--;
    }
    return left >= right;
}

static void Practice24(){
    char str[MaxNum];
    int b;
    scanf("%s", str);
    b = isCycleStr(str);
    printf("CycleStr: %d \n", b);
}

static void Practice25(){
    const int n=537;
    int min=10101010,pos1=1,pos2=1,pos3=1,pos4=1;
    while (min <= 90909090) {
        if (min % n == 0) {
            break;
        }
        if (pos4 <= 8) {
            pos4++;
        }else{
            if (pos3 <= 8) {
                pos3++;
            }else{
                if (pos2 <= 8) {
                    pos2++;
                }else{
                    if (pos1 <= 8) {
                        pos1++;
                    }else{
                        min = -1;
                        break;
                    }
                    pos2=1;
                }
                pos3=1;
            }
            pos4=1;
        }
        min = pos1*10000000+pos2*100000+pos3*1000+pos4*10;
    }
    if (min == -1) {
        printf("N/A \n");
    }else{
        printf("%d \n", min);
    }
}

static int max(int x1, int x2){
    return x1 > x2 ? x1 : x2;
}

static int min(int x1, int x2){
    return x1 < x2 ? x1 : x2;
}

static int isInter(int a1, int a2, int b1, int b2){
    if (a1 >= b1 && a1 <= b2) {
        return 1;
    }
    if (a2 >= b1 && a2 <= b2) {
        return 1;
    }
    if (b1 >= a1 && b1 <= a2) {
        return 1;
    }
    if (b2 >= a1 && b2 <= a2) {
        return 1;
    }
    return 0;
}

static int sort_arr(const void *arr1, const void *arr2){
    int *arr11 = (int *)arr1;
    int *arr22 = (int *)arr2;
    return arr11[0]-arr22[0];
}

// Difficult 🔥🔥🔥
static void Practice26(){
    const int n=11;
    int A[n][2];
    int i,j,x,y,count=0,b,a1,a2;
    for (i=0; i<n; i++) {
        for (j=0; j<2; j++) {
            A[i][j] = 0;
        }
    }
    for (i=0; i<n; i++) {
        scanf("%d %d", &x, &y);
        b=-1;
        for (j=0; j<count; j++) {
            if (A[j][0] == 0) {
                continue;
            }
            if (b >= 0) {
                a1 = A[b][0];
                a2 = A[b][1];
            }else{
                a1 = x;
                a2 = y;
            }
            if (isInter(a1, a2, A[j][0], A[j][1])) {
                if (b >= 0) {
                    A[b][0] = min(A[b][0], a1);
                    A[b][1] = max(A[b][1], a2);
                    A[b][0] = min(A[b][0], A[j][0]);
                    A[b][1] = max(A[b][1], A[j][1]);
                    A[j][0] = 0;
                    A[j][1] = 0;
                }else{
                    b = j;
                    A[j][0] = min(A[j][0], a1);
                    A[j][1] = max(A[j][1], a2);
                }
            }
        }
        if (b == -1) {
            A[count][0] = x;
            A[count][1] = y;
            count++;
        }
    }
    printf("---------------\n");
    qsort(A, count, sizeof(A[0]), sort_arr);
    for (i=0; i<count; i++) {
        if (A[i][0] == 0) {
            continue;
        }
        printf("%d %d \n", A[i][0], A[i][1]);
    }
}

void PointerPractice2Main(int argc, char *argv[]){
//    intPointer();
//    strChange();
//    Practice14();
//    double sum = CountDoubleSum(argc, argv);
//    printf("Sum: %.2lf \n", sum);
//    Practice20();
//    double d1 = 0.011;
//    double d2 = 1.9090;
//    swip_d(&d1, &d2);
//    printf("d1: %lf, d2: %lf \n", d1, d2);
//    Practice22();
//    Practice23();
//    Practice24();
//    Practice25();
//    Practice26();
}
