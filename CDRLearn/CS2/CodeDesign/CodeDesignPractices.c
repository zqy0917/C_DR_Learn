//
//  CodeDesignPractices.c
//  CDRLearn
//
//  Created by Zhaoqianyu on 2019/9/24.
//  Copyright © 2019 Zqy. All rights reserved.
//

#include "CodeDesignPractices.h"
#include <math.h>

#define MaxNum 10000

static void Example8_4(){
    int nums[MaxNum]={0},i,x,count=0;
    for (i=1; i<1000; i++) {
        x = (int)sqrt(i);
        if (x*x == i) {
            nums[count++] = i;
        }
    }
    for (i=0; i<count; i++) {
        printf("%d ", nums[i]);
    }
}

void CodeDesignPracticesMain(int argc, char *argv[]){
    Example8_4();
}
