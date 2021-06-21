//
// Created by 62736 on 2021/6/18.
//

#include "C3.h"

int main(){

    List_visit visit;

    MyList<int> myList = MyList<int>();
    myList.insertAsFirst(3);
    myList.insertAsLast(2);
    myList.insertAsLast(1);
    myList.insertAsFirst(4);
    myList.insert(myList.last(),5);
    myList.traverse(visit);
    myList.sort();
    myList.traverse(visit);

    MyList<int> another_list = MyList<int>(myList(1),4);
    another_list.insertAsLast(3);
    another_list.sort();
    another_list.traverse(visit);
    another_list.uniquify();
    another_list.traverse(visit);
    cout<<another_list.search(3)->data<<endl;
    return 0;
}