#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static float *search(float (*array)[4], int n)
{   
    float *p;
    p = *(array + n);
    return p;
}

static void test2()
{
    float array[][4] = {
        {1.3, 2.4, 2.1, 6.7}, 
        {3.6, 8.4, 5.7, 3.1}, 
        {6.8, 2.4, 4.5, 0.1},
        {4.8, 8.341, 2.2, 4.78},
    };

    float *pt = search(array, 2);
    float *p = pt;
    for (; p<pt+4; p++) {
        printf("%f\t", *p);
    }
    printf("\n");
}

// 冒泡排序
static void strSort(char *strs[], int n){
    char **i;
    char **j;
    for (i=strs; i<strs+n-1; i++) {
        for (j=strs; j<strs+n-1-(i-strs); j++) {
            // 注意：strcmp 比较结果是正负数
            if (strcmp(*j, *(j+1)) > 0) {
                char *t = *j;
                *j = *(j+1);
                *(j+1) = t;
            }
        }
    }
}

// 选择排序
static void strSortSelect(char *strs[], int n){
    char **i;
    char **j;
    for (i=strs; i<strs+n-1; i++) {
        for (j=i+1; j<strs+n; j++) {
            // 注意：strcmp 比较结果是正负数
            if (strcmp(*i, *j) > 0) {
                char *t = *i;
                *i = *j;
                *j = t;
            }
        }
    }
}

static void test3(){
    char *str1 = "Follow me";
    char *str2 = "BASIC";
    char *str3 = "Great Wall";
    char *str4 = "FORTRAN";
    char *str5 = "Computer desgin";
    char *strs[] = {str1, str2, str3, str4, str5};
    strSort(strs, 5);
    // 数组名是数组首元素地址，而此时数组首元素为一个字符串指针(指向字符串首字符的指针)，所以此时数组名为指针的地址。
    // 所以此处应该是二级指针。
    char **p = strs;
    for (; p<strs+5; p++) {
        printf("%s\n", *p);
    }
}

static void check(int *arr, int n){
    int *pt = arr;
    for (; pt<arr+n; pt++) {
        if (*pt < 60) {
            printf("%d ", *pt);
        }
    }
}

static void test4(){
    int *arr = (int *)calloc(5, sizeof(int));
    int *p = arr;
    for (int i=0; i<5; i++) {
        scanf("%d", p++);
    }
    p = arr;
    for (int i=0; i<5; i++) {
        printf("%d ", *p++);
    }
    printf("\n");
    check(arr, 5);
    printf("\n");
    // 注意：谁申请谁释放，必须释放！！！️️️⚠️⚠️⚠️️
    free(arr);
}

// 选择排序
static void sort21(int **arr, int n)
{
    int *i = *arr;
    int *j;
    for (; i<*arr+n; i++) {
        for (j=i+1; j<*arr+n; j++) {
            if (*i > *j) {
                int t = *i;
                *i = *j;
                *j = t;
            }
        }
    }
}

static void printArr(int **arr, int n)
{
    int *first = *arr;
    int *final = (*arr)+n;
    for (; *arr<final; (*arr)++) {
        printf("%d ", **arr);
    }
    printf("\n");
    *arr = first;
}

static void test21(){
    int a[10] = {2, 3, 5, 6, 8, 9, 10, 1, 4, 7};
    int *p = a;
    int **pt = &p;
    printArr(pt, 10);
    sort21(pt, 10);
    printArr(pt, 10);
}

static char * test19New(int n){
    char *a = malloc(n*sizeof(char));
    return a;
}

static void test19Free(char *s){
    free(s);
}

static char *monthStr(int month){
    char *str1 = "一月";
    char *str2 = "二月";
    char *str3 = "三月";
    char *str4 = "四月";
    char *str5 = "五月";
    char *str6 = "六月";
    char *str7 = "七月";
    char *str8 = "八月";
    char *str9 = "九月";
    char *str10 = "十月";
    char *str11 = "十一月";
    char *str12 = "十二月";
    char **strs[] = {&str1, &str2, &str3, &str4, &str5, &str6, &str7, &str8, &str9, &str10, &str11, &str12};
    char *res = **(strs+month-1);
    return res;
}

static void test18(){
    int month;
    while (scanf("%d", &month))
    {
        char *s = monthStr(month);
        printf("%s\n", s);
    }
}

static int test17Strcmp(char *p1, char *p2){
    char *c = p1;
    char *d = p2;
    int res = 0;
    while (*c != '\0' && *d != '\0')
    {
        if (*c != *d) {
            res = *c-*d;
            break;
        }
        c++;
        d++;
    }
    if (res == 0) {
        if (*c!='\0') res = *c;
        else if (*d!='\0') res = -*d;
    }
    return res;
}

int main_day6(int argc,char *argv[])
{
    while (--argc > 0)
    {
        printf("%s%c", *++argv, argc <= 1 ? '\n' : ' ');
    }
    
    // test2();
    // test3();
    // test4();
    // test21();
    // char *aaa = test19New(5);
    // for (int i=0; i<9; i++) {
    //     printf("%p\t", aaa+i);
    // }
    // printf("\n");
    // test19Free(aaa);
    // for (int i=0; i<5; i++) {
    //     printf("%p\t", aaa+i);
    // }
    // printf("\n");
    // test18();
    char *a = "abcdAa";
    char *b = "abcdAaAD";
    int c = test17Strcmp(a, b);
    printf("%d\n", c);

    return 0;
}
