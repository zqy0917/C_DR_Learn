//
//  IntroduceExam.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/16.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "IntroduceExam.h"

static void draw_line(int st, int len, char c1, char c2){
    int i;
    for (i=0; i<st-1; i++) {
        putchar(' ');
    }
    for (i=st; i<st+len; i++) {
        if (i == st || i == st+len-1) {
            putchar(c1);
        }else{
            putchar(c2);
        }
    }
    putchar('\n');
}

static void triangle(int hi, char c1, char c2){
    int i,j;
    for (i=0; i<hi-1; i++){
        putchar(' ');
    }
    putchar(c1);
    putchar('\n');
    for (i=1; i<hi-1; i++) {
        draw_line(hi-i, i*2+1, c1, c2);
    }
    for (j=0; j<hi*2-1; j++) {
        putchar(c1);
    }
    putchar('\n');
}

void triangleEqual(int n, char c){
    int i,j;
    for (i=1; i<=n; i++) {
        for (j=0; j<n-i; j++) {
            putchar(' ');
        }
        for(j=0; j<i; j++){
            putchar(c);
            putchar(' ');
        }
        putchar('\n');
    }
}

static void Covert(float c, char T){
    float res;
    if (T == 'C') {
        printf("<%f>, <%c> \n", c, 'C');
        res = c*9/5+32;
        printf("<%f>, <%c> \n", res, 'F');
    }else if (T == 'F') {
        printf("<%f>, <%c> \n", c, 'F');
        res = (c-32)*5/9;
        printf("<%f>, <%c> \n", res, 'C');
    }else{
        printf("Data invalid \n");
    }
}

static void driveOnRoad(){
}

static void floatOnRiver(){
    int Vb, Vr, s;
    float t=0;
    scanf("%d%d%d", &Vb, &Vr, &s);
    if (s < 0) {
        printf("距离为负数 \n");
        return;
    }
    if (Vb < 0 || Vr < 0) {
        printf("速度为负数 \n");
        return;
    }
    if (Vb < Vr) {
        printf("无解 \n");
        return;
    }
    t += (float)s/(Vb-Vr);
    t += (float)s/(Vb+Vr);
    printf("时间花费：%f \n", t);
    return;
}

static int max_common_divisor(int m, int n){
    int d;
    if (n == 0) {
        return m;
    }
    for (d=m%n; d != 0; d=m%n) {
        m = n;
        n = d;
    }
    return n < 0 ? -n : n;
}

static void calculate_series_integer(int n){
    int i,j,k,sum;
    for (i=1; i<=n/2; i++) {
        sum=i;
        for (j=i+1; sum<n; j++) {
            sum += j;
        }
        if (sum == n) {
            printf("%d=%d", n, i);
            for (k=i+1; k<j; k++) {
                printf("+%d", k);
            }
            putchar('\n');
        }
    }
}

static void data_sum(){
    int a,b,c,d,x,y,sumX,sumY;
    a=1,b=5,c=11,d=20,sumX=0,sumY=0;
    /*
     scanf函数返回成功读入的数据项数,读入数据时遇到了“文件结束”则返回EOF。
     如: scanf( %d%d ,a,b); 函数返回值为int型。如果a和b都被成功读入,那么scanf的返回值就是2; 如果只有a被成功读入,返回值为1;
     如果a和b都未被成功读入,返回值为0;
     如果遇到错误或遇到end of file,返回值为EOF。end of file为Ctrl+z 或者Ctrl+d
     */
    while (scanf("%d %d", &x, &y) == 2) {
        if (!(x >= a && x <= b) || !(y >= c && y <= d)) {
            continue;
        }
        if (x != 0 && y%x != 0) {
            continue;
        }
        if (y != 0 && x%y != 0) {
            continue;
        }
        sumX += x;
        sumY += y;
    }
}

void gotoPractice(){
    char c;
Repeat: printf("Are you sure ?(y/n)\n");
    c = getchar();getchar();
    if (c != 'y' && c != 'n') {
        goto Repeat;
    }
    if (c == 'y') {
        printf("You select YES\n");
    }else if (c == 'n') {
        printf("You select NO\n");
    }
}

static void output_primeNumbers(){
    int i,j,n=1000,sum=0;
    for (i=1; i<=n; i++) {
        for (j=2; j<i; j++) {
            if (i%j == 0) {
                break;
            }
        }
        if (j>=i) {
            sum++;
            printf("%-3d ", i);
            if (sum % 10 == 0) {
                putchar('\n');
            }
        }
    }
    if (sum % 10 != 0) {
        putchar('\n');
    }
}

static void km_covert_mile(){
    printf("%-4s%-8s%-4s%-8s\n", "km", "mile", "km", "mile");
    int i=1,j=20;
    float k=0.621388;
    for (; i<=15; i++,j+=5) {
        printf("%-4d%-8.4f%-4d%-8.4f\n", i, i*k, j, j*k);
    }
}

void IntroduceExamMain(int argc, char *argv[]){
    printf("\n");
//    int n=6;
//    char c1='\010';
//    char c2='*';
//    putchar(c1);
//    triangle(n, c1, c2);
//    triangleEqual(n, c2);
//    int m=11,n=38,x,y;
//    x = (4*m-n)/2;
//    y = m-x;
//    printf("chicken：%d rabbit：%d \n", x, y);
//    int m,n,k;
//    float t;
//    scanf("%d%d%d", &m, &n, &k);
//    t = (float)k/(n-m);
//    printf("After %d minutes chase \n", (int)(t+0.5));
    
//    Covert(100, 'F');
//    floatOnRiver();
//    int m,n,res;
//    scanf("%d %d", &m, &n);
//    res = max_common_divisor(m, n);
//    printf("%d \n", res);
//    calculate_series_integer(150);
//    data_sum();
//    gotoPractice();
//    output_primeNumber();
    km_covert_mile();
}
