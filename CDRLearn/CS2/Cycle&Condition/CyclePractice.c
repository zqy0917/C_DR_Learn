//
//  CyclePractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/17.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "CyclePractice.h"

static int leap_year(int year){
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

static int year_day(int year){
    return leap_year(year) ? 366 : 365;
}

static int month_day(int year, int month){
    int twoMonth = leap_year(year) ? 29 : 28;
    int months[] = {-1,31,twoMonth,31,30,31,30,31,31,30,31,30,31};
    return months[month];
}

static int countDateThatYear(int year, int month, int day){
    int i,sum=0;
    for (i=1; i<month; i++) {
        sum += month_day(year, i);
    }
    sum += day;
    return sum;
}

static int laterThanDate(int y1, int m1, int d1, int y2, int m2, int d2){
    int b=0;
    if (y2 > y1) {
        b = 1;
    }else if (y2 < y1) {
        b = 0;
    }else{
        if (m2 > m1) {
            b = 1;
        }else if (m2 < m1) {
            b = 0;
        }else{
            if (d2 > d1) {
                b = 1;
            }else if (d2 < d1){
                b = 0;
            }else{
                b = -1;
            }
        }
    }
    return b;
}

static int CalculateGapDays(int y1, int m1, int d1, int y2, int m2, int d2){
    int sum=0,i;
    if (y1 < y2) {
        for (i=y1+1; i < y2; i++) {
            sum += year_day(i);
        }
        sum += countDateThatYear(y2, m2, d2);
        sum += year_day(y1)-countDateThatYear(y1, m1, d1);
    }else if (y1 > y2){
        for (i=y2+1; i < y1; i++) {
            sum += year_day(i);
        }
        sum += countDateThatYear(y1, m1, d1);
        sum += year_day(y2)-countDateThatYear(y2, m2, d2);
    }else{
        for (i=1; i < m2; i++) {
            sum += month_day(y2, i);
        }
        sum += d2-1;
    }
    return sum;
}

// 2019 09 17 Tuesday
static void Practice17(){
    int y1,m1,d1,n,week1,week,y2,m2,d2,month;
    y1 = 2019,m1 = 9,d1 = 17,week1 = 2;
    y2 = y1,m2 = m1,d2 = d1;
    scanf("%d", &n);
    week = n%7 <= week1 ? (week1-n%7) : (7-n%7+week1);
    if (n <= d1) {
        d2 -= n;
    }else{
        n -= d1;
        m2 -= 1;
        while (1) {
            month = month_day(y2, m2);
            if (n - month <= 0) {
                break;
            }
            n -= month;
            m2--;
            if (m2 == 0) {
                y2--;
                m2 = 12;
            }
        }
        d2 = month_day(y2, m2)-n;
    }
    printf("%d年 %d月 %d日 星期%d \n", y2, m2, d2, week);
}

static void CalculateWeek(){
    int y1,m1,d1,y2,m2,d2,week1,week2;
    y1 = 2000,m1 = 1,d1 = 1,week1 = 6;
    scanf("%d-%d-%d", &y2, &m2, &d2);
    int gapDays = CalculateGapDays(y1, m1, d1, y2, m2, d2);
    int later = laterThanDate(y1, m1, d1, y2, m2, d2);
    if (later) {
        week2 = (week1+gapDays%7)%7;
    }else{
        week2 = gapDays%7 <= week1 ? (week1-gapDays%7) : (7-gapDays%7+week1);
    }
    printf("gapDays:%d, week: %d\n", gapDays, week2);
}

static void Practice18(){
    CalculateWeek();
}

static void Practice19(){
    int a,i,n=5,sum=0,t=INT32_MIN;
    for (i=0; i<n; i++) {
        scanf("%d", &a);
        if (t > a) {
            sum++;
        }
        t = a;
    }
    printf("Sum:%d\n", sum);
}

static void Practice20(){
    int s,t,i,j,k,sum,count=0;
    scanf("%d %d", &s, &t);
    for(i=1; i<=s/2; i+=2){
        sum=0;
        for (j=i; j<=2*t; j+=2) {
            sum += j;
            if (sum >= s) {
                break;
            }
        }
        if (sum == s) {
            count++;
            printf("%d=%d", s, i);
            for (k=i+2; k<=j; k+=2) {
                printf("+%d", k);
            }
            putchar('\n');
        }
    }
    if (count == 0) {
        printf("NONE \n");
    }
}

static void Practice21(){
    int n,i,sum=1;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        sum *= i;
    }
    while (sum > 0) {
        n = sum % 10;
        if (n != 0) {
            break;
        }
        sum /= 10;
    }
    printf("%d%d\n", sum/10%10, sum%10);
}

static int calculateJieCheng(int n){
    int i,sum=1;
    for (i=1; i<=n; i++) {
        sum *= i;
    }
    return sum;
}

static double calculateMi(double x, int n){
    double sum=1;
    int i,t=n;
    t=t>0?t:t*-1;
    for (i=1; i<=t; i++) {
        sum *= x;
    }
    if (n < 0) {
        sum = 1/sum;
    }
    return sum;
}

static double Sin(double x, int m){
    int i,j=1;
    double sum=0;
    for (i=1; i<=m; i+=2) {
        sum += calculateMi(x, i)*j/calculateJieCheng(i);
        j *= -1;
    }
    return sum;
}

static double Func(double x, int m){
    int i=0;
    double sum=0,t,tmp;
    while (1) {
        t = calculateMi(-1, i)*calculateMi(x, 2*i)/calculateJieCheng(2*i);
        tmp = t>0?t:t*-1;
        if (tmp < calculateMi(10, -m)) {
            break;
        }
        sum += t;
        i++;
    }
    return sum;
}

static void Practice22(){
    double res;
    res = Sin(1.5707963,10);
    printf("result: %.12lf \n", res);
}

static void Practice25(){
    double x,res;
    int m;
    scanf("%lf %d", &x, &m);
    res = Func(x, m);
    printf("result: %.12lf \n", res);
}

static void Practice26(){
    int n=10,i;
    char c1,c2,c3;
    scanf("%c\n%c", &c1, &c2);
    getchar();
    for (i=0; i<n; i++) {
        scanf("%c", &c3);
        if (c3 == c1) {
            putchar(c2);
        }else{
            putchar(c3);
        }
    }
    putchar('\n');
}

void CyclePracticeMain(int argc, char *argv[]){
    int i;
    for (i=1; i<argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
//    Practice17();
//    Practice18();
//    Practice19();
//    Practice20();
//    Practice21();
//    Practice22();
//    Practice25();
    Practice26();
}
