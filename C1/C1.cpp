//
// Created by 62736 on 2021/5/13.
//
#include "iostream"
#include "C1.h"

using namespace std;

void testBubbleSort(int n=0);
void testExtra(int n=0);

//Begin test
int main(){
//    testBubbleSort();
//    testExtra();
//    testExtra(1);
//    testExtra(2);
//    testExtra(3);
//    testExtra(4);
    testExtra(5);
    return 0;
}

void testBubbleSort(int n){
    switch (n) {
        case 0:{
            int A[]={12,4,3,2,1};
            bubbleSort1A(A,sizeof(A)/sizeof(int));
            for(int i :A)
                cout<<i<<endl;
        }
            break;
    }
};

void testExtra(int n){
    int A[]={4,3,2,1};
    switch (n) {
        case 0:
            cout<<countOnes(441)<<endl;
            break;
        case 1:
            cout<<sumI(A,4)<<endl;
            break;
        case 2:
            cout<<power2BF_I(56)<<endl;
            break;
        case 3:
            long long a;
            cout<<fib(10,a)<<endl;
            break;
        case 4:
            cout<<fibI(10)<<endl;
            break;
        case 5:{
            int A[]={12,4,3,54,2,1,41};
            int x1,x2;
            max2(A,0,sizeof(A)/sizeof(int),x1,x2);
            cout<<A[x1]<<","<<A[x2]<<endl;
        }
            break;
    }
}

