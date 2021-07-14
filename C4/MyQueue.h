//
// Created by 62736 on 2021/7/2.
//

#ifndef DATASTRUCTURE_MYQUEUE_H
#define DATASTRUCTURE_MYQUEUE_H

#endif //DATASTRUCTURE_MYQUEUE_H

#include "../C3/MyList.h"

template<typename T>
class MyQueue : public MyList<T> {
public:
    void enqueue(T const &e) {
        MyQueue::insertAsLast(e);
    }

    T dequeue() {
        return MyQueue::remove(MyQueue::first());
    }

    T &front() {
        return MyQueue::first()->data;
    }
};