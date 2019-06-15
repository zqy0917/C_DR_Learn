//
//  Day2.c
//  StudyDay1
//
//  Created by Zqy on 19/6/2.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "Day2.h"
#include <string.h>
#include <math.h>

void bubbleSort(int array[], int count)
{
//    int a[10] = {20, 12, 152, 42, 89, 12, 42, 121, 112 ,12};
    count -= 1 ;
    for (int i=0; i<count; i++)
    {
        for (int j=0; j<count-i; j++)
        {
            if (array[j] > array[j+1]) {
                int t = array[j];
                array[j] = array[j+1];
                array[j+1] = t;
            }
        }
    }
}

void dimensionArray()
{
    int a[2][3] = {{1, 2, 3},{4, 5, 6}};
    int b[3][2];
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++){
            int value = a[i][j];
            b[j][i] = value;
        }
    }
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++){
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}

void strArray(){
    char str1[5], str2[5], str3[5];
    scanf("%s %s %s", str1, str2, str3);
    printf("%s %s %s \n", str1, str2, str3);
}

void strFuncTest(){
    char s1[20] = "china ";
    char s2[] = "hello";
    s1[3] = '>';
    printf("%s \n", strcat(s1, s2));
    
    char s3[20];
    strncpy(s3, s1, 3);
    puts(s3);
    
    char s4[10] = "Chin0";
    char s5[10] = "Chin1";
    printf("%s  %s\n", s4, s5);
    if (strcmp(s4, s5) > 0) {
        printf("字符串 s4 更大 \n");
    }else{
        printf("字符串 s5 更大 \n");
    }
    
    
}

void coculateWordsCount()
{
    char str[100];
    gets(str);
    int sum = 0;
    int isWord = 0;
    for (int i=0; i<strlen(str); i++) {
        char c1 = str[i];
        if (c1 != ' ' && isWord == 0) {
            isWord = 1;
            sum ++;
        }else if (c1 == ' ') {
            isWord = 0;
        }
    }
    
    printf("单词个数：%d 个 \n", sum);
}

void coculateWordsCount2()
{
    char string[81];
    int i, num=0, word=0;
    char c;
    gets(string);
    for (i=0; (c=string[i])!='\0'; i++) {
        if (c == ' ') {
            word = 0;
        }else if (word == 0){
            word = 1;
            num ++;
        }
    }
    
    printf("单词个数：%d 个 \n", num);
}

int max(int a, int b){
    return a>b?a:b;
}

int min(int a, int b){
    return a<b?a:b;
}

