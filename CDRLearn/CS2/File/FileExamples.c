//
//  FileExamples.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/27.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "FileExamples.h"
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct date{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
}Date, *PDate;

#define MaxNum 1000
#define FileName "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Reminder.txt"
#define FileName2 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/data_file.txt"
static void CreateDailyEvent(PDate date, char *buf){
    FILE *fp;
    if ((fp = fopen(FileName, "a")) == NULL) {
        perror("Can not open file");
        return;
    }
    fputs(buf, fp);
    fclose(fp);
}

static int checkEmptyLine(char *s){
    int b=1;
    for (; *s != '\0'; s++) {
        if (!isspace(*s)) {
            b = 0;
            break;
        }
    }
    return b;
}

static void InputEvent(){
    char buf[BUFSIZ];
    int year, month, day, hour, min, sec;
    while (1) {
        fgets(buf, BUFSIZ, stdin);
        if (checkEmptyLine(buf)) {
            break;
        }
        if (sscanf(buf, "%d-%d-%d %d-%d-%d\n", &year, &month, &day, &hour, &min, &sec) != 6) {
            fputs("Input format X-X-X X-X-X \n", stderr);
            continue;
        }
        Date date = {year, month, day, hour, min, sec};
        CreateDailyEvent(&date, buf);
    }
}

static void OutputEvent(){
    FILE *fp;
    char buf[BUFSIZ];
    int year, month, day, hour, min, sec, mon;
    time_t cur_time;
    struct tm *newTime;
    if ((fp = fopen(FileName, "r")) == NULL) {
        perror("Can not open file");
        return;
    }
    time(&cur_time);
    newTime = localtime(&cur_time);
    while (fscanf(fp, "%d-%d-%d %d-%d-%d", &year, &month, &day, &hour, &min, &sec) == 6) {
        fgets(buf, BUFSIZ, fp);
        mon = newTime->tm_mon+1;
        if (month > mon || (mon == month && day >= newTime->tm_mday)) {
            printf("%2d.%-2d %s", month, day, buf);
        }
    }
    fclose(fp);
}

static void Exam_10_1(){
    InputEvent();
    OutputEvent();
}

static int FileLength(FILE *fp){
    if (!fp) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    return (int)ftell(fp);
}

