#include <stdio.h>


void swip(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void sort(int *a, int *b, int *c)
{
    if (*a > *b) swip(a, b);
    if (*a > *c) swip(a, c);
    if (*b > *c) swip(b, c);
}

void pointArray(){
    int a[10] = {1, 2 ,3 ,4 ,5, 6, 7, 8, 9 ,10};
    for (int i=0; i<10; i++){
        printf("%d, ", *(a+i));
    }
    printf("\n ---------------------------- \n");
    int *p;
    for (p=a; p<a+10; p++){
        printf("%d, ", *p);
    }
    printf("\n ---------------------------- \n");
}

void invArray(int *arr, int n);
void invArray2(int *arr, int n);
void sortArr(int *arr, int n);
void printArr(int *arr, int n);
// *p++ 先取p值在自加1
// *++p p先自加1在取值
void pointArray2(){
    int a[10];
    int *p;
    for (p=a; p<a+10; p++) {
        scanf("%d", p);
    }
    printf("\n ---------------------------- \n");
    printArr(a, 10);

    // invArray2(a, 10);
    // printArr(a, 10);

    sortArr(a, 10);
    printArr(a, 10);
}

void printArr(int *arr, int n)
{
    for (int i=0; i<10; i++){
        printf("%d, ", *arr++);
    }
    printf("\n -------------------------- \n");
}

void invArray(int *arr, int n){
    for (int i=0; i<=(n-1)/2; i++) {
        int t = *(arr+i);
        *(arr+i) = *(arr+n-1-i);
        *(arr+n-1-i) = t;
    }
}

void invArray2(int *arr, int n){
    for (int *i = arr,*j = arr+n-1; i<j; i++,j--) {
        int t = *i;
        *i = *j;
        *j = t;
    }
}

// sort array with point
void sortArr(int *arr, int n)
{
    for (int *i=arr; i<arr+n; i++) {
        for (int *j=i+1; j<arr+n; j++) {
            if (*i < *j) {
                int t = *i;
                *i = *j;
                *j = t;
            }
        }
    }
}

void array2(int (*a)[3], int r, int l){
    printf("%d %p", **a, a);
    printf("\n");
    for (int i=0; i<r; i++) {
        for (int j=0; j<l; j++) {
            printf(" %d %p ", *(*(a+i)+j), (*(a+i)+j));
        }
        printf("\n");
    }
}

// p-a 代表绝对距离
void array3(int *a, int n){
    int *p = a;
    for (int i=0; i<n; i++) {
        printf("%d ", *p++);
        if ((p-a) % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void string1(char *c)
{
    printf("%c %s \n", *c, c);
}

void strCopy(char *from, char *to){
    while (*from != '\0')
    {
        *to++ = *from++;
    }
    *to = '\0';
}

void test21(){
    
}

int main()
{
    // int a=10,b=1,c=18;
    // int *aP = &a;
    // int *bP = &b;
    // int *cP = &c;
    // printf("a=%d, b=%d, c=%d \n", a, b, c);
    // sort(aP, bP, cP);
    // printf("a=%d, b=%d, c=%d \n", a, b, c);
    // pointArray2();
    int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    array2(a, 3, 3);
    // array3(a[0], 9);
    // string1("=daaa");
    // char *a = "Where I am ?";
    // char b[100];
    // char *b = "askdjkajksakj";异常，字符串常量不可变需注意
    // void (*s)(char *, char *) = strCopy;
    // (*s)(a, b);

    // printf("%s \n%s \n", a, b);
    return 0;
}
