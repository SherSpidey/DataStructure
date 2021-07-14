//
// Created by 62736 on 2021/7/5.
//

#ifndef DATASTRUCTURE_C5_H
#define DATASTRUCTURE_C5_H

#endif //DATASTRUCTURE_C5_H

#include "iostream"
#include "MyBinTree.h"


using namespace std;

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