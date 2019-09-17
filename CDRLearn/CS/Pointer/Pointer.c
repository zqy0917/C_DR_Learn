//
//  Day3.c
//  StudyDay1
//
//  Created by Zqy on 19/6/7.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "Pointer.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int isNum(char c){
    return (c >= '0' && c<='9');
}

void test16(char *str){
    int *array = malloc(sizeof(int)*3);
    int *arr = array;
    char *a = str;
    int tmp = 0;
    int num = 0;
    int count = 0;
    for (; *a != '\0'; a++) {
        if (isNum(*a)) {
            num = 1;
            tmp *= 10;
            tmp += *a-48;
        }else if (num) {
            *arr++ = tmp;
            count++;
            tmp = 0;
            num = 0;
        }
    }
    
    if (num) {
        *arr++ = tmp;
        count++;
    }
    
    arr = array;
    for (int i=0; i<count; i++) {
        printf("%d ", *arr++);
    }
    free(array);
    printf("\n");
}

void avaige1(float (*arr)[5], int c){
    float (*a)[5] = arr;
    float sum = 0.f;
    for (; a<arr+c; a++) {
        sum += **a;
    }
    printf("第一门课程平均分：%f \n", sum/c);
}

void test_15_2(float (*arr)[5], int c, int l){
    float (*a)[5] = arr;
    for (; a<arr+c; a++) {
        float *d = *a;
        int count = 0;
        float sum = 0.f;
        for (; d<*a+l; d++) {
            sum += *d;
            if (*d < 60) {
                count ++;
            }
        }
        if (count >= 2) {
            printf("学号：%ld \n单科成绩：", a-arr);
            d = *a;
            for (; d<*a+l; d++) {
                printf("%f ", *d);
            }
            printf("\n平均成绩：%f\n", sum/l);
        }
    }
}

void test_15_3(float (*arr)[5], int c, int l)
{
    float (*a)[5] = arr;
    for (; a<arr+c; a++) {
        float *d = *a;
        int count = 0;
        float sum = 0.f;
        for (; d<*a+l; d++) {
            sum += *d;
            if (*d >= 85) {
                count ++;
            }
        }
        if (sum/l >= 90.f || count == 5) {
            printf("满足条件的学生：%ld \n", a-arr);
        }
    }
}


void test_15(){
    float arr[4][5] = {
        {80, 24, 67, 76, 80},
        {80, 34, 75, 96, 86},
        {100, 50, 100, 100, 100},
        {86, 85, 86, 85, 89}};
    avaige1(arr, 4);
    test_15_2(arr, 4, 5);
    test_15_3(arr, 4, 5);
}

void test_14(){
    int n = 10;
    int *a = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        *a++ = i+1;
    }
    a -= n;
    
    int *i = a;
    int *j = a+n-1;
    for (; i<j; i++, j--){
        int t = *i;
        *i = *j;
        *j = t;
    }
    i = a;
    for (; i<a+n; i++) {
        printf("%d ", *i);
    }
    printf("\n");
    free(a);
}

void DefiniteIntegral(double a, double b, double (*func)(double x, int switch_n)){
    int n = 10000;
    double sum = 0;
    for (int i=1; i<=n; i++) {
        double x = a + (b-a)/n*i;
        double y = (*func)(x, 3);
        sum += (b-a)/n*y;
    }
    printf("积分结果：%f\n", sum);
};

double func(double x, int switch_n){
    double res = 0.f;
    // 被积函数 sinx
    if (switch_n == 0) {
        res = sin(x);
    }
    // 被积函数 cosx
    else if (switch_n == 1) {
        res = cos(x);
    }
    // 被积函数 e^x
    else if (switch_n == 2) {
        res = exp(x);
    }
    // 被积函数 x^2+x
    else if (switch_n == 3) {
        res = pow(x, 2) + x;
    }
    return res;
}

void strSrot(char *strs[], int n){
    char **i = strs;
    char **j = strs;
    for (; i < strs+n-1; i++) {
        for (j=i+1; j < strs+n; j++) {
            if (strcmp(*i, *j)<0) {
                char *t = *i;
                *i = *j;
                *j = t;
            }
        }
    }
    i = strs;
    for (; i < strs+n; i++) {
        printf("%s ", *i);
    }
    printf("\n");
}


void swip(int (*arr)[5], int from, int to){
    int t = *(*arr+to);
    *(*arr+to) = *(*arr+from);
    *(*arr+from) = t;
}

