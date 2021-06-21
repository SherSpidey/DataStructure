//
// Created by 62736 on 2021/6/18.
//

#ifndef DATASTRUCTURE_C3_H
#define DATASTRUCTURE_C3_H

#endif //DATASTRUCTURE_C3_H

#include "MyList.h"
#include "iostream"
using namespace std;


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