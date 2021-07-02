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
    while ((0 < crc) && (++mi <= hi)) {           //匹配一段左右数量相同的括号段，crc为0即表示成功匹配，返回
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

bool paren_2(const char exp[], int lo, int hi){
    MyStack<char> S;        //使用栈记录已发现但未匹配的括号
    for(int i=lo; i<= hi;i++)
        switch (exp[i]) {
            case '(':
            case '[':
            case '{':
                S.push(exp[i]);
                break;
            case ')':
                if (S.empty()||'('!=S.pop())
                    return false;
                break;
            case ']':
                if (S.empty()||'['!=S.pop())
                    return false;
                break;
            case '}':
                if (S.empty()||'{'!=S.pop())
                    return false;
                break;
            default:
                break;
        }
    return S.empty();
}

bool reParen(const char exp[], int len) {
    MyStack<char> myStack;
    for (int i =0 ; i < len ; i++){
        if (exp[i] == ')'){             //当前括号为')'且不为空，出栈
            if (myStack.empty())
                return false;
            else
                myStack.pop();
        }
        if (exp[i] == '(')
            myStack.push(exp[i]);       //左括号，入栈
    }
    if(myStack.empty())
        return true;
    return false;
}

void placeQueen(int N, MyStack<int>& cord){
    MyStack<Queen> solu;
    Queen q (0,0);  //初始坐标为原点
    do{
        if(N<=q.x){         //当前遍历超出棋盘
            q=solu.pop();   //上一点不符合要求，出栈
            cord.pop();     //坐标x出栈
            cord.pop();     //坐标y出栈
            q.x++;
        }
        //重载的==可以体现在find函数中
        if((q.x<N)&&(solu.empty()||solu.find(q)<0)){    //前提条件，在棋盘上才能入栈，然后是没有落子可以随意入栈，有子则需要判断冲突
            solu.push(q);
            cord.push(q.x);
            cord.push(q.y);
            Queen temp(0,q.y+1);                //创建下一颗棋子，位于当前棋子的下一支路
            q=temp;
        }else
            q.x++;                      //遍历当前支路的下一坐标
    } while (solu.size()<N);
}










