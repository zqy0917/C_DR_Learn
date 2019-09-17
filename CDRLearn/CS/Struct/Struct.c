//
//  Day4.c
//  StudyDay1
//
//  Created by Zqy on 19/6/8.
//  Copyright © 2019年 Zqy. All rights reserved.
//

#include "Struct.h"
#include <stdlib.h>

struct Student {
    int num;
    char *name;
    int age;
    char *addr;
}a = {1, "Zqy", 24, "霍营"};

struct Person {
//    char *name;
    double count;
    double count2;
    int count3;
    int count4;
    int count5;
};


struct Student2 {
    int num;
    char name[20];
    float score[3];
    float aver;
};

struct Student3 {
    int num;
    float score;
    struct Student3 *next;
};

struct Student4 {
    int num;
    char name[20];
    int gender;
    int age;
    struct Student4 *next;
};

#define N 3
void inputStu(struct Student2 *pt, int n){
    struct Student2 *tPt = pt;
    for ( ;tPt<pt+n; tPt++) {
        scanf("%d %s %f %f %f", &tPt->num, tPt->name, tPt->score, &tPt->score[1], &tPt->score[2]);
        float aver = (tPt->score[0] + tPt->score[1] + tPt->score[2])/3;
        tPt->aver = aver;
    }
}

void output(struct Student2 *p, int n){
    struct Student2 *pt = p;
    for (; pt<p+n; pt++){
        printf("学号：%-5d, 姓名：%-5s, 平均分：%-5f \n", pt->num, pt->name, pt->aver);
    }
}

struct Student3 *createLine2(){
    struct Student3 *s = malloc(sizeof(struct Student3));
    scanf("%d %f", &s->num, &s->score);
    s->next = NULL;
    struct Student3 *head = s;
    struct Student3 *p = s;
    while (1) {
        struct Student3 *s = malloc(sizeof(struct Student3));
        scanf("%d %f", &s->num, &s->score);
        s->next = NULL;
        if (s->num == 0) {
            free(s);
            break;
        }
        p->next = s;
        p = s;
    }
    return head;
}

void createLine(int n){
    struct Student3 *head = NULL;
    struct Student3 *p = NULL;
    for (int i=0; i<n; i++) {
        struct Student3 *s = malloc(sizeof(struct Student3));
        s->num = i+1;s->score = i+1;s->next = NULL;
        if (i == 0) {
            head = s;
        }else{
            p->next = s;
        }
        p = s;
    }
    p = head;
    do {
        printf("Num: %d, score: %f \n", p->num, p->score);
        p = p->next;
    } while (p != NULL);
}

void printS(struct Student3 *head){
    while (head != NULL) {
        printf("num: %-5d, score: %-5f \n", head->num, head->score);
        head = head->next;
    }
}

void printS1(struct Student4 *head){
    while (head != NULL) {
        printf("num: %-5d, name: %-5s, gender: %-5d, age: %-5d \n", head->num, head->name, head->gender, head->age);
        head = head->next;
    }
}

struct Student3 * insertS(struct Student3 *head, int index, struct Student3 *node){
    if (index == 0) {
        node->next = head;
        return node;
    }
    int n=1;
    struct Student3 *p = head->next;
    struct Student3 *lastP = head;
    do {
        if (n == index) {
            lastP->next = node;
            node->next = p;
            break;
        }
        lastP = p;
        p = p->next;
        n++;
    } while (p != NULL);
    return head;
}

struct Student3 * delS(struct Student3 *head, int index){
    if (index == 0) {
        struct Student3 *h = head->next;
        free(head);
        return h;
    }
    int n=1;
    struct Student3 *p = head->next;
    struct Student3 *lastP = head;
    do {
        if (n == index) {
            lastP->next = p->next;
            free(p);
            break;
        }
        lastP = p;
        p = p->next;
        n++;
    } while (p != NULL);
    return head;
}

