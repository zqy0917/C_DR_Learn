#include <stdio.h>
#include <string.h>
#include <math.h>

void calculateData(int year, int month, int date);
int monthDateCount(int month, int leap);
int leapYear(int year);

int main()
{
    calculateData(2019, 3, 1);
    return 0;
}

// 给出年，月，日，计算改日是改年第几天
// 扩展：计算该日是星期几，已知1970年1月1日是星期1。
void calculateData(int year, int month, int date)
{
    int days = 0;
    for(int i=1; i<month; i++)
    {
        days += monthDateCount(i, leapYear(year));
    }
    days += date;
    printf("该日是该年第 %d 天 \n", days);
}

int monthDateCount(int month, int leap)
{
    int days = 31;
    switch (month)
    {
    case 2:
        if (leap) 
            days = 29;
        else
            days = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    default:
        break;
    }
    return days;
}

int leapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}