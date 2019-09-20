//
//  PointPractice.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/20.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "PointPractice.h"
#include <ctype.h>
#include <string.h>

#define MaxNum 1000

static void CovertStr(char *s, char *t){
    char *sub,*first,*last,c;
    if ((sub = strstr(s, t)) == NULL) {
        printf("%s\n", s);
        return;
    }
    first = sub;
    last = sub+strlen(t)-1;
    while (first < last) {
        c = *first;
        *first = *last;
        *last = c;
        first++;
        last--;
    }
}

static void SubStrCovert(){
    char s[MaxNum],t[MaxNum];
    scanf("%s %s", s ,t);
    CovertStr(s, t);
    puts(s);
}

void PointerPracticeMain(int argc, char *argv[]){
    SubStrCovert();
}
