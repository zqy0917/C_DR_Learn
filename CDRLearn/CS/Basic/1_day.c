#include <stdio.h>
#include <math.h>


static int max(int a, int b);
static int min(int a, int b);
static int threeMax(int a, int b, int c);
static void test1();
static void test2();
static void test3();
static void test4();
int maxCommonFactor(int a, int b);
int maxCommonFactorRecursive(int a, int b);
float FahrenheitToCelsius(float fahrenheit);
void EquationsSolve();
void getcharTest();
void exercises1();
void exercises3();
void exercises4();
void exercises5();
void exercises6();
void exercises7();
void exercises8();

int main_day1()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // int aaa = maxCommonFactor(348732821, 234789327);
    // int bbb = maxCommonFactorRecursive(348732821, 234789327);
    // printf("max common factor: %d \n", aaa);
    // printf("max common factorRecursive: %d \n", bbb);
    // printf("Celsius of 86f: %f \n", FahrenheitToCelsius(86));
    // EquationsSolve();
    // getcharTest();
    // exercises1();
    // exercises3();
    // exercises4();
    // exercises5();
    // exercises6();
    // exercises7();
    exercises8();
    return 0;
}

static void test1()
{
    int n, m, sum;
    n = 1090;
    m = 897;
    sum = n + m;
    printf("The sum is %d \n", sum);
}

static void test2()
{
    int a,b;
    scanf("%d %d", &a, &b);
    printf("max = %d \n", max(a, b));
}

static int max(int a,int b)
{
   int z = a > b ? a : b;
   return z; 
}

static int min(int a,int b)
{
   int z = a < b ? a : b;
   return z; 
}

static void test3()
{
    printf("***************** \n");
    printf("Very Good! \n");
    printf("***************** \n");
}

static void test4()
{
    int u, m, n;
    scanf("%d %d %d", &u, &m, &n);
    printf("max: %d \n", threeMax(u, m, n));
}

int threeMax(int a, int b, int c)
{
    int d = a > b ? a : b;
    d = d > c ? d : c;
    return d;
}

int maxCommonFactor(int a, int b)
{
    int maxNum = max(a, b);
    int minNum = min(a, b);
    int result;
    while(1)
    {
        int c = maxNum % minNum;
        if (c == 0) 
        {
            result = minNum;
            break;
        }
        else
        {
            maxNum = minNum;
            minNum = c;
        }
    }
    return result;
}

int maxCommonFactorRecursive(int a, int b)
{
    int maxNum = max(a, b);
    int minNum = min(a, b);
    int c = maxNum % minNum;
    if (c == 0) 
    {
        return minNum;
    }
    return maxCommonFactorRecursive(minNum, c);
}

// 华氏度转摄氏度，物理公式： c = 5/9(f - 32)
float FahrenheitToCelsius(float fahrenheit) 
{
    long long a = 1289182981928;
    int ccc = -2147483648;
    float celsius = (5.0/9)*(fahrenheit - 32);
    printf("sizeof %lu \n", sizeof(ccc));
    char ddd = 'c';
    printf("sizeof %lu \n", sizeof(ddd));
    return celsius;
}

// 齐次线性方程组的根
void EquationsSolve()
{
    double a, b, c, p, q, x1, x2;
    scanf("%lf %lf %lf", &a, &b, &c);
    p = -b/(2.0*a);
    q = sqrt(b*b-4*a*c)/(2.0*a);
    x1 = p + q;
    x2 = p - q;
    printf("x1 = %7.2lf, x2 = %7.2lf \n", x1, x2);
}

void getcharTest()
{
    char a, b, c;
    a = getchar();
    b = getchar();
    c = getchar();
    putchar(a);
    putchar(b);
    putchar(c);
    putchar('\n');
}

void exercises1()
{
    double sumMoney = 1000.f;
    int years = 5;
    int saveType;
    scanf("%d", &saveType);
    double finalMoney;
    double oneYearsRate = 4.14/100;
    double twoYearsRate = 4.68/100;
    double threeYearsRate = 5.4/100;
    double fiveYearsRate = 5.85/100;
    double aliveYearsRate = 0.72/100;
    switch (saveType)
    {
    case 1:
        finalMoney = sumMoney*(1+5*fiveYearsRate);
        break;
    case 2:
        finalMoney = sumMoney*(1+2*twoYearsRate)*(1+3*threeYearsRate);
        break;
    case 3:
        finalMoney = sumMoney*(1+3*threeYearsRate)*(1+2*twoYearsRate);
        break;
    case 4:
        finalMoney = sumMoney*pow(1+oneYearsRate, years);
        break;
    case 5:
        finalMoney = sumMoney*pow(1+aliveYearsRate/4, years*4);
        break;
    default:
        break;
    }
    printf("Final money: %lf \n", finalMoney);
}

void exercises3()
{
    double d = 300000;
    double p = 6000;
    double r = 1.0/100;
    double m = log(p/(p-d*r))/log(1+r);
    printf("还款 %.1f 个月 \n", m);
}

void exercises4()
{
    int c1, c2;
    c1 = 197;
    c2 = 198;
    printf("c1 = %c, c2 = %c \n", c1, c2);
    printf("c1 = %d, c2 = %d \n", c1, c2);
}

void exercises5()
{
    int c1 = 'C';
    int c2 = 'h';
    int c3 = 'i';
    int c4 = 'n';
    int c5 = 'a';
    c1 += 4;
    c2 += 4;
    c3 += 4;
    c4 += 4;
    c5 += 4;
    putchar(c1);putchar(c2);putchar(c3);putchar(c4);putchar(c5);putchar('\n');
    printf("%c%c%c%c%c \n", c1, c2, c3, c4, c5);
}

void exercises6()
{

}

void exercises7()
{
    int c1,c2;
    c1 = getchar();
    c2 = getchar();
    putchar(c1);putchar(c2);putchar('\n');
    printf("%d%d \n", c1, c2);
}

void exercises8()
{
    int a = 3, b = 4, c = 5;
    if (!(a>b) && (!c || 1)) 
    {
        printf("ohoho");
    }
}
