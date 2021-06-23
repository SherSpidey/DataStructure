//
// Created by 62736 on 2021/6/23.
//
#include "MyStack.h"

//十进制正整数向base的进制转化
void convert(MyStack<char> & S, __int64 n, int base){
    //定义进制表示符号，最高为16进制
    static char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','F'};
    if(0 < n){
        S.push(digit[n%base]);
        convert(S,n/base, base);
    }
}

void convert2(MyStack<char> & S, __int64 n, int base){
    static char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','F'};
    while(0 < n){
        S.push(digit[n%base]);
        n /= base;
    }
}