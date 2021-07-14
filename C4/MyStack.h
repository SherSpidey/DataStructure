//
// Created by 62736 on 2021/6/23.
//

#ifndef DATASTRUCTURE_MYSTACK_H
#define DATASTRUCTURE_MYSTACK_H

#endif //DATASTRUCTURE_MYSTACK_H

#include "../C2/myVector.h"


template<typename T>
class MyStack : public MyVector<T> {
public:
    void push(T const &e) {
        MyStack::insert(MyStack::size(), e);
    }

    T pop() {
        return MyStack::remove(MyStack::size() - 1);
    }

    T &top() {
        return (*this)[MyStack::size() - 1];
    }
};

struct Queen {
    int x, y;   //棋子的坐标
    Queen(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    //重载相等操作，意味冲突
    bool operator==(Queen const &q) const {
        return (x == q.x) || (y == q.y) || (x - y == q.x - q.y) || (x + y == q.x + q.y);
        //对应四种情况，行相对、列相对、正斜对、反斜对，只要一种情况就是冲突
    }

    bool operator!=(Queen const &q) const {
        return !(*this == q);
    }
};