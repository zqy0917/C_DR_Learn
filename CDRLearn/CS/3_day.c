#include <stdio.h>
#include <string.h>

static int test1(int root)
{
    if (root == 1) {
        return 1;
    }
    return root * test1(root-1);
}

static void move(int stratum, int cIndex, int tIndex);

/*
汉诺塔：堪称递归经典问题，经典！经典！经典！！！！！

stratum: 当前塔层数
cIndex: 当前位置
tIndex: 目标位置
*/
void Hanoi(int stratum, int cIndex, int tIndex)
{
    int tmpIndex;
    if (stratum == 1) {
        move(1, cIndex, tIndex);
        return;
    }else{
        if (cIndex == 0) {
            if (tIndex == 1){
                tmpIndex = 2;
            }else if (tIndex == 2){
                tmpIndex = 1;
            }
        }else if (cIndex == 1) {    
            if (tIndex == 0){
                tmpIndex = 2;
            }else if (tIndex == 2){
                tmpIndex = 0;
            }
            
        }else if (cIndex == 2) {
            if (tIndex == 0){
                tmpIndex = 1;
            }else if (tIndex == 1){
                tmpIndex = 0;
            }
        }
    }
    Hanoi(stratum-1, cIndex, tmpIndex);
    move(stratum, cIndex, tIndex);
    Hanoi(stratum-1, tmpIndex, tIndex);
}
static int a=0;
static void move(int stratum, int cIndex, int tIndex){
    ++a;
    char c,t;
    switch (cIndex)
    {
    case 0:
        c = 'A';
        break;
    case 1:
        c = 'B';
        break;
    case 2:
        c = 'C';
        break;
    default:
        break;
    }
    switch (tIndex)
    {
    case 0:
        t = 'A';
        break;
    case 1:
        t = 'B';
        break;
    case 2:
        t = 'C';
        break;
    default:
        break;
    }
    printf("将第 %d 个盘子从 %c 座移动到 %c 座 \n", stratum, c, t);
}

void sortWithSelect(int array[], int n)
{
    for (int i=0; i<n-1; i++) {
        int a = array[i];
        for (int j=i+1; j<n; j++) {
            if (array[j] > a) {
                a = array[j];
                array[j] = array[i];
                array[i] = a;
            }
        }
    }
}

static int isCharacter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// 输出最长单词
static void test10(char str[])
{
    int len=0,tmp=0,index=0,isWord=0;
    char res[10000];
    for (int i=0; i<strlen(str); i++) {
        char c = str[i];
        if (isCharacter(c)) {
            if (i == strlen(str)-1) {
                ++tmp;
                if (tmp > len) {
                    len = tmp;
                    index = i-len+1;
                }
            }else{
                isWord = 1;
                tmp ++;
            }
        }else if (isWord){
            if (tmp > len) {
                len = tmp;
                index = i-len;
            }
            tmp = 0;
            isWord = 0;
        }
    }
    printf("%d, %d \n", index, len);
    strncpy(res, str+index, len);
    res[len] = '\0';
    printf("%s \n", res);
}

static void test11()
{

}

void sortWithId(int ids[10], char names[10][100]){
    for (int i=0; i<9; i++) {
        for (int j=0; j<9-i; j++){
            if (ids[j] > ids[j+1]) {
                int t = ids[j];
                ids[j] = ids[j+1];
                ids[j+1] = t;
                char str1[100];
                char str2[100];
                strcpy(str1, names[j]);
                strcpy(str2, names[j+1]);
                strcpy(names[j], str2);
                strcpy(names[j+1], str1);
            }
        }
    }
}

void printStaff(int ids[10], char names[10][100]){
    for (int i=0; i<10; i++) {
        printf("员工 Id：%d, 姓名：%s \n", ids[i], names[i]);
    }
}

int findStaff(int ids[10], int left, int right ,int findId)
{
    int mid = (left + right)/2;
    if ((ids[mid] != findId) && (right == left)) {
        return -1;
    }
    if ((ids[mid] == findId) || (right == left)){
        return mid;
    }else{
        if (ids[mid] > findId) {
            return findStaff(ids, left, mid-1, findId);
        }else{
            return findStaff(ids, mid+1, right, findId);
        }
    }
}

static void test15()
{
    int ids[10] = {6, 2, 3, 4, 5, 1, 7, 10, 9, 8};
    char names[10][100] = {"name 6", "name 2", "name 3", "name 4", "name 5", "name 1", "name 7", "name 10", "name 9", "name 8"};
    printStaff(ids, names);
    sortWithId(ids, names);
    printf("***************\n");
    printStaff(ids, names);
    int findIndex = findStaff(ids, 0, 9, 11);
    printf("***************\n");
    if (findIndex >= 0) {
        printf("寻找到的名字：%s \n", names[findIndex]);
    }else{
        printf("没找到 \n");
    }
    
}

static int convertNum(int a){
    static int res = 0;
    if (a < 16) {
        res += a;
        return res;
    }else{
        int b = a%16;
        res += 10*b+convertNum(a/16);
        return res;
    }
}

int main_day3()
{
    // int res = test1(10);
    // printf("阶乘结果： %d \n", res);
    // Hanoi(64, 0, 2);
    // printf("总共移动了：%d 次 \n", a);
    // int a[10] = {1, 4, 22, 3, 45, 2, 12, 34, 10, 1};
    // sortWithSelect(a, 10);
    // for (int i=0; i<10; i++) {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");
    // char a[100] = "asas1212asdffffffa111 kjdjsdbjasbdj  qas 12 as";
    // test10(a);
    // test15();
    int a = convertNum(0x11);
    printf("%d \n", a);
    printf("%d \n", 0x3f % 16);
    return 0;
}
