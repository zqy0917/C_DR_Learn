//
//  StructPractices.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/25.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "StructPractices.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define MaxNum 10000

typedef struct LNode{
    int data;
    struct LNode *link;
}LNode, *LinkList;
#define LNodeSize sizeof(LNode)

typedef union data_u{
    int data;
    char str[28];
}UData, *ULink;

static LinkList CreateList(int data[], int n){
    LinkList list=NULL,r=NULL,t;
    int i;
    for (i=0; i<n; i++) {
        t = (LinkList)malloc(LNodeSize);
        t->data = data[i];
        t->link = NULL;
        if (r == NULL) {
            list = t;
        }else{
            r->link = t;
        }
        r = t;
    }
    return list;
}

static void PrintList(LinkList list){
    LinkList p = list;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->link;
    }
    putchar('\n');
}

// list convert
static LinkList InverseList(LinkList list){
    LinkList p = list,r,t;
    r = p->link;
    p->link = NULL;
    while (r != NULL) {
        t = r->link;
        r->link = p;
        p = r;
        r = t;
    }
    return p;
}

static void Exam_9_6(){
    const int n = 10;
    int data[n] = {1,2,3,4,5,6,7,8,9,10};
    LinkList list = CreateList(data, n);
    PrintList(list);
    list = InverseList(list);
    PrintList(list);
    LNode lll = {-1198, list};
    PrintList(&lll);
}

static void Exam_9_8(){
    ULink u = malloc(sizeof(UData));
    memcpy(u->str, "sdsdsd", sizeof("sdsdsd"));
    u->data = -1000;
    printf("%s \n", u->str);
}

typedef struct data_t{
    int type;
    union{
        int i_val;
        double d_val;
    }data;
    struct data_t *link;
}Data_t, *LData;

static void Push(LData *STACK, LData item){
    item->link = *STACK;
    *STACK = item;
}

static LData Pop(LData *STACK){
    LData p = *STACK;
    *STACK = (*STACK)->link;
    return p;
}

static void cal_int(int a, int b, char op, LData res){
    int sum=0;
    switch (op) {
        case '+':
            sum = a + b;
            break;
        case '-':
            sum = a - b;
            break;
        case '*':
            sum = a * b;
            break;
        case '/':
            sum = a / b;
            break;
    }
    res->type = 0;
    res->data.i_val = sum;
}

static void cal_flt(double a, double b, char op, LData res){
    double sum=0;
    switch (op) {
        case '+':
            sum = a + b;
            break;
        case '-':
            sum = a - b;
            break;
        case '*':
            sum = a * b;
            break;
        case '/':
            sum = a / b;
            break;
    }
    res->type = 1;
    res->data.d_val = sum;
}

static LData calculate(LData num1, LData num2, char op){
    double d1,d2;
    LData res=malloc(sizeof(Data_t));
    res->link = NULL;
    if (num1->type == num2->type) {
        if (num1->type == 0) {
            cal_int(num1->data.i_val, num2->data.i_val, op, res);
        }else{
            cal_flt(num1->data.d_val, num2->data.d_val, op, res);
        }
    }else{
        d1 = num1->type == 0 ? num1->data.i_val : num1->data.d_val;
        d2 = num2->type == 0 ? num2->data.i_val : num2->data.d_val;
        cal_flt(d1, d2, op, res);
    }
    return res;
}

static void Exam_9_9(){
    char strs[MaxNum];
    LData STACK=NULL,t,num1,num2;
    while (scanf("%s", strs) == 1) {
        if (isdigit(strs[0])) {
            t = malloc(sizeof(Data_t));
            t->link = NULL;
            if (strchr(strs, '.') == NULL) {
                t->type = 0;
                t->data.i_val = atoi(strs);
            }else{
                t->type = 1;
                t->data.d_val = atof(strs);
            }
            Push(&STACK, t);
            continue;
        }
        num1 = Pop(&STACK);
        num2 = Pop(&STACK);
        t = calculate(num2, num1, strs[0]);
        Push(&STACK, t);
    }
    t = Pop(&STACK);
    if (t->type == 0) {
        printf("Result: %d \n", t->data.i_val);
    }else{
        printf("Result: %.3lf \n", t->data.d_val);
    }
}

static void Exam_9_10(){
    time_t t;
    int i;
    for (i=0; i<1; i++) {
        t = time(NULL);
        printf("The current time is %s \n", ctime(&t));
    }
}

static void QuickSort(int A[], int l, int r){
    int left=l+1,right=r,temp;
    if (l >= r) {
        return;
    }
    while (1) {
        while (A[left] <= A[l]) {
            left++;
        }
        while (A[right] > A[l]) {
            right--;
        }
        if (left < right) {
            temp = A[left];
            A[left] = A[right];
            A[right] = temp;
        }else{
            break;
        }
    }
    temp = A[l];
    A[l] = A[right];
    A[right] = temp;
    QuickSort(A, l, right-1);
    QuickSort(A, right+1, r);
}

