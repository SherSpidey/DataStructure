//
// Created by 62736 on 2021/6/23.
//
#include "MyStack.h"

//十进制正整数向base的进制转化
void convert(MyStack<char> &S, __int64 n, int base) {
    //定义进制表示符号，最高为16进制
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'F'};
    if (0 < n) {
        S.push(digit[n % base]);
        convert(S, n / base, base);
    }
}

void convert2(MyStack<char> &S, __int64 n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'F'};
    while (0 < n) {
        S.push(digit[n % base]);
        n /= base;
    }
}

void trim(const char exp[], int &lo, int &hi) {
    while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))    //查找第一个和最后一个圆括号，找不到hi将小于lo
        lo++;                                           //后一循环也将跳过
    while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))
        hi--;
}

//存在左右数量匹配但是依旧不合规则的情况，如'())('
//divide不做检测
int divide(const char exp[], int lo, int hi) {
    int mi = lo;
    int crc = 1;        //左括号为1，右括号为-1，进行匹配
    while ((0 < crc) && (++mi < hi)) {           //匹配一段左右数量相同的括号段，crc为0即表示成功匹配，返回
        if (exp[mi] == ')')                      //如果不能匹配，mi会大于hi
            crc--;
        if (exp[mi] == '(')
            crc++;
    }
    return mi;
}


bool paren(const char exp[], int lo, int hi) {
    trim(exp, lo, hi);
    if (lo > hi)
        return true;
    if (exp[lo] != '(')
        return false;
    int mi = divide(exp, lo, hi);
    if (mi > hi)
        return false;
    return paren(exp,lo+1,mi-1)&&paren(exp, mi + 1, hi);
}

bool reParen(const char exp[], int len) {
    MyStack<char> myStack;
    for (int i =0 ; i < len ; i++){
        if (exp[i] == ')'){
            if (myStack.empty())
                return false;
            else
                myStack.pop();
        }
        if (exp[i] == '(')
            myStack.push(exp[i]);
    }
    if(myStack.empty())
        return true;
    return false;
}