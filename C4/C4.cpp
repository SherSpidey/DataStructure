//
// Created by 62736 on 2021/6/23.
//

#include "C4.h"

int main() {
    List_visit visit;
    MyStack<int> myStack;

    myStack.push(0);
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    myStack.push(4);
    myStack.pop();
    cout << myStack.size() << endl;
    cout << myStack.top() << endl;
    cout << myStack[0] << endl;
    myStack.traverse(visit);


    int a = 16;
    MyStack<char> cvt;
    convert2(cvt, a, 16);

    cvt.traverse(visit);

    cout << "this is C4!" << endl;

    char str[]{"{()+()+([])}"};
    cout << reParen(str, sizeof(str) / sizeof(char)) << endl;
    cout << paren(str, 0, sizeof(str) / sizeof(char)) << endl;
    cout << paren_2(str, 0, sizeof(str) / sizeof(char)) << endl;

    MyStack<int> cord;
    placeQueen(8, cord);

    cord.traverse(visit);

    MyQueue<int> myQueue;
    myQueue.enqueue(0);
    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.traverse(visit);
    cout << myQueue.front() << endl;
    cout << myQueue.dequeue() << endl;
    myQueue.traverse(visit);

}