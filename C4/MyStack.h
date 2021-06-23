//
// Created by 62736 on 2021/6/23.
//

#ifndef DATASTRUCTURE_MYSTACK_H
#define DATASTRUCTURE_MYSTACK_H

#endif //DATASTRUCTURE_MYSTACK_H

#include "../C2/myVector.h"


template <typename T> class MyStack: public MyVector<T>{
public:
    void push(T const& e){
        MyStack::insert(MyStack::size(), e);
    }
    T pop(){
        return MyStack::remove(MyStack::size()-1);
    }
    T& top(){
        return (*this)[MyStack::size()-1];
    }
};