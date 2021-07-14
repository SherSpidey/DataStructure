//
// Created by 62736 on 2021/6/15.
//

#include "C2.h"
#include "iostream"

int main() {
    using namespace std;
    int A[]{3, 1, 54, 6, 21, 4, 1, 65, 53, 7, 54, 7, 2, 81, 8, 5, 18, 8, 3, 43};
    MyVector<int> myVector = MyVector<int>(A, 20);
    myVector.sort();
    myVector.print();
    cout << myVector.search(3) << endl;
    return 0;
}