static void Exam_10_3(){
    int i, buf[BUFSIZ], p;
    long len;
    FILE *fp;
    if ((fp = fopen(FileName2, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    for (i=0; i<BUFSIZ; i++) {
        if ((p = fscanf(fp, "%d", &buf[i])) != 1){
            break;
        }
    }
    len = ftell(fp);
    printf("%d int read, current position is %ld \n", i, len);
    printf("File length: %d \n", FileLength(fp));
    fclose(fp);
}

#define MaxLine 100
#define MaxRows 300
static void Exam_10_4(){
    long lines[MaxLine]={0}, count=0;
    char buf[MaxRows];
    FILE *fp;
    if ((fp = fopen(FileName, "r")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    while (fgets(buf, MaxRows, fp) != NULL) {
        lines[++count] = ftell(fp);
    }
    count--;
    for (; count >= 0; count--) {
        fseek(fp, (int)lines[count], SEEK_SET);
        fgets(buf, MaxRows, fp);
        fputs(buf, stdout);
    }
    fclose(fp);
}

typedef struct Date_t{
    int month;
    int day;
    int offset;
}Date_t, *P_Date;

static void inputDate(){
    int month,day;
    char buf[BUFSIZ];
    FILE *fp;
    if ((fp = fopen(FileName, "a")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    while (1) {
        fgets(buf, BUFSIZ, stdin);
        if (checkEmptyLine(buf)) {
            fclose(fp);
            break;
        }
        if (sscanf(buf, "%d.%d", &month, &day) != 2) {
            fputs("Input format: <month>.<day> <message> \n", stderr);
            continue;
        }
        fputs(buf, fp);
    }
}

#define MaxDate 100
static int Sort_date(const void *d1, const void *d2){
    P_Date d11 = *(P_Date *)d1;
    P_Date d22 = *(P_Date *)d2;
    if (d11->month > d22->month) {
        return 1;
    }else if ((d11->month == d22->month) && (d11->day > d22->day)){
        return 1;
    }
    return 0;
}

static void OutputDates(){
    int month,day, mon, count=0, i;
    P_Date dates[MaxDate];
    char buf[BUFSIZ];
    time_t cur_time;
    struct tm *newTime;
    FILE *fp;
    if ((fp = fopen(FileName, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    time(&cur_time);
    newTime = localtime(&cur_time);
    while (fscanf(fp, "%d.%d", &month, &day) == 2) {
        mon = newTime->tm_mon+1;
        if (month > mon || (month == mon && day >= newTime->tm_mday)) {
            dates[count] = malloc(sizeof(Date_t));
            dates[count]->month = month;
            dates[count]->day = day;
            dates[count++]->offset = (int)ftell(fp);
        }
        fgets(buf, BUFSIZ, fp);
    }
    qsort(dates, count, sizeof(dates[0]), Sort_date);
    for (i=0; i<count; i++) {
        fseek(fp, dates[i]->offset, SEEK_SET);
        fgets(buf, BUFSIZ, fp);
        printf("%d.%d %s", dates[i]->month, dates[i]->day, buf);
    }
    fclose(fp);
}

static void Exam_10_2_1(){
    inputDate();
    OutputDates();
}

static void Exam_10_5(){
    const int n=10;
    int write_arr[n] = {1,2,3,4,5,6,7,8,9,10}, read_arr[MaxNum], count, len;
    FILE *fp;
    if ((fp = fopen(FileName, "a+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fwrite(write_arr, n, sizeof(read_arr[0]), fp);
    fseek(fp, 0, SEEK_SET);
    count = (int)fread(read_arr, sizeof(read_arr[0]), MaxNum, fp);
    len = (int)ftell(fp);
    fclose(fp);
    printf("%d int read, current position is: %d \n", count, len);
}

static void Exam_10_5_1(){
    const int n=10;
    double write_arr[n] = {1.0001,2.02,3.45,4.2738283,5.0,6.23232,7,8,9,10}, read_arr[MaxNum];
    int count, len;
    FILE *fp;
    if ((fp = fopen(FileName, "a+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fwrite(write_arr, n, sizeof(read_arr[0]), fp);
    fseek(fp, 0, SEEK_SET);
    count = (int)fread(read_arr, sizeof(read_arr[0]), MaxNum, fp);
    len = (int)ftell(fp);
    fclose(fp);
    printf("%d int read, current position is: %d \n", count, len);
}

typedef struct node{
    int data;
    char str[10];
}EncodeData;

static void Exam_10_5_2(){
    FILE *fp;
    const int n=10;
    int i,count;
    EncodeData encode_data[n],decode_data[n];
    for (i=0; i<n; i++) {
        encode_data[i].data = i;
        sprintf(encode_data[i].str, "Str:%d", i);
    }
    if ((fp = fopen(FileName, "a+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(encode_data, sizeof(encode_data[0]), n, fp);
    fseek(fp, 0, SEEK_SET);
    fread(&count, sizeof(int), 1, fp);
    fread(decode_data, sizeof(decode_data[0]), n, fp);
    fclose(fp);
}

#define FileName3 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice3.txt"
static void Practice9(){
    const int n=20;
    char strs[n]="Abcdefgaseiow";
    char strs2[n];
    FILE *fp;
    if ((fp = fopen(FileName3, "a+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
//    fprintf(fp, "%s", strs);
    char *s=strs;
//    fwrite(strs, sizeof(char), strlen(strs), fp);
    fseek(fp, 0, SEEK_SET);
    fread(strs2, sizeof(char), strlen(strs), fp);
    fclose(fp);
}

static void Practice16(int argc, char *argv[]){
    char c;
    if (argc-1 > 1) {
        fprintf(stderr, "Input: <I> or <O> \n");
        return;
    }
    if (argc == 1) {
        OutputDates();
    }else{
        c = argv[1][0];
        if (strlen(argv[1])!= 1 || (c != 'I' && c != 'O')) {
            fprintf(stderr, "Input: <I> or <O> \n");
        }else{
            if (c == 'I') {
                inputDate();
            }else{
                OutputDates();
            }
        }
    }
}

static int sort_file(const void *f1, const void *f2){
    int *f11 = (int *)f1;
    int *f22 = (int *)f2;
    return f11[1] - f22[1];
}

static void Practice17(int argc, char *argv[]){
    if (argc <= 1) {
        fprintf(stderr, "Please input <filename1> <filename2> ... \n");
        return;
    }
    int i, datas[argc-1][2], count=0;
    FILE *fp;
    char *fileName;
    for (i=1; i<argc; i++) {
        fileName = argv[i];
        if ((fp = fopen(fileName, "r")) == NULL) {
            continue;
        }
        fseek(fp, 0, SEEK_END);
        datas[count][0] = i;
        datas[count++][1] = (int)ftell(fp);
        fclose(fp);
    }
    qsort(datas, count, sizeof(datas[0]), sort_file);
    for (i=0; i<count; i++) {
        printf("%s  ", argv[datas[i][0]]);
    }
    putchar('\n');
}

typedef struct Staff{
    char name[12];
    int age;
    int gander;
    double wage;
}Staff, *p_Staff;

#define FileName18 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice18.txt"
#define FileName18_bin "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice18_bin.bin"
static void Practice18(){
    char strs[MaxNum];
    int count=0,i;
    Staff staff;
    FILE *fp;
    FILE *fp_bin;
    if ((fp = fopen(FileName18, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fopen(FileName18_bin, "a+");
    if ((fp_bin = fopen(FileName18_bin, "w+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp_bin);
    while (fgets(strs, MaxNum, fp) != NULL) {
        count++;
        if (sscanf(strs, "%s %d %d %lf", staff.name, &staff.age, &staff.gander, &staff.wage) == 4){
            fwrite(&staff, sizeof(Staff), 1, fp_bin);
        }
    }
    fseek(fp_bin, 0, SEEK_SET);
    fwrite(&count, sizeof(int), 1, fp_bin);
    fclose(fp);
    fclose(fp_bin);
}

#define FileName19_txt "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice18_bin.txt"
static void Practice19(){
    int len,i;
    Staff staff;
    FILE *fp_bin;
    if ((fp_bin = fopen(FileName18_bin, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    FILE *fp_txt;
    if ((fp_txt = fopen(FileName19_txt, "r+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fread(&len, sizeof(int), 1, fp_bin);
    fprintf(fp_txt, "Data count: %d\n", len);
    for (i=0; i<len; i++) {
        fread(&staff, sizeof(Staff), 1, fp_bin);
        fprintf(fp_txt, "%s %d %d %lf\n", staff.name, staff.age, staff.gander, staff.wage);
    }
    fclose(fp_bin);
    fclose(fp_txt);
}

static void Practice20(){
    int org_len, len, i;
    Staff staff;
    FILE *fp_txt;
    FILE *fp_bin;
    if ((fp_txt = fopen(FileName19_txt, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    if ((fp_bin = fopen(FileName18_bin, "r+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fscanf(fp_txt, "Data count: %d\n", &len);
    fread(&org_len, sizeof(int), 1, fp_bin);
    org_len += len;
    fseek(fp_bin, 0, SEEK_SET);
    fwrite(&org_len, sizeof(int), 1, fp_bin);
    fseek(fp_bin, 0, SEEK_END);
    for (i=0; i<len; i++) {
        fscanf(fp_txt, "%s %d %d %lf\n", staff.name, &staff.age, &staff.gander, &staff.wage);
        fwrite(&staff, sizeof(Staff), 1, fp_bin);
    }
    fclose(fp_txt);
    fclose(fp_bin);
}

static void Practice20_1(){
    int len,i;
    Staff staff;
    FILE *fp_bin;
    if ((fp_bin = fopen(FileName18_bin, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    fread(&len, sizeof(int), 1, fp_bin);
    fprintf(stdout, "Data count: %d\n", len);
    for (i=0; i<len; i++) {
        fread(&staff, sizeof(Staff), 1, fp_bin);
        fprintf(stdout, "%s %d %d %lf\n", staff.name, staff.age, staff.gander, staff.wage);
    }
    fclose(fp_bin);
}

#define FileName22_1 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice22_1.bin"
static void Practice22_1(){
    FILE *fp;
    const int n=5;
    double data[n][n] = {
        {0.01, 2.30, 3.23, 3.5567, 10.2323},
        {0.1, 2.0, 3.23, 3.567, 10.2},
        {0.01, 2.30, 3.23, 3.57, 10.21233},
        {0.1, 2.3, 3.23, 3.7, 10.2233},
        {0.01, 2.30, 3.23, 3.57, 10.2673}
    };
    if ((fp = fopen(FileName22_1, "w+")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    fwrite(data, n, sizeof(data[0]), fp);
    fclose(fp);
}

static void Practice22_1_1(){
    FILE *fp;
    const int n=5;
    int i, j;
    double data[n][n];
    if ((fp = fopen(FileName22_1, "r")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    fread(data, n, sizeof(data[0]), fp);
    fclose(fp);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%-7.3lf", data[i][j]);
        }
        putchar('\n');
    }
}

#define FileName22_2 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice22_2.txt"
static void Practice22_2(){
    FILE *fp;
    char num[MaxNum];
    char sum[MaxNum]={'\0'};
    const int n=5;
    int i, j;
    double data[n][n] = {
        {0.01, 2.30, 3.23, 3.5567, 10.2323},
        {0.1, 2.0, 3.23, 3.567, 10.2},
        {0.01, 2.30, 3.23, 3.57, 10.21233},
        {0.1, 2.3, 3.23, 3.7, 10.2233},
        {0.01, 2.30, 3.23, 3.57, 10.2673}
    };
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            sprintf(num, "%.3lf ", data[i][j]);
            strcat(sum, num);
        }
        strcat(sum, "\n");
    }
    if ((fp = fopen(FileName22_2, "w+")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    fputs(sum, fp);
    fclose(fp);
}

static void Practice22_2_1(){
    FILE *fp;
    const int n=5;
    int i, j, isD=0, count=0, row=0;
    double data[n][n];
    char sum[MaxNum],*s;
    if ((fp = fopen(FileName22_2, "r")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    while (fgets(sum, MaxNum, fp) != NULL) {
        s = sum;
        while (*s != '\n') {
            if (*s != ' ') {
                if (!isD) {
                    data[row][count++] = atof(s);
                    isD = 1;
                }
            }else{
                isD = 0;
            }
            s++;
        }
        row++;
        count = 0;
    }
    fclose(fp);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%-7.3lf", data[i][j]);
        }
        putchar('\n');
    }
}

#define FileName23 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice23.txt"
#define m 10
#define k 3
static void Practice23(){
    int nums[m]={0},count=0,p=0,isNum=0,i,sum=0,max,min;
    char buf[BUFSIZ],*s;
    FILE *fp;
    if ((fp = fopen(FileName23, "r")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    while (fgets(buf, BUFSIZ, fp) != NULL) {
        s = buf;
        p = 0;
        isNum = 0;
        while (*s != '\n') {
            if (*s != ' ') {
                if (!isNum) {
                    p++;
                    if (p == k) {
                        nums[count++] = atoi(s);
                        break;
                    }
                }
                isNum = 1;
            }else{
                isNum = 0;
            }
            s++;
        }
        if (p < k) {
            nums[count++] = 0;
        }
    }
    max = nums[0];
    min = nums[0];
    for (i=0; i<count; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
        if (nums[i] < min) {
            min = nums[i];
        }
        sum += nums[i];
    }
    printf("Max: %d, Min: %d, Avg: %.3lf\n", max, min, (double)sum/count);
}

static void StatisticStorage(){
    
}

#define FileName24 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice24.txt"
static void Practice24(){
    int sum=0;
    char buf[BUFSIZ], *tarStr="GB", *tarPos;
    FILE *fp;
    if ((fp = fopen(FileName24, "r")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    while (fgets(buf, BUFSIZ, fp) != NULL) {
        if ((tarPos = strstr(buf, tarStr)) != NULL) {
            while (isdigit(*(--tarPos)));
            sum += atoi(tarPos);
        }
    }
    printf("Sum: %d\n", sum);
}

#define FileName25 "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Practice25.txt"
#define MaxCount 1000000
#define MaxLength 2000
typedef struct Data{
    uint pos;
    int len;
}Data, *PData;
FILE *fp;

static int comp_file(const void *f1, const void *f2){
    Data f11 = *(PData)f1;
    Data f22 = *(PData)f2;
    char f1s[MaxLength],f2s[MaxLength];
    if (f11.len == f22.len) {
        fseek(fp, f11.pos, SEEK_SET);
        fgets(f1s, MaxLength, fp);
        fseek(fp, f22.pos, SEEK_SET);
        fgets(f2s, MaxLength, fp);
        return strcmp(f1s, f2s);
    }else{
        return f11.len-f22.len;
    }
}

static void Practice25(){
    Data datas[MaxCount];
    char buf[MaxLength];
    int count=0,strLen,i;
    if ((fp = fopen(FileName25, "r")) == NULL) {
        perror("Can not open this file\n");
        return;
    }
    while (fgets(buf, MaxLength, fp) != NULL) {
        strLen = (int)strlen(buf);
        datas[count].pos = (uint)ftell(fp)-strLen;
        datas[count++].len = strLen;
    }
    qsort(datas, count, sizeof(Data), comp_file);
    for (i=0; i<count; i++){
        fseek(fp, datas[i].pos, SEEK_SET);
        fgets(buf, MaxLength, fp);
        fprintf(stdout, "%s", buf);
    }
}

static void PrintCycle(int n){
    int i,j,ks=1,A[n][n];
    for (i=0; i<n/2; i++) {
        for (j=i; j<n-i; j++) {
            A[i][j] = ks++;
        }
        for (j=i+1; j<n-i; j++) {
            A[j][n-i-1] = ks++;
        }
        for (j=n-2-i; j>=i; j--) {
            A[n-1-i][j] = ks++;
        }
        for (j=n-2-i; j>=i+1; j--) {
            A[j][i] = ks++;
        }
    }
    if (n % 2 != 0) {
        A[n/2][n/2] = ks;
    }
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%-3d ", A[i][j]);
        }
        puts("\n");
    }
}

static void PrintPrimes(int n){
    int i,primes[MaxNum],count=0,p;
    primes[count++] = 2;
    if (n >= 2) {
        primes[count++] = 3;
    }
    while (count < n) {
        p = primes[count-1]+2;
        while (1) {
            for (i=0; i<count; i++) {
                if (p % primes[i] == 0) {
                    break;
                }
            }
            if (i >= count) {
                break;
            }
            p += 2;
        }
        primes[count++] = p;
    }
    for (i=0; i<n; i++) {
        printf("%3d ", primes[i]);
    }
    puts("\n");
}

#define FileName26 "/Users/zqy/C_DR_Learn/CDRLearn/CS2/File/Practice26.txt"
#define FileName26_1 "/Users/zqy/C_DR_Learn/CDRLearn/CS2/File/Practice26_1.txt"

static void ChangeWorld(){
    char *old = "Directly", *new = "HHHHHHHHHHHHHHH", word[BUFSIZ], c;
    int isWorld = 0,len=0;
    FILE *fp1,*fp2;
    if ((fp1 = fopen(FileName26, "r")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    if ((fp2 = fopen(FileName26_1, "w+")) == NULL) {
        perror("Can not open this file \n");
        return;
    }
    while ((c = fgetc(fp1)) != -1) {
        if (isupper(c) || islower(c)) {
            if (!isWorld) {
                len = 0;
            }
            isWorld = 1;
            len++;
        }else{
            if (isWorld) {
                fseek(fp1, -len-1, SEEK_CUR);
                fgets(word, len+1, fp1);
                word[len] = '\0';
                if (strcmp(word, old) == 0) {
                    fputs(new, fp2);
                }else{
                    fputs(word, fp2);
                }
            }else{
                fputc(c, fp2);
            }
            isWorld = 0;
        }
    }
    fclose(fp1);
    fclose(fp2);
}

#define TextFileName "/Users/zqy/C_DR_Learn/CDRLearn/CS2/File/Test_file.txt"
static void Test(){
    FILE *fp;
    int d1,d2,a[6] = {1,2,3,4,5,6};
    fp = fopen(TextFileName, "w");
    fprintf(fp, "%d%d%d\n", a[0], a[1], a[2]);
    fprintf(fp, "%d%d%d\n", a[3], a[4], a[5]);
    fclose(fp);
    fp = fopen(TextFileName, "r");
    fscanf(fp, "%d %d", &d1, &d2);
    printf("%d %d \n", d1, d2);
}

void FileExamplesMain(int argc, char *argv[]){
//    Exam_10_1();
//    Exam_10_3();
//    Exam_10_4();
//    Exam_10_2_1();
//    Exam_10_5();
//    Exam_10_5_1();
//    Exam_10_5_2();
//    Practice9();
//    Practice16(argc, argv);
//    Practice17(argc, argv);
//    Practice18();
//    Practice19();
//    Practice20();
//    Practice20_1();
//    Practice22_1();
//    Practice22_1_1();
//    Practice22_2();
//    Practice22_2_1();
//    Practice23();
//    Practice24();
//    Practice25();
//    PrintCycle(9);
//    PrintPrimes(20);
//    ChangeWorld();
    Test();
}


