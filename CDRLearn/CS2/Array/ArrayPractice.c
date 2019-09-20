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

/* 🔥🔥🔥 */
static void Practice23(){
    int i;
//    for ()  /
}

static void Practice24(){
    char strs[MaxNum],*res=NULL,*subs=NULL,c;
    fgets(strs, MaxNum, stdin);
    int i=0,isWord=0,maxLen=0,length=0;
    while ((c=strs[i]) != '\0') {
        if (islower(c) || isupper(c)) {
            if (isWord == 0) {
                length = 0;
                subs = strs+i;
                isWord = 1;
            }
            length++;
        }else{
            if (isWord == 1) {
                if (length > maxLen) {
                    res = subs;
                    maxLen = length;
                }
            }
            isWord = 0;
        }
        i++;
    }
    printf("MaxLength: %d \n", maxLen);
    for (i=0; i<maxLen; i++) {
        putchar(*(res+i));
    }
    putchar('\n');
}

static void Practice25(){
    const int n=26;
    int res[n][2] = {{0}},min_index=MaxNum,min_length=MaxNum,current_index=0,current_length=0;
    char strs[MaxNum],c;
    fgets(strs, MaxNum, stdin);
    int i=0,j,isword=0,count=0;
    while ((c = strs[i]) != '\0') {
        if (islower(c) || isupper(c)) {
            if (!isword) {
                isword = 1;
                current_index = i;
                current_length = 0;
            }
            current_length++;
        }else{
            if (isword) {
                if (count < n) {
                    res[count][0] = current_index;
                    res[count++][1] = current_length;
                }else{
                    if (min_length < current_length) {
                        res[min_index][0] = current_index;
                        res[min_index][1] = current_length;
                    }
                }
                min_length = MaxNum;
                for (j=0; j<count; j++) {
                    if (res[j][1] < min_length) {
                        min_length = res[j][1];
                        min_index = j;
                    }
                }
            }
            isword = 0;
        }
        i++;
    }
    // Sort
    for (i=0; i<count-1; i++) {
        for (j=0; j<count-i-1; j++) {
            if (res[j][1] > res[j+1][1]) {
                current_index = res[j][0];
                current_length = res[j][1];
                res[j][0] = res[j+1][0];
                res[j][1] = res[j+1][1];
                res[j+1][0] = current_index;
                res[j+1][1] = current_length;
            }
        }
    }
    
    // Print
    for (i=0; i<count; i++) {
        for (j=res[i][0]; j<res[i][0]+res[i][1]; j++) {
            putchar(strs[j]);
        }
        putchar('\n');
    }
}

static void Practice26(){
    const int n=3;
    float matrix[n][n] = {
        {0.1, 0.2, 0.3},
        {0.4, 0.5, 0.6},
        {0.7, 0.8, 0.9}
    };
    int i;
    float mainSum=0,viceSum=0;
    for (i=0; i<n; i++) {
        mainSum += matrix[i][i];
        viceSum += matrix[i][n-1-i];
    }
    printf("%f %f \n", mainSum, viceSum);
}

static void PrintMatrix(int matrix[][MaxNum], int row, int col){
    int i,j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            printf("%-4d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

static void Practice27(){
    const int n=5;
    int i,j,matrix[n][MaxNum]={0},m=1;
    for (i=0; i<n/2; i++) {
        for (j=i; j<n-i; j++) {
            matrix[i][j] = m++;
        }
        for (j=i+1; j<n-i; j++) {
            matrix[j][n-i-1] = m++;
        }
        for (j=n-2-i; j>=i; j--) {
            matrix[n-i-1][j] = m++;
        }
        for (j=n-2-i; j>i; j--) {
            matrix[j][i] = m++;
        }
    }
    if (n%2 != 0) {
        matrix[n/2][n/2] = m;
    }
    PrintMatrix(matrix, n, n);
}

// 🔥🔥🔥
static void Practice30(){
    
}

// Three leaf line

static void PrintCharMatrix(char matrix[][MaxNum], int row, int col){
    int i,j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            printf("%c", matrix[i][j]);
        }
        putchar('\n');
    }
}

static void initMatrix(char matrix[][MaxNum], int r){
    int i,j;
    for (i=0; i<r*2+1; i++) {
        for (j=0; j<r*2+1; j++) {
            matrix[i][j] = ' ';
        }
    }
    for (i=0; i<r*2+1; i++) {
        matrix[r][i] = '-';
        matrix[i][r] = '|';
    }
}

static void drawLine(char matrix[][MaxNum], int r){
    int i;
    double x,y;
    double t;
    for (i=0; i <= 360; i++) {
        t=M_PI*2/360*i;
        x = r*sin(t*3)*sin(t);
        y = r*sin(t*3)*cos(t);
        matrix[r-(int)x][r-(int)y] = '*';
    }
}
static void Practice31(){
    const int r=20;
    int i,j;
    char matrix[r*2+1][MaxNum]={{}};
    initMatrix(matrix, r);
    drawLine(matrix, r);
    PrintCharMatrix(matrix, r*2+1, r*2+1);
}

void ArrayPracticeMain(int argc, char *argv[]){
//    longLine();
//    DrawFuncGraph();
//    copyArray();
//    oppositePrintStrs();
//    Practice21();
//    Practice22();
//    Practice23();
//    Practice24();
//    Practice25();
//    Practice26();
//    Practice27();
//    Practice30();
//    Practice31();
    
}
