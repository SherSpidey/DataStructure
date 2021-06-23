//
// Created by 62736 on 2021/6/23.
//

#ifndef DATASTRUCTURE_C4_H
#define DATASTRUCTURE_C4_H

#endif //DATASTRUCTURE_C4_H

#include "iostream"
#include "MyStack.h"

using namespace std;

void convert(MyStack<char> & S, __int64 n, int base);
void convert2(MyStack<char> & S, __int64 n, int base);

class List_visit{

public:
    template <typename T>
    void operator() (T e){
        cout<<e<<' ';
    }

    void operator() (){
        cout<<endl;
    }

};