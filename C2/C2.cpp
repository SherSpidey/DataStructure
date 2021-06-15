//
// Created by 62736 on 2021/6/15.
//

#include "C2.h"
#include "iostream"

int main(){
    using namespace std;
    int A[]  {0,1,2,3,4,5,6,7,8,9};
    MyVector<int> myVector = MyVector<int>(A,10);
    permute(myVector);
    cout<<myVector[1]<< endl;
    return 0;
}