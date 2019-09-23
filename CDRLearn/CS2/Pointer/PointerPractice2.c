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
    while (*str != '\0' && isspace(*str)) {
        str++;
    }
    if (sscanf(str, "%lf", d) != 1) {
        return NULL;
    }
    while (*str != '\0' && !isspace(*str)) {
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

void PointerPractice2Main(int argc, char *argv[]){
//    intPointer();
//    strChange();
//    Practice14();
}
