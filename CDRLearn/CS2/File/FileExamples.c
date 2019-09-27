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

typedef struct date{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
}Date, *PDate;

#define FileName "/Users/zhaoqianyu/C_DR_Learn/C_DR_Learn/CDRLearn/CS2/File/Reminder.txt"
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

void FileExamplesMain(int argc, char *argv[]){
    Exam_10_1();
}
