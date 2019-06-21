#include <stdio.h>
#include <math.h>

int max(int a,int b)
{
   int z = a > b ? a : b;
   return z; 
}

int min(int a,int b)
{
   int z = a < b ? a : b;
   return z; 
}

void test1()
{
    int a;
    scanf("%d", &a);
    while(a>=1000 || a<=0)
    {
        scanf("%d", &a);
    }
    float b = sqrt(a);
    printf("平方根：%.0f \n", b);
}

void segmentFunc(int x)
{
    int y;
    if (x < 1) 
    {
        y = x;
    }
    else if (x >= 1 && x < 10) 
    {
        y = 2 * x - 1;
    }
    else if (x >= 10)
    {
        y = 3 * x - 11;
    }
    printf("y is: %d \n", y);
}

void segmentFunc2()
{
    int x,y;
    printf("enter x:");
    scanf("%d", &x);
    y = -1;
    if (x != 0) 
    {
        if (x > 0)
            y = 1;
    }
    else
    {
        y = 0;
    }
    printf("x=%d, y=%d \n", x, y);
}

void convertNum()
{
    int a;
    scanf("%d", &a);
    int count = 0;
    int output = 0;
    printf("a is : %d \n", a);
    while(a >= 1)
    {
        count += 1;
        int tmp = a % 10;
        printf("%d ", tmp);
        output *= 10;
        output += tmp;
        a /= 10;
    }
    printf("数字个数：%d \n", count);
    printf("反转后：%d \n", output);
}

void calculateHigh()
{
    float x,y;
    printf("enter x, y \n");
    scanf("%f %f", &x, &y);
    float high = 0.0;
    if ((x-2)*(x-2)+(y-2)*(y-2)-1 < 1e-6) 
    {
        high = 10.0;
    }
    else if ((x+2)*(x+2)+(y-2)*(y-2)-1 < 1e-6)
    {
        high = 10.0;
    }
    else if ((x+2)*(x+2)+(y+2)*(y+2)-1 < 1e-6)
    {
        high = 10.0;
    }
    else if ((x-2)*(x-2)+(y+2)*(y+2)-1 < 1e-6) 
    {
        high = 10.0;
    }
    printf("该点海拔：%f \n", high);
}

void outputSqit()
{
    for(int i=1; i<5; i++)
    {
        for (int j=1; j<6; j++)
        {
            if(j==5)
            {
                printf("%d \n", i*j);
            }
            else
            {
                printf("%d     ", i*j);
            }
            
        }
    }
}

void Fibonacci()
{
    int a=1,b=1;
    for(int i=0; i<40; i++)
    {
        int c = a+b;
        printf("%.12d\n", c);
        a = b;
        b = c;
    }

}

void primeNum()
{
    for(int i=3; i<200; i++)
    {
        int s = sqrt(i);
        int b = 0;
        for(int j=s; j>1; j--)
        {
            if(i%j == 0)
            {
                b = 1;
                break;
            }
        }
        if(!b)
        {
            printf("%d 是素数\n", i);
        }
    }
}

void LargestCommonDivisor()
{
    int a,b;
    printf("Enter a,b \n");
    scanf("%d %d", &a, &b);
    int minN = min(a,b);
    int maxN = max(a,b);
    while (maxN % minN != 0)
    {
        int tmp = minN;
        minN = maxN%minN;
        maxN = tmp;
    }
    printf("最大公约数 Value: %d \n", minN);
    int minC = minN;
    minC *= a/minN;
    minC *= b/minN;
    printf("最小公倍数 Value: %d \n", minC);

}

void calculateNum()
{
    char c;
    int e,t,n,o = 0;
    while ((c = getchar())!='\n')
    {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            e++;
        }
        else if (c == 32 || c == 9)
        {
            t++;
        }
        else if (c >= 48 && c <= 57)
        {
            n++;
        }
        else
        {
            o++;
        }
        putchar(c);
    }
    putchar('\n');
    printf("英文：%d 个，空格：%d 个，数字：%d 个，其他：%d 个 \n", e, t, n, o);
    
}

int main()
{
    // test1();
    // segmentFunc(100);
    // segmentFunc2();
    // convertNum();
    // calculateHigh();
    // outputSqit();
    // Fibonacci();
    // primeNum();
    // LargestCommonDivisor();
    calculateNum();

    return 0;
}

