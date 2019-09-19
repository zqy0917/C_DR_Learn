//
//  ArrayPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/19.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "ArrayPractice.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxNum 1000

static void longLine(){
    char arr[2][MaxNum] = {{""}};
    char result[MaxNum];
    unsigned long in=0,longest=1,maxLen=0,len,temp;
    while (gets(arr[in]) != NULL) {
        len = strlen(arr[in]);
        if (len > maxLen) {
            maxLen = len;
            temp = in;
            in = longest;
            longest = temp;
        }
    }
    sprintf(result, "%ld: %s", maxLen, arr[longest]);
    printf("%s\n", result);
}

void initCoordinate(char arr[][MaxNum], int w, int h){
    int i;
    char s[MaxNum];
    for (i=1; i<w; i++) {
        s[i] = ' ';
    }
    s[0] = '|';
    s[w] = '\0';
    for (i=0; i<h; i++) {
        strcpy(arr[i], s);
    }
    for (i=1; i<w; i++) {
        arr[h/2][i] = '-';
    }
}

static void drawFunc(char arr[][MaxNum], int w, int h, int ang){
    int u,v;
    double x,y;
    for (u=0; u<w; u++) {
        x = u*ang/w*M_PI/180;
        y = cos(x);
        v = (int)(h/2-y*h/2);
        arr[v][u] = '*';
        y = sin(x);
        v = (int)(h/2-y*h/2);
        arr[v][u] = '.';
    }
}

void DrawFuncGraph(){
    int i,w=30,h=12,ang=360;
    char arr[w][MaxNum];
    initCoordinate(arr, w, h);
    drawFunc(arr, w, h, ang);
    for (i=0; i<h; i++) {
        puts(arr[i]);
    }
}

static void memcopy(int A[], int n, int *B){
    memcpy(B, A, sizeof(A[0])*(n-1));
}

static void copyArray(){
    const int n = 10;
    int A[n] = {1,2,3,1,5,1,7,1,9,10};
    int B[n] = {-1},i;
    memcopy(A, n, B);
    for (i=0; i<n; i++) {
        printf("%d ", B[i]);
    }
    putchar('\n');
}

static void PrintBanairyArray(int (*A)[MaxNum], int row, int col){
    int i,j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            printf("%d ",(*(A+i))[j]);
        }
        putchar('\n');
    }
}

static void oppositePrintStrs(){
    char s[101];
    int i=0,j;
    while (((s[i]=getchar()) != '\n')&&i<100) {
        i++;
    }
    s[i] = '\0';
    for (j=i-1; j>=0; j--) {
        if (s[j] >= 'A' && s[j] <= 'Z') {
            printf("%c", s[j]);
        }
    }
    putchar('\n');
}

static int checkLeft(char c){
    return (c == '(' || c == '{'  || c == '[' || c == '<' );
}

static int checkRight(char c){
    return (c == ')' || c == '}'  || c == ']' || c == '>' );
}

static int checkSuitable(char c1, char c2){
    if (c1 == '(' && c2 == ')') {
        return 1;
    }
    if (c1 == '{' && c2 == '}') {
        return 1;
    }
    if (c1 == '[' && c2 == ']') {
        return 1;
    }
    if (c1 == '<' && c2 == '>') {
        return 1;
    }
    return 0;
}

static void Practice20(){
    int STACK[MaxNum],top=-1;
    char c,h;
    FILE *fp;
    if ((fp = fopen("/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/Array/ArrayPractice.h","r"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    while ((c = fgetc(fp)) != -1) {
        if (checkLeft(c)) {
            STACK[++top] = c;
        }else if (checkRight(c)) {
            h = STACK[top];
            if (checkSuitable(h, c)) {
                top--;
            }else{
                break;
            }
        }
    }
    fclose(fp);
    if (top < 0) {
        printf("compliance !! \n");
    }else{
        printf("illegal !! \n");
    }
}

static int check21(char c1, char c2){
    if (islower(c1) && islower(c2) && c1 < c2) {
        return 1;
    }
    if (isupper(c1) && isupper(c2) && c1 < c2) {
        return 1;
    }
    if (isdigit(c1) && isdigit(c2) && c1 < c2) {
        return 1;
    }
    return 0;
}

// Difficult!!! 🔥🔥🔥
static void Practice21(){
    char strs[MaxNum],r='\0',c;
    int i=0,n,left;
    fgets(strs, MaxNum, stdin);
    n = (int)strlen(strs)-1;
    strs[n] = '\0';
    for (i=0; i<n; i++) {
        c = strs[i];
        if (r == '\0' && c == '-') {
            i += 1;
            continue;
        }
        if (r == '\0' && c != '-') {
            r = c;
            continue;
        }
        if (r != '\0' && c != '-') {
            putchar(r);
            r = c;
        }else if (r != '\0' && c == '-'){
            if (check21(r, strs[i+1])) {
                for (left=r; left < strs[i+1]; left++) {
                    putchar(left);
                }
                r = strs[i+1];
                i++;
            }else{
                r = strs[i+2];
                i+=2;
            }
        }
    }
    if (strs[n-1] != '-') {
        putchar(strs[n-1]);
    }
    putchar('\n');
}

static void Practice22(){
    const int m=5,n=3;
    int l=0;
    int arr1[m] = {1,3,4,9,9};
    int arr2[n] = {9,8,1};
    int com[MaxNum];
    int i,j,k;
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            if (arr1[i] == arr2[j]) {
                break;
            }
        }
        if (j < n) {
            for (k=0; k<l; k++) {
                if (com[k] == arr1[i]) {
                    break;
                }
            }
            if (k >= l) {
                com[l++] = arr1[i];
            }
        }
    }
    // Sort
    
    // Print
    for (i=0; i<l; i++) {
        printf("%d ", com[i]);
    }
    putchar('\n');
}

void ArrayPracticeMain(int argc, char *argv[]){
//    longLine();
//    DrawFuncGraph();
//    copyArray();
//    oppositePrintStrs();
//    Practice21();
    Practice22();
    
}
