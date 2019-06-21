#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char * String;

enum Color{
    red,
    yellow,
    blue,
    white,
    black,
};

typedef struct
{
    int num;
    char name[20];
    char sex;
    char job;
    union
    {
        int class;
        char position[10];
    }category;
    
}person[2];

char *printSingle(enum Color  a) {
    char *c = "";
    switch (a)
    {
    case red:
        c = "红";
        break;
    case yellow:
        c = "黄";
        break;
    case blue:
        c = "蓝";
        break;
    case white:
        c = "白";
        break;
    case black:
        c = "黑";
        break;
    default:
        break;
    }
    return c;
}

void printRes(enum Color  a, enum Color  b, enum Color  c) {
    printf("%s %s %s \n", printSingle(a), printSingle(b), printSingle(c));
}

/* 13个人围成一圈 从第一个人开始报号 1，2，3.凡报到3退出圈子。
找到最后留在圈子的人原来的序号,循环链表实现*/
struct Person
{
    int num;
    struct Person *next;
};

void printPersons(struct Person *head){
    struct Person *h = head;
    do
    {
        printf("第 %d 个人 \n", h->num);
        h = h->next;
    } while (h->next != head->next);
}

struct Person *createPersons(int n){
    struct Person *head = NULL;
    struct Person *tmp = NULL;
    for (int i=1; i<=n; i++) {
        struct Person *p = malloc(sizeof(struct Person));
        p->num = i;
        p->next = NULL;
        if (i == 1) {
            head = p;
        }else{
            tmp->next = p;
        }
        tmp = p;
    }
    // 链表尾节点应指向头节点
    tmp->next = head;
    // 返回尾节点
    return tmp;
}


#define N 3
#define Count 10
void test6(){
    struct Person*endNode = createPersons(Count);
    // printPersons(endNode->next);
    struct Person *p = endNode->next;
    struct Person *pLast = endNode;
    int n = 1;
    while (p->next != p)
    {
        if (n == N) {
            struct Person *t = p;
            pLast->next = p->next;
            p = p->next;
            free(t);
            n = 1;
        }else{
            pLast = p;
            p = p->next;
            n++;
        }
    }
    printf("链表最后剩下的人：%d \n", p->num);
}

// 牛批！牛批！牛批！
void test6Legend(){
    int n, s = 0; 
    for (int i = 2; i <= Count; ++i) {
        s = (s+N)%i; 
    }
    printf("Legend 最后剩下的人：%d \n", s+1);
}

void fetchBall(){
    int n = 0;
    for (enum Color i=red; i<=black; i++) {
        for(enum Color j=red; j<=black; j++) {
            if (i != j) {
                for(enum Color k=red; k<=black; k++) {
                    if (k!=i && k!=j) {
                        n+=1;
                        printRes(i, j, k);
                    }
                }
            }
        }
    }
    printf("一共 %d 种输入法 \n", n);
}

void FileTest(){
    FILE *fp;
    if ((fp=fopen("file1.dat", "w+"))==NULL) {
        printf("Open file error \n");
        exit(0);// 终止程序
    }
    char ch = getchar();
    while (ch != '#')
    {
        fputc(ch, fp);
        putchar(ch);
        ch = getchar();
    }
    fclose(fp);
    putchar(10);
}