void sort(long a[], int n){
    for (int i=0; i<n-1; i++) {
        for (int j = i+1; j<n; j++){
            if (a[i]>a[j]) {
                long t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void test_10(int (*arr)[5], int l){
    int a=INT_MAX,b=INT_MAX,c=INT_MAX,d=INT_MAX;
    long aI=0,bI=0,cI=0,dI=0;
    int max=INT_MIN;
    long maxI=0;
    int *num = *arr;
    for (; num<(int *)(arr+l); num++) {
        if (*num<=a) {
            dI = cI;
            cI = bI;
            bI = aI;
            aI = num - (int *)(arr);
            d = c;
            c = b;
            b = a;
            a = *num;
        }else if (*num<=b){
            dI = cI;
            cI = bI;
            bI = num - (int *)(arr);
            d = c;
            c = b;
            b = *num;
        }else if (*num<=c){
            dI = cI;
            cI = num - (int *)(arr);
            d = c;
            c = *num;
        }else if (*num<=d){
            dI = num - (int *)(arr);
            d = *num;
        }
        if (*num>max) {
            maxI = num - (int *)(arr);
            max = *num;
        }
    }
//    long t[5] = {aI, bI, cI, dI, max};
    num = *arr;
    for (; num<(int *)(arr+l); num++) {
        printf("%d ", *num);
        if ((num - (int *)(arr) + 1) % 5 == 0){
            printf("\n");
        }
    }
}

void convert(int (*arr)[4], int l){
    int (*array)[4] = arr;
    int (*newA)[4] = malloc(sizeof(int)*16);
    for (int i=0; array<arr+l; array++, i++) {
        for (int *a=*array, j=0; a<*array+4; a++, j++) {
            *(*(newA+j)+i) = *a;
        }
    }
    array = newA;
    for (; array<newA+l; array++) {
        for (int *a=*array; a<*array+4; a++) {
            printf("%d ", *a);
        }
        printf("\n");
    }
    free(newA);
}

int *next(int *head, int *cursor, int n){
    do {
        cursor++;
        if (cursor-head >= n) {
            cursor = head;
        }
    } while (*cursor<0);
    return cursor;
}

void cirle(int m, int n){
    int *arr = malloc(sizeof(int)*n);
    int *a = arr;
    for (int i=1; a<arr+n; a++, i++) {
        *a = i;
    }
    int *head = arr;
    int *cursor = head;
    int tmp = 0;
    int *tmpCur = cursor;
    int removeC = 0;
    do {
        if (++tmp % m == 0){
            *cursor = -1;
            removeC++;
            tmp = 0;
        }
        tmpCur = cursor;
    } while ((cursor = next(head, cursor, n)) && *cursor != *tmpCur && removeC < n-1);
    
    printf("我的算法：%d \n", *cursor);
}

// 这特么什么算法？？？牛逼 牛逼 牛逼！！！！
void nbNb(int M,int n){
    int s = 0;
    for (int i = 2; i <= n; ++i)
        s = (s+M)%i;
    printf("nb 算法：%d\n", s+1);
}

void EntranceDay3(){
    printf("Hello Day3, today study array! \n");
//    test16("aa 12 jj 11 jnnn 34 k 878 jkjk 989 klkl 09090 hjsha 7676opop 0");
//    test_15();
//    test_14();
//    DefiniteIntegral(1, 2, &func);
//    char *strs[] = {"abcd", "abcdf", "abcde"};
//    strSrot(strs, 3);
//    int arr[5][5] = {
//        {1, 2, 3, 4, 1},
//        {6, 7, 8, 9 ,10},
//        {11, 12, -13, 14, 15},
//        {16, 17, 18, 19, 20},
//        {21, 22, 23, 24, 25}
//    };
//    test_10(arr, 5);
//    int arr[4][4] = {
//        {1, 2, 3, 4},
//        {6, 7, 8, 9 },
//        {11, 12, 13, 14},
//        {16, 17, 18, 19},
//    };
//    convert(arr, 4);
//    int n,m;
//    while (scanf("%d %d", &n, &m)) {
//        nbNb(n,m);
//        cirle(n,m);
//    }

    const int n = 5;
    char *strs[n] = {
        "12345",
        "24680",
        "abcde",
        "ABCED",
        "POILK",
    };
    char **s;
    for (s=strs; s<strs+n; s++) {
        printf("%s \a\n", *s);
    }
    
}