static int sort_int(const void *x1, const void *x2){
    int x11 = *((int *)x1);
    int x22 = *((int *)x2);
    return x11 - x22;
}

static void Practice15(){
    char str[MaxNum],c,*p;
    int i=0,nums[MaxNum]={0},k=0;
    while (scanf("%c", str+i) != -1 && (c=str[i]) != '\n') {
        if (isdigit(c)) {
            nums[k++] = c-'0';
        }
        i++;
    }
    str[i] = '\0';
    qsort(nums, k, sizeof(nums[0]), sort_int);
    p = str;
    k=0;
    while (*p != '\0') {
        if (isdigit(*p)) {
            putchar('0'+nums[k++]);
        }else{
            putchar(*p);
        }
        p++;
    }
    putchar('\n');
}

typedef struct word{
    int pos;
    int len;
    int count;
}NWord, *LWord;

static int compareStrs(char artical[MaxNum], NWord word1, NWord word2){
    int i,j;
    if (word1.len != word2.len) {
        return 0;
    }
    i = word1.pos;
    j = word2.pos;
    while (i<word1.pos+word1.len) {
        if (artical[i] != artical[j]) {
            return 0;
        }
        i++;
        j++;
    }
    return 1;
}

static void PushData(char artical[MaxNum], NWord words[MaxNum], int *count){
    int i;
    for (i=0; i<(*count)-1; i++) {
        if (compareStrs(artical, words[i], words[*count-1]) == 1) {
            words[i].count++;
            break;
        }
    }
    if (i<(*count)-1) {
        words[*count-1].count = 0;
        words[*count-1].pos = 0;
        words[*count-1].len = 0;
        *count = *count-1;
    }
}

static void PrintStr(char artical[MaxNum], NWord word){
    int i;
    putchar('<');
    for (i=word.pos; i<word.pos+word.len; i++) {
        putchar(artical[i]);
    }
    printf("> <%d>\n", word.count);
    
}

static void Practice16(){
    char artical[MaxNum],c;
    NWord words[MaxNum];
    int i=0,count=0,isWord=0,pos=0,len=0;
    fgets(artical, MaxNum, stdin);
    while ((c = artical[i]) != '\0') {
        if (c != ' ' && c != '\n') {
            if (!isWord) {
                pos=i;
                len=0;
            }
            len++;
            isWord = 1;
        }else{
            if (isWord) {
                words[count].count++;
                words[count].pos = pos;
                words[count++].len = len;
                PushData(artical, words, &count);
            }
            isWord = 0;
        }
        i++;
    }
    artical[i] = '\0';
    for (i=0; i<count; i++) {
        PrintStr(artical, words[i]);
    }
    putchar('\n');
}

// ignore
static void Practice17(){
    
}

// Read difficult 🔥🔥🔥
static void Practice18(){
    
}

// Difficult 🔥🔥🔥
static void Practice19(){
    const int n=1000;
    int lines=0;
    char strs[n],c;
    FILE *fp;
    if ((fp=fopen("/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/Struct&Union/StructPractices.h", "r")) == NULL){
        printf("Open file failed \n");
        exit(0);
    }
    while((fgets(strs, n, fp)) != NULL){
        printf("%s", strs);
    }
}

static void PrintWord(char words[][MaxNum], int m, char *word, int used[]){
    int i;
    signed long len=strlen(word);
    char newStr[len+1];
    for (i=0; i<len; i++) {
        newStr[used[i]-1] = word[i];
    }
    newStr[len]='\0';
    for (i=0; i<m; i++) {
        if (strcmp(newStr, word) == 0) {
            continue;
        }
        if (strcmp(words[i], newStr) == 0) {
            printf("%s ", newStr);
        }
    }
}

static void ArrangeMent(char words[][MaxNum], int m, char *word, int k, int used[]){
    int i;
    unsigned long n=strlen(word);
    if (k == n+1) {
        PrintWord(words, m, word, used);
    }
    for (i=0; i<n; i++) {
        if (used[i] == 0) {
            used[i] = k;
            ArrangeMent(words, m, word, k+1, used);
            used[i] = 0;
        }
    }
}

static void Practice20(){
    const int m=7;
    int i,count=0,userd[MaxNum]={0};
    char words[m][MaxNum];
    while (count < m) {
        fgets(words[count], MaxNum, stdin);
        words[count][strlen(words[count])-1]='\0';
        count++;
    }
    putchar('\n');
    ArrangeMent(words, m, "army", 1, userd);
    putchar('\n');
    ArrangeMent(words, m, "mage", 1, userd);
    putchar('\n');
    ArrangeMent(words, m, "bed", 1, userd);
    putchar('\n');
}

void StructPracticesMain(int argc, char *argv[]){
//    Exam_9_6();
//    Exam_9_8();
//    Exam_9_9();
//    Exam_9_10();
//    Practice15();
//    Practice16();
//    Practice17();
//    Practice18();
//    Practice19();
    Practice20();
}