void destoryS(struct Student3 *pt){
    while (pt != NULL) {
        free(pt);
        pt = pt->next;
    }
}

// 选择排序法给链表排序
static struct Student3 *sort(struct Student3 *head){
    struct Student3 *pi = head;
    struct Student3 *piLast = NULL;
    struct Student3 *pj = head;
    struct Student3 *pjLast = NULL;
    while (pi->next != NULL) {
        pj = pi->next;
        pjLast = pi;
        while (pj != NULL) {
            if (pi->num > pj->num) {
                int t = pi->num;
                float s = pi->score;
                pi->num = pj->num;
                pj->num = t;
                pi->score = pj->score;
                pj->score = s;
            }
            pjLast = pj;
            pj = pj->next;
        }
        piLast = pi;
        pi = pi->next;
    }
    return head;
}

static void text10(){
    printf("输入链表 a\n");
    struct Student3 *a = createLine2();
    printf("输入链表 b\n");
    struct Student3 *b = createLine2();
    printf("a 初始状态：－－－－－－－－\n");
    printS(a);
    printf("b 初始状态：－－－－－－－－\n");
    printS(b);
    printf("a 和 b 合并后初始状态：－－－－－－－－\n");
    struct Student3 *p = a;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = b;
    printS(a);
    printf("排序后：－－－－－－－－\n");
    sort(a);
    printS(a);
    destoryS(a);
}

static struct Student3 *rmSame(struct Student3 *aHead, struct Student3 *bHead){
    struct Student3 *pi = aHead;
    struct Student3 *piLast = NULL;
    struct Student3 *pj = NULL;
    while (pi != NULL) {
        pj = bHead;
        int change = 0;
        while (pj != NULL) {
            if (pi->num == pj->num) {
                change=1;
                if (piLast == NULL) {
                    aHead = pi->next;
                    free(pi);
                    pi = aHead;
                }else{
                    struct Student3 *t = pi;
                    piLast->next = pi->next;
                    pi = pi->next;
                    free(t);
                }
                break;
            }
            pj = pj->next;
        }
        if (pi == NULL) {
            break;
        }else if (!change) {
            piLast = pi;
            pi = pi->next;
        }
    }
    return aHead;
}

static void text11(){
    printf("输入链表 a\n");
    struct Student3 *a = createLine2();
    printf("输入链表 b\n");
    struct Student3 *b = createLine2();
    printf("a 初始状态：－－－－－－－－\n");
    printS(a);
    printf("b 初始状态：－－－－－－－－\n");
    printS(b);
    printf("筛选后：－－－－－－－－\n");
    a = rmSame(a, b);
    printS(a);
    destoryS(a);
    destoryS(b);
}



struct Student4 *create(){
    struct Student4 *head = malloc(sizeof(struct Student4));
    head->next = NULL;
    scanf("%d %s %d %d", &head->num, head->name, &head->gender, &head->age);
    struct Student4 *p = head;
    while (1) {
        struct Student4 *node = malloc(sizeof(struct Student4));
        node->next = NULL;
        scanf("%d %s %d %d", &node->num, node->name, &node->gender, &node->age);
        if (node->num == 0) {
            free(node);
            break;
        }
        p->next = node;
        p = node;
    }
    
    return head;
}

struct Student4 *delSameAge(struct Student4 *head, int delAge){
    struct Student4*p = head;
    struct Student4*lastP = NULL;
    while (p != NULL) {
        if (p->age == delAge) {
            struct Student4*t = p;
            if (lastP == NULL) {
                head = p = p->next;
            }else{
                lastP->next = p->next;
                p = lastP->next;
            }
            free(t);
            continue;
        }
        lastP = p;
        p = p->next;
    }
    return head;
}

static void test12(){
    printf("输入一串链表 0 结尾\n");
    struct Student4 *head = create();
    printf("初始状态：－－－－－－－－\n");
    printS1(head);
    printf("输入要删除的年龄：－－－－－－－－\n");
    int n;
    scanf("%d", &n);
    head = delSameAge(head, n);
    printf("删除后：－－－－－－－－\n");
    printS1(head);
    
}

