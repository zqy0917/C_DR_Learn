//
//  CodeDesignPractices.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/24.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "CodeDesignPractices.h"
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MaxNum 1000000

static int DiffNum(int a){
    int nums[MaxNum]={0},count=0,i,j;
    while (a > 0) {
        nums[count++] = a%10;
        a /= 10;
    }
    for (i=0; i<count; i++) {
        for (j=i+1; j<count; j++) {
            if (nums[i] == nums[j]) {
                break;
            }
        }
        if (j < count) {
            break;
        }
    }
    return i >= count;
}

static void Example8_4(){
    int nums[MaxNum]={0},i,j,k,temp,count=0,search=0;
    for (i=1; i<1000; i++) {
        temp = (int)sqrt(i);
        if (temp*temp == i && i>100 && DiffNum(i)) {
            nums[count++] = i;
        }
    }
    for (i=0; i<count; i++) {
        printf("%d \n", nums[i]);
    }
    printf("-----------------------\n");
    for (i=0; i<count; i++) {
        for (j=i+1; j<count; j++) {
            for (k=j+1; k<count; k++) {
                search++;
                temp = nums[i]*1000000+nums[j]*1000+nums[k];
                if (DiffNum(temp)) {
                    printf("Collection: %d %d %d \n", nums[i], nums[j], nums[k]);
                }
            }
        }
    }
    printf("Search count: %d \n", search);
}

// Combination n(1,2,3,...) numbers from m.
static void output_com(int m, int used[MaxNum]){
    int i;
    for (i=1; i<=m; i++) {
        if (used[i]) {
            printf("%d ", i);
        }
    }
    putchar('\n');
}

static void combination(int m, int n, int used[MaxNum], int k, int i){
    int j;
    if (k == n) {
        output_com(m, used);
        return;
    }
    for (j=i; j<=m; j++) {
        used[j] = 1;
        combination(m, n, used, k+1, j+1);
        used[j] = 0;
    }
}

static void CombinationExam(){
    int used[MaxNum]={0};
    int m=5,n=3;
    combination(m, n, used, 0, 1);
}

static void arrange_output(int m, int n, int used[MaxNum]){
    int i;
    int A[MaxNum]={0};
    for (i=1; i<=m; i++) {
        if (used[i]) {
            A[used[i]] = i;
        }
    }
    for (i=1; i<=n; i++) {
        printf("%d ", A[i]);
    }
    putchar('\n');
}

static void arrangement(int m, int n, int used[MaxNum], int k){
    int j;
    if (k == n+1) {
        // arrangement
        arrange_output(m, n, used);
        return;
    }
    for (j=1; j<=m; j++) {
        if(used[j] == 0){
            used[j] = k;
            arrangement(m, n, used, k+1);
            used[j] = 0;
        }
    }
}

static void ArrangementExam(){
    int used[MaxNum]={0};
    int m=5,n=3;
    arrangement(m, n, used, 1);
}

static void alphabet_print(int used[MaxNum], int m){
    int i;
    for (i=1; i<=m; i++) {
        if (used[i]) {
            printf("%c ", 'a'+i-1);
        }
    }
    putchar('\n');
}

static void CombinationAlphabet(int used[MaxNum], int m, int n, int k, int i){
    int j;
    if (k == n) {
        alphabet_print(used, m);
        return;
    }
    for (j=i; j<=m; j++) {
        used[j] = 1;
        CombinationAlphabet(used, m, n, k+1, j+1);
        used[j] = 0;
    }
}

static void CombinationAlphabetExam(){
    int used[MaxNum]={0};
    int m=5,n=3;
    CombinationAlphabet(used, m, n, 0, 1);
}

// Max common Yue Shu
static int MaxCommon(int a, int b){
    int k=a%b;
    while (k != 0) {
        a = b;
        b = k;
        k = a%b;
    }
    return b < 0 ? -b : b;
}

static void Practice23(){
    int n=6,i,j;
    for (i=2; i<=n; i++) {
        for (j=1; j<i; j++) {
            if (MaxCommon(i, j) == 1) {
                printf("%d/%d \n", j, i);
            }
        }
    }
}

static void Practice26(){
    char words[MaxNum],*c,*r;
    char words1[100][100];
    char words2[100][100];
    int isWord=0,len=0,first=0,words1Count=0,words2Count=0,i,j;
    fgets(words, MaxNum, stdin);
    c = words;
    while (*c != '\n') {
        if (islower(*c) || isupper(*c)) {
            if (!isWord) {
                len=0;
                r = c;
            }
            len++;
            isWord = 1;
        }else{
            if (isWord) {
                if (first == 1) {
                    strncpy(words1[words1Count++], r, len);
                    words1[words1Count-1][len] = '\0';
                }else if (first == 2){
                    strncpy(words2[words2Count++], r, len);
                    words2[words2Count-1][len] = '\0';
                }
            } else if (*c == '(') {
                first++;
            }
            isWord = 0;
        }
        c++;
    }
    for (i=0; i<words1Count; i++) {
        for (j=0; j<words2Count; j++) {
            if (strcmp(words1[i], words2[j]) == 0) {
                printf("Common: %s \n", words1[i]);
            }
        }
    }
}

void CodeDesignPracticesMain(int argc, char *argv[]){
//    Example8_4();
//    CombinationExam();
    ArrangementExam();
//    CombinationAlphabetExam();
//    Practice23();
//    Practice26();
}