void test21(){
    int a[10] = {1, 9, 2, 7, 8, 7, 67, 2, 3, 4};
    for (int i=0; i<10-1; i++) {
        for (int j=i+1; j<10; j++) {
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
    for (int i=0; i<10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void test7(){
    int n = 5;
    int nums[5][5] = {0};
    int lastR = 0;
    int lastL = 0;
    for (int i=1; i<=n*n; i++) {
        int currentR = 0;
        int currentL = 0;
        if (i == 1) {
            currentR = 0;
            currentL = n/2;
        }else{
            currentR = lastR-1;
            currentL = lastL+1;
            if (lastR == 0) {
                currentR = n-1;
            }
            if (lastL == n-1) {
                currentL = 0;
            }
            if (nums[currentR][currentL] != 0) {
                currentR = lastR + 1;
                currentL = lastL;
            }
        }
        
        nums[currentR][currentL] = i;
        lastR = currentR;
        lastL = currentL;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d\t", nums[i][j]);
        }
        printf("\n");
    }
}

void test6()
{
    int n = 10;
    int a[10][10];
    a[0][0] = 1;
    a[1][0] = 1;
    a[1][1] = 1;
    for (int i=2; i<n; i++) {
        for (int j=0; j<=i; j++) {
            if (j == 0 || j == i) {
                a[i][j] = 1;
            }else{
                a[i][j] = a[i-1][j] + a[i-1][j-1];
            }
        }
    }
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<=i; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    
}

void test3()
{
    int a[11] = {1, 1, 2, 7, 8, 17, 67, 211, 311, 411};
    int target = 5;
    a[10] = target;
    int index =10;
    for (int i=9; i>0; i--) {
        if (a[i] > target) {
            int t = a[i];
            a[i] = a[index];
            a[index] = t;
            index--;
        }
    }
    for (int i=0; i<11; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    
}

void test8()
{
    int nums[4][5] = {{2, 18, 17, 111, 311},
                      {2, 9, 9, 10, 10},
                      {9, 17, 25, 81, 41},
                      {1, 18, 10, 81, 81}};
    int row = 3;
    int line = 5;
    for (int i=0; i<row; i++){
        int maxIndex = 0;
        int maxValue = -1000000000;
        for (int j=0; j<line; j++){
            if (nums[i][j] >= maxValue){
                maxValue = nums[i][j];
                maxIndex = j;
            }
        }
        for (int l=0; l<line; l++) {
            if (nums[i][l] == maxValue) {
                int minLineValue = maxValue;
                for (int i=0; i<row; i++) {
                    if (nums[i][maxIndex] <= minLineValue) {
                        minLineValue = nums[i][maxIndex];
                    }
                }
                if (minLineValue == maxValue) {
                    printf("该点是鞍点位于 %d 行，%d 列，值是：%d \n", i, l, minLineValue);
                }
            }
        }
    }
}

void test9()
{
    int nums[15] = {125, 14, 193, 12, 1231, 120, 9, 83, 73, 27, 98, 19 ,19, 1378, 1290};
    bubbleSort(nums, 15);
    for (int i=0; i<15; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    int target = 83;
    
    int left = 0;
    int right = 14;
    int index = (left + right)/2;
    while ((nums[index] != target) && right-left>1) {
        int tmp = nums[index];
        if (target > tmp) {
            left = index;
        }else{
            right = index;
        }
        index = (left + right)/2;
    }
    if (nums[index] != target) {
        index = -1;
    }
    if (index < 0) {
        printf("没找到\n");
    }else{
        printf("当前位置：%d, 取值：%d\n", index, nums[index]);
    }
}

void test10()
{
    char strs[3][100] = {
        "aaaaAAAA&*#$8989       ",
        "",
        "",
    };
    int a, b, ch ,d, e;
    for (int i=0; i<3; i++) {
        char s[100];
        strcpy(s, strs[i]);
        for (int j=0; j<strlen(s); j++){
            char c = s[j];
            if (c >= 'A' && c <= 'Z') {
                a++;
            }else if (c >= 'a' && c <= 'z'){
                b++;
            }else if (c >= '0' && c <= '9'){
                ch++;
            }else if (c == ' ' || c == '\t' || c == '\n'){
                d++;
            }else{
                e++;
            }
        }
    }
    printf("大写字母：%d\n小写字母：%d\n数字：%d\n空格：%d\n其他：%d\n", a, b, ch, d, e);
}

void test11()
{
    char str[5][100] = {
        {'*', '\t', '*', '\t', '*', '\t', '*', '\t', '*'},
        {'\t', '*', '\t', '*', '\t', '*', '\t', '*', '\t', '*'},
        {'\t', '\t', '*', '\t', '*', '\t', '*', '\t', '*', '\t', '*'},
        {'\t', '\t', '\t', '*', '\t', '*', '\t', '*', '\t', '*', '\t', '*'},
        {'\t', '\t', '\t', '\t', '*', '\t', '*', '\t', '*', '\t', '*', '\t', '*'},
    };
    for (int i=0; i<5; i++) {
        printf("%s \n", str[i]);
    }
}

void test12()
{
    char str[200] = "bsadbjkKLzx::NDLN:ONAU:DBwyil耨：JJSX皮皮O：io; ";
    printf("加密前： %s \n", str);
    for (int i=0; i<strlen(str); i++)
    {
        char c = str[i];
        if (c >= 'a' && c <= 'z') {
            c = 'a' + 26 - (c-'a'+1);
            str[i] = c;
        }else if (c >= 'A' && c <= 'Z'){
            c = 'A' + 26 - (c-'A'+1);
            str[i] = c;
        }
        
    }
    printf("加密后： %s \n", str);
}

void test13()
{
    char str1[20] = "Hello, ";
    char str2[20] = "World !!!";
    unsigned long str1L = strlen(str1);
    for (int i=0; i<strlen(str2); i++) {
        str1[str1L+i] = str2[i];
    }
    printf("拼接后： %s \n", str1);
}

void test14()
{
    char str1[] = "d1sdasaaa5";
    char str2[] = "d1sdasaaa";
    unsigned long str1Len = strlen(str1);
    unsigned long str2Len = strlen(str2);
    int minLen = min((int)str1Len, (int)str2Len);
    int maxLen = max((int)str1Len, (int)str2Len);
    int a = 0;
    for (int i=0; i<maxLen; i++) {
        if (i == minLen) {
            str1Len > str2Len ? (a = str1[i]) : (a = -str2[i]);
            break;
        }
        char cstr1 = str1[i];
        char cstr2 = str2[i];
        a = cstr1-cstr2;
        if (a != 0) {
            break;
        }
    }
    
    printf("1与2 差值：%d \n", a);
}

void test15()
{
    char str1[100] = "This is a str rí¢ hahaha !! ";
    printf("%s \n", str1);
    char str2[300];
    unsigned long len = strlen(str1);
    for (int i=0; i<len; i++) {
        char c = str1[i];
        str2[i] = c;
        if (i == len-1) {
            str2[i+1] = '\0';
        }
    }
    printf("%s \n", str2);
}

void EntranceDay2()
{
    printf("Hello Day2, today study array! \n");
//    bubbleSort();
//    dimensionArray()
//    strArray();
//    strFuncTest();
//    coculateWordsCount();
    test7();
}