void FileTest2(){
    FILE *in,*out;
    if ((in = fopen("file1.dat","r"))==NULL){
        printf("Open file error \n");
        exit(0);// 终止程序
    }
    if ((out = fopen("file2.dat","w"))==NULL){
        printf("Open file error \n");
        exit(0);// 终止程序
    }
    char ch;
    while((ch = fgetc(in))!=-1) {
        fputc(ch,out);
        putchar(ch);
    }
    putchar(10);
    fclose(in);
    fclose(out);
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

void FileTest3(){
    char strs[5][10];
    char *strsPt[10];
    char ch[10];
    for (int i=0; i<5; i++) {
        scanf("%s", strs[i]);
    }
    for (int i=0; i<5; i++) {
        *(strsPt+i) = strs[i];
    }
    printf("排序后: \n");
    char **pt = strsPt;
    strSortSelect(pt, 5);
    pt = strsPt;
    for (; pt<strsPt+5; pt++) {
        printf("%s\n", *pt);
    }
    printf("开始写文件: \n");
    FILE *out;
    if ((out = fopen("string.dat","w"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    pt = strsPt;
    for (; pt<strsPt+5; pt++) {
        fputs(*pt, out);
        fputs("\n", out);
    }
    printf("写入成功 \n");
    fclose(out);
}

void readFile(){
    FILE *fp;
    if ((fp = fopen("string.dat","r"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    char strs[5][10];
    int i=0;
    while(fgets(strs[i],10,fp)!=NULL){
        i++;
    }
    for (i=0; i<5; i++) {
        printf("%s", strs[i]);
    }
}

typedef struct{
    int num;
    char name[20];
    int age;
    char addr[20];
}Student;

typedef struct{
    int num;
    char name[20];
    float grade1;
    float grade2;
    float grade3;
    float aver;
}Student2;

#define COUNT 5

void save(Student stus[], int n){
    FILE *fp;
    if ((fp = fopen("struct.txt","wb")) == NULL) {
        printf("打开文件失败 \n");
    }
    for (int i=0; i<n; i++) {
        if (fwrite(&stus[i], sizeof(Student), 1, fp) != 1) {
            printf("write error \n");
        }
    }
    fclose(fp);
}

void printStudent(Student stus[], int n){
    for (int i=0; i<n; i++) {
        printf("%d, %s, %d, %s \n", stus[i].num, stus[i].name, stus[i].age, stus[i].addr);
    }
}

void readData(){
    Student stus[COUNT];
    FILE *fp;
    if ((fp = fopen("struct.txt","rb"))==NULL) {
        printf("打开文件失败 \n");
    }
    for (int i=0; i<COUNT; i++) {
        fread(&stus[i], sizeof(Student), 1, fp);
    }
    fclose(fp);
    printStudent(stus, COUNT);
}

void eg1(){
    Student stus[COUNT];
    for (int i=0; i<COUNT; i++) {
        scanf("%d %s %d %s", &stus[i].num, stus[i].name, &stus[i].age, stus[i].addr);
    }
    save(stus, COUNT);
}

void rewindTest(){
    FILE *fp;
    FILE *fpout;
    if ((fp = fopen("file2.dat", "rb")) == NULL) {
        printf("打开文件失败 \n");
    }
    if ((fpout = fopen("string.dat", "wb")) == NULL) {
        printf("打开文件失败 \n");
    }
    char ch;
    while((ch = fgetc(fp)) != -1)
    {
        putchar(ch);
    }
    printf("\n");
    rewind(fp);
    while((ch = fgetc(fp)) != -1)
    {
        fputc(ch, fpout);
    }
    fclose(fp);
    fclose(fpout);
}

#define SUM 10 
void createStus(){
    Student stus[SUM];
    for (int i=0; i<SUM; i++) {
        scanf("%d %s %d %s", &stus[i].num, stus[i].name, &stus[i].age, stus[i].addr);
    }
    save(stus, SUM);
}

void randomRead(){
    FILE *fp;
    if ((fp = fopen("struct.txt", "rb")) == NULL) {
        printf("打开文件失败 \n");
    }
    int t = 1;
    Student stus[SUM];
    for (int i=0; i<SUM; i++, t++) {
        if (t%2 == 0) {
            fseek(fp, sizeof(Student), SEEK_CUR);
        }else
        {
            fread(&stus[i], sizeof(Student), 1, fp);
            printf("%d, %s, %d, %s \n", stus[i].num, stus[i].name, stus[i].age, stus[i].addr);
        }
    }
    fclose(fp);
}

void practice1()
{
    char str[100];
    char *p = str;
    char c;
    while ((c = getchar())>0)
    {
        if (c>='a' && c<='z') {
            c-='a'-'A';
        }
        *p++ = c;
        if (c=='!') {
            *p = '\0';
            break;
        }
    }
    FILE *fp;
    if ((fp = fopen("test", "w"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fputs(str, fp);
    fclose(fp);
}

void sortStr(char str[], int n){
    char *i = str;
    char *j;
    for (; i<str+n-1; i++) {
        for (j=i+1; j<str+n; j++) {
            if (*i>*j) {
                char t = *i;
                *i = *j;
                *j = t;
            }
        }
    }
}

void practice2(){
    FILE *fp;
    if ((fp = fopen("test1", "r")) == NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp);
    char strs[100];
    rewind(fp);
    fgets(strs, n+1, fp);
    fclose(fp);

    if ((fp = fopen("test2", "r")) == NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int m = ftell(fp);
    rewind(fp);
    fgets(strs+n, m+1, fp);
    fclose(fp);

    // 开始排序
    sortStr(strs, m+n);
    if ((fp = fopen("test3", "w")) == NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fputs(strs, fp);
    fclose(fp);
}

void saveStu2(Student2 stus[], int n, char *fileName){
    FILE *fp;
    if ((fp = fopen(fileName,"w")) == NULL) {
        printf("打开文件出错  \n");
        exit(0);
    }
    float aver = 0.f;
    char *t;
    for (int i=0; i<5; i++) {
        aver = (stus[i].grade1+stus[i].grade2+stus[i].grade3)/3;
        fprintf(fp, "%d %s %f %f %f %f \n", stus[i].num, stus[i].name, stus[i].grade1, stus[i].grade2, stus[i].grade3, aver);
    }
    fclose(fp);
}

void practice5(){
    FILE *fp;
    if ((fp = fopen("test5","w")) == NULL) {
        printf("打开文件出错  \n");
        exit(0);
    }
    Student2 stus[5];
    float aver = 0.f;
    char *t;
    for (int i=0; i<5; i++) {
        scanf("%d %s %f %f %f", &stus[i].num, stus[i].name, &stus[i].grade1, &stus[i].grade2, &stus[i].grade3);
        aver = (stus[i].grade1+stus[i].grade2+stus[i].grade3)/3;
        fprintf(fp, "%d %s %f %f %f %f \n", stus[i].num, stus[i].name, stus[i].grade1, stus[i].grade2, stus[i].grade3, aver);
    }
    fclose(fp);
}

void printStudent2(Student2 stus[], int n){
    for (int i=0; i<n; i++) {
        printf("%d, %s, %f, %f, %f \n", stus[i].num, stus[i].name, stus[i].grade1, stus[i].grade2, stus[i].grade3);
    }
}

void practice6(){
    FILE *fp;
    if ((fp = fopen("test5","r"))==NULL) {
        printf("打开文件出错 \n");
        exit(0);
    }
    Student2 stus[5];
    float avers[5];
    for (int i=0; i<5; i++) {
        fscanf(fp, "%d %s %f %f %f %f", &stus[i].num, stus[i].name, &stus[i].grade1, &stus[i].grade2, &stus[i].grade3, &avers[i]);
    }
    printStudent2(stus, 5);
    printf("\n");
    for (int i=0; i<5-1; i++) {
        for (int j=0; j<5-i-1; j++) {
            if (avers[j]>avers[j+1]) {
                Student2 s = stus[j];
                float aver = avers[j];
                stus[j] = stus[j+1];
                stus[j+1] = s;
                avers[j] = avers[j+1];
                avers[j+1] = aver;
            }
        }
    }
    printf("sort: \n");
    printStudent2(stus, 5);
    saveStu2(stus, 5, "stu_sort");
}

void practice8Input(){
    FILE *fp;
    if ((fp = fopen("test6","w")) == NULL) {
        printf("打开文件出错  \n");
        exit(0);
    }
    Student2 stus[5];
    float aver = 0.f;
    char *t;
    for (int i=0; i<5; i++) {
        scanf("%d %s %f %f %f", &stus[i].num, stus[i].name, &stus[i].grade1, &stus[i].grade2, &stus[i].grade3);
        aver = (stus[i].grade1+stus[i].grade2+stus[i].grade3)/3;
        stus[i].aver = aver;
        fwrite(&stus[i], sizeof(Student2), 1, fp);
    }
    fclose(fp);
}

void practice8output(){
    FILE *fp;
    if ((fp = fopen("test6","r")) == NULL) {
        printf("打开文件出错  \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int it = ftell(fp);
    Student2 stus[it/sizeof(Student2)+2];
    rewind(fp);
    int i=0;
    while (fread(&stus[i], sizeof(Student2), 1, fp) == 1)
    {
        printf("学号 ：%d, 名字: %s, 平均分：%f \n", stus[i].num, stus[i].name, stus[i].aver);
        i++;
    }
    fclose(fp);
}

void practice8(){
    Student2 stu;
    printf("请输入新成员信息 \n");
    scanf("%d %s %f %f %f", &stu.num, stu.name, &stu.grade1, &stu.grade2, &stu.grade3);
    float average = (stu.grade1 + stu.grade2 + stu.grade3)/3;
    stu.aver = average;
    FILE *fp;
    if ((fp = fopen("test6","rb+")) == NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int it = ftell(fp);
    Student2 stus[it/sizeof(Student2)+2];
    int i=0,n=0;
    rewind(fp);
    while (fread(&stus[i], sizeof(Student2), 1, fp) == 1)
    {
        if (average > stus[i].aver) {
            n = i;
        }
        i++;
    }
    if (n!=0) ++n;
    fseek(fp, sizeof(Student2)*n, SEEK_SET);
    if (fwrite(&stu, sizeof(Student2), 1, fp) != 1){
        printf("write error ! \n");
        exit(0);
    }
    for (int j=n; j<i; j++) {
        if (fwrite(&stus[j], sizeof(Student2), 1, fp) != 1){
            printf("write error ! \n");
            exit(0);
        }
    }
    fclose(fp);
    practice8output();
}

typedef struct{
    char name[20];
    int num;
    int gender;
    int age;
    char addr[20];
    float wage;
    int health;
    int literacy;
}Employee;

typedef struct{
    char name[20];
    float wage;
}EmployeeWage;

void inputEmployee(){
    FILE *fp;
    if ((fp = fopen("test9", "w"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    Employee employes[10];
    for (int i=0; i<10; i++) {
        scanf("%s %d %d %d %s %f %d %d", 
        employes[i].name, &employes[i].num, &employes[i].gender, 
        &employes[i].age, employes[i].addr, &employes[i].wage, 
        &employes[i].health, &employes[i].literacy);
        fwrite(&employes[i], sizeof(Employee), 1, fp);
    }
    fclose(fp);
}

void outputEmployee(){
    FILE *fp;
    if ((fp = fopen("test9", "r"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int it = ftell(fp)/sizeof(Employee);
    rewind(fp);
    Employee employes[it];
    int i=0;
    while (fread(&employes[i], sizeof(Employee), 1, fp) == 1) {
        printf("姓名：%s, 工号：%d, 性别：%d, 年龄：%d, 住址：%s, 薪水：%f, 健康：%d, 文化程度：%d \n", 
        employes[i].name, employes[i].num, employes[i].gender, 
        employes[i].age, employes[i].addr, employes[i].wage, 
        employes[i].health, employes[i].literacy );
        i++;
    }
    fclose(fp);
}

void fetchWage(){
    FILE *fp1;
    if ((fp1 = fopen("test9Wage", "w"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    FILE *fp2;
    if ((fp2 = fopen("test9", "r"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp2, 0, SEEK_END);
    int it = ftell(fp2)/sizeof(Employee);
    rewind(fp2);
    Employee employes[it];
    int i=0;
    EmployeeWage employeWages;
    while (fread(&employes[i], sizeof(Employee), 1, fp2) == 1) {
        strcpy(employeWages.name, employes[i].name);
        employeWages.wage = employes[i].wage;
        fwrite(&employeWages, sizeof(EmployeeWage), 1, fp1);
        i++;
    }
    fclose(fp1);
    fclose(fp2);
}

void outputWage(){
    FILE *fp;
    if ((fp = fopen("test9Wage", "r"))==NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int it = ftell(fp)/sizeof(EmployeeWage);
    rewind(fp);
    EmployeeWage employeWages[it];
    int i=0;
    while (fread(&employeWages[i], sizeof(EmployeeWage), 1, fp) == 1) {
        printf("姓名：%s, 薪水：%f \n", employeWages[i].name, employeWages[i].wage);
        i++;
    }
    fclose(fp);
}

void delWage(int n){
    FILE *fp;
    if ((fp = fopen("test9Wage", "r")) == NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int it = ftell(fp)/sizeof(EmployeeWage);
    if (n <= 0 || n > it) {
        printf("参数异常\n");
        return;
    }
    rewind(fp);
    EmployeeWage employees[it];
    int j=0;
    for (int i=0; i<it; i++) {
        if (i == n-1) {
            fseek(fp, sizeof(EmployeeWage), SEEK_CUR);
        }else{
            fread(&employees[j], sizeof(EmployeeWage), 1, fp);
            j++;
        }  
    }
    fclose(fp);
    if ((fp = fopen("test9Wage", "w")) == NULL) {
        printf("打开文件失败 \n");
        exit(0);
    }
    for (int i=0; i<it-1; i++) {
        if (fwrite(&employees[i], sizeof(EmployeeWage), 1, fp) != 1) {
            printf("写入数据失败 \n");
            exit(0);
        }
    }
    fclose(fp);
}

void practice9(){
    // inputEmployee();
    // outputEmployee();
    // fetchWage();
    // outputWage();
    delWage(6);
    outputWage();
}

void inputWords(){
    char strs[10][100];
    for (int i=0; i<10; i++) {
        scanf("%s", strs[i]);
    }
    FILE *fp;
    if ((fp = fopen("test10","w")) == NULL) {
        printf("打开文件错误 \n");
        exit(0);
    }
    for (int i=0; i<10; i++) {
        fputs(*(strs+i), fp);
        if (i != 9) fputs("\n", fp);
    }
    fclose(fp);
}

void practice10(){
    inputWords();
    FILE *fp;
    if ((fp = fopen("test10","r")) == NULL) {
        printf("打开文件错误 \n");
        exit(0);
    }
    printf("\n");
    char tmp[100];
    char *t = NULL;
    while(fgets(tmp, 100, fp)){
        t = tmp;
        while(*t != '\0'){
            *t = toupper(*t);
            t++;
        }
        printf("%s", tmp);
    }
    printf("\n");
}


int main(int argc, String argv[]){
    while (--argc > 0)
    {
        printf("%s%c", *++argv, argc <= 1 ? '\n' : ' ');
    }

    // scanf("%d %s", &person[0].category.class, person[1].category.position);

    // printf("%d \n", person[0].category.class);
    // printf("%s \n", person[1].category.position);
    // fetchBall();
    // test6();
    // test6Legend();
    // FileTest();
    // FileTest2();
    // FileTest3();
    // readFile();
    // eg1();
    // readData();
    // rewindTest();
    // createStus();
    // randomRead();
    // practice1();
    // practice6();
    // practice8Input();
    // practice9();
    // practice10();

    return 0;
}