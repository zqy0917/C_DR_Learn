//
//  main.c
//  CDRLearn
//
//  Created by Zqy on 19/6/15.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "CS/Day2.h"
#include "CS/Day3.h"
#include "CS/Day4.h"
#include "LinearTable.h"
#include "CycleLinearTable.h"

void input()
{
    char c;
    while ((c = getchar()) != '\n') {
        putchar(c);
    }
    putchar('\n');
}

void addTest()
{
    int n;
    scanf("%d", &n);
    int sum = 0;
    for (int i=1; i<=n; i++)
    {
        int tmp = 1;
        for (int j=i; j>=1; j--)
        {
            tmp *= j;
        }
        sum += tmp;
    }
    
    printf("和为： %d \n", sum);
}

// 水仙花数
void test2()
{
    for(int i=100; i<=1000; i++)
    {
        int sum = 0;
        int a = i;
        while (a > 0) {
            sum += pow(a%10, 3);
            a /= 10;
        }
        if (sum == i)
        {
            printf("这是一个水仙花数：%d \n", i);
        }
    }
}

// 找完数
void findPrefect()
{
    for (int i=1; i<=10000; i++)
    {
        int sum = 1;
        for (int j=i-1; j>1; j--)
        {
            if (i%j == 0)
            {
                sum += j;
            }
        }
        if (sum == i)
        {
            printf("%8d 是一个完数 \n", i);
        }
    }
}

// 球反弹问题
void ball()
{
    float high = 0.f;
    float bounceHigh = 100.f;
    for (int i=1; i<= 10; i++) {
        if (i == 1) {
            high = 100.f;
        }else{
            high += bounceHigh*2;
        }
        bounceHigh /= 2;
        printf("第 %d 次落地, 共经过路程：%f \n, 可弹起高度：%f \n", i, high, bounceHigh);
    }
}

// 猴子吃桃问题
void monkeyEatPanch()
{
    int a = 1;
    for (int i = 10; i>=1; i--) {
        printf("第 %d 天，还剩 %d 个桃子 \n", i, a);
        a = (a+1)*2;
    }
}

// 迭代法求开方
void squt()
{
    double x0 = 1.0;
    double a = 3.0;
    double x2 = 1.0;;
    do{
        x0 = x2;
        x2 = (x0+a/x0)/2;
    }while(fabs(x2-x0)>1e-10);
    printf("a 开方近似解：%lf \n", x2);
}

// 牛顿迭代法求根
void root()
{
    double a = 1.5;
    double a0 = 1.5;
    do{
        a = a0;
        a0 = pow((4*a*a-3*a+6)/2, (double)1/3);
    }while(fabs(a0-a)>1e-6);
    printf("方程近似解： %lf \n", a0);
}

// 二分法
void root2()
{
    double left = -10;
    double right = 10;
    double res;
    double mid;
    do{
        mid = (left+right)/2;
        res = 2*mid*mid*mid-4*mid*mid+3*mid-6;
        if (res < 0) {
            left = mid;
        }else{
            right = mid;
        }
    }while(fabs(res-0) > 1e-4);
    printf("方程近似解： %lf \n", mid);
}

void printPoint()
{
    int a = 23;
    for (int i=1; i<=a/2+1; i++) {
        for (int j=1; j<=a/2+i; j++) {
            if (j <= (a-2*i+1)/2){
                printf(" ");
            }else{
                printf("*");
            }
        }
        printf("\n");
    }
    for (int i=1; i<=a/2; i++) {
        for (int j=1; j<=a-i; j++) {
            if (j <= i){
                printf(" ");
            }else{
                printf("*");
            }
        }
        printf("\n");
    }
}

int main(int argc, char * argv[]) {
    // insert code here...
    //    addTest();
    //    test2();
    //    findPrefect();
    //    ball();
    //    monkeyEatPanch();
    //    squt();
    //    root2();
    //    printPoint();
    //    EntranceDay2();
    //    EntranceDay3();
    //    EntranceDay4();
//    DRDay2();
    DRDay3(argc, argv);
    
    return 0;
}
