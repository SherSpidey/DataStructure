//
// Created by 62736 on 2021/6/23.
//

#ifndef DATASTRUCTURE_C4_H
#define DATASTRUCTURE_C4_H

#endif //DATASTRUCTURE_C4_H

#include "iostream"
#include "MyStack.h"
#include "MyQueue.h"

using namespace std;

void convert(MyStack<char> &S, __int64 n, int base);

void convert2(MyStack<char> &S, __int64 n, int base);

bool paren(const char exp[], int lo, int hi);

bool reParen(const char exp[], int len);

bool paren_2(const char exp[], int lo, int hi);

void placeQueen(int N, MyStack<int> &cord);

class List_visit {

public:
    template<typename T>
    void operator()(T e) {
        cout << e << ' ';
    }

    void operator()() {
        cout << endl;
    }

};