#include <string.h>
/*
 
s=“This is C programming text”，t=“This is a text for C programming”，则函数返回“programming”
 */
char *maxword(char *s, char *t){
    
    char *maxWordBeginIndex = NULL; /* 最长公共单词起始位置，用于最后输出 */
    int maxWordLen = 0; /* 最长公共单词长度 */
    
    // 遍历 s 时用于记录单词的迭代变量
    int sIsWord = 0;
    char *sub = NULL;
    int subLen = 0;
    for (int i=0; i<=strlen(s); i++) {
        // 遍历取出 s 中每个单词
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            if (!sIsWord) {
                sub = s+i;
            }
            subLen ++;
            sIsWord = 1;
        }else if (sIsWord) {
            s[i] = '\0';
            // 遍历 t 若果找到相同单词且 subLen > maxWordLen 则记录到 maxWordBeginIndex 和 maxWordLen 中
            // 遍历 t 时用于记录单词的迭代变量
            int tISWord = 0;
            char *tSub = NULL;
            int tSubLen = 0;
            for (int j=0; j<=strlen(t); j++) {
                if ((t[j] >= 'a' && t[j] <= 'z') || (t[j] >= 'A' && t[j] <= 'Z')) {
                    if (!tISWord) {
                        tSub = t+j;
                    }
                    tSubLen ++;
                    tISWord = 1;
                }else if (tISWord) {
                    t[j] = '\0';
                    if ((strcmp(sub, tSub) == 0) && subLen > maxWordLen) {
                        maxWordLen = subLen;
                        maxWordBeginIndex = sub;
                        t[j] = ' ';
                        break;
                    }
                    t[j] = ' ';
                    tISWord = 0;
                    tSub = NULL;
                    tSubLen = 0;
                }
            }
            
            s[i] = ' ';
            sIsWord = 0;
            sub = NULL;
            subLen = 0;
        }
    }
    if (maxWordBeginIndex != NULL && maxWordLen > 0) {
        *(maxWordBeginIndex+maxWordLen) = '\0';
    }
    return maxWordBeginIndex;
}

void EntranceDay4(){
    
    printf("Hello Day4, today study Struct! \n");

//    printf("%d\n%s\n%d\n%s\n", a.num, a.name, a.age, a.addr);
//    printf("%p \n", &a);
//    printf("%p \n", &a.num);
    
//    for (int i=0; i<2; i++) {
//        printf("%s, %d \n", leader[i].name, leader[i].count);
//    }
//    struct Person persons[] = {{1, 1}, {2, 2}, {3, 3}};
//    struct Person* pt = persons;
//    for (; pt<persons+3; pt++) {
//        printf("%p \n", pt);
//        printf("name: %-5s, count: %-5d \n", pt->count2, pt->count);
//    }
    
//    struct Student2 students[N];
//    inputStu(students, N);
//    output(students, N);
//    createLine(4);
//    struct Student3 *pt = createLine2();
//    printf("初始状态：－－－－－－－－\n");
//    printS(pt);
//    printf("删除索引 1 之后：－－－－－－－－\n");
//    struct Student3 *h = delS(pt, 1);
//    printS(h);
//    printf("索引 2 处加数据之后之后：－－－－－－－－\n");
//    struct Student3 *s = malloc(sizeof(struct Student3));
//    s->num = 999;
//    s->score = 9999.f;
//    s->next = NULL;
//    h = insertS(h, 2, s);
//    printS(h);
//    destoryS(h);
//    text10();
//    text11();
//    test12();
    char s[100] = "This is prrogrammingprogramminga 11 prrogrammingprogramming programming text";
    char t[100] = "This is a text for prrogrammingprogramminga 11 prrogrammingprogramming programming ";
    char *res = maxword(s, t);
    printf("结果： %s \n", res);
    
}



